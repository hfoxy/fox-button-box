#include "encoder.h"

#include <hardware/gpio.h>
#include <pico/time.h>

encoder_t* encoder_by_gpio[30] = {};

void handle_rotary_state_change(uint gpio, uint32_t events);

void encoder_Initialise(encoder_t* encoder)
{
    gpio_init(encoder->gpio_a);
    gpio_set_dir(encoder->gpio_a, GPIO_IN);
    if (encoder->pull_up)
    {
        gpio_pull_up(encoder->gpio_a);
    }

    encoder_by_gpio[encoder->gpio_a] = encoder;
    gpio_set_irq_enabled_with_callback(encoder->gpio_a, 0b1100, true, handle_rotary_state_change);

    gpio_init(encoder->gpio_b);
    gpio_set_dir(encoder->gpio_b, GPIO_IN);
    if (encoder->pull_up)
    {
        gpio_pull_up(encoder->gpio_b);
    }

    encoder_by_gpio[encoder->gpio_b] = encoder;
    gpio_set_irq_enabled_with_callback(encoder->gpio_b, 0b1100, true, handle_rotary_state_change);
}

int8_t encoder_GetState(encoder_t* encoder)
{
    int8_t state = encoder->state;

    // if (to_ms_since_boot(get_absolute_time()) >= encoder->state_persist_until)
    // {
    //     encoder->state = 0;
    // }

    return state;
}

void handle_rotary_state_change(uint gpio, uint32_t events)
{
    encoder_t* encoder = encoder_by_gpio[gpio];
    if (encoder == NULL)
    {
        return;
    }

    uint8_t a = gpio_get(encoder->gpio_a);
    uint8_t b = gpio_get(encoder->gpio_b);

    if (encoder->pull_up)
    {
        a = a == 0 ? 1 : 0;
        b = b == 0 ? 1 : 0;
    }

    bool changed = false;

    if (gpio == encoder->gpio_a)
    {
        if (!encoder->cw_fall && a == 1 && b == 0)
        {
            encoder->cw_fall = true;
        }

        if (encoder->ccw_fall && a == 0 && b == 0)
        {
            encoder->cw_fall = false;
            encoder->ccw_fall = false;
            encoder->state = -1;
            changed = true;
        }
    } else if (gpio == encoder->gpio_b)
    {
        if (!encoder->cw_fall && a == 0 && b == 1)
        {
            encoder->ccw_fall = true;
        }

        if (encoder->cw_fall && a == 0 && b == 0)
        {
            encoder->cw_fall = false;
            encoder->ccw_fall = false;
            encoder->state = 1;
            changed = true;
        }
    }

    if (!changed)
    {
        encoder->state = 0;
    }
}
