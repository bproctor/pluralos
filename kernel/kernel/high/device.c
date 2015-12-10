
/*
 *  device.c
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * $Id: device.c,v 1.5 2002/12/06 13:27:53 fredlie Exp $
 */

#include <sys/types.h>
#include <sys/errno.h>
#include <device.h>

ulong DeviceCreate (void)
{
   return (ENOSYS);
}

ulong DeviceDestroy (void)
{
   return (ENOSYS);
}

ulong DeviceInit (void)
{
   return (ENOSYS);
}

ulong DeviceOp (void)
{
   return (ENOSYS);
}

ulong DeviceStat (void)
{
   return (ENOSYS);
}