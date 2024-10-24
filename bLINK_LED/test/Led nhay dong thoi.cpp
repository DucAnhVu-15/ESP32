#include <Arduino.h>

int led[] = {13, 25, 26};
int count = 0;
unsigned int but = 1;
void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(led[i], OUTPUT);
  }

}

void loop() {
  count++;
  delay(1);
  if (count % 250 == 0 ){
    digitalWrite(led[0], LOW);
  }

  if ( count % 500 == 0){
    digitalWrite(led[1], LOW);
    digitalWrite(led[0], HIGH);
  }

  if ( count % 1000 == 0){
    digitalWrite(led[2], LOW);
    digitalWrite(led[1], HIGH);
  }
  if(count % 2000 ==0){
    digitalWrite(led[2], HIGH);
    count = 0;
  }
}

// #include <Arduino.h>
// int count = 0,i, cnt=0; 

// int led[] = {13, 25, 26};
// unsigned int but_on = 1;
// unsigned int but_off = 1;

// void setup() {
//   Serial.begin(9600);
//   for (int i = 0; i < 3; i++) {
//     pinMode(led[i], OUTPUT);
//     digitalWrite(led[i], HIGH);
//   }
//   pinMode( 18, INPUT);
//   pinMode( 27, INPUT);
// }

// void loop() {
//   but_on = digitalRead(27);
//   cnt++;
//   delay(1);
//   if ( but_on == 0 ){
//     count++;
//     delay(1);
//   }
//   if ( count % 2 == 1 ){
//     digitalWrite( led[0], 0);
//   }
//   else {
//     digitalWrite( led[0], 1);
//   }

//   if ( cnt % 300 == 0 ){
//     digitalWrite(led[1],0);
//   }

//   if ( cnt % 600 == 0){
//     digitalWrite( led[2], 0);
//     digitalWrite( led[1], 1);
//   }

//   if ( cnt % 1200 == 0){
//     digitalWrite(led[2], 1);
//     cnt = 0;
//   }
// }

