#include <Arduino.h>
#include <Servo.h>

Servo sg90;
int pos;
int cnt = 0;
int bientro = 34;
void setup() {
    Serial.begin(9600);
    sg90.attach(22);
}

void loop() {
    cnt = analogRead(bientro);
    pos = map(cnt,0,1023,0,180);
    sg90.write(pos);
    Serial.println(pos);
    delay(500);
}
