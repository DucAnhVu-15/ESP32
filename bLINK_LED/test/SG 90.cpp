#include <Arduino.h>
#include <Servo.h>

Servo sg90;

void setup() {
  sg90.attach(22);
}

void loop() {
  for (int i = 0; i <= 180; i++) {
    sg90.write(i);
    delay(10);
  }
  for (int i = 180; i >= 0; i--) {
    sg90.write(i);
    delay(10);
  }
}
