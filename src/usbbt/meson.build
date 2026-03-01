argtable_dep = dependency('argtable3', default_options: ['default_library=static'])
cwalk_dep = dependency('cwalk', default_options: ['default_library=static'])

usbbt_src = files([
  'main.c',
  'cmd_list.c',
  'cmd_reset.c',
])

executable('usbbt',
  sources : usbbt_src,
  dependencies : [
    libusbbluetooth_dep,
    argtable_dep,
    cwalk_dep
  ],
  install: true
)
