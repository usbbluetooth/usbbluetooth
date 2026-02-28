# Statically link it in Windows targets
libs_static = target_machine.system() == 'windows' or target_machine.system() == 'cygwin'

# Check for dependencies...
libusb_dep = dependency('libusb-1.0', static : libs_static)
if libusb_dep.found()
  add_project_arguments('-DHAVE_LIBUSB', language : 'c')
endif
libserialport_dep = dependency('libserialport', static : libs_static, required : false)
if libserialport_dep.found()
  add_project_arguments('-DHAVE_LIBSERIALPORT', language : 'c')
endif

# Project library
libusbbluetooth_inc = include_directories('.')
libusbbluetooth_src = files([
  'usbbluetooth_err.c',
  'usbbluetooth_core.c',
  'usbbluetooth_device.c',
  'usbbluetooth_io.c',
  'usbbluetooth_log.c',
  'utils_libusb.c',
  'utils_ser.c',
])
libusbbluetooth_pub_headers = files([
  'usbbluetooth.h',
  'usbbluetooth_err.h',
  'usbbluetooth_api.h',
  'usbbluetooth_core.h',
  'usbbluetooth_device.h',
  'usbbluetooth_io.h',
  'usbbluetooth_log.h'
])
libusbbluetooth_target = library('usbbluetooth',
  sources : libusbbluetooth_src,
  include_directories: libusbbluetooth_inc,
  install: true,
  vs_module_defs : 'usbbluetooth.def',
  dependencies : [libusb_dep, libserialport_dep])

# Header installation
install_headers(libusbbluetooth_pub_headers, subdir : 'usbbluetooth')

# PC file
pkg_mod = import('pkgconfig')
pkg_mod.generate(
  name : 'usbbluetooth',
  description : 'LibUSB based Bluetooth device driver',
  libraries : libusbbluetooth_target,
)

# Library dependency
libusbbluetooth_dep = declare_dependency(
  include_directories: libusbbluetooth_inc,
  link_with : libusbbluetooth_target,
  dependencies : [libusb_dep, libserialport_dep]
)
