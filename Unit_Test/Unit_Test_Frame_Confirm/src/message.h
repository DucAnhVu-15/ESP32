#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "stdint.h"

#define START_BYTE 0XAA55             // 2 byte StartFrame
#define LENGTH_DEFAULT 0x04           // 2 byte StartFrame + 2 byte TypeMessage
#define LENGTH_MESSAGE_SET_PORT 0x05  // 2 byte length data + 1 byte data + 2 byte check sum
#define LENGTH_MESSAGE_ASK_DATA 0x06  // 2 byte length data + 2 byte data + 2 byte check sum
#define LENGTH_MESSAGE_CONFIRM 0x06   // 2 byte length data + 2 byte data + 2 byte check sum
#define LENGTH_MESSAGE_RESPOND_LUX 10 /* Length_data + Port + TypeSensor + 4 byte Data + Checksum*/
#define LENGTH_MESSAGE_RESPOND_RTC 13 /* Length_data + Port + TypeSensor + 7 byte Data + Checksum*/
#define LENGTH_MESSAGE_RESPOND_NTC 10 /* Length_data + Port + TypeSensor + 4 byte Data + Checksum*/
#define LENGTH_MESSAGE_RESPOND_RES 8  /* Length_data + Port + TypeSensor + 2 byte Data + Checksum*/

extern uint8_t count_check;
#define SIZE_LIST_SENSOR 4
typedef enum
{
    SENSOR_LUX = 0x01,
    SENSOR_RTC = 0x02,
    SENSOR_NTC = 0x03,
    SENSOR_RES = 0x04,
} type_Sensor_e;

typedef enum
{
    PORT_A = 0x01,
    PORT_B = 0x02,
} port_e;

typedef enum
{
    TYPE_MESSAGE_SET_PORT = 0x01,
    TYPE_MESSAGE_ASK_DATA = 0x02,
    TYPE_MESSAGE_SENSOR_CONFIRM = 0x03,
    TYPE_MESSAGE_SENSOR_RESPOND_DATA = 0x04,
} type_Message_e;

typedef struct
{
    uint16_t StartFrame;
    uint16_t TypeMessage;
    uint16_t Length; // tính từ Length + Data
    uint8_t Data[10];
    uint16_t CheckFrame;
} frame_Message_t;

uint16_t Message_Frame_Create_Set_Port(port_e datain_port, uint8_t *data_out);

uint8_t Messagee_Frame_Create_Confirm(uint8_t datain_port, uint8_t datain_sensor, uint8_t *dataout);

uint8_t Message_Frame_Create_Ask(port_e datain_port, type_Sensor_e datain_sensor, uint8_t *dataout);

uint8_t Message_Frame_Detect(uint8_t *sensor_datain, frame_Message_t *sensor_dataout);

uint8_t Message_Frame_Response_LUX(port_e datain_port, type_Sensor_e datain_sensor, float datain_value, uint8_t *dataout);

uint8_t Message_Frame_Response_NTC(port_e datain_port, type_Sensor_e datain_sensor, float datain_value, uint8_t *dataout);

uint8_t Message_Create_Frame_Respond_RES(uint16_t datain_value, uint8_t *dataout);
/************************************************************************************************************ */
uint8_t Message_Get_Port(frame_Message_t datain_frame);

uint8_t Message_Get_Type_Sensor(frame_Message_t datain_frame);

uint16_t Message_Get_Data_Sensor_Res(frame_Message_t datain_frame);

float Message_Get_Data_Sensor_Lux(frame_Message_t datain_frame);

float Message_Get_Data_Sensor_NTC(frame_Message_t datain_frame);

uint8_t *Message_Get_Data_Sensor_RTC(frame_Message_t datain_frame, uint8_t *arr_time_out);

uint16_t Check_Sum(uint8_t *buf, uint8_t len);

#endif