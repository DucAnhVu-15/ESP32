#ifndef _TIME_USART_H_
#define _TIME_USART_H_

#include <Arduino.h>

extern hw_timer_t *timer;
extern volatile uint8_t flag_status;

void IRAM_ATTR onTimer();
void TimeUART_setup(void);

#endif