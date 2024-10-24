#include <Arduino.h>

#define BUTTON_PIN    2  // Pin của nút
#define LED_PIN_RED   18   // Pin của đèn
#define LED_PIN_GREEN 19

int count_press = 0;
int reading_button = 0;
int lastButtonState = 0;  // Trạng thái trước đó của nút (0 hoặc 1)

void Handle_push_button();
void Read_Button();
void Led_Red();
void Led_Green();

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_PIN_GREEN, OUTPUT);
  pinMode(LED_PIN_RED, OUTPUT);
}

void loop() 
{
  Led_Red();
  delay(1000);
  Led_Green();
  delay(1000);
}

void Led_Red()
{
  digitalWrite(LED_PIN_RED, 0);
  digitalWrite(LED_PIN_GREEN, 1);
}

void Led_Green()
{
  digitalWrite(LED_PIN_RED, 1);
  digitalWrite(LED_PIN_GREEN, 0);
}

// void Handle_push_button()
// {
//   if(count_press%2 != 0)
//   {
//     digitalWrite(LED_PIN, 1);
//   }
//   else
//   {
//     digitalWrite(LED_PIN, 0);
//   }
//   if(count_press == 100)
//   {
//     count_press = 0;
//   }
// }

// void Read_Button()
// {
//   reading_button = digitalRead(BUTTON_PIN);
//   // Nếu trạng thái của nút thay đổi
//   if (reading_button != lastButtonState) 
//   {
//     // Chờ một khoảng thời gian ngắn để chống nhiễu
//     delay(50);
//     // Đọc lại trạng thái của nút
//     reading_button = digitalRead(BUTTON_PIN);
//     // Nếu trạng thái của nút thay đổi một lần nữa
//     if (reading_button != lastButtonState) 
//     {
//       // Cập nhật trạng thái của nút
//       lastButtonState = reading_button;

//       if (lastButtonState == HIGH) // Nếu nút được nhấn
//       {  
//         count_press++;
//       }
//     }
//   }
//   lastButtonState = reading_button;  // Lưu trạng thái của nút
// }
