#pragma once

#include <stdbool.h>
#include <pico/types.h>

#include "button.h"

typedef enum {
    counterclockwise = -1,
    no_rotation = 0,
    clockwise = 1,
}direction_t;

typedef void(*encoder_irq_callback_t)(direction_t direction);

typedef struct
{
    uint8_t id_incr;
    uint8_t id_decr;
    uint8_t gpio_a;
    uint8_t gpio_b;
    bool pull_up;
    uint32_t debounce_ms;
    button_t button;

    int8_t pulse_per_detent;
    int8_t pulse_counter;
    int8_t state;
    direction_t rotation;
    uint8_t last_a;
    uint8_t last_b;
    encoder_irq_callback_t callback;
} encoder_t;




void encoder_Initialise(encoder_t* button);

// -1 = decr, 0 = idle, 1 = incr
int8_t encoder_GetState(encoder_t* encoder);

void encoder_ResetState(encoder_t* encoder);
