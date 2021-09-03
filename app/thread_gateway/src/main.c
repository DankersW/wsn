#include <zephyr.h>
#include <dk_buttons_and_leds.h>
#include <logging/log.h>

#include "cli_shell.h"
#include "ot.h"

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

void main(void)
{
	int ret = dk_leds_init();
	if (ret) {
		LOG_ERR("Cannot init leds, (error: %d)", ret);
		return;
	}

	init_ot();
	enable_shell();
}