#include <Arduino.h>


/*
	Sim SMS oki
	 ESP32  -  SIM800A
	TX2(17) -   RX
	RX2(16) -   TX
*/
void send_SMS();
void updateSerial();
void test_sim800_module();

void setup() {
  Serial.begin(9600);
  Serial2.begin(9600);

  delay(3000);
  test_sim800_module();
  send_SMS();
}
void loop() {
  updateSerial();
}
void test_sim800_module()
{
  Serial2.print("AT\r\n");
  updateSerial();
//   Serial.println();
  Serial2.print("AT+CSQ\r\n");
  updateSerial();
  Serial2.print("AT+IPR= 9600\r\n");
  updateSerial();
  Serial2.print("AT+CMGF=1\r\n");
  updateSerial();
  Serial2.print("AT+CNMI=2,1,0,0,0\r\n");
  updateSerial();
}
void updateSerial()
{
  delay(500);
  while (Serial.available())
  {
    Serial2.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while (Serial2.available())
  {
    Serial.write(Serial2.read());//Forward what Software Serial received to Serial Port
  }
}
void send_SMS()
{
  Serial2.print("AT+CMGF=1\r\n"); // Configuring TEXT mode
  updateSerial();
  Serial2.print("AT+CMGS=\"+84969656498\"\r\n");//change ZZ with country code and xxxxxxxxxxx with phone number to sms
  updateSerial();
  Serial2.print("Thuy Son, Thai Thuy, Thai Binh"); //text content
  updateSerial();
  Serial2.write(26);
}