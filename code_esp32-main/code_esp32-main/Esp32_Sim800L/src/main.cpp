#include <Arduino.h>
/*
	ESP32   -  SIM800l
	TX2(17) -   RX
	RX2(16) -   TX
*/


void Call_SMS();
void Send_SMS();
void Update_Serial();
void Test_sim800_module();

void setup() 
{
  Serial.begin(115200);
  Serial2.begin(115200);

  Test_sim800_module();
  //Send_SMS();
  //Call_SMS();
}

void loop() 
{
  Update_Serial();
}


void Update_Serial()
{
  delay(500);
  
  while (Serial2.available())
  {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }
}

void Send_SMS()
{
  Serial2.print("AT+CMGF=1\r\n"); // Cau hinh tin nhan dang text
  Update_Serial();
  Serial2.print("AT+CMGS=\"+84969114238\"\r\n");
  Update_Serial();
  Serial2.print("Hellu mn, minh la Chao day"); 
  Update_Serial();
  Serial2.write(26); // = Ctrl+Z , Duoc su dung de ket thuc và gui tin nhan di
}

void Call_SMS()
{
  Serial2.print("ATD0969114238;\r\n");
  Update_Serial();
}

void Test_sim800_module()
{
  Serial2.print("AT\r\n"); // Kiem tra module con hoat dong khong
  Update_Serial();
  Serial2.print("AT+CSQ\r\n"); // Kiem tra chat luong song
  Update_Serial();
  Serial2.print("AT+CPIN?\r\n"); // Kiem tra Simcard
  Update_Serial();
  Serial2.print("AT+COPS?\r\n"); // Kiem tra nha mang
  Update_Serial();
  Serial2.print("AT+IPR= 115200\r\n"); // Cau hinh Baud Rate
  Update_Serial();
  Serial2.print("AT+CMGF=1\r\n"); // Cau hinh tin nhan dang text
  Update_Serial();
  Serial2.print("AT+CNMI=2,2,0,0\r\n"); // Hien thi noi dung tin nhan
  Update_Serial();
  Serial2.print("AT+CUSD=1,\"*101#\"\r\n"); // Kiem tra so du tai khoan
  Update_Serial();
  // Serial2.print("AT&W\r\n"); // Luu cau hinh
  // Update_Serial();
}

// Serial2.print("ATA\r\n"); // Chap nhan cuoc goi den
// Serial2.print("ATH\r\n"); // Huy cuoc goi den
