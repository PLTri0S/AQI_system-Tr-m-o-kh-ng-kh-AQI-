#ifndef MICS_H
#define MICS_H

// Initialize the sensor and handle warm-up
void initMICS();

// Fetch specific gas data (defaults to CO)
int get_CO();

#endif