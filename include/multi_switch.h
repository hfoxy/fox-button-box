

#pragma once

#include "button.h"


typedef struct {
    button_t up;
    button_t down;
    button_t left;
    button_t right;
    button_t push;
}multi_switch_t;

void multi_switch_Initialise(multi_switch_t* multi_switch);
