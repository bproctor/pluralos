
/*
 *  smp.h
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
 * $Id: smp.h,v 1.2 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __SMP_H__
#define __SMP_H__

#define SMP_MAGIC    ('_' | ('M' << 8) | ('P' << 16) | ('_' << 24))

#define CPU_STEPPING_MASK     0x000F
#define CPU_MODEL_MASK        0x00F0
#define CPU_FAMILY_MASK       0x0F00

#define BUSTYPE_EISA          "EISA"
#define BUSTYPE_ISA           "ISA"
#define BUSTYPE_MCA           "MCA"
#define BUSTYPE_VL            "VL"
#define BUSTYPE_PCI           "PCI"
#define BUSTYPE_PCMCIA        "PCMCIA"
#define BUSTYPE_INTERN        "INTERN"

typedef struct
{
   char     signature[4];
   ushort   size;
   char     version;
   char     checksum;
   char     oem_string[8];
   char     product_id[12];
   void    *oem_pointer;
   short    oem_size;
   short    oem_count;
   ulong    apic_address;
   ulong    reserved;
} SMPConfigTable;

typedef struct
{
   char     signature[4];
   SMPConfigTable *config;
   uchar    length;
   uchar    version;
   uchar    checksum;
   uchar    feature1;
   uchar    feature2;
   uchar    reserved[3];
} SMPFloatingPointer;

#endif /* __SMP_H__ */
