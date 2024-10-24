#ifndef LIB_BUTTON_h
#define LIB_BUTTON_h

#include "lib_sys.h"

#define BUTTON_PIN 22

extern uint8_t button_flag;

void BUTTON_Init(void);
void BUTTON_Read(void);

#endif

