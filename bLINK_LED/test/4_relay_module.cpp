
#include <Arduino.h>

#define relayPin_1 25
// #define relayPin_2 14
// #define relayPin_3 27

void setup() {
  Serial.begin(9600);
}

void loop() {
  digitalWrite(relayPin_1, HIGH);
  delay(1000);
  digitalWrite(relayPin_1, LOW);
  delay(1000);
  // digitalWrite(relayPin_2, HIGH);
  // delay(1000);
  // digitalWrite(relayPin_2, LOW);
  // delay(1000);
  // digitalWrite(relayPin_3, HIGH);
  // delay(1000);
  // digitalWrite(relayPin_3, LOW);
  // delay(1000);
}
