#include <Arduino.h>
#include <Servo.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <SPI.h>

Servo sg90_1;
Servo sg90_2;
Servo sg90_3;

#define VrxPin 26
#define VryPin 27

#define Button_Servo 25

#define Bientro 34

uint32_t x_Direction = 0;
uint32_t y_Direction = 0;

uint32_t x_Servo = 0;
uint32_t y_Servo = 0;

uint32_t Button_Servo_old = 1;
uint32_t Button_Servo_new = 1;
uint32_t Button_Servo_Cnt = 0;

uint32_t Kabuto_Servo = 0;

uint32_t Control_bientro = 0;

uint32_t Servopos_1 = 0;

void Control_sevor();

void setup()
{
    Serial.begin(9600);

    sg90_1.attach(23);
    sg90_2.attach(22);
    sg90_3.attach(19);

    sg90_1.write(90);
    sg90_2.write(90);
    // pinMode(Bientro, INPUT_PULLUP);

    pinMode(Button_Servo, INPUT);
}

void loop()
{
    Control_sevor();
}

void Control_sevor()
{

    // Control_bientro = map(analogRead(Bientro), 0, 1023, 0, 180);

    x_Direction = analogRead(VrxPin);
    y_Direction = analogRead(VryPin);
    
    x_Servo = map(x_Direction, 0, 4095, 0, 90);
    y_Servo = map(y_Direction, 0, 4095, 0, 90);

    Serial.print("X-axis: ");
    Serial.println(x_Servo);
    delay(200);

    Serial.print("Y-axis: ");
    Serial.println(y_Servo);
    delay(200);

    sg90_1.write(x_Servo);
    sg90_2.write(y_Servo);

    Button_Servo_old = Button_Servo_new;
    Button_Servo_new = digitalRead(Button_Servo);

    if (Button_Servo_old == 1 && Button_Servo_new == 0)
    {
        Button_Servo_Cnt++;
    }
    Serial.println("Button Servo cnt: "+ String(Button_Servo_Cnt));
    delay(100);

    if (Button_Servo_Cnt % 2 == 1)
    {
        sg90_3.write(30);
    }
    else
    {
        sg90_3.write(0);
    }
}
