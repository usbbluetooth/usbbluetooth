#ifndef _H_LIBUSB_IO_
#define _H_LIBUSB_IO_

#include "../usbbluetooth_device.h"

usbbluetooth_status_t  _libusb_open(usbbluetooth_device_t *dev);
void _libusb_close(usbbluetooth_device_t *dev);
usbbluetooth_status_t _libusb_write(usbbluetooth_device_t *dev, uint8_t *data, uint16_t size);
usbbluetooth_status_t _libusb_read(usbbluetooth_device_t *dev, uint8_t *data, uint16_t *size);

#endif
