# Documentation

This project consist of a library that allows you to enumerate and control USB Bluetooth devices.

There is also an example binary compiled to test the library in your platform, it is called `usbbt`.
The `usbbt` executable allows you to list available devices and to send them a reset command.


## Plaform quirks

### Windows

In Windows you may have to install WinUSB driver in your device using Zadig. Otherwise, UsbBluetooth will detect your device but it may not be able to take control of your device.


### Linux

Your Linux user must have permissions to access USB hardware. Here are several options to ensure access:

- **Run as root**: Execute the application with elevated privileges using `sudo`. Note that this may not be ideal for security reasons.

- **Add user to a group**: Add your user to the `plugdev`, `usb` or `uucp` group (depending on your distribution). Remeber to reboot or log out and log back in for the changes to take effect. For example:
  ```
  sudo usermod -a -G plugdev $USER
  ```
  

- **Create a udev rule**: Create a custom udev rule to automatically set permissions for USB Bluetooth devices. Create a file like `/etc/udev/rules.d/99-usbbluetooth.rules` with content similar to:
  ```
  SUBSYSTEM=="usb", ATTR{idVendor}=="your_vendor_id", ATTR{idProduct}=="your_product_id", MODE="0666"
  ```
  Replace `your_vendor_id` and `your_product_id` with the actual vendor and product IDs of your device (you can find these using `lsusb`). Then reload udev rules with `sudo udevadm control --reload-rules && sudo udevadm trigger`.


## Usage

This library has been programmed in C. You can find information on how to compile, install and use it in the [C API document](API_C.md).

You can also find documentation for the [Python API](API_Python.md) or the [C# API](API_CSharp.md).


## Architecture

You may find more information about the design and architecture of this software in the [Architecture](Architecture.md) document.
