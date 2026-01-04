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

#ifndef _STLSERIES_H
#define _STLSERIES_H

#include <hidapi/hidapi.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 * Library type definitions
 */

typedef hid_device* STLSERIES;

/*
 * Constants
 */

/* Error numbers */

enum StlseriesStatus {
	STLSERIES_OK = 0,       /* No error */
	STLSERIES_EINIT,        /* Initialisation routines failure */
	STLSERIES_EOPEN,        /* Unable to open HID device */
	STLSERIES_EINVAL,       /* Invalid function parameter */
	STLSERIES_EIO           /* Input/Output error */
};

/* LED colors */

enum StlseriesColor {
	STLSERIES_COLOR_NONE    = 0U,
	STLSERIES_COLOR_RED     = 1U,
	STLSERIES_COLOR_ORANGE  = 2U,
	STLSERIES_COLOR_YELLOW  = 3U,
	STLSERIES_COLOR_GREEN   = 4U,
	STLSERIES_COLOR_SKY     = 5U,
	STLSERIES_COLOR_BLUE    = 6U,
	STLSERIES_COLOR_PURPLE  = 7U,
	STLSERIES_COLOR_WHITE   = 8U
};

/* Color saturation */

enum StlseriesSaturation {
	STLSERIES_SATURATION_HIGH   = 0U,
	STLSERIES_SATURATION_MED    = 1U,
	STLSERIES_SATURATION_LOW    = 2U,
	STLSERIES_SATURATION_NULL   = 3U
};

/* Keyboard zone */

enum StlseriesZone {
	STLSERIES_ZONE_LEFT     = 1U,
	STLSERIES_ZONE_CENTER   = 2U,
	STLSERIES_ZONE_RIGHT    = 3U,
};

/* Keyboard mode */

enum StlseriesMode {
	STLSERIES_MODE_NORMAL   = 1U,
	STLSERIES_MODE_GAMING   = 2U,
	STLSERIES_MODE_BREATHE  = 3U,
	STLSERIES_MODE_DEMO     = 4U,
	STLSERIES_MODE_WAVE     = 5U,
};


/*
 * Functions
 */

STLSERIES stlseries_open(enum StlseriesStatus *status);
void stlseries_close(STLSERIES handle);
enum StlseriesStatus stlseries_setmode(STLSERIES handle, enum StlseriesMode mode);
enum StlseriesStatus stlseries_setcolor(STLSERIES handle, enum StlseriesZone zone, enum StlseriesColor color, enum StlseriesSaturation saturation);
enum StlseriesStatus stlseries_setcolor_normal(STLSERIES handle, enum StlseriesZone zone, enum StlseriesColor color, enum StlseriesSaturation saturation);

#ifdef __cplusplus
}
#endif

#endif /* _STLSERIES_H */

