#include <Arduino.h>

int led[] = {13, 25, 26, 33, 32};
unsigned int but_on = 1;
int count = 0;

void Effect1(int n);
void Effect2(int n);
void Effect3(int n);
void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }
  pinMode(18,INPUT);
}

void loop() {
 // Effect1(1);
  // Effect2(3);
 // Effect3(5);
  but_on = digitalRead(18);
  if ( but_on == 0){
    count++;
    delay(1);
  }
  if ( count % 2 == 1 ){
    for ( int i = 0 ; i < 5; i++){
      digitalWrite( led[i], LOW);
      delay( 100 );
      digitalWrite(led[i], HIGH);
//      delay( 100 );
    }
  }
  else {
    for ( int i = 0 ; i <5; i++){
      digitalWrite(led[i], HIGH);
      delay( 100 );
    }
  }
}

 
void Effect1(int n){
  for(int i = 0; i < n; i++){
    for(int i = 0 ; i < 5; i++){
      digitalWrite( led[i], LOW);
      delay( 100 );
    }
    for(int i = 0 ; i <5; i++){
      digitalWrite(led[i], HIGH);
      delay( 100 );
    }
  }
}

void Effect2(int n){
  
  for ( int i = 0 ; i < 5; i++){
      digitalWrite( led[i], LOW);
      delay( 100 );
    }
    delay (100);
    for ( int i = 4 ; i >= 0; i--){
      digitalWrite(led[i], HIGH);
      delay( 100 );
    }
    delay(100);
}
void Effect3(int n){
  for ( int i = 0; i <= 5; i++){
    digitalWrite( led[i],0);
    delay( 100 );
    digitalWrite(led[i-1],1);
    delay(1000);
  }
}