#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>

#define LIGHT_URI_PATH "light"
#define TEMP_URI_PATH "temp"
#define CONFIG_URI_PATH "config"
#define COAP_PORT 5683

#define OT_CONNECTION_LED DK_LED1

#define CHIP_TEMP_MSG_SIZE 3

enum ot_thread_commands {
	THREAD_COAP_LIGHT_CMD_OFF = '0',
	THREAD_COAP_LIGHT_CMD_ON = '1',
	THREAD_COAP_LIGHT_CMD_TOGGLE = '2',
	THREAD_COAP_TEMP_PUBLISH_ON_CMD = '3',
	THREAD_COAP_TEMP_PUBLISH_OFF_CMD = '4',
	THREAD_COAP_TEMP_MSG_CMD = '5'
};

typedef struct OtTempData
{
	uint8_t cmd;
	int16_t temperature;
} OtTempData;


#endif // DEFINITIONS_H
