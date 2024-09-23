#include "gamepad.h"
#include "button.h"
#include "encoder.h"
#include "multi_switch.h"

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

multi_switch_t multi_switches[NUMBER_OF_MULTI_SWITCHES] = {
    // multi switch 1
    [0].up.id = 7,
    [0].up.gpio = 9,
    [0].up.debounce_ms = 0,

    [0].right.id = 8,
    [0].right.gpio = 10,
    [0].right.debounce_ms = 0,

    [0].down.id = 9,
    [0].down.gpio = 11,
    [0].down.debounce_ms = 0,

    [0].left.id = 10,
    [0].left.gpio = 13,
    [0].left.debounce_ms = 0,

    [0].push.id = 11,
    [0].push.gpio = 12,
    [0].push.debounce_ms = 0,


    // multi switch 2
    [1].up.id = 12,
    [1].up.gpio = 4,
    [1].up.debounce_ms = 0,

    [1].right.id = 13,
    [1].right.gpio = 3,
    [1].right.debounce_ms = 0,

    [1].down.id = 14,
    [1].down.gpio = 5,
    [1].down.debounce_ms = 0,

    [1].left.id = 15,
    [1].left.gpio = 7,
    [1].left.debounce_ms = 0,

    [1].push.id = 16,
    [1].push.gpio = 6,
    [1].push.debounce_ms = 0,
};

encoder_t encoders[NUMBER_OF_ENCODERS] = {
    // front encoder 1
    [0].id_incr = 17,
    [0].id_decr = 18,
    [0].button.id = 19,

    [0].gpio_a = 21,
    [0].gpio_b = 22,
    [0].pull_up = true,

    [0].button.gpio = 23,
    [0].button.debounce_ms = 10,


    // front encoder 2
    [1].id_incr = 20,
    [1].id_decr = 21,
    [1].button.id = 22,

    [1].gpio_a = 26,
    [1].gpio_b = 27,
    [1].pull_up = true,

    [1].button.gpio = 28,
    [1].button.debounce_ms = 10,


    // side encoder 1
    [2].id_incr = 23,
    [2].id_decr = 24,
    [2].button.id = 25,

    [2].gpio_a = 17,
    [2].gpio_b = 19,

    [2].button.gpio = 16,
    [2].button.debounce_ms = 0,


    // side encoder 2
    [3].id_incr = 26,
    [3].id_decr = 27,
    [3].button.id = 28,

    [3].gpio_a = 0,
    [3].gpio_b = 1,

    [3].button.gpio = 18,
    [3].button.debounce_ms = 0,
};

button_t shifters[NUMBER_OF_SHIFTERS] = {
    [0].id = 29,
    [0].gpio = 15,
    [0].debounce_ms = 0,

    [1].id = 30,
    [1].gpio = 2,
    [1].debounce_ms = 0,
};

void gamepad_Initialise(void)
{
    /* Configure the inital pin state as well as inputs/pull ups. */
    for (int i = 0; i < NUMBER_OF_BUTTONS; i++)
    {
        button_Initialise(&buttons[i]);
    }

    for (int i = 0; i < NUMBER_OF_MULTI_SWITCHES; i++)
    {
        multi_switch_Initialise(&multi_switches[i]);
    }

    for (int i = 0; i < NUMBER_OF_ENCODERS; i++)
    {
        encoder_Initialise(&encoders[i]);
        button_Initialise(&encoders[i].button);
    }

    for (int i = 0; i < NUMBER_OF_SHIFTERS; i++)
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
        result = result | (button_GetState(&buttons[i]) << (buttons[i].id - 1));
    }

    for (int i = 0; i < NUMBER_OF_MULTI_SWITCHES; i++)
    {
        multi_switch_t* msw = &multi_switches[i];
        result = result | (button_GetState(&msw->up) << (msw->up.id - 1));
        result = result | (button_GetState(&msw->right) << (msw->right.id - 1));
        result = result | (button_GetState(&msw->down) << (msw->down.id - 1));
        result = result | (button_GetState(&msw->left) << (msw->left.id - 1));
        result = result | (button_GetState(&msw->push) << (msw->push.id - 1));
    }

    for (int i = 0; i < NUMBER_OF_ENCODERS; i++)
    {
        encoder_t* enc = &encoders[i];
        result = result | (button_GetState(&enc->button) << (enc->button.id - 1));

        int8_t state = encoder_GetState(enc);
        if (state == -1)
        {
            result = result | (1 << (enc->id_decr - 1));
        } else if (state == 1)
        {
            result = result | (1 << (enc->id_incr - 1));
        }

        encoder_ResetState(enc);
    }

    for (int i = 0; i < NUMBER_OF_SHIFTERS; i++)
    {
        result = result | (button_GetState(&shifters[i]) << (shifters[i].id - 1));
    }

    return result;
}
