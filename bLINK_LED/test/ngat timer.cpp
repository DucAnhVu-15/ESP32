#include <Arduino.h>
int led = 26;
hw_timer_t * timer = NULL;

unsigned int state = 0;

void IRAM_ATTR onTimer(){
  state = !state;
}

void setup() {
  Serial.begin(9600);

  pinMode(led, OUTPUT);

  timer = timerBegin(0, 8000, true);

  timerAttachInterrupt(timer, &onTimer, true);

  timerAlarmWrite(timer, 1000, true);

  timerAlarmEnable(timer);

  Serial.println("start timer");

}

void loop() {
  if ( state ){
    digitalWrite ( led, 1);
  }
  else digitalWrite( led, 0);
}