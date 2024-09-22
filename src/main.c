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
#include "core1_entry.h"
#include "usb_descriptors.h"
#include "buttons.h"

//--------------------------------------------------------------------+
// MACRO CONSTANT TYPEDEF PROTYPES
//--------------------------------------------------------------------+

gamepad_report_t build_report();

void send_report(gamepad_report_t *report);

/*------------- MAIN -------------*/
int main(void)
{
  stdio_init_all();

  multicore_launch_core1(core1_entry);

  multicore_fifo_pop_blocking();

  board_init();

  buttons_Initialise();

  while (1)
  {
    gamepad_report_t report = build_report();
    send_report(&report);
  }
}

gamepad_report_t build_report()
{
  gamepad_report_t report = {
    .buttons_a = buttons_GetShortState(),
    .buttons_b = 0,
    .buttons_c = 0,
    .buttons_d = 0,
  };

  return report;
}

void send_report(gamepad_report_t *report)
{
  uint32_t report_send = report->buttons_a | report->buttons_b << 8 | report->buttons_c << 16 | report->buttons_d << 24;
  multicore_fifo_push_blocking(report_send);
}
