
#include "core1_entry.h"

#include <device/usbd.h>

#include "pico/multicore.h"

void core1_entry()
{
    // chuck something on core
    multicore_fifo_push_blocking(0xFFFFFFFF);

    // init device stack on configured roothub port
    tud_init(BOARD_TUD_RHPORT);

    while (1)
    {
        tud_task(); // tinyusb device task

        hid_task();
    }
}

// Every 10ms, we will sent 1 report for each HID profile (keyboard, mouse etc ..)
// tud_hid_report_complete_cb() is used to send the next report after previous one is complete
void hid_task(void)
{
    //
}
