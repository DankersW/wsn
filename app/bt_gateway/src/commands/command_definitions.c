#include "command_definitions.h"

static int cmd_misc_ping(const struct shell *shell, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(shell, "pong");
	return 0;
}

static int cmd_misc_blinky(const struct shell *shell, size_t argc, char **argv)
{
	uint8_t blinks = 5;
	uint16_t sleep = 250;
	shell_print(shell, "Blinking %d times with an sleep period of %d ms", blinks, sleep);
	blink(blinks, sleep);
	return 0;
}

static int cmd_misc_version(const struct shell *shell, size_t argc, char **argv)
{
	char *version = get_version();
	shell_print(shell, "version: %s", version);
	return 0;
}

static int cmd_bt_enable(const struct shell *shell, size_t argc, char **argv)
{
	shell_print(shell, "Enabling bt stack");
	if (enable_bluetooth())
	{
		shell_print(shell, "Bluetooth subsystem initialized");
		return 0;
	}
	return 1;
}

static int cmd_bt_scan(const struct shell *shell, size_t argc, char **argv)
{
	beacon_scanning();
	return 0;
}
