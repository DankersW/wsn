#include "ot_cmd_handlers.h"

int cmd_ot_start(const struct shell *shell, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	shell_print(shell, "started");
	return 0;
}