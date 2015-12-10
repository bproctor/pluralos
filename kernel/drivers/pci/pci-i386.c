
/*
 *  pci-i386.c
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
 * $Id: pci-i386.c,v 1.3 2002/12/02 04:16:28 fredlie Exp $
 */

#include <sys/types.h>
#include <stdio.h>
#include <system.h>

#define PCI_FUNCTION_ID 	0xb1XX
#define PCI_BIOS_PRESENT 	0xb101

#define PCIBIOS_FIND_PCI_DEVICE		0xb102
#define PCIBIOS_FIND_PCI_CLASS_CODE	0xb103
#define PCIBIOS_GENERATE_SPECIAL_CYCLE	0xb106
#define PCIBIOS_READ_CONFIG_BYTE	0xb108
#define PCIBIOS_READ_CONFIG_WORD	0xb109
#define PCIBIOS_READ_CONFIG_DWORD	0xb10a
#define PCIBIOS_WRITE_CONFIG_BYTE	0xb10b
#define PCIBIOS_WRITE_CONFIG_WORD	0xb10c
#define PCIBIOS_WRITE_CONFIG_DWORD	0xb10d

#define BIOS32_SIGNATURE	(('_' << 0) + ('3' << 8) + ('2' << 16) + ('_' << 24))
#define PCI_SIGNATURE		(('P' << 0) + ('C' << 8) + ('I' << 16) + (' ' << 24))
#define PCI_SERVICE		(('$' << 0) + ('P' << 8) + ('C' << 16) + ('I' << 24))

typedef struct bios32
{
   ulong signature;
   ulong entry;
   uchar revision;
   uchar length;
   uchar checksum;
   uchar reserved[5];
} bios32;

typedef struct long_addr
{
   ulong offset;
   ushort selector;
} long_addr;

static long_addr bios32_entry = {0, 0x08};
static long_addr pci_entry = {0, 0x08};


static ulong pci_service (ulong service)
{
   uchar ret;
   ulong addr;
   ulong length;
   ulong entry;
   
   __asm__ ("lcall *(%%edi)"
      : "=a" (ret),
        "=b" (addr),
        "=c" (length),
        "=d" (entry)
      : "0" (service),
        "1" (0),
        "D" (&bios32_entry));
   
   switch (ret)
   {
      case 0:
         return (addr + entry);
      case 0x80:
         printf ("pci_service (%ld): Not present\n", service);
         return (0);
      default:
         printf ("pci_service (%ld): returned (0x%08x)\n", service, ret);
         return (0);
   }
}

static void pci_check (void)
{
   ulong sig, pack;
   uchar present, major, minor;
   
   if ((pci_entry.offset = pci_service (PCI_SERVICE)))
   {
      __asm__ ("lcall *(%%edi)\n\t"
         "jc 1f\n\t"
         "xor %%ah,%%ah\n"
         "1:\tshl $8,%%ax\n\t"
         "movw %%bx,%%ax"
         : "=d" (sig),
           "=a" (pack)
         : "1" (PCI_BIOS_PRESENT),
           "D" (&pci_entry)
         : "bx", "cx");
      present = (pack >> 16) & 0xFF;
      major = (pack >> 8) & 0xFF;
      minor = pack & 0xFF;
      
      if (present || (sig != PCI_SIGNATURE))
      {
         printf ("PCI: %s: BIOS32 Service Directory says PCI BIOS present,\n"
            "     but PCI_BIOS_PRESENT subfunction fails with present status of 0x%08x\n"
            "     and signature of 0x%08lx (%c%c%c%c).\n",
            (sig == PCI_SIGNATURE) ? "warning" : "ERROR",
            present, sig,
            (char)(sig), (char)(sig >> 8),
            (char)(sig >> 16), (char)(sig >> 24));
         if (sig != PCI_SIGNATURE)
            pci_entry.offset = 0;
      }
      if (pci_entry.offset)
         printf ("PCI: PCI BIOS revision %x.%02x entry at 0x%08lx\n",
            major, minor, pci_entry.offset);
   }
}

void __init__ init_pci (void)
{
   bios32 *b;
   
   for (b = (bios32 *)0xE0000; b <= (bios32 *)0xFFFF0; b++)
   {
      if (b->signature != BIOS32_SIGNATURE)
         continue;
      if (!b->length)
         continue;
      if (b->entry >= 0x100000 - 4)
      {
         printf ("PCI: entry in high memory, unable to access\n");
         return;
      }
      bios32_entry.offset = b->entry;
      printf ("PCI: BIOS32 Service Directory structure at 0x%p, entry at 0x%08lx\n",
         b, bios32_entry.offset);
      pci_check ();
      return;
   }
   printf ("PCI: bios not found\n");
}

#if 0
void show_pci_info (PCIEntry *pci)
{
   printf ("Vendor    = %04x\n"
           "Device    = %04x\n"
           "Revision  = %01x\n", pci->vendor, pci->device, pci->revision);
           
   printf ("Base0     = %08x\n"
           "Base1     = %08x\n"
           "Base2     = %08x\n"
           "Base3     = %08x\n"
           "Base4     = %08x\n"
           "Base5     = %08x\n", pci->base0, pci->base1, pci->base2,
           pci->base3, pci->base4, pc->base5);
}
#endif
