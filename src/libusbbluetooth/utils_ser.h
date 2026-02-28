#ifndef _H_UTILS_
#define _H_UTILS_

#include <libserialport.h>
#include <stdbool.h>

int _ser_is_bluetooth_device(struct sp_port *dev, bool *is_bt);

#endif
