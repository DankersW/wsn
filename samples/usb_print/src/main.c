#include <zephyr.h>
#include <sys/printk.h>

#include <usb/usb_device.h>

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
