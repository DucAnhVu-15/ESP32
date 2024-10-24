#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "stdint.h"

#define START_BYTE              0XAA55
#define LENGTH_DEFAULT          3
#define SENSOR_LIST_SIZE        2
#define LENGTH_SENSOR_RESPOND   4
#define LENGTH_SENSOR_SEND_DATA 6


#define SIZE_LIST_SENSOR_I2C    2
typedef enum
{
    SENSOR_LIGTH = 1,
    SENSOR_DS1307 = 2,
} list_I2C_e;

#define SIZE_LIST_SENSOR_ADC 2
typedef enum
{
    SENSOR_NTC      = 1,
    SENSOR_RHEOSTAT = 2,
} list_ADC_e;

#define SIZE_LIST_SENSOR 4
typedef enum
{
    SENSOR_LIGTH    = 1,
    SENSOR_DS1307   = 2,
    SENSOR_NTC      = 3,
    SENSOR_RHEOSTAT = 4,
} list_Sensor_e;

typedef enum
{
    TYPE_MASTER_START            = 1,
    TYPE_MASTER_ASK_DATA         = 2,
    TYPE_MESSAGE_SENSOR_RESPOND  = 3,
    TYPE_MESSAGE_SENSOR_SENDDATA = 4, 
} type_message_e;

// typedef enum
// {
//     TYPE_MESSAGE_SENSOR_RESPOND  = 1,
//     TYPE_MESSAGE_SENSOR_SENDDATA = 2, 
// }type_message_e;

// typedef enum
// {
//     TYPE_MASTER_START           = 1,
//     TYPE_MASTER_ASK_DATA        = 3,
// } type_message_Master_e;

typedef struct
{
    uint16_t StartFrame;
    uint16_t TypeMessage;
    uint16_t LengthData;
    uint8_t  Data[12];
    uint16_t CheckFrame;
} frame_Sensor_t;

uint8_t Check_Sum(uint8_t *buf, uint8_t len);

#endif