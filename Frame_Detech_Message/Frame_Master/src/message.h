#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include <stdint.h>

#define START_BYTE                 0XAA55
#define LENGTH_MASTER_DEFAULT      3
#define LENGTH_MASTER_START        3
#define LENGTH_MASTER_REQUEST      3  
#define LENGTH_MASTER_ASK_DATA     2
#define LENGTH_MASTER_RECEVEI_DATA 6           

typedef enum
{
    SENSOR_LIGTH    = 1,
    SENSOR_DS1307   = 2,
    SENSOR_NTC      = 3,
    SENSOR_RHEOSTAT = 4,
} list_Sensor_e;

typedef enum
{
    TYPE_MASTER_START           = 1,
    TYPE_MASTER_ASK_DATA        = 2,
    TYPE_MESSAGE_SENSOR_RESPOND  = 3,
    TYPE_MESSAGE_SENSOR_SENDDATA = 4, 
} type_message_e;

// typedef enum
// {
//     TYPE_MESSAGE_SENSOR_RESPOND  = 1,
//     TYPE_MESSAGE_SENSOR_SENDDATA = 2, 
// }type_message_Sensor_e;

typedef struct
{
    uint16_t StartFrame;
    uint16_t  TypeMessage;
    uint16_t LengthData;
    uint8_t  Data[12];
    uint16_t CheckFrame;
} frame_Master_t;

uint8_t Message_Create_Frame_Master(frame_Master_t DataIn, uint8_t *DataOut);
uint8_t Message_Detech_Frame_Master(uint8_t* Master_DataIn, frame_Master_t* Master_DataOut);
uint8_t Check_Sum(uint8_t *buf, uint8_t len);

#endif