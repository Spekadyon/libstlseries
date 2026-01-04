project('libstlseries',
  'c',
  default_options: ['c_std=c99'])

pkg = import('pkgconfig')

hidapi_dep = dependency('hidapi-libusb')

src = ['lib.c']
headers = ['stlseries.h']

lib = library('stlseries', src,
  version: '0.0.2',
  soversion: '0',
  dependencies: [ hidapi_dep ],
  install: true)

install_headers(headers)

pkg.generate(lib)
