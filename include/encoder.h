#pragma once

#include "button.h"

typedef struct
{
    uint8_t id_incr;
    uint8_t id_decr;
    uint8_t gpio_a;
    uint8_t gpio_b;
    button_t button;

    int8_t state;
    uint8_t last_a;
    uint8_t last_b;
} encoder_t;

void encoder_Initialise(encoder_t* button);

// -1 = decr, 0 = idle, 1 = incr
int8_t encoder_GetState(encoder_t* encoder);
