#ifndef _MPU6050_H_
#define _MPU6050_H_

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Arduino.h>

extern Adafruit_MPU6050 mpu;
extern float X_out;
extern float Y_out;
extern float Z_out;

extern uint8_t flag_read_mpu6050;

extern float data_read[300];
extern uint16_t count_data_sensor; 

void setup_mpu6050(void);
void run_mpu6050(void);

#endif