#pragma once

#include "button.h"

typedef struct
{
    uint8_t id;
    uint8_t gpio_a;
    uint8_t gpio_b;
    button_t button;
} encoder_t;

void encoder_Initialise(button_t* button);
void encoder_GetState(encoder_t* encoder);
