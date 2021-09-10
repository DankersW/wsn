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

#endif // OT_DEFINITIONS_H