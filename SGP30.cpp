#include "SGP30.h"
#include <Wire.h>
#include "Adafruit_SGP30.h"

Adafruit_SGP30 sgp;

// Internal function for humidity math 
uint32_t getAbsoluteHumidity(float temperature, float humidity) {
    // approximation formula from Sensirion SGP30 Driver Integration chapter 3.15
    const float absoluteHumidity = 216.7f * ((humidity / 100.0f) * 6.112f * exp((17.62f * temperature) / (243.12f + temperature)) / (273.15f + temperature)); // [g/m^3]
    const uint32_t absoluteHumidityScaled = static_cast<uint32_t>(1000.0f * absoluteHumidity); // [mg/m^3]
    return absoluteHumidityScaled;
}

void initSGP() {
  if (!sgp.begin()) { 
    Serial.println("Kiểm tra kết nối SGP!"); 
    return;
  }
  Serial.print("Kết nối thành công SGP");
  Serial.println();
}

bool readSGP() {
  return sgp.IAQmeasure();
}

uint16_t get_TVOC() {
  return sgp.TVOC; 
}

uint16_t get_eCO2() {
  return sgp.eCO2; 
}

void applySGPCompensation(float temp, float hum) {
  sgp.setHumidity(getAbsoluteHumidity(temp, hum));
}