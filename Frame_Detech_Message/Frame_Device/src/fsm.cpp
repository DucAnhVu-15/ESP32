#include <fsm.h>

uint8_t fsm_count_arr = 0;
uint8_t fsm_length_data;

fsm_state_e fsm_state = FSM_STATE_START_FRAME;

uint8_t Fsm_Array_Recevei(uint8_t arr_in, uint8_t *arr_out)
{
    uint8_t data = arr_in;
    switch (fsm_state)
    {
    case FSM_STATE_START_FRAME:
        arr_out[fsm_count_arr] = data;
        fsm_count_arr++;
        if (fsm_count_arr == FSM_STATE_CHANGE_VALUE_START_FRAME)
        {
            fsm_state = FSM_STATE_TYPE_MESSAGE;
        }
        break;
    case FSM_STATE_TYPE_MESSAGE:
        arr_out[fsm_count_arr] = data;
        fsm_count_arr++;
        if (fsm_count_arr == FSM_STATE_CHANGE_VALUE_TYPE_MESSAGE)
        {
            fsm_state = FSM_STATE_PORT;
        }
        break;
    case FSM_STATE_PORT:
        arr_out[fsm_count_arr] = data;
        fsm_count_arr++;
        if (fsm_count_arr == FSM_STATE_CHANGE_VALUE_PORT)
        {
            fsm_state = FSM_STATE_SENSOR_NAME;
        }
        break;
    case FSM_STATE_SENSOR_NAME:
        arr_out[fsm_count_arr] = data;
        fsm_count_arr++;
        if (fsm_count_arr == FSM_STATE_CHANGE_VALUE_SENSOR_NAME)
        {
            fsm_state = FSM_STATE_LENGTHDATA;
        }
        break;
    case FSM_STATE_LENGTHDATA:
        arr_out[fsm_count_arr] = data;
        fsm_count_arr++;
        if (fsm_count_arr == FSM_STATE_CHANGE_VALUE_LENGHT_DATA)
        {
            fsm_state = FSM_STATE_CHECK_FRAME;
        }
        break;
    case FSM_STATE_CHECK_FRAME:
        arr_out[fsm_count_arr] = data;
        fsm_count_arr++;
        if (fsm_count_arr == FSM_STATE_CHANGE_VALUE_PORT)
        {
            fsm_count_arr = 0;
            fsm_state = FSM_STATE_START_FRAME;
            return 1;
        }
        break;
    } 
    return 0;
}