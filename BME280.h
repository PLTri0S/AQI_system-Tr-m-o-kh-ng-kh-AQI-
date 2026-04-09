#ifndef BME280_H
#define BME280_H

#include <Arduino.h>

// Initialize the BME280 sensor via I2C
void initBME();

// Read and return the temperature in Celsius
int getBMETemp();

// Read and return the humidity percentage
int getBMEHum();

#endif