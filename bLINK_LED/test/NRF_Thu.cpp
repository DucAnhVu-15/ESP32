#include <Arduino.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

RF24 radio(16, 5);

const byte direccion[7] = "150104";

Servo myservo;

int angulo;

void setup()
{

  Serial.begin(9600);

  // myservo.attach(3);

  radio.begin();

  radio.openReadingPipe(0, direccion);
  radio.setPALevel(RF24_PA_MIN);

  radio.startListening();
}

void loop()
{
  if (radio.available())
  {
    radio.read(angulo, sizeof(angulo));
    Serial.println(angulo);
    // myservo.write(angulo);
    
  }
}