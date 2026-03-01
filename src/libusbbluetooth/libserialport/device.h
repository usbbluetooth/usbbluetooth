#ifndef _H_LIBSERIALPORT_DEVICE_
#define _H_LIBSERIALPORT_DEVICE_

#include "../usbbluetooth_device.h"
#include <libserialport.h>

int _serial_count_bluetooth_devices(struct sp_port **list, int *num);
usbbluetooth_device_t *_serial_create_dev(struct sp_port *dev);
void _serial_free_dev(usbbluetooth_device_t **dev_ptr);

void _serial_vid_pid(usbbluetooth_device_t *dev, uint16_t *vid, uint16_t *pid);
char *_serial_device_manufacturer(usbbluetooth_device_t *dev);
char *_serial_device_product(usbbluetooth_device_t *dev);
char *_serial_device_serial_num(usbbluetooth_device_t *dev);
char *_serial_device_description(usbbluetooth_device_t *dev);

#endif
