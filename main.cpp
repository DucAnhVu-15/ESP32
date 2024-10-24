#include "main.h"

HardwareSerial uart1(1);
const int Rx_1 = 15;
const int Tx_1 = 16;

hw_timer_t *My_timer = NULL;
bool data_available = false;
static uint8_t data_rec = 0;

DynamicJsonDocument data(1024);
char Buffer[1000];
int Length_Buffer;
String ESP32_Data;

void IRAM_ATTR onTimer()
{
  if (uart1.available() > 0)
  {
    data_rec = uart1.read();
    data_available = true;
  }
}
void Data_to_Json(String status, String ix);

void setup()
{
  Serial.begin(115200);
  uart1.begin(115200, SERIAL_8N1, Rx_1, Tx_1);

  /* Config Timer */
  TIMER_Init();
}

void loop()
{
  Data_to_Json("idle", "2");
  delay(1000);
}

void Send_DataToUart1(uint8_t data)
{
  uart1.write(data);
}

void TIMER_Init(void)
{
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 1000, true);
  timerAlarmEnable(My_timer);
}

void Data_to_Json(String status, String ix)
{
  ESP32_Data = "{\"status\":\"" + String(status) + "\",\"ix\":\"" + String(ix) + "\"}\n";
  Length_Buffer = ESP32_Data.length() + 1;
  ESP32_Data.toCharArray(Buffer, Length_Buffer);
  uart1.write(Buffer);
}

