#ifndef CLI_DEFINITIONS_H
#define CLI_DEFINITIONS_H

#include <stdlib.h>
#include <shell/shell.h>
#include "misc_cmd_handlers.h"
#include "commands_bt.h"

static int cmd_bt_enable(const struct shell *shell, size_t argc, char **argv);
static int cmd_bt_scan(const struct shell *shell, size_t argc, char **argv);

#endif // CLI_DEFINITIONS_H
