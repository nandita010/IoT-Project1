**MATERNAL HEALTH TRACKER**
This project heps track health data for women during pregnancy like their heartrate and blood oxygen, temperature and steps. The system displays all readings on an LCD screen and also uses a web-based dashboard built with HTML, CSS, and JavaScript. The ESP32 collects sensor data in real time and updates the webpage automatically, allowing users to view their health information easily and continuously.

**🧩 Hardware Used**
- ESP32 Dev Board
- MAX30205 — measures heart rate (bpm) and blood oxygen (SpO2)
- MAX30101 — measures temperature (37- 40 deg celcius)
- GY-25 — measures steps (using g unit)

**⭐ Features**
- Reads MAX30205 data
- Reads MAX30101 data
- Reads GY-25 data
- Hosts a web server showing live sensor values

**🔌 Wiring**
- MAX30205 → SDA: 21, SCL: 23  
- MAX30101 → SDA: 21, SCL: 23  
- GY-25 → SDA: 21, SCL: 23

**▶️ How to Run**
1. Install the required libraries:     
#include <WiFi.h>
#include <Wire.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include <MAX30100_PulseOximeter.h>
#include "homepage.h"
#include <MPU6050.h>
#include <math.h>
2. Open the code in Arduino IDE.  
3. Select ESP32 board and connect to designated port.(DOIT ESP32 DEVKIT V1)  
4. Upload the code.  
5. Open the serial monitor to see the IP address.  
6. Open the IP address in a browser to view the sensor dashboard.

**📷 Output**
- Live heart rate  
- Live SpO2  
- Live temperature  
- Live step count  
