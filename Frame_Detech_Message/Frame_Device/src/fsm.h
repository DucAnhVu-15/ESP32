#ifndef _FSM_H_
#define _FSM_H_

#include <stdint.h>
#include <message.h>
#include <convert.h>

#define FSM_STATE 5 
typedef enum
{
    FSM_STATE_START_FRAME   = 0,
    FSM_STATE_TYPE_MESSAGE  = 1,
    FSM_STATE_PORT          = 2,
    FSM_STATE_SENSOR_NAME   = 3,
    FSM_STATE_LENGTHDATA    = 4,
    FSM_STATE_CHECK_FRAME   = 5,
} fsm_state_e;

typedef enum
{
    FSM_STATE_CHANGE_VALUE_START_FRAME  = 0,
    FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE = 2,
    FSM_STATE_CHANGE_VALUE_PORT         = 3,
    FSM_STATE_CHANGE_VALUE_SENSOR_NAME  = 6,
    FSM_STATE_CHANGE_VALUE_LENGHT_DATA  = 4,
    FSM_STATE_CHANGE_VALUE_CHECK_FRAME  = 6,
} fsm_state_change_value_e;

uint8_t Fsm_Array_Recevei(uint8_t arr_in, uint8_t *arr_out);

#endif
