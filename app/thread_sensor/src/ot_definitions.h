#ifndef OT_DEFINITIONS_H
#define OT_DEFINITIONS_H

#include <dk_buttons_and_leds.h>

#define OT_CONNECTION_LED DK_LED1
#define LIGHT_LED DK_LED4
#define TEMP_PUB_LED DK_LED2

#define LIGHT_URI_PATH "light"
#define TEMP_URI_PATH "temp"
#define CONFIG_URI_PATH "config"
#define COAP_PORT 5683

enum ot_thread_commands {
	THREAD_COAP_LIGHT_CMD_OFF = '0',
	THREAD_COAP_LIGHT_CMD_ON = '1',
	THREAD_COAP_LIGHT_CMD_TOGGLE = '2',
	THREAD_COAP_TEMP_PUBLISH_ON_CMD = '3',
	THREAD_COAP_TEMP_PUBLISH_OFF_CMD = '4'
};

#endif // OT_DEFINITIONS_H