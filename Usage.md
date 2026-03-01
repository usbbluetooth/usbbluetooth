# API for C

The `usbbluetooth` library can be used via a C API.

The C api can be used by importing the corresponding C library header.
You must also link against the library or use a shared library version. For this, you need a binary library file compiled for your platform.


## Installing

The library is distributed y binary format available in https://github.com/antoniovazquezblanco/usbbluetooth/releases.
The library may also be available for installation via your favourite package manager.

### Macos
If you will use `brew` as your package manager you need to install first `fmt` and `libusb`.

```bash
brew install fmt libusb
meson setup build --wipe --wrap-mode=forcefallback
cd build
sudo meson install
```

The command `meson setup build --wipe --wrap-mode=forcefallback` is to ensure non-cached packages.

In case an error with the `ccache` and versions, run the `brew reinstall ccache`.
```bash
# Example error
[1/5] Compiling C object src/usbbt/usbbt.p/main.c.o
FAILED: [code=134] src/usbbt/usbbt.p/main.c.o 
ccache cc -Isrc/usbbt/usbbt.p -Isrc/usbbt -I../src/usbbt -Isrc/libusbbluetooth -I../src/libusbbluetooth -I../subprojects/cwalk-1.2.9/include -I/opt/homebrew/Cellar/libusb/1.0.29/include/libusb-1.0 -fdiagnostics-color=always -Wall -Winvalid-pch -O0 -g -MD -MQ src/usbbt/usbbt.p/main.c.o -MF src/usbbt/usbbt.p/main.c.o.d -o src/usbbt/usbbt.p/main.c.o -c ../src/usbbt/main.c
dyld[32146]: Library not loaded: /opt/homebrew/opt/fmt/lib/libfmt.11.dylib
  Referenced from: <3FE95377-F54E-353D-9397-74E23EA42650> /opt/homebrew/Cellar/ccache/4.11.3_1/bin/ccache
  Reason: tried: '/opt/homebrew/opt/fmt/lib/libfmt.11.dylib' (no such file), '/System/Volumes/Preboot/Cryptexes/OS/opt/homebrew/opt/fmt/lib/libfmt.11.dylib' (no such file), '/opt/homebrew/opt/fmt/lib/libfmt.11.dylib' (no such file), '/opt/homebrew/Cellar/fmt/12.1.0/lib/libfmt.11.dylib' (no such file), '/System/Volumes/Preboot/Cryptexes/OS/opt/homebrew/Cellar/fmt/12.1.0/lib/libfmt.11.dylib' (no such file), '/opt/homebrew/Cellar/fmt/12.1.0/lib/libfmt.11.dylib' (no such file)
[3/5] Linking target src/libusbbluetooth/libusbbluetooth.dylib
ninja: build stopped: subcommand failed.  
```

You can also choose to compile it for you platform.
To compile the project just follow the common steps to compile using meson.

```bash
meson setup build
meson compile -C build
cd build
sudo meson install
```


## Usage

The following code is an example on how this library can be used:
```C
#include <usbbluetooth.h>

int main(int argc, char **argv) {
    int ret = 0;

    // Initialize the library...
    usbbluetooth_status_t r = usbbluetooth_init();
    if (r < 0)
    {
        fprintf(stderr, "Could not initialize usbbluetooth (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
        ret = -1;
        goto exit;
    }

    // List all available devices...
    usbbluetooth_device_t **devs = NULL;
    r = usbbluetooth_get_device_list(&devs);
    if (r < 0)
    {
        fprintf(stderr, "Could get a device list (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
        ret = -1;
        goto exit;
    }

    // Get the first one...
    usbbluetooth_device_t *dev = devs[0];

    // Open the device for communication...
    printf("Opening %04x:%04x @ 0x%p\n", dev->vendor_id, dev->product_id, dev);
    r = usbbluetooth_open(dev);
    if (r != USBBLUETOOTH_STATUS_OK)
    {
        fprintf(stderr, "Could not open device (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
        ret = -1;
        goto exit;
    }

    // Send encoded HCI reset
    r = usbbluetooth_write(dev, (uint8_t *)"\x01\x03\x0c\x00", 4);
    if (r != USBBLUETOOTH_STATUS_OK)
    {
        fprintf(stderr, "Could not send command (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
        ret = -1;
        goto exit;
    }

    // Await a response...
    uint8_t buf[BUFFSIZE];
    memset(buf, 0, BUFFSIZE);
    uint16_t bufsize = BUFFSIZE;
    r = usbbluetooth_read(dev, buf, &bufsize);
    if (r != USBBLUETOOTH_STATUS_OK)
    {
        fprintf(stderr, "Could not read command response (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
        ret = -1;
        goto exit;
    }

    // Verify response...
    if (buf[6] != 0)
    {
        fprintf(stderr, "Command response status not OK! (status=%d)\n", buf[6]);
        ret = -1;
        goto exit;
    }
    printf("Device reset OK!\n");

exit:
    usbbluetooth_close(dev);
    usbbluetooth_free_device_list(&devs);
    usbbluetooth_exit();

    return ret;
}
```
