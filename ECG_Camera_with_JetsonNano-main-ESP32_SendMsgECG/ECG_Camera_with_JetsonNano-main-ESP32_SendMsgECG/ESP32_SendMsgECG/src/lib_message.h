#ifndef _LIB_MESSAGE_H_
#define _LIB_MESSAGE_H_

#include <stdio.h>
#include <stdlib.h>

#include "lib_convert.h"

#define START_BYTE 0xAA55

/*
	@brief: Declare the Frame ECG data type.
	@node: The function of this data type is to contain Frame ECG information.
	@param StartFrame: Is a variable of type uint16_t containing Start Frame information.
	@param LengthData: LengthData = 1 byte (LengthData) + n byte (Data) + 1 byte (CheckFrame).
	@param CheckFrame: Byte (LengthData) + nByte (Data).
*/
typedef struct
{
	uint16_t    StartFrame;
	uint8_t     LengthData;
	uint8_t     Data[8];
	uint8_t     CheckFrame;
}ecg_FrameMsg_t;        

/*
	@brief: Standard Frame data creation function.
	@node: The main function of the function is to create newsletters
	@param datain: Is a struct containing information specified by the user to create a newsletter.
	@param dataout: Is the pointer used to get the star array when created successfully.
	@retval: Returns the total length of the message.
*/
uint8_t Message_Create_Frame(ecg_FrameMsg_t data_in, uint8_t *data_out);                                              

/*
	@brief: CheckSum test function.
	@node: The function of the function is to check CheckSum ECG.
	@param buf: Is an array containing data.
	@param len: Is the length of the entire message.
	@retval: Returns the CheckSum value.
*/
uint8_t ECG_CheckSum(uint8_t *buf, uint8_t len);

#endif
