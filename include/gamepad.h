#pragma once
#include "button.h"

typedef struct
{
    button_t up_button;
    button_t down_button;
    button_t left_button;
    button_t right_button;
    button_t push_button;
} multi_switch_t;

void gamepad_Initialise(void);
void gamepad_GetState(button_t* buttons);
uint32_t gamepad_GetShortState(void);

#define NUMBER_OF_BUTTONS 6U
#define NUMBER_OF_MULTI_SWITCHES 2U
#define NUMBER_OF_ENCODERS 4U
