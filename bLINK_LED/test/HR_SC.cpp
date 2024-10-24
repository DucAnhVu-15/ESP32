#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

const int trigPin = 5;
const int echoPin = 18;

// define sound speed in cm/uS
#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701

long duration;
float distanceCm;

void setup()
{
    Serial.begin(9600);     // Starts the serial communication
    pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
    pinMode(echoPin, INPUT);  // Sets the echoPin as an Input
}

void loop()
{
    
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);


    duration = pulseIn(echoPin, HIGH);


    distanceCm = duration * SOUND_SPEED / 2;

    Serial.print("Distance (cm): ");
    Serial.println(distanceCm);

    delay(1000);
}