#ifndef COMMAND_DEFINITIONS_H
#define COMMAND_DEFINITIONS_H

#include <stdlib.h>
#include <shell/shell.h>
#include "commands_misc.h"
#include "commands_bt.h"

static int cmd_misc_version(const struct shell *shell, size_t argc, char **argv);
static int cmd_misc_ping(const struct shell *shell, size_t argc, char **argv);
static int cmd_misc_blinky(const struct shell *shell, size_t argc, char **argv);

static int cmd_bt_enable(const struct shell *shell, size_t argc, char **argv);
static int cmd_bt_scan(const struct shell *shell, size_t argc, char **argv);

SHELL_STATIC_SUBCMD_SET_CREATE(sub_misc,
	SHELL_CMD(version, NULL, "Prints the adapter version", cmd_misc_version),
	SHELL_CMD(ping, NULL, "Ping-pong", cmd_misc_ping),
	SHELL_CMD(blinky, NULL, "blinky", cmd_misc_blinky),
	SHELL_SUBCMD_SET_END
);
SHELL_CMD_REGISTER(misc, &sub_misc, "Miscellaneous commands", NULL);

SHELL_STATIC_SUBCMD_SET_CREATE(sub_bt,
	SHELL_CMD(enable, NULL, "Enables Bluetooth stack", cmd_bt_enable),
	SHELL_CMD(scan, NULL, "Scan for beaconing devices", cmd_bt_scan),
	SHELL_SUBCMD_SET_END
);
SHELL_CMD_REGISTER(bt, &sub_bt, "Bluetooth commands", NULL);

#endif // COMMAND_DEFINITIONS_H
