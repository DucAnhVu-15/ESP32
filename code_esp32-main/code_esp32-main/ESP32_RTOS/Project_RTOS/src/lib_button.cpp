#include "lib_button.h"

#define BUTTON_PIN 2

uint8_t button_flag = 0;
uint8_t reading_button = 0;
uint8_t lastButtonState = 0;

void BUTTON_Init(void)
{
  pinMode(BUTTON_PIN, INPUT);
}

void BUTTON_Read()
{
  reading_button = digitalRead(BUTTON_PIN);
  // Nếu trạng thái của nút thay đổi
  if (reading_button != lastButtonState) 
  {
    // Chờ một khoảng thời gian ngắn để chống nhiễu
    // delay(50);
    // Đọc lại trạng thái của nút
    reading_button = digitalRead(BUTTON_PIN);
    // Nếu trạng thái của nút thay đổi một lần nữa
    if (reading_button != lastButtonState) 
    {
      // Cập nhật trạng thái của nút
      lastButtonState = reading_button;

      if (lastButtonState == HIGH) // Nếu nút được nhấn
      {  
        button_flag = 1;
      }
    }
  }
  lastButtonState = reading_button;  // Lưu trạng thái của nút
}

