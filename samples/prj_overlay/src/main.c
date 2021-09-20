#include <zephyr.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <logging/log.h>

#define LOG_MODULE_NAME usb_print_example
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

void main(void)
{
	if (usb_enable(NULL)) {
		return;
	}
	k_sleep(K_SECONDS(1));

	while (1) {
		k_sleep(K_SECONDS(2));
		printk("Hello world\n");
	}
}
