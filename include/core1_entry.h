#pragma once
#include <stdint.h>

void core1_entry();

typedef struct
{
    uint8_t buttons_a;
    uint8_t buttons_b;
    uint8_t buttons_c;
    uint8_t buttons_d;
} gamepad_report_t;

void hid_task(gamepad_report_t *report_local);
