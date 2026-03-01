#ifndef _H_LIBUSB_DEVICE_
#define _H_LIBUSB_DEVICE_

#include "../usbbluetooth_device.h"
#include <libusb.h>

/**
 * USB device context structure.
 */
typedef struct
{
    libusb_device_handle *handle;
    uint8_t interface_num;
    uint8_t epnum_evt;
    uint8_t epnum_acl_in;
    uint8_t epnum_acl_out;
} _device_ctx_usb_t;

int _libusb_count_bluetooth_devices(libusb_device **list, int *num);
usbbluetooth_device_t *_dev_from_libusb(libusb_device *dev);

#endif
