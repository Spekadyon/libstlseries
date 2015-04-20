/*
 * Copyright 2015 - Geoffrey Brun <geoffrey+git@spekadyon.org>
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
const char *stlseries_colors[] = {
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
const char *stlseries_modes[] = {
	NULL,
	"normal",
	"gaming",
	"breathe",
	"demo",
	"wave",
	NULL
};

/* Zones */
const char *stlseries_zones[] = {
	NULL,
	"left",
	"center",
	"right",
	NULL
};

/* Color saturation */
const char *stlseries_saturation[] = {
	"high",
	"medium",
	"low",
	"null",
	NULL
};

/* Default message (invalid) */
const char stlseries_msg_inval[] = "invalid";


/*
 * Constant to name conversion functions
 */

const char *stlseries_strcolor(unsigned char color)
{
	if (color > STLSERIES_COLOR_WHITE)
		return stlseries_msg_inval;
	else
		return stlseries_colors[color];
}

const char *stlseries_strmode(unsigned char mode)
{
	if ( (mode == 0) || (mode > STLSERIES_MODE_WAVE) )
		return stlseries_msg_inval;
	else
		return stlseries_modes[mode];
}

const char *stlseries_strzone(unsigned char zone)
{
	if ( (zone == 0) || (zone > STLSERIES_ZONE_RIGHT) )
		return stlseries_msg_inval;
	else
		return stlseries_zones[zone];
}

const char *stlseries_strsaturation(unsigned char saturation)
{
	if (saturation > STLSERIES_SATURATION_NULL)
		return stlseries_msg_inval;
	else
		return stlseries_saturation[saturation];
}


/*
 * Device initialization
 */

int stlseries_open(STLSERIES *handle)
{
	hid_device *hidp;

	if (handle == NULL)
		return STLSERIES_EINVAL;

	if (hid_init() == -1) {
		fprintf(stderr, "Unable to initialize hid subsystem.\n");
		return STLSERIES_EINIT;
	}

	hidp = hid_open(VENDORID, PRODUCTID, NULL);
	if (hidp == NULL) {
		fprintf(stderr, "Unable to open USB device %04X:%04X. You may try to check the permissions of "
				"this device. ", VENDORID, PRODUCTID);
#ifdef _HIDAPI_LIBUSB_
		fprintf(stderr, "Check /dev/bus/usb/...\n");
#else
		fprintf(stderr, "Check /dev/hidrawXX\n");
#endif
		return STLSERIES_EOPEN;
	}
	*handle = hidp;
	return 0;
}


/*
 * Close the device
 */

void stlseries_close(void)
{
	if (hid_exit() == -1) {
		fprintf(stderr, "Unable to close hidapi!\n");
	}
}


/*
 * Set keyboard LED mode
 */

int stlseries_setmode(STLSERIES handle, unsigned char mode)
{
	unsigned char buf[8] = {1, 2, 65, 0, 0, 0, 0, 236};

	/* Sanitize */
	if (handle == NULL) {
		fprintf(stderr, "Invalid pointer (null)\n");
		return STLSERIES_EINVAL;
	}
	if (mode == 0 || mode > STLSERIES_MODE_WAVE) {
		fprintf(stderr, "Invalid mode: %hhu\n", mode);
		return STLSERIES_EINVAL;
	}

	buf[3] = mode;

	if (hid_send_feature_report(handle, buf, 8) == -1) {
		fprintf(stderr, "Unable to change mode (%s)\n", stlseries_strmode(mode));
		return STLSERIES_EIO;
	}

	return 0;
}


/*
 * Set keyboard color.
 */

int stlseries_setcolor(STLSERIES handle, unsigned char zone, unsigned char color, unsigned char saturation)
{
	unsigned char buf[8] = {1, 2, 66, 0, 0, 0, 0, 236};

	/* Sanitize */
	if (handle == NULL) {
		fprintf(stderr, "Invalid pointer (null)\n");
		return STLSERIES_EINVAL;
	}
	if ( (zone == 0) || (zone > STLSERIES_ZONE_RIGHT) ) {
		fprintf(stderr, "Invalid zone: %hhu\n", zone);
		return STLSERIES_EINVAL;
	}
	if (color > STLSERIES_COLOR_WHITE) {
		fprintf(stderr, "Invalid color: %hhu\n", color);
		return STLSERIES_EINVAL;
	}
	if (saturation > STLSERIES_SATURATION_NULL) {
		fprintf(stderr, "Invalid color saturation value: %hhu\n", saturation);
		return STLSERIES_EINVAL;
	}

	/* Message build */
	buf[3] = zone;
	buf[4] = color;
	buf[5] = saturation;

	/* Sending message */
	if (hid_send_feature_report(handle, buf, 8) == -1) {
		fprintf(stderr, "Unable to set (%s, %s, %s)\n", stlseries_strzone(zone),
				stlseries_strcolor(color), stlseries_strsaturation(saturation));
		return STLSERIES_EIO;
	}

	return 0;
}


/*
 * Set keyboard color in "normal" illumination mode.
 */

int stlseries_setcolor_normal(STLSERIES handle, unsigned char zone, unsigned char color, unsigned char saturation)
{
	int ret;

	ret = stlseries_setmode(handle, STLSERIES_MODE_NORMAL);
	if (ret)
		return ret;

	ret = stlseries_setcolor(handle, zone, color, saturation);
	if (ret)
		return ret;

	return 0;
}

