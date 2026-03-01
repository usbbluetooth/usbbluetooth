#include "device.h"

#include "utils.h"
#include <stdlib.h>
#include <string.h>

int _libusb_count_bluetooth_devices(libusb_device **list, int *num)
{
    // Iterate all devices...
    libusb_device *dev;
    for (int i = 0; (dev = list[i]) != NULL; i++)
    {
        // Check if device has a Bluetooth interface...
        bool is_bt = false;
        int r = _libusb_is_bluetooth_device(dev, &is_bt);
        if (r == LIBUSB_ERROR_NOT_FOUND)
            is_bt = false;
        else if (r < LIBUSB_SUCCESS)
            return r;
        if (is_bt)
            (*num)++;
    }
    return LIBUSB_SUCCESS;
}

usbbluetooth_device_t *_libusb_create_dev(libusb_device *dev)
{
    usbbluetooth_device_t *btdev = calloc(1, sizeof(usbbluetooth_device_t));
    btdev->ref_count = 0;
    btdev->type = USBBLUETOOTH_DEVICE_TYPE_USB;
    btdev->device = libusb_ref_device(dev);
    _device_ctx_usb_t *ctx = calloc(1, sizeof(_device_ctx_usb_t));
    memset(ctx, 0, sizeof(_device_ctx_usb_t));
    btdev->context = ctx;
    return btdev;
}

void _libusb_free_dev(usbbluetooth_device_t **dev_ptr)
{
    usbbluetooth_device_t *dev = *dev_ptr;
    libusb_unref_device(dev->device);
    free(dev->context);
    free(dev);
    *dev_ptr = NULL;
}
