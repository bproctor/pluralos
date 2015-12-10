
/*
 *  device.h
 *  Copyright (c) 2001-2002 Brad Proctor
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * $Id: device.h,v 1.4 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __DEVICE_H__
#define __DEVICE_H__

#ifndef __SYS_TYPES_H__
#include <sys/types.h>
#endif

typedef struct DeviceOps
{
   ulong (*open)(void);
   ulong (*close)(void);
   ulong (*read)(void);
   ulong (*write)(void);
   ulong (*seek)(void);
   ulong (*flush)(void);
   ulong (*lock)(void);
   ulong (*ioctl)(void);
   ulong (*sync)(void);
} DeviceOps;

typedef struct Device
{
   ulong (*init)(void);
   ulong (*op)(ulong);
   ulong (*stat)(ulong);
} Device;

#endif /* __DEVICE_H__ */
