# libstlseries

steelseries keyboard LED color configuration


## Description

Plain C re-implementation of *msi-keyboard* and *stseries-light*. Used to set
the backlight color of steelseries keyboards found on MSI notebooks.


## References

* [msi-keyboard](https://github.com/wearefractal/msi-keyboard)
* [stseries-light](https://github.com/blackwolf-70/stseries-light)
* [HIDAPI CMake find module](https://github.com/rpavlik/cmake-modules)


## Dependencies

* [HID API](http://www.signal11.us/oss/hidapi/)
* CMake (build)


## Build

To build the library on Linux:

1. mkdir build && cd build
2. cmake
3. make
4. **(as root)** make install
5. **(optional)** install `udev/99-stlseries.rules` in /etc/udev/rules.d (grant
   access to the keyboard to users in the *plugdev* group)

A simple, quick & dirty GUI is available in stlseries_gui/. Qt 4 or 5 is
required to build it (just type `qmake` and `make`).


## Usage

1. Open the usb device using stlseries_open()
2. Change the mode and/or color using stlseries_setcolor\*()
3. Close the device with stlseries_close()

Except stlseries_close() which returns nothing, all functions return 0 on
success, and a positive value on error.


## Example

```C
#include <stdio.h>
#include <stdlib.h>
#include <stlseries.h>

int main(void)
{
	STLSERIES handle;

	if (stlseries_open(&handle)) {
		fprintf(stderr, "Unable to open SteelSeries keyboard.\n");
		exit(EXIT_FAILURE);
	}

	if (stlseries_setcolor_normal(handle, STLSERIES_ZONE_CENTER,
			STLSERIES_COLOR_RED, STLSERIES_SATURATION_HIGH)) {
		fprint(stderr, "Unable to set color.\n");
		exit(EXIT_FAILURE);
	}

	stlseries_close();

	return EXIT_SUCCESS;

}

```

## TODO
* command line interface

