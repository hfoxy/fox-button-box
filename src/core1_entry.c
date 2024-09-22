
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

        hid_task(&report_local);
    }
}

void hid_task(gamepad_report_t *report_local)
{
    if((multicore_fifo_get_status() & 0b0001) != 0)
    {
        uint32_t data_received = multicore_fifo_pop_blocking();
        report_local->buttons_a = (uint8_t)(data_received & 0xFF);
        report_local->buttons_b = (uint8_t)(data_received >> 8 & 0xFF);
        report_local->buttons_c = (uint8_t)(data_received >> 16 & 0xFF);
        report_local->buttons_d = (uint8_t)(data_received >> 24 & 0xFF);
        if (tud_hid_ready()) {
            tud_hid_report(0, report_local, sizeof(gamepad_report_t));
        }
    }
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
    (void) remote_wakeup_en;
}

// Invoked when usb bus is resumed
void tud_resume_cb(void)
{
}

// Invoked when received GET_REPORT control request
// Application must fill buffer report's content and return its length.
// Return zero will cause the stack to STALL request
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t* buffer, uint16_t reqlen)
{
    // TODO not Implemented
    (void) instance;
    (void) report_id;
    (void) report_type;
    (void) buffer;
    (void) reqlen;

    return 0;
}

// Invoked when received SET_REPORT control request or
// received data on OUT endpoint ( Report ID = 0, Type = 0 )
void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id, hid_report_type_t report_type, uint8_t const* buffer, uint16_t bufsize)
{
    (void) instance;

    // echo back anything we received from host
    tud_hid_report(report_id, buffer, bufsize);
}
