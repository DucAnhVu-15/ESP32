#ifndef _ADXL345_H_
#define _ADXL345_H_

#include <stdint.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/* Assign a unique ID to this sensor at the same time */
extern Adafruit_ADXL345_Unified accel;
extern float X_out, Y_out, Z_out;

void displaySensorDetails(void);
void displayDataRate(void);
void displayRange(void);

void set_up_ADXL345(void);
void run_ADXL345(void);

#endif
