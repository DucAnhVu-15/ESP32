#include <Servo.h>
#include <Wire.h>
#include <Arduino.h>
#include <Adafruit_Sensor.h>

#define swPin 14
#define VrxPin 26
#define VryPin 27

uint32_t x_Direction = 0;
uint32_t y_Direction = 0;
uint32_t switchState = 1;

uint8_t Address = 0;

void setup()
{
    Serial.begin(9600);

    pinMode(swPin, INPUT);
    digitalWrite(swPin, HIGH);
}

void loop()
{
    x_Direction = analogRead(VrxPin);
    y_Direction = analogRead(VryPin);

    switchState = digitalRead(swPin);

    Serial.print("Switch: ");
    Serial.println(switchState);

    Serial.print("X-axis: ");
    Serial.println(y_Direction);

    if (!switchState)
    {
        Serial.println("Go!");
    }

    if (x_Direction < 480)
    {
        Serial.println("Left");
        Address = 1;
    }
    else if (x_Direction > 520)
    {
        Serial.println("Right");
        Address = 2;
    }
    else if (y_Direction < 480)
    {
        Serial.println("Down");
        Address = 3;
    }
    else if (y_Direction > 520)
    {
        Serial.println("Up");
        Address = 4;
    }
}
