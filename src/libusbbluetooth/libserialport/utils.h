#ifndef _H_LIBSERIALPORT_UTILS_
#define _H_LIBSERIALPORT_UTILS_

#include <libserialport.h>
#include <stdbool.h>

int _serial_is_bluetooth_device(struct sp_port *dev, bool *is_bt);

#endif
