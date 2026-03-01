#include "device.h"

#include "utils.h"

int _serial_count_bluetooth_devices(struct sp_port **list, int *num)
{
    // Iterate all devices...
    struct sp_port *dev;
    for (int i = 0; (dev = list[i]) != NULL; i++)
    {
        // Check if device is a Bluetooth controller...
        bool is_bt = false;
        int r = _serial_is_bluetooth_device(dev, &is_bt);
        if (r < SP_OK)
            return r;
        if (is_bt)
            (*num)++;
    }
    return SP_OK;
}

usbbluetooth_device_t *_serial_create_dev(struct sp_port *dev)
{
    usbbluetooth_device_t *btdev = calloc(1, sizeof(usbbluetooth_device_t));
    btdev->ref_count = 0;
    btdev->type = USBBLUETOOTH_DEVICE_TYPE_SERIAL;
    sp_copy_port(dev, (struct sp_port **)&btdev->device);
    return btdev;
}

void _serial_free_dev(usbbluetooth_device_t **dev_ptr)
{
    usbbluetooth_device_t *dev = *dev_ptr;
    sp_free_port(dev->device);
    free(dev);
    *dev_ptr = NULL;
}

void _serial_vid_pid(usbbluetooth_device_t *dev, uint16_t *vid, uint16_t *pid)
{
    enum sp_transport tp = sp_get_port_transport(dev->device);
    if (tp == SP_TRANSPORT_USB)
    {
        int usb_vid, usb_pid;
        sp_get_port_usb_vid_pid(dev->device, &usb_vid, &usb_pid);
        *vid = usb_vid;
        *pid = usb_pid;
    }
    else
    {
        *vid = 0;
        *pid = 0;
    }
}

char *_serial_device_manufacturer(usbbluetooth_device_t *dev)
{
    return strdup(sp_get_port_usb_manufacturer(dev->device));
}

char *_serial_device_product(usbbluetooth_device_t *dev)
{
    return strdup(sp_get_port_usb_product(dev->device));
}

char *_serial_device_serial_num(usbbluetooth_device_t *dev)
{
    return strdup(sp_get_port_usb_serial(dev->device));
}

char *_serial_device_description(usbbluetooth_device_t *dev)
{
    return strdup(sp_get_port_description(dev->device));
}
