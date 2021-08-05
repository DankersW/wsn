#include <zephyr.h>
#include <sys/printk.h>

#include <usb/usb_device.h>

#include <logging/log.h>

#define LOG_MODULE_NAME testnig
LOG_MODULE_REGISTER(LOG_MODULE_NAME, LOG_LEVEL_DBG);

void main(void)
{
	if (usb_enable(NULL)) {
		return;
	}

	struct log_msg_ids src_level = {
		.level = LOG_LEVEL_INTERNAL_RAW_STRING,
		.source_id = 0, /* not used as level indicates raw string. */
		.domain_id = 0, /* not used as level indicates raw string. */
	};
	
	//printk("All ready to roll...");
	//printk("hello sys-t on board\n");

	/* standard print */
	LOG_ERR("Error message example.");
	LOG_WRN("Warning message example.");
	LOG_INF("Info message example.");
	LOG_DBG("Debug message example.");

	LOG_DBG("Debug message example, %d", 1);
	LOG_DBG("Debug message example, %d, %d", 1, 2);
	LOG_DBG("Debug message example, %d, %d, %d", 1, 2, 3);
	LOG_DBG("Debug message example, %d, %d, %d, 0x%x", 1, 2, 3, 4);

	/* log output string */
	log_string_sync(src_level, "%s", "log string sync");

	
	while (1) {
		k_sleep(K_SECONDS(0.5));
		printk("Hello world\n");
	}
	
}
