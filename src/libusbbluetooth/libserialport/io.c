#include "io.h"

#include <libserialport.h>

usbbluetooth_status_t _serial_open(usbbluetooth_device_t *dev)
{
    enum sp_return err = sp_open(dev->device, SP_MODE_READ_WRITE);
    if (err < SP_OK)
        return USBBLUETOOTH_STATUS_ERR_UNK;
    return USBBLUETOOTH_STATUS_OK;
}

void _serial_close(usbbluetooth_device_t *dev)
{
    sp_close(dev->device);
}

usbbluetooth_status_t _serial_write(usbbluetooth_device_t *dev, uint8_t *data, uint16_t size)
{
    enum sp_return err = sp_blocking_write(dev->device, data, size, 2000);
    if (err < SP_OK || err < size)
        return USBBLUETOOTH_STATUS_ERR_UNK;
    return USBBLUETOOTH_STATUS_OK;
}

usbbluetooth_status_t _serial_read(usbbluetooth_device_t *dev, uint8_t *data, uint16_t *size)
{
    enum sp_return err = sp_nonblocking_read(dev->device, data, *size);
    if (err < SP_OK)
        return USBBLUETOOTH_STATUS_ERR_UNK;
    *size = err;
    return USBBLUETOOTH_STATUS_OK;
}
