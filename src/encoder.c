#include "encoder.h"

#include <hardware/gpio.h>
#include <pico/time.h>

encoder_t* encoder_by_gpio[30] = {};

void handle_rotary_state_change(uint gpio, uint32_t events);
void encoderRisingEdgeHandler(encoder_t* encoder, uint gpio);
void encoderFallingEdgeHandler(encoder_t* encoder, uint gpio);

void encoder_Initialise(encoder_t* encoder)
{
    /* Configure pins */
    gpio_init(encoder->gpio_a);
    gpio_init(encoder->gpio_b);
    gpio_set_input_hysteresis_enabled(encoder->gpio_a, true);
    gpio_set_input_hysteresis_enabled(encoder->gpio_b, true);
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

    if(encoder->dual_interrupt) {
        gpio_set_irq_enabled_with_callback(encoder->gpio_b,
    GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL,
    true, handle_rotary_state_change);
    }
}

int8_t encoder_GetState(encoder_t* encoder)
{
    direction_t direction = no_rotation;

    if(encoder->pulse_counter >= encoder->pulse_per_detent) {
        direction = clockwise;

        encoder->state_counter++;
        if (encoder->state_counter >= 2)
        {
            encoder->pulse_counter = 0;
        }
    } else if (encoder->pulse_counter <= -(encoder->pulse_per_detent)) {
        direction = counterclockwise;

        encoder->state_counter++;
        if (encoder->state_counter >= 2)
        {
            encoder->pulse_counter = 0;
        }
    }

    return direction;
}

void handle_rotary_state_change(uint gpio, uint32_t events)
{
    encoder_t* encoder = encoder_by_gpio[gpio];
    if (encoder == NULL)
    {
        return;
    }


    switch (events) {
        case GPIO_IRQ_EDGE_RISE: {
            encoderRisingEdgeHandler(encoder, gpio);
            break;
        }
        case GPIO_IRQ_EDGE_FALL: {
            encoderFallingEdgeHandler(encoder, gpio);
            break;
        }
        default: {
            return;
        }
    }
}

void encoderRisingEdgeHandler(encoder_t* encoder, uint gpio) {
    if(gpio == encoder->gpio_a) {
        if(gpio_get(encoder->gpio_b)) {
            encoder->pulse_counter += counterclockwise;
        }
        else {
            encoder->pulse_counter += clockwise;
        }
    }

    if(gpio == encoder->gpio_b) {
        if(gpio_get(encoder->gpio_a)) {
            encoder->pulse_counter += clockwise;
        }
        else {
            encoder->pulse_counter += counterclockwise;
        }
    }
}

void encoderFallingEdgeHandler(encoder_t* encoder, uint gpio) {
    if(gpio == encoder->gpio_a) {
        if(gpio_get(encoder->gpio_b)) {
            encoder->pulse_counter += clockwise;
        }
        else {
            encoder->pulse_counter += counterclockwise;
        }
    }
    if(gpio == encoder->gpio_b) {
        if(gpio_get(encoder->gpio_a)) {
            encoder->pulse_counter += counterclockwise;
        }
        else {
            encoder->pulse_counter += clockwise;
        }
    }
}
