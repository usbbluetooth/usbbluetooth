#include "usbbluetooth_io.h"

#include "usbbluetooth_log.h"

#if HAVE_LIBUSB
#include "libusb/io.h"
#endif

usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_open(usbbluetooth_device_t *dev)
{
    switch (dev->type)
    {
#if defined(HAVE_LIBUSB)
    case USBBLUETOOTH_DEVICE_TYPE_USB:
        return _libusb_open(dev);
#endif
    default:
        return USBBLUETOOTH_STATUS_ERR_UNK;
    }
}

void USBBLUETOOTH_CALL usbbluetooth_close(usbbluetooth_device_t *dev)
{
    switch (dev->type)
    {
#if defined(HAVE_LIBUSB)
    case USBBLUETOOTH_DEVICE_TYPE_USB:
        _libusb_close(dev);
        break;
#endif
    default:
        break;
    }
}

usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_write(usbbluetooth_device_t *dev, uint8_t *data, uint16_t size)
{
    switch (dev->type)
    {
#if defined(HAVE_LIBUSB)
    case USBBLUETOOTH_DEVICE_TYPE_USB:
        return _libusb_write(dev, data, size);
#endif
    default:
        return USBBLUETOOTH_STATUS_ERR_UNK;
    }
}

usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_read(usbbluetooth_device_t *dev, uint8_t *data, uint16_t *size)
{
    switch (dev->type)
    {
#if defined(HAVE_LIBUSB)
    case USBBLUETOOTH_DEVICE_TYPE_USB:
        return _libusb_read(dev, data, size);
#endif
    default:
        return USBBLUETOOTH_STATUS_ERR_UNK;
    }
}
