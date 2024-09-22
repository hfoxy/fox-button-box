#include "gamepad.h"
#include "button.h"
#include "encoder.h"

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

encoder_t encoders[NUMBER_OF_ENCODERS] = {
    // front encoder 1
    [0].id_incr = 17,
    [0].id_decr = 18,
    [0].button.id = 19,

    [0].gpio_a = 21,
    [0].gpio_b = 22,

    [0].button.gpio = 23,
    [0].button.debounce_ms = 0,


    // front encoder 2
    [1].id_incr = 20,
    [1].id_decr = 21,
    [1].button.id = 22,

    [1].gpio_a = 26,
    [1].gpio_b = 27,

    [1].button.gpio = 28,
    [1].button.debounce_ms = 0,


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
        button_Initialise(&multi_switches[i].up_button);
        button_Initialise(&multi_switches[i].right_button);
        button_Initialise(&multi_switches[i].down_button);
        button_Initialise(&multi_switches[i].left_button);
        button_Initialise(&multi_switches[i].push_button);
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
        result = result | (button_GetState(&msw->up_button) << (msw->up_button.id - 1));
        result = result | (button_GetState(&msw->right_button) << (msw->right_button.id - 1));
        result = result | (button_GetState(&msw->down_button) << (msw->down_button.id - 1));
        result = result | (button_GetState(&msw->left_button) << (msw->left_button.id - 1));
        result = result | (button_GetState(&msw->push_button) << (msw->push_button.id - 1));
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
    }

    for (int i = 0; i < NUMBER_OF_SHIFTERS; i++)
    {
        result = result | (button_GetState(&shifters[i]) << (shifters[i].id - 1));
    }

    return result;
}
