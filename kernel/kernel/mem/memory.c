
/*
 *  memory.c
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
 * $Id: memory.c,v 1.11 2002/12/02 09:06:25 fredlie Exp $
 */
 
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <system.h>
#include <sys/errno.h>
#include <config.h>
#include <thread.h>

#define MEM_FREE     0x00
#define MEM_KERNEL   0x01
#define MEM_USER     0x02

extern void *_end, *_init, *_einit;

static uchar *page_map;
static ulong page_map_size;

void free_init_memory (void)
{
   ulong i, free;

   puts ("Freeing Unused kernel memory... ");

   /* Now we free the memory that in the .init section cause
      it won't be used again. _init and _einit are already
      page aligned so no need to worry about it here, see 
      'boot/plural.ld'*/

   for (free = 0, i = (ulong)&_init >> 12; i < (ulong)&_einit >> 12; ++i)
      page_map[i] = MEM_FREE, free += 4096;

   printf ("%ldKb freed.\n", free / 1024);
}

/* This function is can get confusing, so i've heavily commented it */
void __init__ init_memory (ulong memsize)
{
   ulong i, end, reserved, kernel, free;

   /* The page map is located right after the kernel */
   page_map = (uchar *)&_end;
   
   /* This is the size of the page map */
   page_map_size = memsize >> 12;

   puts ("Initializing memory... \n");

   /* Calculate the real end of the kernel memory, that is,
      the size of the kernel that was loaded + the page map,
      and aligned on a page boundary */
   end = (((ulong)&_end + page_map_size) + 4095) & ~4095;
   
   /* Reserved memory is the parts below 1Mb...
    *    0x00000000 - 0x00001000  BIOS
    *    0x000A0000 - 0x00100000  Video mem, BIOS
    */     
   reserved = 0x100000 - 0xA0000 + 0x1000;
   
   /* Mark the first page as kernel memory because it is reserved
      for the BIOS */
   page_map[0] = MEM_KERNEL;     /* 0x0000 is reserved for BIOS */

   /* This code marks the all the memory that was used by the
      kernel from the 1Mb line up the real end, including the
      page map */
   for (i = 0x100000 >> 12; i < end >> 12; ++i)
      page_map[i] = MEM_KERNEL;

   /* Mark this page as free, because it was used to start the
      kernel and is not used again, see 'boot/start.S' */
   page_map[0x107000 >> 12] = MEM_FREE;

   /* Mark the video, BIOS, ROM as used */
   for (i = 0xA0000 >> 12; i < 0x100000 >> 12; ++i)
      page_map[i] = MEM_KERNEL;

   /* Now we find all the memory that was is marked as used
      by the kernel in the page_map and add up a total of
      how much memory the kernel is using. We skip the first
      1Mb because memory marked below 1Mb as MEM_KERNEL is
      reserved for the BIOS. */
   for (kernel = 0, i = 0x100000 >> 12; i < end >> 12; ++i)
      if (page_map[i] == MEM_KERNEL)
         kernel += 4096;

   /* This is the amount of free memory available */
   free = memsize - kernel - reserved;
   
   printf ("Total memory:     %8lu bytes\n"
           "Kernel memory:    %8lu bytes\n"
           "   Pagemap size:  %8lu bytes\n"
           "Reserved memory:  %8lu bytes\n"
           "Free memory:      %8lu bytes\n", 
           memsize, kernel, page_map_size, reserved, free);
}

/*
 * find_high_page
 *  
 *     Find first free page of memory starting at highest address.
 */

static inline ulong find_high_page (void)
{
   ulong i;
   for (i = page_map_size-1; i > 0; --i)
      if (page_map[i] == MEM_FREE)
         return (i << 12);
   return (0);
}

/*
 * find_low_page
 *
 *     Find first free page of memory starting at lowest address.
 */

static inline ulong find_low_page (void)
{
   ulong i;
   for (i = 1; i < page_map_size; ++i)
      if (page_map[i] == MEM_FREE)
         return (i << 12);
   return (0);
}

static ulong find_free_pages (ulong pages)
{
   ulong i, addr, count;
   for (i = page_map_size; i > 0; --i)
   {
      count = pages;
      addr = i;
      do {
         if (page_map[i] != MEM_FREE)
            break;
         --i;
      } while (--count);
      if (count == 0)
      {
         if (current->tid == TID_KERNEL)
            for (i = 0; i < pages; ++i)
               page_map[addr-i] = MEM_KERNEL;
         else
            for (i = 0; i < pages; ++i)
               page_map[addr-i] = MEM_USER;           
         return (addr << 12);
      }
   }
   return (0);
}

/*
 * free_page
 *
 *     Free a page of memory at the specified physical address.
 */

static inline void free_page (ulong addr)
{
   if (page_map[addr >> 12] == MEM_KERNEL)
   {
      if (current->tid == TID_KERNEL)
         page_map[addr >> 12] = MEM_FREE;
   }
   else
      page_map[addr >> 12] = MEM_FREE;
}

ulong MemoryAlloc (ulong pages)
{
   ulong addr;
   addr = find_free_pages (pages);
   printf ("mem: alloc: %08lX\n", addr);
   return (addr);
}

ulong MemoryFree (ulong addr)
{
   
   return (ENOSYS);
}

ulong MemoryMap (void)
{
   return (ENOSYS);
}

ulong MemoryUnmap (void)
{
   return (ENOSYS);
}

ulong MemoryProtect (void)
{
   return (ENOSYS);
}
