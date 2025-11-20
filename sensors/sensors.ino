#include <Wire.h>                    //needed for both the accelerometer and heart sensor
#include "MAX30100_PulseOximeter.h" // Importing libraries for the heart sensor
#include <Adafruit_MPU6050.h>       //remember to install libraries
#include <Adafruit_Sensor.h>        //the other library

#define REPORTING_PERIOD_MS 1000

Adafruit_MPU6050 mpu; //handles sensor

void setup(void) {
  // put your setup code here, to run once:
Serial.begin(115200); 

}

void loop() {
  // put your main code here, to run repeatedly:

}
