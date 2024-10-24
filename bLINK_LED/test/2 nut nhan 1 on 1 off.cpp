#include <Arduino.h>
int count = 0,i; 

int led[] = {13, 25, 26};
unsigned int but_on = 1;
unsigned int but_off = 1;

void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 3; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], LOW);
  }
  pinMode( 18, INPUT);
  pinMode( 27, INPUT);
}

void loop() {
  // but_on = digitalRead(27);
  // but_off = digitalRead(18);
  // if ( but_on == 0 ){
  //   count++;
  //   delay(1);
  // }
  // if ( count % 2 == 1 ){
  //   for ( i = 0 ; i < 3; i++){
  //       digitalWrite( led[i], 0);
  //   }
  // }
  // if ( but_off == 0 ){
  //   count=0;
  //   for ( i = 0; i < 3 ; i++){
  //       digitalWrite(led[i], 1);
  //       delay(1);
  //   }  
  // }
}
