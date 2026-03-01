#include <usbbluetooth_device.h>

#include "usbbluetooth_log.h"
#if defined(HAVE_LIBUSB)
#include "libusb/device.h"
#include "libusb/utils.h"
#endif
#include <stdlib.h>

usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_get_device_list(usbbluetooth_device_t ***list_ptr)
{
    usbbluetooth_log_debug("usbbluetooth_get_device_list");

    // Check list parameter
    if (list_ptr == NULL)
        return USBBLUETOOTH_STATUS_ERR_UNK;

    int num_devs = 0;

#if defined(HAVE_LIBUSB)
    // Get a list of USB devices...
    libusb_device **devs_internal_usb;
    int r = libusb_get_device_list(NULL, &devs_internal_usb);
    usbbluetooth_log_debug("libusb_get_device_list[r=%d]", r);
    if (r < LIBUSB_SUCCESS)
        return USBBLUETOOTH_STATUS_ERR_UNK;

    // Count the number of USB Bluetooth devices...
    r = _libusb_count_bluetooth_devices(devs_internal_usb, &num_devs);
    usbbluetooth_log_debug("_count_bluetooth_devices[r=%d, n=%d]", r, num_devs);
    if (r < LIBUSB_SUCCESS)
        return USBBLUETOOTH_STATUS_ERR_UNK;
#endif

    // Create a new list!
    *list_ptr = calloc((size_t)num_devs + 1, sizeof(struct usbbluetooth_device_t *));
    if (*list_ptr == NULL)
        return USBBLUETOOTH_STATUS_ERR_NOMEM;

    // Terminate the list...
    (*list_ptr)[num_devs] = NULL;

    // Get the list
    usbbluetooth_device_t **list = *list_ptr;

#if defined(HAVE_LIBUSB)
    // Now copy devices to the list...
    libusb_device *dev;
    for (int i = 0, pos = 0; (dev = devs_internal_usb[i]) != NULL; i++)
    {
        bool is_bt = false;
        if (_libusb_is_bluetooth_device(dev, &is_bt) == LIBUSB_SUCCESS && is_bt)
            list[pos++] = usbbluetooth_reference_device(_libusb_create_dev(dev));
    }

    // Cleanup...
    libusb_free_device_list(devs_internal_usb, 1);
#endif

    return USBBLUETOOTH_STATUS_OK;
}

void USBBLUETOOTH_CALL usbbluetooth_free_device_list(usbbluetooth_device_t ***list)
{
    // Cannot clean empty list...
    if (list == NULL || *list == NULL)
        return;

    // Iterate each device...
    usbbluetooth_device_t *dev;
    for (int i = 0; (dev = (*list)[i]) != NULL; i++)
        usbbluetooth_unreference_device(&dev);

    // Free the list
    free(*list);

    // Set the pointer to null...
    *list = NULL;
}

usbbluetooth_device_t *USBBLUETOOTH_CALL usbbluetooth_reference_device(usbbluetooth_device_t *dev)
{
    usbbluetooth_log_debug("usbbluetooth_reference_device[dev=%p]\n", dev);
    dev->ref_count++;
    return dev;
}

void USBBLUETOOTH_CALL usbbluetooth_unreference_device(usbbluetooth_device_t **dev_ptr)
{
    if (dev_ptr == NULL || *dev_ptr == NULL)
        return;

    usbbluetooth_device_t *dev = *dev_ptr;
    dev->ref_count--;

    if (dev->ref_count == 0)
        switch (dev->type)
        {
#if defined(HAVE_LIBUSB)
        case USBBLUETOOTH_DEVICE_TYPE_USB:
            _libusb_free_dev(dev_ptr);
            break;
#endif
        default:
            break;
        }
}

void USBBLUETOOTH_CALL usbbluetooth_device_vid_pid(usbbluetooth_device_t *dev, uint16_t *vid, uint16_t *pid)
{
    switch (dev->type)
    {
#if defined(HAVE_LIBUSB)
    case USBBLUETOOTH_DEVICE_TYPE_USB:
        _libusb_vid_pid(dev, vid, pid);
        break;
#endif
    default:
        break;
    }
}

char *USBBLUETOOTH_CALL usbbluetooth_device_manufacturer(usbbluetooth_device_t *dev)
{
    switch (dev->type)
    {
#if defined(HAVE_LIBUSB)
    case USBBLUETOOTH_DEVICE_TYPE_USB:
        return _libusb_device_manufacturer(dev);
#endif
    default:
        return NULL;
    }
}

char *USBBLUETOOTH_CALL usbbluetooth_device_product(usbbluetooth_device_t *dev)
{
    switch (dev->type)
    {
#if defined(HAVE_LIBUSB)
    case USBBLUETOOTH_DEVICE_TYPE_USB:
        return _libusb_device_product(dev);
#endif
    default:
        return NULL;
    }
}

char *USBBLUETOOTH_CALL usbbluetooth_device_serial_num(usbbluetooth_device_t *dev)
{
    switch (dev->type)
    {
#if defined(HAVE_LIBUSB)
    case USBBLUETOOTH_DEVICE_TYPE_USB:
        return _libusb_device_serial_num(dev);
#endif
    default:
        return NULL;
    }
}

char *USBBLUETOOTH_CALL usbbluetooth_device_description(usbbluetooth_device_t *dev)
{
    switch (dev->type)
    {
#if defined(HAVE_LIBUSB)
    case USBBLUETOOTH_DEVICE_TYPE_USB:
        return _libusb_device_description(dev);
#endif
    default:
        return NULL;
    }
}
