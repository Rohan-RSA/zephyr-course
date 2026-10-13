#include <zephyr/drivers/sensor.h>
#include <zephyr/logging/log.h>
#include <zephyr/drivers/gpio.h>

#define DT_DRV_COMPAT our_driver

LOG_MODULE_REGISTER(our_driver, LOG_LEVEL_INF);

bool led_state = true;

/* The devicetree node identifier for the "led0" alias. */
#define LED_NODE DT_ALIAS(app_led)

static const struct gpio_dt_spec led = GPIO_DT_SPEC_GET(LED_NODE, gpios);

static int sensor_sample_fetch_my_impl(const struct device *dev,
				                         enum sensor_channel chan)
{
    if (gpio_pin_set_dt(&led, 1) < 0) return 0;
    
    led_state = !led_state;
    LOG_INF("sensor_sample_fetch_my_impl() : LED state: %s", led_state ? "ON" : "OFF");

    return 0;
}

static int sensor_channel_get_my_impl(const struct device *dev,
                                      enum sensor_channel chan,
                                      struct sensor_value *val)
{
    if (gpio_pin_set_dt(&led, 0) < 0) return 0;
    
    led_state = !led_state;
    LOG_INF("sensor_channel_get_my_impl() : LED state: %s", led_state ? "ON" : "OFF");

    return 0;
}

static DEVICE_API(sensor, simple_device_api) = {
    .sample_fetch = sensor_sample_fetch_my_impl,
    .channel_get = sensor_channel_get_my_impl
};

static int init_function(const struct device * dev)
{
    if (!gpio_is_ready_dt(&led)) return 0;

    if (gpio_pin_configure_dt(&led, GPIO_OUTPUT_ACTIVE) < 0) return 0;

    LOG_INF("Device initialized from init_function withing our_driver.c");

    return 0;
}

#define DEV_INST(inst) DEVICE_DT_INST_DEFINE(inst, init_function, NULL, NULL, NULL, \
                                             POST_KERNEL, 80, &simple_device_api);

DT_INST_FOREACH_STATUS_OKAY(DEV_INST)
