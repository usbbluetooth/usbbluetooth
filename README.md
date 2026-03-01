# USB Bluetooth

[![Build](https://github.com/usbbluetooth/usbbluetooth/actions/workflows/build.yml/badge.svg)](https://github.com/usbbluetooth/usbbluetooth/actions/workflows/build.yml)
[![CodeQL](https://github.com/usbbluetooth/usbbluetooth/actions/workflows/codeql.yml/badge.svg)](https://github.com/usbbluetooth/usbbluetooth/actions/workflows/codeql.yml)

LibUSB based Bluetooth device driver. Take full control of your USB Bluetooth devices using C!

For general documentation about the project, please visit [usbbluetooth.github.io](https://usbbluetooth.github.io).

For a Python version of this library, check out [UsbBluetooth for Python](https://github.com/usbbluetooth/usbbluetooth-python) or [Scapy UsbBluetooth](https://github.com/usbbluetooth/scapy-usbbluetooth) for direct integration with Scapy.

For a C# version of this library, check out [UsbBluetooth for C#](https://github.com/usbbluetooth/usbbluetooth-csharp).

## Usage

This project consist of a C library that allows you to enumerate and control USB Bluetooth devices.

There is also an example binary compiled to test the library in your platform, it is called `usbbt`.
The `usbbt` executable allows you to list available devices and to send them a reset command.

Check out the [usage document](Usage.md) for more information.

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

### MacOs
In MacOs you may have to install `fmt` and `libusb`. For more information about troubleshooting read the [usage document](Usage.md) for more information.

## Contributors

Special thanks to [Tarlogic Security](https://github.com/TarlogicSecurity/) for sponsoring part of the development of this project via paid work hours.
