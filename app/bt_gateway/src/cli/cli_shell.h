#ifndef CLI_SHELL_H
#define CLI_SHELL_H

#include <usb/usb_device.h>
#include <drivers/uart.h>

void enable_shell(void);
void setup_uart_console(void);

#endif // CLI_SHELL_H