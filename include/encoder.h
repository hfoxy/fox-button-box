#pragma once

#include <stdbool.h>

#include "button.h"

typedef struct
{
    uint8_t id_incr;
    uint8_t id_decr;
    uint8_t gpio_a;
    uint8_t gpio_b;
    bool pull_up;
    uint32_t debounce_ms;
    button_t button;

    int8_t state;

    bool ccw_fall;
    bool cw_fall;
} encoder_t;

void encoder_Initialise(encoder_t* button);

// -1 = decr, 0 = idle, 1 = incr
int8_t encoder_GetState(encoder_t* encoder);
