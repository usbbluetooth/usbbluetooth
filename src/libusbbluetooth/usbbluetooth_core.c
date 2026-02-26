#include <usbbluetooth_err.h>

#include <libusb.h>
#include "usbbluetooth_log.h"

usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_init()
{
    usbbluetooth_log_set_level(USBBLUETOOTH_LOG_NONE);
    int r = libusb_init(NULL);
    libusb_set_option(NULL, LIBUSB_OPTION_USE_USBDK);
    return (r == LIBUSB_SUCCESS) ? USBBLUETOOTH_STATUS_OK : USBBLUETOOTH_STATUS_ERR_UNK;
}

void USBBLUETOOTH_CALL usbbluetooth_exit()
{
    libusb_exit(NULL);
}
