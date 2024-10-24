#include <Arduino.h>

int ledPin = 17;    // define the LED pin
int brightness = 0; // initialize the LED brightness

void setup() {
  pinMode(ledPin, OUTPUT); // set the LED pin as output
}

void loop() {
  // increase brightness from 0 to 255
  for (int i = 0; i <= 255; i++) {
    analogWrite(ledPin, i); // set the LED brightness
    delay(10);             // wait for 10ms
  }
  
  // decrease brightness from 255 to 0
  for (int i = 255; i >= 0; i--) {
    analogWrite(ledPin, i); // set the LED brightness
    delay(10);             // wait for 10ms
  }
}
