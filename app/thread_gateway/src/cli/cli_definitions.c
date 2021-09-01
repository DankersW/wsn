#include "cli_definitions.h"

SHELL_STATIC_SUBCMD_SET_CREATE(sub_misc,
	SHELL_CMD(version, NULL, "Prints the adapter version", cmd_misc_version),
	SHELL_CMD(ping, NULL, "Ping-pong", cmd_misc_ping),
	SHELL_CMD(blinky, NULL, "blinky", cmd_misc_blinky),
	SHELL_SUBCMD_SET_END
);
SHELL_CMD_REGISTER(misc, &sub_misc, "Miscellaneous commands", NULL);

SHELL_STATIC_SUBCMD_SET_CREATE(sub_thread,
	SHELL_CMD(start, NULL, "Thread start", cmd_ot_start),
	SHELL_SUBCMD_SET_END
);
SHELL_CMD_REGISTER(thread, &sub_thread, "thread", NULL);
