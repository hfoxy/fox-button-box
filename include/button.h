#pragma once
#include <stdint.h>

typedef struct
{
    uint8_t id;
    uint8_t gpio;
    uint32_t debounce_ms;
} button_t;

void button_Initialise(button_t* button);
uint8_t button_GetState(button_t* button);
