/*
 * Copyright 2015-2026 - Geoffrey Brun <geoffrey+git@spekadyon.org>
 *
 * This file is part of libstlseries.
 *
 * libstlseries is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option)
 * any later version.
 *
 * libstlseries is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with libstlseries. If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdio.h>

#include <hidapi/hidapi.h>

#include "stlseries.h"

/*
 * Constants
 */

/* Steel series keyboard vendor id and product id */
#define VENDORID	0x1770
#define PRODUCTID	0xff00


/*
 * Constant strings
 */

/* Colors names */
static char const *stlseries_colors[] = {
	"none",
	"red",
	"orange",
	"yellow",
	"green",
	"sky",
	"blue",
	"purple",
	"white",
	NULL
};

/* Modes */
static char const *stlseries_modes[] = {
	NULL,
	"normal",
	"gaming",
	"breathe",
	"demo",
	"wave",
	NULL
};

/* Zones */
static char const *stlseries_zones[] = {
	NULL,
	"left",
	"center",
	"right",
	NULL
};

/* Color saturation */
static char const *stlseries_saturation[] = {
	"high",
	"medium",
	"low",
	"null",
	NULL
};

/* Default message (invalid) */
static char const stlseries_msg_inval[] = "invalid";


/*
 * Constant to name conversion functions
 */

static char const *stlseries_strcolor(enum StlseriesColor color)
{
	if (color > STLSERIES_COLOR_WHITE) {
		return stlseries_msg_inval;
	} else {
		return stlseries_colors[color];
	}
}

static char const *stlseries_strmode(enum StlseriesMode mode)
{
	if ( (mode <= 0) || (mode > STLSERIES_MODE_WAVE) ) {
		return stlseries_msg_inval;
	} else {
		return stlseries_modes[mode];
	}
}

static char const *stlseries_strzone(enum StlseriesZone zone)
{
	if ( (zone <= 0) || (zone > STLSERIES_ZONE_RIGHT) ) {
		return stlseries_msg_inval;
	} else {
		return stlseries_zones[zone];
	}
}

static char const *stlseries_strsaturation(enum StlseriesSaturation saturation)
{
	if (saturation < 0 || saturation > STLSERIES_SATURATION_NULL) {
		return stlseries_msg_inval;
	} else {
		return stlseries_saturation[saturation];
	}
}


/*
 * Device initialization
 */

STLSERIES stlseries_open(enum StlseriesStatus *status)
{
	hid_device *hidp;

	if (hid_init() == -1) {
		fprintf(stderr, "Unable to initialize hid subsystem: %ls.\n", hid_error(NULL));
		if (status) {
			*status = STLSERIES_EINIT;
		}
		return NULL;
	}

	hidp = hid_open(VENDORID, PRODUCTID, NULL);
	if (hidp == NULL) {
		fprintf(stderr, "Unable to open USB device %04X:%04X: %ls.\n", VENDORID, PRODUCTID, hid_error(NULL));
#ifdef _HIDAPI_LIBUSB_
		fprintf(stderr, "Check /dev/bus/usb/...\n");
#else
		fprintf(stderr, "Check /dev/hidrawXX\n");
#endif
		if (status) {
			*status = STLSERIES_EOPEN;
		}
		return NULL;
	}
	if (status) {
		*status = STLSERIES_OK;
	}
	return hidp;
}


/*
 * Close the device
 */

enum StlseriesStatus stlseries_close(STLSERIES handle)
{
	int ret;

	hid_close(handle);
	ret = hid_exit();

	if (ret == -1) {
		fprintf(stderr, "Unable to close hidapi!\n");
		return STLSERIES_EINIT;
	}

	return STLSERIES_OK;
}


/*
 * Set keyboard LED mode
 */

enum StlseriesStatus stlseries_setmode(STLSERIES handle, enum StlseriesMode mode)
{
	unsigned char buf[8] = {1, 2, 65, 0, 0, 0, 0, 236};

	/* Sanitize */
	if (handle == NULL) {
		fprintf(stderr, "Invalid pointer (null)\n");
		return STLSERIES_EINVAL;
	}
	if (mode == 0 || mode > STLSERIES_MODE_WAVE) {
		fprintf(stderr, "Invalid mode: %d\n", (int)mode);
		return STLSERIES_EINVAL;
	}

	buf[3] = mode;

	if (hid_send_feature_report(handle, buf, 8) == -1) {
		fprintf(stderr, "Unable to change mode (%s): %ls.\n",
			stlseries_strmode(mode), hid_error(handle));
		return STLSERIES_EIO;
	}

	return STLSERIES_OK;
}


/*
 * Set keyboard color.
 */

enum StlseriesStatus stlseries_setcolor(STLSERIES handle, enum StlseriesZone zone, enum StlseriesColor color, enum StlseriesSaturation saturation)
{
	unsigned char buf[8] = {1, 2, 66, 0, 0, 0, 0, 236};

	/* Sanitize */
	if (handle == NULL) {
		fprintf(stderr, "Invalid pointer (null)\n");
		return STLSERIES_EINVAL;
	}
	if ( (zone <= 0) || (zone > STLSERIES_ZONE_RIGHT) ) {
		fprintf(stderr, "Invalid zone: %d\n", (int)zone);
		return STLSERIES_EINVAL;
	}
	if (color < 0 || color > STLSERIES_COLOR_WHITE) {
		fprintf(stderr, "Invalid color: %d\n", (int)color);
		return STLSERIES_EINVAL;
	}
	if (saturation < 0 || saturation > STLSERIES_SATURATION_NULL) {
		fprintf(stderr, "Invalid color saturation value: %d\n", (int)saturation);
		return STLSERIES_EINVAL;
	}

	/* Message build */
	buf[3] = zone;
	buf[4] = color;
	buf[5] = saturation;

	/* Sending message */
	if (hid_send_feature_report(handle, buf, 8) == -1) {
		fprintf(stderr, "Unable to set (%s, %s, %s): %ls.\n", stlseries_strzone(zone),
			stlseries_strcolor(color), stlseries_strsaturation(saturation),
			hid_error(handle));
		return STLSERIES_EIO;
	}

	return 0;
}


/*
 * Set keyboard color in "normal" illumination mode.
 */

enum StlseriesStatus stlseries_setcolor_normal(STLSERIES handle, enum StlseriesZone zone, enum StlseriesColor color, enum StlseriesSaturation saturation)
{
	enum StlseriesStatus ret;

	ret = stlseries_setmode(handle, STLSERIES_MODE_NORMAL);
	if (ret != STLSERIES_OK) {
		return ret;
	}

	return stlseries_setcolor(handle, zone, color, saturation);
}

