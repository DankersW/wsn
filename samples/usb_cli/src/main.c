#include <zephyr.h>
#include <sys/printk.h>
#include <shell/shell.h>
#include <logging/log.h>
#include <stdlib.h>

#include <usb/usb_device.h>
#include <drivers/uart.h>


LOG_MODULE_REGISTER(cdc_acm_echo, LOG_LEVEL_INF);


static int cmd_demo_ping(const struct shell *shell, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(shell, "pong");
	return 0;
}

static int cmd_dict(const struct shell *shell, size_t argc, char **argv, void *data)
{
	int val = (intptr_t)data;
	shell_print(shell, "(syntax, value) : (%s, %d)", argv[0], val);
	return 0;
}

SHELL_SUBCMD_DICT_SET_CREATE(sub_dict_cmds, cmd_dict,
	(value_0, 0), (value_1, 1), (value_2, 2), (value_3, 3)
);

SHELL_STATIC_SUBCMD_SET_CREATE(sub_demo,
	SHELL_CMD(dictionary, &sub_dict_cmds, "Dictionary commands", NULL),
	SHELL_CMD(ping, NULL, "Ping command.", cmd_demo_ping),
	SHELL_SUBCMD_SET_END /* Array terminated. */
);
SHELL_CMD_REGISTER(demo, &sub_demo, "Demo commands", NULL);

void main(void)
{
	if (usb_enable(NULL)) {
		return;
	}

	const struct device *dev = device_get_binding(CONFIG_UART_CONSOLE_ON_DEV_NAME);
	uint32_t dtr = 0;
	while (!dtr) {
		uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
	}

	if (strlen(CONFIG_UART_CONSOLE_ON_DEV_NAME) != strlen("CDC_ACM_0") ||
	    strncmp(CONFIG_UART_CONSOLE_ON_DEV_NAME, "CDC_ACM_0",
		    strlen(CONFIG_UART_CONSOLE_ON_DEV_NAME))) {
		printk("Error: Console device name is not USB ACM\n");

		return;
	}

	printk("All ready to roll...");
	while (1) {
		k_sleep(K_SECONDS(0.1));
	}
	
}
