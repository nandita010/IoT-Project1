#include <Wire.h>

// MAX30205 default I2C address
#define MAX30205_ADDRESS 0x48

void setup() {
  Serial.begin(115200);
  Wire.begin();   // SDA = GPIO 21, SCL = GPIO 22 on ESP32

  Serial.println("MAX30205 Temperature Sensor Test");
}

void loop() {
  float temperature = readTemperature();

  if (!isnan(temperature)) {
    Serial.print("Temperature: ");
    Serial.print(temperature, 2);
    Serial.println(" °C");
  } else {
    Serial.println("Sensor read error!");
  }

  delay(1000); // Read once per second
}

// -----------------------
// Read temperature function
// -----------------------
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
