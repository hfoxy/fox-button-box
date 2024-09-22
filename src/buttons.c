
#include "buttons.h"
#include "button.h"

/*
button_t buttons[NUMBER_OF_BUTTONS] = {
    [0].id = 1,
    [0].gpio = 14,
    [0].debounce_ms = 0,

    [1].id = 2,
    [1].gpio = 20,
    [1].debounce_ms = 0,

    [2].id = 3,
    [2].gpio = 24,
    [2].debounce_ms = 0,

    [3].id = 4,
    [3].gpio = 8,
    [3].debounce_ms = 0,

    [4].id = 5,
    [4].gpio = 29,
    [4].debounce_ms = 0,

    [5].id = 6,
    [5].gpio = 25,
    [5].debounce_ms = 0,
};*/

button_t buttons[NUMBER_OF_BUTTONS] = {
    [0].id = 1,
    [0].gpio = 3,
    [0].debounce_ms = 0,

    [1].id = 2,
    [1].gpio = 4,
    [1].debounce_ms = 0,

    [2].id = 3,
    [2].gpio = 5,
    [2].debounce_ms = 0,

    [3].id = 4,
    [3].gpio = 6,
    [3].debounce_ms = 0,

    [4].id = 5,
    [4].gpio = 7,
    [4].debounce_ms = 0,

    [5].id = 6,
    [5].gpio = 8,
    [5].debounce_ms = 0,
};

void buttons_Initialise(void) {
    /* Configure the initiale pin state as well as inputs/pull ups. */
    for(int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        button_Initialise(&buttons[i]);
    }

}

void buttons_GetState(button_t *buttons) {
    /* nice function to return all information about the buttons. Likely not needed. */
}

uint8_t buttons_GetShortState(void) {
    uint8_t result = 0;
    for(int i = 0; i < NUMBER_OF_BUTTONS; i++) {
        result = button_GetState(&buttons[i]) << i;
    }
    return result;
}