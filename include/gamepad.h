#pragma once
#include "button.h"

void gamepad_Initialise(void);
void gamepad_GetState(button_t* buttons);
uint32_t gamepad_GetShortState(void);

#define NUMBER_OF_BUTTONS 6U
#define NUMBER_OF_MULTI_SWITCHES 2U
#define NUMBER_OF_ENCODERS 4U
#define NUMBER_OF_SHIFTERS 2U
