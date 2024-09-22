
#pragma once
#include "button.h"

void gamepad_Initialise(void);
void gamepad_GetState(button_t *buttons);
uint8_t gamepad_GetShortState(void);

#define NUMBER_OF_BUTTONS 6U