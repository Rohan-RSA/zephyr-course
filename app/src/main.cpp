#include <cstdlib>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

#include "our_driver.h"

#define SLEEP_TIME_MS 1000

const struct device * driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

our_struct_t our_struct = {
    .mutable_int = 0
};

int main(void)
{
    while (1) {
        
        sensor_sample_fetch(driver);
        k_msleep(SLEEP_TIME_MS);

        sensor_channel_get(driver, SENSOR_CHAN_MAX, NULL);
        k_msleep(SLEEP_TIME_MS);

        LOG_INF("Incrementing integer: %d", my_extension_api_func(&our_struct));
    }
    return 0;
}
