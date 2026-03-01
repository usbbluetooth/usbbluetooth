#ifndef _H_LIBSERIALPORT_IO_
#define _H_LIBSERIALPORT_IO_

#include "../usbbluetooth_device.h"

usbbluetooth_status_t _serial_open(usbbluetooth_device_t *dev);
void _serial_close(usbbluetooth_device_t *dev);
usbbluetooth_status_t _serial_write(usbbluetooth_device_t *dev, uint8_t *data, uint16_t size);
usbbluetooth_status_t _serial_read(usbbluetooth_device_t *dev, uint8_t *data, uint16_t *size);

#endif
