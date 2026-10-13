#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/sensor.h>

#define SLEEP_TIME_MS 1000

const struct device * driver = DEVICE_DT_GET(DT_NODELABEL(our_driver0));

LOG_MODULE_REGISTER(main, LOG_LEVEL_INF);

int main(void)
{
    while (1) {
        
        sensor_sample_fetch(driver);
        k_msleep(SLEEP_TIME_MS);

        sensor_channel_get(driver, SENSOR_CHAN_MAX, NULL);
        k_msleep(SLEEP_TIME_MS);
    }
    return 0;
}
