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
usbbluetooth_device_t *_libusb_create_dev(libusb_device *dev);
void _libusb_free_dev(usbbluetooth_device_t **dev_ptr);

void _libusb_vid_pid(usbbluetooth_device_t *dev, uint16_t *vid, uint16_t *pid);
char *_libusb_device_manufacturer(usbbluetooth_device_t *dev);
char *_libusb_device_product(usbbluetooth_device_t *dev);
char *_libusb_device_serial_num(usbbluetooth_device_t *dev);
char *_libusb_device_description(usbbluetooth_device_t *dev);

#endif
