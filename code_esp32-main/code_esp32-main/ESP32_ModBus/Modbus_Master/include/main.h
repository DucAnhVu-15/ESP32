#ifndef _MAIN_H_
#define _MAIN_H_

#include <set>
#include <ctime>
#include <vector>
#include <string>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <string.h>

#define ENA_LIB_JSON    0
#define ENA_LIB_MQTT    0
#define ENA_LIB_MODBUS  1
#define ENA_LIB_LOG     1

#if ENA_LIB_LOG
	#include <plog/Log.h>
	#include <plog/Initializers/RollingFileInitializer.h>
	#include <plog/Init.h>
	#include <plog/Formatters/TxtFormatter.h>
	#include <plog/Appenders/ColorConsoleAppender.h>
#endif

#if  ENA_LIB_JSON
	#include <jsoncpp/json/json.h>
#else
	#include "jsoncpp/json/json.h"
#endif

#if ENA_LIB_MODBUS
	#include <modbus/modbus.h>
#endif

#if ENA_LIB_MQTT
	#include <mqtt_protocol.h>
	#include <mosquitto.h>
#else
	#include "mqtt_protocol.h"
	#include "mosquitto.h"
#endif

#include "wg_debug.h"
#include "wg_modbus.h"
#include "wg_convert.h"

#define SLAVE_ADDRESS 						0x01
#define BAUDRATE_MODBUS      				9600
#define PORT_MODBUS_NAME      				"/dev/ttyUSB0"

#define RETRUN_ERROR 						-1

#define SENSOR_DATA_START_REGISTER 			0
#define SENSOR_DATA_END_REGISTER			31
#define BUTTON_DATA_START_REGISTER 			32
#define BUTTON_DATA_END_REGISTER 			39
#define BUTTON_CHANGE_STATE_REGISTER 		40
#define NEW_MESSAGE_REGISTER 				41
#define PING_STATUS_START_REGISTER 			42
#define PING_STATUS_END_REGISTER 			47
#define CALIB_PARAMETERS_START_REGISTER 	48
#define CALIB_PARAMETERS_END_REGISTER 		53
#define GET_STATUS_START_REGISTER 			54
#define GET_STATUS_END_REGISTER 			59


class MS_Read 															// Master read holding registers from Slave
{
	public:
		int Get_NewMessage(void);										// Read Status - Have ping or new message
		int Get_ButtonChangeState(void);								// Read Button State Change
		int Get_SensorData(float arr[]);								// Read Sensor Data
		int Get_ButtonState(uint8_t arr[]);								// Read Status Button
		int Get_CalibParameters(float *a, float *b, float *c);			// Read Config calib parameter
		int Get_Status(uint16_t *data, std::string *phone_number);		// Read Get Status
		int Get_PingState(uint16_t *data, std::string *phone_number);  	// Read Ping Status

	private:

};

void Modbus_Init(void);

#endif 
