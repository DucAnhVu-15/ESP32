#include <Arduino.h>
int count = 0,i;
int count1 = 0;
int led[] = {13, 25, 26};
unsigned int but_on = 1;
unsigned int but_off = 1;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }
}

void loop() {
  but_on = digitalRead(27);
  if ( but_on == 0 ){
    count++;
  }
  if ( count % 2 == 1 ){
    count = 1;
    for ( i = 0 ; i < 3; i++){
        digitalWrite( led[i], 0);
        delay(1500);
        digitalWrite( led[i], 1);
        delay(1500);
    }
  }
  if ( count % 2 == 0 ){
    count = 0;
    for ( i = 0; i < 3 ; i++){
        digitalWrite(led[i], 1);
        delay(100);
    }  
  }
}