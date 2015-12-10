
/*
 *  pci-db.c
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
 * $Id: pci-db.c,v 1.3 2002/12/02 04:16:28 fredlie Exp $
 */


#include <system.h>

struct pci_device_info
{
   unsigned short device;
   unsigned short seen;
   const char *name;
};

struct pci_vendor_info
{
   unsigned short vendor;
   unsigned short seen;
   const char *name;
   struct pci_device_info *devices;
};

#define VENDOR(a,b)        static char __init_data__ __vendor_##a[] = b;
#define DEVICE(a,b,c)      static char __init_data__ __device_##a##b[] = c;
#define ENDVENDOR()
#include "pci-dev.h"

#define VENDOR(a,b)        static struct pci_device_info __init_data__ __devices_##a[] = {
#define DEVICE(a,b,c)      {0x##b, 0, __device_##a##b},
#define ENDVENDOR()        };
#include "pci-dev.h"

static struct pci_vendor_info __init_data__ pci_vendor_list[] = {
#define VENDOR(a,b)        {0x##a, sizeof(__devices_##a) / sizeof (struct pci_device_info), __vendor_##a, __devices_##a},
#define DEVICE(a,b,c)
#define ENDVENDOR()
#include "pci-dev.h"
};

