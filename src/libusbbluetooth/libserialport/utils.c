#include "utils.h"

int _ser_is_bluetooth_device(struct sp_port *dev, bool *is_bt)
{
    // Any serial device will be treated as a potential Bluetooth device...
    *is_bt = true;
    return SP_OK;
}
