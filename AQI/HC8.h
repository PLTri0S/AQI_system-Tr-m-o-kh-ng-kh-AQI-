#ifndef HC8_H
#define HC8_H

#include <Arduino.h>


void initHC8();

// Fetch specific gas data (defaults to CO)
int get_CO2();

#endif