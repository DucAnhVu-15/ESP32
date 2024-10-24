#ifndef _MAIN_H_
#define _MAIN_H_

#include <Arduino.h>

#include "lib_convert.h"
#include "lib_message.h"

#define LENGTH_MSG_DATA 12

void Update_FrameMsg(void);
void ECG_Send_DataToUart0(uint8_t data);
void ECG_Send_DataToUart2(uint8_t data);
void TIMER_Init(void);

#endif // _MAIN_H_
