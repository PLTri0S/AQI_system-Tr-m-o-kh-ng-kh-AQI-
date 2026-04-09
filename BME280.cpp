#include "BME280.h"
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h> 

// Create the sensor object 
Adafruit_BME280 bme; 

void initBME() {

  if (!bme.begin(0x76)) {
    Serial.println("Kiểm tra kết nối BME!");
    return; 
  }
  Serial.print("Kết nối thành công BME");
  Serial.println();
}

// Lấy nhiệt độ
int getBMETemp() {

  return int(bme.readTemperature()); 
}

//Lấy độ ẩm
int getBMEHum() {

  return int(bme.readHumidity()); 
}