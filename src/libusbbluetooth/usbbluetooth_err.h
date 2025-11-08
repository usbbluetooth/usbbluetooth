#ifndef _H_USBBLUETOOTH_ERR_
#define _H_USBBLUETOOTH_ERR_

#include <usbbluetooth_api.h>

/**
 * Error code list.
 */
typedef enum
{
    USBBLUETOOTH_STATUS_OK = 0,
    USBBLUETOOTH_STATUS_ERR_UNK = -1,
    USBBLUETOOTH_STATUS_ERR_NOMEM = -2,
    USBBLUETOOTH_STATUS_ERR_DEVICE_CLOSED = -3,
    USBBLUETOOTH_STATUS_WRONG_DRIVER = -4,
} usbbluetooth_status_t;

/**
 * Return a descriptive string from an error number.
 */
const char * USBBLUETOOTH_CALL usbbluetooth_status_name(usbbluetooth_status_t status);

#endif