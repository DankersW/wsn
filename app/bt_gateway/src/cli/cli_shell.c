#include "cli_shell.h"

void enable_shell(void)
{
    if (usb_enable(NULL)) {
		return;
	}
	setup_uart_console();
}

void setup_uart_console(void)
{
	const struct device *dev = device_get_binding(CONFIG_UART_CONSOLE_ON_DEV_NAME);
	uint32_t dtr = 0;
	while (!dtr) {
		uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
	}
}