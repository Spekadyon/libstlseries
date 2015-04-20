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

#define STLSERIES_EINIT		1	/* Initialisation routines failure */
#define STLSERIES_EOPEN		2	/* Unable to open HID device */
#define STLSERIES_EINVAL	3	/* Invalid function parameter */
#define STLSERIES_EIO		4	/* Input/Output error */

/* LED colors */

#define STLSERIES_COLOR_NONE	0U
#define STLSERIES_COLOR_RED	1U
#define STLSERIES_COLOR_ORANGE	2U
#define STLSERIES_COLOR_YELLOW	3U
#define STLSERIES_COLOR_GREEN	4U
#define STLSERIES_COLOR_SKY	5U
#define STLSERIES_COLOR_BLUE	6U
#define STLSERIES_COLOR_PURPLE	7U
#define STLSERIES_COLOR_WHITE	8U

/* Color saturation */

#define STLSERIES_SATURATION_HIGH	0U
#define STLSERIES_SATURATION_MED	1U
#define STLSERIES_SATURATION_LOW	2U
#define STLSERIES_SATURATION_NULL	3U

/* Keyboard zone */

#define STLSERIES_ZONE_LEFT	1U
#define STLSERIES_ZONE_CENTER	2U
#define STLSERIES_ZONE_RIGHT	3U

/* Keyboard mode */

#define STLSERIES_MODE_NORMAL	1U
#define STLSERIES_MODE_GAMING	2U
#define STLSERIES_MODE_BREATHE	3U
#define STLSERIES_MODE_DEMO	4U
#define STLSERIES_MODE_WAVE	5U


/*
 * Functions
 */

int stlseries_open(STLSERIES *handle);
void stlseries_close(void);
int stlseries_setmode(STLSERIES handle, unsigned char mode);
int stlseries_setcolor(STLSERIES handle, unsigned char zone, unsigned char color, unsigned char saturation);
int stlseries_setcolor_normal(STLSERIES handle, unsigned char zone, unsigned char color, unsigned char saturation);

#ifdef __cplusplus
}
#endif

#endif /* _STLSERIES_H */

