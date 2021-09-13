#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>

#include "ot_coap.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

void main(void)
{
	dk_leds_init();

	init_ot_coap();
}
