#include "ot_cmd_handlers.h"

int cmd_ot_multi_light_toggle(const struct shell *shell, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	light_toggle();
	return 0;
}

int cmd_ot_multi_light_on(const struct shell *shell, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	light_set_state(true);
	return 0;
}

int cmd_ot_multi_light_off(const struct shell *shell, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	light_set_state(false);
	return 0;
}

int cmd_ot_monitor_temp_on(const struct shell *shell, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	temp_monitor_set_state(true);
	return 0;
}

int cmd_ot_monitor_temp_off(const struct shell *shell, size_t argc, char **argv)
{
	ARG_UNUSED(argc);
	ARG_UNUSED(argv);
	temp_monitor_set_state(false);
	return 0;
}