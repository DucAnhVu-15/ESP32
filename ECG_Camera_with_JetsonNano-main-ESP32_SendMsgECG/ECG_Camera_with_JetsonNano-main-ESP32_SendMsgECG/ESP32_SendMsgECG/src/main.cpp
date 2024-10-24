#include "main.h"

ecg_FrameMsg_t ecg_FrameMsg;

hw_timer_t *My_timer = NULL;
static uint8_t count_time_4ms = 0;
static uint8_t flag_time_4ms = 0;

static uint8_t data_index = 0;
static uint8_t arr_frame[LENGTH_MSG_DATA] = {0};

void IRAM_ATTR onTimer()
{
  /* Count timer */
  count_time_4ms++;
  if (count_time_4ms >= 4)
  {
    flag_time_4ms = 1;
    count_time_4ms = 0;
  }
}

void setup() 
{
  /* Init Serial */
  Serial.begin(115200);
  Serial2.begin(115200);
  /* Config Timer */
  TIMER_Init();
  /* Update Frame Message */
  Update_FrameMsg();
}

void loop() 
{
  /* Send Frame every 4ms */
  if (flag_time_4ms == 1) 
  {
    flag_time_4ms = 0;

    if (data_index < LENGTH_MSG_DATA) 
    {
      /* Send Frame */
      // ECG_Send_DataToUart0(arr_frame[data_index]);
      ECG_Send_DataToUart2(arr_frame[data_index]);
      data_index++;
    } 
    else 
    {
      /* Reset Data Index */
      data_index = 0;
      /* Update Frame Message */
      Update_FrameMsg();
    }
  }
}

void Update_FrameMsg(void)
{
  /* Update Frame Message */
  ecg_FrameMsg.StartFrame = START_BYTE;
  ecg_FrameMsg.LengthData = 0x0A;
  ecg_FrameMsg.Data[0] = 0x01;
  for (uint8_t i = 1; i < ecg_FrameMsg.LengthData - 2; i++)
  {
    ecg_FrameMsg.Data[i] = random(0, 255);
  }

  /* Create Frame */
  Message_Create_Frame(ecg_FrameMsg, arr_frame);
}

void ECG_Send_DataToUart0(uint8_t data)
{
  Serial.println(data, HEX); // For Python Receive Frame Msg
  // Serial.write(data); // For C++ Receive Frame Msg
}

void ECG_Send_DataToUart2(uint8_t data)
{
  // Serial2.println(data, HEX); // For Python Receive Frame Msg
  Serial2.write(data); // For C++ Receive Frame Msg
}

void TIMER_Init(void)
{
  My_timer = timerBegin(0, 80, true); // 80 prescaler = 1 tick = 1µs
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 1000, true); // 1ms interval
  timerAlarmEnable(My_timer);
}
