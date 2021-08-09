#include <zephyr.h>
#include <usb/usb_device.h>
#include <drivers/uart.h>

#include <logging/log.h>
LOG_MODULE_REGISTER(cdc_acm_echo, LOG_LEVEL_INF);

void setup_uart_console()
{
	const struct device *dev = device_get_binding(CONFIG_UART_CONSOLE_ON_DEV_NAME);
	uint32_t dtr = 0;
	while (!dtr) {
		uart_line_ctrl_get(dev, UART_LINE_CTRL_DTR, &dtr);
	}
}

void main(void)
{
	if (usb_enable(NULL)) {
		return;
	}
	setup_uart_console();
}
