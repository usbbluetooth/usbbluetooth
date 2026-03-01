#include "device.h"

#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

void _libusb_vid_pid(usbbluetooth_device_t *dev, uint16_t *vid, uint16_t *pid)
{
    libusb_device *usb = (libusb_device *)dev->device;
    struct libusb_device_descriptor desc;
    libusb_get_device_descriptor(usb, &desc);
    *vid = desc.idVendor;
    *pid = desc.idProduct;
}

char *_libusb_get_descriptor_ascii(libusb_device_handle *dev_handle, uint8_t desc_num)
{
    if (dev_handle == NULL)
        return NULL;
    char tmp[256];
    int r = libusb_get_string_descriptor_ascii(dev_handle, desc_num, (uint8_t *)tmp, sizeof(tmp));
    if (r < LIBUSB_SUCCESS)
        return NULL;
    tmp[r] = 0;
    return strdup(tmp);
}

char *_libusb_device_manufacturer(usbbluetooth_device_t *dev)
{
    libusb_device *usb = (libusb_device *)dev->device;
    _device_ctx_usb_t *ctx = (_device_ctx_usb_t *)dev->context;
    struct libusb_device_descriptor desc;
    libusb_get_device_descriptor(usb, &desc);
    if (desc.iManufacturer == 0)
        return NULL;
    return _libusb_get_descriptor_ascii(ctx->handle, desc.iManufacturer);
}

char *_libusb_device_product(usbbluetooth_device_t *dev)
{
    libusb_device *usb = (libusb_device *)dev->device;
    _device_ctx_usb_t *ctx = (_device_ctx_usb_t *)dev->context;
    struct libusb_device_descriptor desc;
    libusb_get_device_descriptor(usb, &desc);
    if (desc.iProduct == 0)
        return NULL;
    return _libusb_get_descriptor_ascii(ctx->handle, desc.iProduct);
}

char *_libusb_device_serial_num(usbbluetooth_device_t *dev)
{
    libusb_device *usb = (libusb_device *)dev->device;
    _device_ctx_usb_t *ctx = (_device_ctx_usb_t *)dev->context;
    struct libusb_device_descriptor desc;
    libusb_get_device_descriptor(usb, &desc);
    if (desc.iSerialNumber == 0)
        return NULL;
    return _libusb_get_descriptor_ascii(ctx->handle, desc.iSerialNumber);
}

#define MAX_LEN 256

char *_libusb_device_description(usbbluetooth_device_t *dev)
{
    libusb_device *usb = (libusb_device *)dev->device;
    _device_ctx_usb_t *ctx = (_device_ctx_usb_t *)dev->context;
    // Get USB descriptor
    struct libusb_device_descriptor desc;
    libusb_get_device_descriptor(usb, &desc);
    // Create a tmp string with VID and PID
    uint16_t len_rem = MAX_LEN;
    char tmp[MAX_LEN];
    len_rem -= snprintf(tmp, len_rem, "VID=0x%04x PID=0x%04x", desc.idVendor, desc.idProduct);
    // Add accesory info if available
    char *manuf = _libusb_get_descriptor_ascii(ctx->handle, desc.iManufacturer);
    if (manuf)
    {
        len_rem -= snprintf(tmp + strlen(tmp), len_rem, " %s", manuf);
        free(manuf);
    }
    char *prod = _libusb_get_descriptor_ascii(ctx->handle, desc.iProduct);
    if (prod)
    {
        len_rem -= snprintf(tmp + strlen(tmp), len_rem, " %s", prod);
        free(prod);
    }
    char *sernum = _libusb_get_descriptor_ascii(ctx->handle, desc.iSerialNumber);
    if (sernum)
    {
        len_rem -= snprintf(tmp + strlen(tmp), len_rem, " %s", sernum);
        free(sernum);
    }
    return strdup(tmp);
}
