# Examples
## devices.c

This example shows how to list all available USB Bluetooth devices detected by the usbbluetooth library.

### Build
```bash
# macOS and Linux
gcc devices.c -o devices $(pkg-config --cflags --libs usbbluetooth)
```

### Common build error

On some systems (especially when installing via Homebrew on macOS), you may encounter an error similar to the following:
```bash
/usr/local/include/usbbluetooth/usbbluetooth.h:4:10: error: 'usbbluetooth_err.h' file not found with <angled> include; use "quotes" instead
    4 | #include <usbbluetooth_err.h>
      |          ^~~~~~~~~~~~~~~~~~~~
      |          "usbbluetooth_err.h"
In file included from devices.c:5:
In file included from /usr/local/include/usbbluetooth/usbbluetooth.h:4:
/usr/local/include/usbbluetooth/usbbluetooth_err.h:4:10: error: 'usbbluetooth_api.h' file not found with <angled> include; use "quotes" instead
    4 | #include <usbbluetooth_api.h>
      |          ^~~~~~~~~~~~~~~~~~~~
      |          "usbbluetooth_api.h"

```
This happens because the usbbluetooth headers are located in a subdirectory that is not automatically added to the compiler include paths.

### Fix

Explicitly add the usbbluetooth include directory using -I:
```bash
gcc devices.c -o devices \
    $(pkg-config --cflags --libs usbbluetooth) \
    -I/opt/homebrew/include/usbbluetooth
```
## Notes

The include path may vary depending on your operating system and installation method.

Before compiling, verify the actual installation path of the headers (for example, using `pkg-config --cflags usbbluetooth` or `brew info usbbluetooth` on macOS).