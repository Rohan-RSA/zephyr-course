// #include <cstddef>
// #include <cstdlib>
#include <sys/_intsup.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>

#include "our_driver.h"
#include "zephyr/shell/shell_string_conv.h"

#define SLEEP_TIME_MS 1000
#define PARAM_MIN     0
#define PARAM_MAX     100

const struct device * driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

our_struct data = {
    .mutable_int = 0
};

static int new_val = 0;

static int cmd_fetch(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "Turning on the LED using custom shell commands!");
    return sensor_sample_fetch(driver);
}

static int cmd_read(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "Turning off the LED using custom shell commands!");
    return sensor_channel_get(driver, SENSOR_CHAN_MAX, NULL);
}

static int cmd_info(const struct shell *sh, size_t argc, char **argv)
{
    shell_print(sh, "Device name: %s and state is: %s", driver->name, \
                device_is_ready(driver) ? "ready" : "not ready");
    return 0;
}

static int cmd_set(const struct shell *sh, size_t argc, char **argv)
{
    int err = 0;
    long val = shell_strtol(argv[1], 10, &err);

    shell_print(sh, "Current data value before change is %d", data.mutable_int);

	if (err != 0) {
		shell_error(sh, "'%s' is not a valid number", argv[1]);
		return -EINVAL;
	}

	if (val < PARAM_MIN || val > PARAM_MAX) {
		shell_error(sh, "value %ld out of range (%d-%d)",
			    val, PARAM_MIN, PARAM_MAX);
		return -EINVAL;
	}

    shell_print(sh, "Parameter value passed is %s", argv[1]);
    new_val = my_extension_api_func(&data, (int)val);
    shell_print(sh, "New value is %d", new_val);

    return 0;
}

SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
    SHELL_CMD(fetch, NULL, "Turn LED on using our_driver", cmd_fetch),
    SHELL_CMD(read, NULL, "Turn LED off using our_driver", cmd_read),
    SHELL_CMD(info, NULL, "Show device info related to our_driver", cmd_info),
    SHELL_CMD_ARG(set, NULL, SHELL_HELP("Set device parameter", "<0-100>"), cmd_set, 2, 0),
    SHELL_SUBCMD_SET_END
);
SHELL_CMD_REGISTER(sensor, &sub_sensor, "Module 7 task 1 shell commands", NULL);

int main(void)
{
    LOG_INF("data initialezed to %d", data.mutable_int);

    while (1) {   
        k_msleep(SLEEP_TIME_MS);    
    }
    return 0;
}
