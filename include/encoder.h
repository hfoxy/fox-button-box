#pragma once

#include <stdbool.h>
#include <pico/types.h>

#include "button.h"

typedef enum {
    counterclockwise = -1,
    no_rotation = 0,
    clockwise = 1,
}direction_t;

typedef struct
{
    uint8_t id_incr;
    uint8_t id_decr;
    uint8_t gpio_a;
    uint8_t gpio_b;
    bool pull_up;
    uint32_t debounce_ms;
    button_t button;

    uint8_t state_hold_ms;
    direction_t held_state;
    uint32_t held_state_until;

    int8_t pulse_per_detent;
    int8_t pulse_counter;
    direction_t rotation;
    bool dual_interrupt;

    uint8_t state_counter;
} encoder_t;


void encoder_Initialise(encoder_t* button);

// -1 = decr, 0 = idle, 1 = incr
int8_t encoder_GetState(encoder_t* encoder);