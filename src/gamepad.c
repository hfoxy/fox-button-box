#include "gamepad.h"
#include "button.h"

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
};

multi_switch_t multi_switches[NUMBER_OF_MULTISWITCHES] = {
    // multi switch 1
    [0].up_button.id = 7,
    [0].up_button.gpio = 9,
    [0].up_button.debounce_ms = 0,

    [0].right_button.id = 8,
    [0].right_button.gpio = 10,
    [0].right_button.debounce_ms = 0,

    [0].down_button.id = 9,
    [0].down_button.gpio = 11,
    [0].down_button.debounce_ms = 0,

    [0].left_button.id = 10,
    [0].left_button.gpio = 13,
    [0].left_button.debounce_ms = 0,

    [0].push_button.id = 11,
    [0].push_button.gpio = 12,
    [0].push_button.debounce_ms = 0,


    // multi switch 2
    [1].up_button.id = 12,
    [1].up_button.gpio = 4,
    [1].up_button.debounce_ms = 0,

    [1].right_button.id = 13,
    [1].right_button.gpio = 3,
    [1].right_button.debounce_ms = 0,

    [1].down_button.id = 14,
    [1].down_button.gpio = 5,
    [1].down_button.debounce_ms = 0,

    [1].left_button.id = 15,
    [1].left_button.gpio = 7,
    [1].left_button.debounce_ms = 0,

    [1].push_button.id = 16,
    [1].push_button.gpio = 6,
    [1].push_button.debounce_ms = 0,
};

void gamepad_Initialise(void)
{
    /* Configure the initiale pin state as well as inputs/pull ups. */
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        button_Initialise(&buttons[i]);
    }
}

void gamepad_GetState(button_t* buttons)
{
    /* nice function to return all information about the buttons. Likely not needed. */
}

uint32_t gamepad_GetShortState(void)
{
    uint32_t result = 0;

    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        result = result | (button_GetState(&buttons[i]) << (int)(buttons[i].id - 1));
    }

    for (int i = 0; i < NUMBER_OF_MULTISWITCHES; i++)
    {
        multi_switch_t* msw = &multi_switches[i];
        result = result | (button_GetState(&msw->up_button) << (int)(msw->up_button.id - 1));
        result = result | (button_GetState(&msw->right_button) << (int)(msw->right_button.id - 1));
        result = result | (button_GetState(&msw->down_button) << (int)(msw->down_button.id - 1));
        result = result | (button_GetState(&msw->left_button) << (int)(msw->left_button.id - 1));
        result = result | (button_GetState(&msw->push_button) << (int)(msw->push_button.id - 1));
    }

    return result;
}
