
#include "core1_entry.h"

#include <class/hid/hid_device.h>
#include <device/usbd.h>

#include "pico/multicore.h"

static gamepad_report_t report;

void core1_entry()
{
    // chuck something on core
    multicore_fifo_push_blocking(0xFFFFFFFF);

    // init device stack on configured roothub port
    tud_init(BOARD_TUD_RHPORT);

    gamepad_report_t report_local = {};
    while (1)
    {
        tud_task(); // tinyusb device task

        hid_task(report_local);
    }
}

void hid_task(gamepad_report_t report_local)
{
    if((multicore_fifo_get_status() & 0b0001) != 0)
    {
        uint32_t data_received = multicore_fifo_pop_blocking();
        report_local.buttons_a = (uint8_t)(data_received & 0xFF);
        report_local.buttons_b = (uint8_t)((data_received >> 8) & 0xFF);
        report_local.buttons_c = (uint8_t)((data_received >> 16) & 0xFF);
        report_local.buttons_d = (uint8_t)((data_received >> 24) & 0xFF);
        if (tud_hid_ready()) {
            tud_hid_report(0, &report, sizeof(report));
        }
    }
}
