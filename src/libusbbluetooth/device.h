#ifndef _H_DEVICE_
#define _H_DEVICE_

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

#endif
