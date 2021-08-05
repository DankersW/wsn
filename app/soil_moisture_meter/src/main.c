#include <zephyr.h>
#include <device.h>
#include <usb/usb_device.h>
#include <logging/log.h>

#include "mesh.h"
#include "ui.h"

LOG_MODULE_REGISTER(wsn_node, LOG_LEVEL_DBG);

void init_node(void)
{
	usb_enable(NULL);
	enable_bt();

	enable_ui();
}

void main(void)
{
	init_node();

	while (1) {
		k_msleep(250);
		show_heartbeat();
	}
}
