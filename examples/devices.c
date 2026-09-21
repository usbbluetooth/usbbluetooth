/*
Author: Kevin Leon
Date: 24/12/2025
*/
#include <usbbluetooth/usbbluetooth.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  int ret = 0;

  // Initialize the library...
  usbbluetooth_status_t r = usbbluetooth_init();
  if (r < 0)
  {
      fprintf(stderr, "Could not initialize usbbluetooth (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
      ret = -1;
      return ret;
  }

  // List all available devices...
  usbbluetooth_device_t **devs = NULL;
  r = usbbluetooth_get_device_list(&devs);
  if (r < 0)
  {
      fprintf(stderr, "Could get a device list (r=%d, s=%s)\n", (int)r, usbbluetooth_status_name(r));
      ret = -1;
      return ret;
  }

  // Show device list
  printf("[*] Bluetooth USB devices:\n");

  for (int i = 0; devs[i] != NULL; i++){
    char *desc = usbbluetooth_device_description(devs[i]);
    
    if (desc){
      printf("[%d] %s\n", i, desc);
      free(desc);
    }
  }

  // Free and liberate
  usbbluetooth_free_device_list(&devs);
  usbbluetooth_exit();
  return ret;
}