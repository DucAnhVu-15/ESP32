#include <Arduino.h>

const int soilMoisturePin = 4;  // Sử dụng cổng analog 34 trên ESP32

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  int value = analogRead(soilMoisturePin);    
  int percent = map(value, 0, 4095, 100, 0);
  Serial.print(percent);
  Serial.println('%');

  delay(1000);  // Đọc giá trị mỗi giây
}
