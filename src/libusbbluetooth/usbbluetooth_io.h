#ifndef _H_USBBLUETOOTH_IO_
#define _H_USBBLUETOOTH_IO_

#include "usbbluetooth_api.h"
#include "usbbluetooth_device.h"
#include <stdint.h>

/**
 * Claim a device to be able to interact with it.
 */
usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_open(usbbluetooth_device_t *dev);

/**
 * Close the device and let others interact with it.
 */
void USBBLUETOOTH_CALL usbbluetooth_close(usbbluetooth_device_t *dev);

/**
 * Write HCI to a device.
 */
usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_write(usbbluetooth_device_t *dev, uint8_t *data, uint16_t size);

/**
 * Read HCI from a device.
 */
usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_read(usbbluetooth_device_t *dev, uint8_t *data, uint16_t *size);

#endif
