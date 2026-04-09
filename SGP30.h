#ifndef SGP30_H
#define SGP30_H

#include <Arduino.h>

void initSGP();

bool readSGP();

// Getters for the measured values
uint16_t get_TVOC();
uint16_t get_eCO2();

// Optional: Apply humidity compensation using BME280 data
void applySGPCompensation(float temp, float hum);

#endif