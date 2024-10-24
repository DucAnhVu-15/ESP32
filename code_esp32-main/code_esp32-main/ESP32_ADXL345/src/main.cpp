#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_ADXL345_U.h>

/*
  SDA - 21
  SCL - 22
*/

Adafruit_ADXL345_Unified accel = Adafruit_ADXL345_Unified(12345); // The parameter is the sensor's I2C address (default is 0x53)

void setup(void) {
  Serial.begin(115200);
  Serial.println("Adafruit ADXL345 test!");

  if(!accel.begin()) {
    Serial.println("Could not find a valid ADXL345 sensor, check wiring!");
    while(1);
  }
}

void loop(void) {
  sensors_event_t event;
  accel.getEvent(&event);

  Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" m/s^2\t");
  Serial.println();
  Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" m/s^2\t");
  Serial.println();
  Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print(" m/s^2\t");
  Serial.println();

  delay(500);
}
