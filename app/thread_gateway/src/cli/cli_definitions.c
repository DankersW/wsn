#include "cli_definitions.h"

SHELL_STATIC_SUBCMD_SET_CREATE(sub_misc,
	SHELL_CMD(version, NULL, "Prints the adapter version", cmd_misc_version),
	SHELL_CMD(ping, NULL, "Ping-pong", cmd_misc_ping),
	SHELL_CMD(blinky, NULL, "blinky", cmd_misc_blinky),
	SHELL_SUBCMD_SET_END
);
SHELL_CMD_REGISTER(misc, &sub_misc, "Miscellaneous commands", NULL);

SHELL_STATIC_SUBCMD_SET_CREATE(sub_thread_multi_light,
	SHELL_CMD(toggle, NULL, "Toggle all lights", cmd_ot_multi_light_toggle),
	SHELL_CMD(on, NULL, "All lights on", cmd_ot_multi_light_on),
	SHELL_CMD(off, NULL, "All lights off", cmd_ot_multi_light_off),
	SHELL_SUBCMD_SET_END
);
SHELL_STATIC_SUBCMD_SET_CREATE(sub_thread,
	SHELL_CMD(multi_light, &sub_thread_multi_light, "Multicast light ctrl", NULL),
	SHELL_SUBCMD_SET_END
);
SHELL_CMD_REGISTER(thread, &sub_thread, "thread", NULL);


SHELL_CMD_REGISTER(tt, NULL, "thread", test_send_on);
