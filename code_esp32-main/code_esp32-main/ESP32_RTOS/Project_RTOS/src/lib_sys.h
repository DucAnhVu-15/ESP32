#ifndef _LIB_SYS_H_
#define _LIB_SYS_H_

#include <Arduino.h>
#include "lib_led.h"
#include "lib_button.h"

void SYS_Setup(void);
void SYS_Run(void);
void TASK_LedRed(void *parameters);
void TASK_LedGreen(void *parameters);
void TASK_Button(void *parameters);

#endif
