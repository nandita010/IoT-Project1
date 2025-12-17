// This code is derived from the HelloServer Example 
// in the (ESP32) WebServer library .
//
// It hosts a webpage which has one temperature reading to display.
// The webpage is always the same apart from the reading which would change.
// The getTemp() function simulates getting a temperature reading.
// homePage.h contains 2 constant string literals which is the two parts of the
// webpage that never change.
// handleRoot() builds up the webpage by adding as a C++ String:
// homePagePart1 + getTemp() +homePagePart2 
// It then serves the webpage with the command:  
// server.send(200, "text/html", message);
// Note the text is served as html.
//
// Replace the code in the homepage.h file with your own website HTML code.
// 
// This example requires only an ESP32 and download cable. No other hardware is reuired.
// A wifi SSID and password is required.
// Written by: Natasha Rohan  12/3/23

#include <WiFi.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <MAX30100_PulseOximeter.h>
#include "homepage.h"

#define MAX30205_ADDRESS 0x48

#define REPORTING_PERIOD_MS   1000

PulseOximeter pox;
uint32_t tsLastReport = 0;
uint32_t lastTempRead = 0;

const char* ssid = "eir45455838";
const char* password = "EXE2AdsFaF";

WebServer server(80);

void onBeatDetected() {
    Serial.println("♥ Beat!");
}

float readTemperature() {
  Wire.beginTransmission(MAX30205_ADDRESS);
  Wire.write(0x00);  // Temperature register
  if (Wire.endTransmission(false) != 0) {
    return NAN;  // Sensor not responding
  }

  Wire.requestFrom(MAX30205_ADDRESS, 2);
  if (Wire.available() < 2) return NAN;

  uint8_t msb = Wire.read();
  uint8_t lsb = Wire.read();

  // Combine bytes (MSB + LSB) into 16-bit value
  uint16_t raw = (msb << 8) | lsb;

  // Convert raw to temperature (per MAX30205 datasheet)
  float temp = raw * 0.00390625; // 1/256

  return temp;
}

 
void handleRoot() {
  
 String page = homePagePart1;
page+= String(pox.getHeartRate());
page+= homePagePart2;
page+= String(pox.getSpO2());
page+= homePagePart3;
page+= String(readTemperature());
page+= homePagePart4;


  server.send(200, "text/html", page);
}
void handleNotFound() {
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++) {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void setup() {

Serial.begin(115200);
delay(1000);
  Wire.begin(21, 22);
Serial.print("Initializing pulse oximeter..");

if (!pox.begin()) {
      Serial.println("FAILED");
      for(;;);
  } else {
      Serial.println("SUCCESS");
  }

  // Configure sensor to use 7.6mA for LED drive
  pox.setIRLedCurrent(MAX30100_LED_CURR_50MA);

    // Register a callback routine
  pox.setOnBeatDetectedCallback(onBeatDetected);

    
WiFi.mode(WIFI_STA);
WiFi.begin(ssid, password);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", handleRoot);
  server.on("/inline", []() {
    server.send(200, "text/plain", "this works as well");
  });
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");
  
  //temp sensor

  Serial.println("MAX30205 Temperature Sensor Test");
}
  // Initialize sensor
  
void loop() {

  server.handleClient();
  pox.update();

    // Grab the updated heart rate and SpO2 levels
    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate:");
        Serial.print(pox.getHeartRate());
        Serial.print("bpm / SpO2:");
        Serial.print(pox.getSpO2());
        Serial.println("%");

        tsLastReport = millis();
    }

  if (millis() - lastTempRead > 1000) {
    float temperature = readTemperature();
    if (!isnan(temperature)) {
      Serial.print("Temperature: ");
      Serial.println(temperature);
    }
    lastTempRead = millis();
  }
}




