#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>

// USB printing
#include <sys/printk.h>
#include <usb/usb_device.h>

#include "ot_coap.h"

#define LOG_MODULE_NAME main
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

void setup()
{
	
	dk_leds_init();
	init_ot_coap();	
}

void main(void)
{
	setup();

	usb_enable(NULL);

	publisher();
}
