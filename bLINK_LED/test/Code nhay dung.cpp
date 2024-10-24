#include <Arduino.h>

int led[] = {13, 25, 26, 33, 32};
unsigned int count = 0, i;
unsigned int n = 5;
void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(led[i], OUTPUT);
    digitalWrite(led[i], HIGH);
  }
}

void loop() {
  while ( n != 0 ){
    for ( i = 0; i < n; i++){
      digitalWrite(led[i], LOW);
      delay(120);
      digitalWrite(led[i], HIGH);
    }
    digitalWrite(led[n-1], LOW);
    n--;
  }

  if ( n == 0 ){
    for ( i = 0; i < 5; i++ ){
      digitalWrite(led[i], HIGH);
    }
    delay(400);
    n = 5;
  }
}
