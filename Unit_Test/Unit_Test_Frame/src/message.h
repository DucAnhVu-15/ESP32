#ifndef _MESSAGE_H_
#define _MESSAGE_H_

#include "stdint.h"
#include "convert.h"

#define START_BYTE                          0XAA55
#define LENGTH_DEFAULT                      0x03
#define LENGTH_MESSAGE_SET_PORT             0x04
#define LENGTH_MESSAGE_ASK_DATA             0x05
#define LENGTH_MESSAGE_SENSOR_CONFIRM       0x05
#define LENGTH_MESSAGE_SENSOR_RESPOND_DATA  0x08


#define SIZE_LIST_SENSOR 4
typedef enum
{
    SENSOR_LUX      = 0x01,
    SENSOR_RTC      = 0x02,
    SENSOR_NTC      = 0x03,
    SENSOR_RES      = 0x04,
} type_Sensor_e;

typedef enum
{
	PORT_NUMBER_1 = 1,
	PORT_NUMBER_2 = 2,
}port_number_list_e;

typedef enum
{
    TYPE_MESSAGE_SET_PORT                = 0x01,
    TYPE_MESSAGE_ASK_DATA                = 0x02,
    TYPE_MESSAGE_SENSOR_CONFIRM          = 0x03,
    TYPE_MESSAGE_SENSOR_RESPOND_DATA     = 0x04, 
} type_Message_e;

typedef struct
{
    uint16_t StartFrame;
    uint8_t  TypeMessage;
    uint16_t LengthData;
    uint8_t  Data[12];
    uint16_t CheckFrame;
} frame_Master_t;


typedef struct
{
    uint16_t StartFrame;    //2 byte
    uint8_t  TypeMessage;   //1 byte
    uint16_t LengthData;    //2 byte
    uint8_t  Data[12];      //1 byte
    uint16_t CheckFrame;    //2 byte
} frame_Sensor_t;           //19 byte

uint8_t Message_Create_Frame_Master(frame_Master_t DataIn, uint8_t *DataOut);
uint8_t Message_Create_Frame_Slave(frame_Sensor_t DataIn, uint8_t *DataOut);

uint8_t Message_Detech_Frame_Master(uint8_t *Master_DataIn, frame_Master_t *Master_DataOut);
uint8_t Message_Detech_Frame_Slave(uint8_t *Sensor_DataIn, frame_Sensor_t *Sensor_DataOut);
uint16_t CheckSum(uint8_t *buf, uint8_t len);

#endif