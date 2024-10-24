#include <Arduino.h>
int count = 0;
int led[] = {13, 25, 26, 33, 32};

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 5; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }
  pinMode(4, INPUT);
}

void loop() {
  count++;
  int sensor = digitalRead(4);
  if ( sensor == LOW ){
    Serial.println(sensor);
    for ( int i = 0; i<5; i++){
      digitalWrite(led[i], 0);
    }
  }
  else {
    for ( int i = 0; i<5; i++){
      digitalWrite(led[i], 1);
    }
  }
  delay(200);
}
