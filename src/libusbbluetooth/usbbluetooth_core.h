#ifndef _H_USBBLUETOOTH_CORE_
#define _H_USBBLUETOOTH_CORE_

#include "usbbluetooth_api.h"
#include "usbbluetooth_err.h"

/**
 * Initialize USB Bluetooth library.
 *
 * This function must be called before any other call to the library.
 */
usbbluetooth_status_t USBBLUETOOTH_CALL usbbluetooth_init();

/**
 * Close any open USB context and cleanup.
 */
void USBBLUETOOTH_CALL usbbluetooth_exit();

#endif
