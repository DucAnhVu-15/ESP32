// Libraries
#include <Arduino.h>


const double VCC            = 3.3;             // NodeMCU on board 3.3v vcc
const double R2             = 10000;            // 10k ohm series resistor
const double ADC_resolution = 4095; // 10-bit adc
const double A              = 0.0010757;   // thermistor equation parameters
const double B              = 0.000234125;
const double C              = 0.0000000876741; 

void setup() {
  Serial.begin(112500);  /* Define baud rate for serial communication */
}

void loop() {
  double Vout, Rth, temperature, adc_value; 

  adc_value = analogRead(34);
  Vout = (adc_value * VCC) / ADC_resolution;
  Rth = (VCC * R2 / Vout) - R2;
  temperature = (1 / (A + (B * log(Rth)) + (C * pow((log(Rth)),3))));   // Temperature in kelvin

  temperature = temperature - 273.15;  // Temperature in degree celsius
  Serial.print("Temperature = ");
  Serial.print(temperature);
  Serial.println(" degree celsius");
  delay(500);
}