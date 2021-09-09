#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>

#define LIGHT_URI_PATH "light"
#define TEMP_PUB_URI_PATH "temp_pub"
#define COAP_PORT 5683

#define OT_CONNECTION_LED DK_LED1

enum light_command {
	THREAD_COAP_LIGHT_CMD_OFF = '0',
	THREAD_COAP_LIGHT_CMD_ON = '1',
	THREAD_COAP_LIGHT_CMD_TOGGLE = '2'
};

#endif // DEFINITIONS_H
