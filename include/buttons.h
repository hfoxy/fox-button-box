
#pragma once
#include "button.h"

void buttons_Initialise(void);
void buttons_GetState(button_t *buttons);
uint8_t buttons_GetShortState(void);

#define NUMBER_OF_BUTTONS 6U