#include <Arduino.h>

void setup()
{
  Serial.begin(9600);
}

void main()
{
  Serial.println("ADC: ", + String(analog));
}
