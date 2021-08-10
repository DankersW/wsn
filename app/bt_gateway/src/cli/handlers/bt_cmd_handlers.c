#include "bt_cmd_handlers.h"

int cmd_bt_enable(const struct shell *shell, size_t argc, char **argv)
{
	shell_print(shell, "Enabling bt stack");
	if (enable_bluetooth())
	{
		shell_print(shell, "Bluetooth subsystem initialized");
		return 0;
	}
	return 1;
}

int cmd_bt_scan(const struct shell *shell, size_t argc, char **argv)
{
	beacon_scanning();
	return 0;
}

int cmd_bt_prov(const struct shell *shell, size_t argc, char **argv)
{
	shell_print(shell, "Let's go");
	return 0;
}