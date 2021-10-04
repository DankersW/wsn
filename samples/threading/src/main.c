#include <zephyr.h>
#include <sys/printk.h>
#include <usb/usb_device.h>
#include <logging/log.h>

#define LOG_MODULE_NAME usb_print_example
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

#define MY_STACK_SIZE 500
#define MY_PRIORITY 5

void my_entry_point()
{
	while (true)
	{
		printk("hello");
		k_sleep(K_SECONDS(2));
	}	
}

K_THREAD_STACK_DEFINE(my_stack_area, MY_STACK_SIZE);
struct k_thread my_thread_data;

void main(void)
{
	if (usb_enable(NULL)) {
		return;
	}

	k_tid_t my_tid = k_thread_create(&my_thread_data, my_stack_area, K_THREAD_STACK_SIZEOF(my_stack_area), my_entry_point, NULL, NULL, NULL, MY_PRIORITY, 0, K_NO_WAIT);
	printk("done\n");
}
