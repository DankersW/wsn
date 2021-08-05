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

	LOG_ERR("Error message example.");
	LOG_WRN("Warning message example.");
	LOG_INF("Info message example.");
	LOG_DBG("Debug message example.");

	LOG_DBG("Debug message example, %d", 1);
	LOG_DBG("Debug message example, %d, %d", 1, 2);
	LOG_DBG("Debug message example, %d, %d, %d", 1, 2, 3);
	LOG_DBG("Debug message example, %d, %d, %d, 0x%x", 1, 2, 3, 4);
	
	while (1) {
		k_sleep(K_SECONDS(2));
		printk("Hello world\n");
	}
}
