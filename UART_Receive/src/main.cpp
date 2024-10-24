#include "main.h"

HardwareSerial uart1(1);
const int Rx_1 = 15;
const int Tx_1 = 16;

hw_timer_t *My_timer = NULL;
bool data_available = false;
static uint8_t data_rec = 0;

void IRAM_ATTR onTimer()
{
  if (uart1.available() > 0)
  {
    data_rec = uart1.read();
    data_available = true;
  }
}

void setup()
{
  Serial.begin(115200);
  uart1.begin(115200, SERIAL_8N1, Rx_1, Tx_1);

  /* Config Timer */
  TIMER_Init();
}

void loop()
{
  if (data_available)
  {
    Receive_DataToUart1(data_rec);
    data_available = false;
  }
}

void Receive_DataToUart1(uint8_t data)
{
  uart1.print("Data received: ");
  uart1.write(data);
  uart1.print("\n");
  delay(100);
}

void TIMER_Init(void)
{
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 1000, true);
  timerAlarmEnable(My_timer);
}
