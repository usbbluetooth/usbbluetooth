#include "utils.h"

static int _serial_native_is_bluetooth_device(struct sp_port *dev, bool *is_bt)
{
    // I have not yet seen any HCI Bluetooth device over serial over Bluetooth...
    *is_bt = false;
    return SP_OK;
}

static int _serial_usb_is_bluetooth_device(struct sp_port *dev, bool *is_bt)
{
    /* TODO: Implement
    int usb_vid, usb_pid;
    sp_get_port_usb_vid_pid(dev->device, &usb_vid, &usb_pid);
    sp_get_port_usb_manufacturer(dev->device)
    sp_get_port_usb_product(dev->device)
    sp_get_port_usb_serial(dev->device)
    sp_get_port_description(dev->device)
    */
    *is_bt = false;
    return SP_OK;
}

static int _serial_bluetooth_is_bluetooth_device(struct sp_port *dev, bool *is_bt)
{
    // TODO: Implement
    *is_bt = false;
    return SP_OK;
}

int _serial_is_bluetooth_device(struct sp_port *dev, bool *is_bt)
{
    // Evaluate based on the serial port transport...
    switch (sp_get_port_transport(dev))
    {
    case SP_TRANSPORT_NATIVE:
        return _serial_native_is_bluetooth_device(dev, is_bt);
    case SP_TRANSPORT_USB:
        return _serial_usb_is_bluetooth_device(dev, is_bt);
    case SP_TRANSPORT_BLUETOOTH:
        return _serial_bluetooth_is_bluetooth_device(dev, is_bt);
    default:
        *is_bt = false;
        return SP_OK;
    }
}
