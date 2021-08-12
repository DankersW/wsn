#ifndef BT_CMD_HANDLERS_H
#define BT_CMD_HANDLERS_H

#include <stdlib.h>
#include <shell/shell.h>

#include "commands_bt.h"
#include "provisioning.h"

int cmd_bt_enable(const struct shell *shell, size_t argc, char **argv);
int cmd_bt_scan(const struct shell *shell, size_t argc, char **argv);

int cmd_bt_prov(const struct shell *shell, size_t argc, char **argv);

#endif // BT_CMD_HANDLERS_H