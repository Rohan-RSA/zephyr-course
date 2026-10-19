#include <cstddef>
#include <sys/_types.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>
#include <zephyr/shell/shell.h>

#define SLEEP_TIME_MS 1000

const struct device * driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);


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

SHELL_STATIC_SUBCMD_SET_CREATE(sub_sensor,
    SHELL_CMD(fetch, NULL, "Turn LED on using our_driver", cmd_fetch),
    SHELL_CMD(read, NULL, "Turn LED off using our_driver", cmd_read),
    SHELL_CMD(info, NULL, "Show device info related to our_driver", cmd_info),
    SHELL_SUBCMD_SET_END
);

SHELL_CMD_REGISTER(sensor, &sub_sensor, "Module 7 task 1 shell commands", NULL);

int main(void)
{
    while (1) {
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}
