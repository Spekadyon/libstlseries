# libstlseries

steelseries keyboard LED color configuration


## Description

Plain C re-implementation of *msi-keyboard* and *stseries-light*. Used to set
the backlight color of steelseries keyboards found on some MSI notebooks (at
least GE72 Apache).
The keyboard is identified by `lsusb` as follows:
```
ID 1770:ff00 MSI steel series rgb keyboard
```


## References

* [msi-keyboard](https://github.com/wearefractal/msi-keyboard)
* [stseries-light](https://github.com/blackwolf-70/stseries-light)


## Dependencies

* [HIDAPI](https://github.com/libusb/hidapi)
* meson (build)


## Build

To build the library on Linux:

1. clone this repository, cd to it (i.e. `git clone https://github.com/Spekadyon/libstlseries.git && cd libstlseries`)
1. configure the build: `meson setup build/ --prefix=/usr/local/ --buildtype=release` (adjust prefix as needed)
1. compile the project: `meson compile -C build/`
1. install the library, header and pkgconfig file: `meson install -C build/`
1. **(optional)** install `udev/99-stlseries.rules` in /etc/udev/rules.d (grant
   access to the keyboard to users in the *plugdev* group)


## Usage

1. Open the usb device using stlseries_open()
2. Change the mode and/or color using stlseries_setcolor\*()
3. Close the device with stlseries_close()


## Example

```c
#include <stdio.h>
#include <stdlib.h>
#include <stlseries.h>

int main(void)
{
	STLSERIES handle;
    enum StlseriesStatus status;

	handle = stlseries_open(&status);

    if (handle == NULL) {
		fprintf(stderr, "Unable to open SteelSeries keyboard: %d.\n", (int)status);
		exit(EXIT_FAILURE);
	}

	if (stlseries_setcolor_normal(handle, STLSERIES_ZONE_CENTER,
			STLSERIES_COLOR_RED, STLSERIES_SATURATION_HIGH) != STLSERIES_OK) {
		fprint(stderr, "Unable to set color.\n");
		exit(EXIT_FAILURE);
	}

	stlseries_close();

	return EXIT_SUCCESS;

}

```

## TODO
* command line interface
* documentation
* allow to disable logging
