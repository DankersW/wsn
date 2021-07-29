#include <zephyr.h>
#include <sys/printk.h>
#include <logging/log.h>
#include <stdlib.h>

#include <usb/usb_device.h>
#include <drivers/uart.h>


LOG_MODULE_REGISTER(cdc_acm_echo, LOG_LEVEL_INF);

void main(void)
{
	
	if (usb_enable(NULL)) {
		return;
	}

	printk("All ready to roll...");
	while (1) {
		k_sleep(K_SECONDS(0.5));
		printk("Hello world\n");
	}
	
}
