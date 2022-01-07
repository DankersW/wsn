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
SHELL_STATIC_SUBCMD_SET_CREATE(sub_thread_monitor_temp,
	SHELL_CMD(on, NULL, "Turn on temperature monitoring", cmd_ot_monitor_temp_on),
	SHELL_CMD(off, NULL, "Turn off temperature monitoring", cmd_ot_monitor_temp_off),
	SHELL_SUBCMD_SET_END
);
SHELL_STATIC_SUBCMD_SET_CREATE(sub_thread_monitor_decode,
	SHELL_CMD(off, NULL, "HEX protobuf", cmd_ot_monitor_decode_off),
	SHELL_CMD(on, NULL, "Readable ASCII", cmd_ot_monitor_decode_on),
	SHELL_SUBCMD_SET_END
);
SHELL_STATIC_SUBCMD_SET_CREATE(sub_thread_monitor,
	SHELL_CMD(temp, &sub_thread_monitor_temp, "Temperature monitoring", NULL),
	SHELL_CMD(decode, &sub_thread_monitor_decode, "Translated received data from hex (protobuf) to readable ascii", NULL),
	SHELL_SUBCMD_SET_END
);
SHELL_STATIC_SUBCMD_SET_CREATE(sub_thread,
	SHELL_CMD(multi_light, &sub_thread_multi_light, "Multicast light ctrl", NULL),
	SHELL_CMD(monitor, &sub_thread_monitor, "Monitoring commands", NULL),
	SHELL_SUBCMD_SET_END
);
SHELL_CMD_REGISTER(thread, &sub_thread, "thread", NULL);
