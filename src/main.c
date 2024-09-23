/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2019 Ha Thach (tinyusb.org)
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//#include "bsp/board_api.h"
#include <bsp/board.h>
#include <pico/multicore.h>
#include <pico/stdio.h>

#include "tusb.h"
#include "usb_descriptors.h"
#include "gamepad.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

typedef struct
{
    uint8_t buttons_a;
    uint8_t buttons_b;
    uint8_t buttons_c;
    uint8_t buttons_d;
} gamepad_report_t;

void send_report();

/*------------- MAIN -------------*/
int main(void)
{
    stdio_init_all();

    tud_init(BOARD_TUD_RHPORT);

    gamepad_Initialise();

    while (1)
    {
        tud_task(); // tinyusb device task

        if(tud_hid_ready()) {
            send_report();
        }

    }
}

void send_report()
{
    uint32_t report = gamepad_GetShortState();
    gamepad_report_t report_local;
    report_local.buttons_a = (uint8_t)(report & 0xFF);
    report_local.buttons_b = (uint8_t)(report >> 8 & 0xFF);
    report_local.buttons_c = (uint8_t)(report >> 16 & 0xFF);
    report_local.buttons_d = (uint8_t)(report >> 24 & 0xFF);
    tud_hid_report(0, &report_local, sizeof(gamepad_report_t));
}


//--------------------------------------------------------------------+
// Device callbacks
//--------------------------------------------------------------------+

// Invoked when device is mounted
void tud_mount_cb(void)
{
}

// Invoked when device is unmounted
void tud_umount_cb(void)
{
}

// Invoked when usb bus is suspended
// remote_wakeup_en : if host allow us  to perform remote wakeup
// Within 7ms, device must draw an average of current less than 2.5 mA from bus
void tud_suspend_cb(bool remote_wakeup_en)
{
    (void)remote_wakeup_en;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer,
                               uint16_t reqlen)
{
    // TODO not Implemented
    (void)instance;
    (void)report_id;
    (void)report_type;
    (void)buffer;
    (void)reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer,
                           uint16_t bufsize)
{
    (void)instance;

    // echo back anything we received from host
    tud_hid_report(report_id, buffer, bufsize);
}
