#include <time_uart.h>

hw_timer_t *timer = NULL;
volatile uint8_t flag_status = 0;

void IRAM_ATTR onTimer()
{
  flag_status = 1;
}

void TimeUART_setup(void)
{
    timer = timerBegin(0, 8000, true);
    timerAttachInterrupt(timer, &onTimer, true);
    timerAlarmWrite(timer, 200, true); // Đặt ngắt mỗi 20ms
    timerAlarmEnable(timer);
}