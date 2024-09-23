#include "encoder.h"

#include <hardware/gpio.h>
#include <pico/time.h>

encoder_t* encoder_by_gpio[30] = {};

void handle_rotary_state_change(uint gpio, uint32_t events);

void encoder_Initialise(encoder_t* encoder)
{
    /* Configure pins */
    gpio_init(encoder->gpio_a);
    gpio_init(encoder->gpio_b);
    gpio_set_dir(encoder->gpio_a, GPIO_IN);
    gpio_set_dir(encoder->gpio_b, GPIO_IN);
    gpio_set_pulls(encoder->gpio_a, encoder->pull_up, false);
    gpio_set_pulls(encoder->gpio_b, encoder->pull_up, false);

    /* Setup array for callback. */
    encoder_by_gpio[encoder->gpio_a] = encoder;
    encoder_by_gpio[encoder->gpio_b] = encoder;

    /* Setup callbacks. */
    gpio_set_irq_enabled_with_callback(encoder->gpio_a,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true, handle_rotary_state_change);

    gpio_set_irq_enabled_with_callback(encoder->gpio_b,
        GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
        true, handle_rotary_state_change);
}

int8_t encoder_GetState(encoder_t* encoder)
{
    return encoder->state;
}

void encoder_ResetState(encoder_t* encoder)
{
    encoder->state = 0;
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

    bool changed = false;

    switch (events)
    {
        case GPIO_IRQ_EDGE_RISE: {
            if(gpio == encoder->gpio_a) {
                /* Rising edge of */
            }
            break;
        }
        case GPIO_IRQ_EDGE_FALL: {

            break;
        }
        default: {
            return;
        }
    }

    if (encoder->last_a == 0 && encoder->last_b == 0 && a == 1 && b == 0)
    {
        encoder->rotation = 1;
        encoder->state = 1;
        changed = true;
    } else if (encoder->rotation == 1 && encoder->last_a == 1 && encoder->last_b == 0 && a == 1 && b == 1)
    {
        encoder->rotation = 1;
        encoder->state = 1;
        changed = true;
    } else if (encoder->rotation == 1 && encoder->last_a == 1 && encoder->last_b == 1 && a == 0 && b == 1)
    {
        encoder->rotation = 1;
        encoder->state = 1;
        changed = true;
    } /*else if (encoder->rotation == 1 && encoder->last_a == 0 && encoder->last_b == 1 && a == 0 && b == 0)
    {
        encoder->rotation = 1;
        encoder->state = 1;
        changed = true;
        // cw rotation complete
    }*/ else if (encoder->last_a == 0 && encoder->last_b == 0 && a == 0 && b == 1)
    {
        encoder->rotation = -1;
        encoder->state = -1;
        changed = true;
    } else if (encoder->rotation == -1 && encoder->last_a == 0 && encoder->last_b == 1 && a == 1 && b == 1)
    {
        encoder->rotation = -1;
        encoder->state = -1;
        changed = true;
    } else if (encoder->rotation == -1 && encoder->last_a == 1 && encoder->last_b == 1 && a == 1 && b == 0)
    {
        encoder->rotation = -1;
        encoder->state = -1;
        changed = true;
    } /*else if (encoder->rotation == -1 && encoder->last_a == 1 && encoder->last_b == 0 && a == 0 && b == 0)
    {
        encoder->rotation = -1;
        encoder->state = -1;
        changed = true;
    }*/ else
    {
        encoder->rotation = 0;
        encoder->state = 0;
    }

    if (!changed)
    {
        encoder->state = 0;
    }

    encoder->last_a = a;
    encoder->last_b = b;
}

void risingEdgeHandler(encoder_t* encoder, uint gpio) {
    if(gpio == encoder->gpio_a) {
        if(gpio_get(encoder->gpio_b)) {
            encoder->rotation = 1;
        }
    }
    if(gpio == encoder->gpio_b) {

    }

}
