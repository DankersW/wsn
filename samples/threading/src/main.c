#include <zephyr.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <logging/log.h>

#define LOG_MODULE_NAME usb_print_example
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

#define MY_STACK_SIZE 500
#define MY_PRIORITY 7

void my_entry_point()
{
	while (true)
	{
		printk("hello");
		k_sleep(K_SECONDS(2));
	}	
}

K_THREAD_DEFINE(my_tid, MY_STACK_SIZE, my_entry_point, NULL, NULL, NULL, MY_PRIORITY, 0, 0);


void main(void)
{
	if (usb_enable(NULL)) {
		return;
	}
	printk("done\n");
}
