#include <Arduino.h>


void SIM800L_Setup();
void SIM800L_UpdateSerial();


void setup() 
{
  Serial.begin(115200);
  Serial2.begin(115200);
  SIM800L_Setup();
}

void loop() 
{
  if (Serial2.available())
  {
    String message = Serial2.readStringUntil('\n');
    // Xử lý tin nhắn ở đây
    Serial.println("Received message: " + message);
  }
}


void SIM800L_Setup()
{
  Serial2.print("AT\r\n"); // Kiem tra module con hoat dong khong
  SIM800L_UpdateSerial();
  Serial2.print("AT+CSQ\r\n"); // Kiem tra chat luong song
  SIM800L_UpdateSerial();
  Serial2.print("AT+CLIP=1\r\n"); // Bật chức năng báo cuộc gọi đến
  SIM800L_UpdateSerial();
  Serial2.print("AT+IPR=115200\r\n"); // Cau hinh Baud Rate
  SIM800L_UpdateSerial();
  Serial2.print("AT+CMGF=1\r\n"); // Cau hinh tin nhan dang text
  SIM800L_UpdateSerial();
  Serial2.print("AT+CNMI=2,2,0,0,0\r\n"); // Chuyển đổi chế độ nhận tin nhắn
  SIM800L_UpdateSerial();
  Serial2.print("AT+CNMI=2,2,0,0\r\n"); // Hien thi noi dung tin nhan
  SIM800L_UpdateSerial();
  Serial2.print("AT+CUSD=1,\"*101#\"\r\n"); // Kiem tra so du tai khoan
  SIM800L_UpdateSerial();
  // Serial2.print("AT&W\r\n"); // Luu cau hinh
  // SIM800L_UpdateSerial();
}

void SIM800L_UpdateSerial()
{
  delay(300);
  // while (Serial.available())
  // {
  //   Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  // }
  while (Serial2.available())
  {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }
}