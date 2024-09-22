#include "button.h"

#include <hardware/gpio.h>

void button_Initialise(button_t* button)
{
    gpio_set_input_hysteresis_enabled(button->gpio, true);
    gpio_set_dir(button->gpio, GPIO_IN);
}

uint8_t button_GetState(button_t* button)
{
    return !gpio_get(button->gpio);
}
