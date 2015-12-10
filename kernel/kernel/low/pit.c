
/*
 *  pit.c
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
 * $Id: pit.c,v 1.7 2002/12/02 09:06:24 fredlie Exp $
 */

#include <system.h>
#include <irq.h>
#include <pit.h>
#include <io.h>
#include <sys/types.h>
#include <stdio.h>
#include <console.h>

extern void int_timer (void);

volatile ulong clock_tick = 0;

void __init__ init_pit (ulong ms, uchar c)
{
   ulong i;
   i = 1193180 / (1000 / ms);

   outb (PIT_CTRL, (c << 6) + PIT_BOTH + PIT_MODE2);
   outb (PIT_CTRL0+c, (uchar)i);
   outb (PIT_CTRL0+c, (uchar)(i >> 8));
}

ulong pit_getchannel (uchar c)
{
   ulong i = 0;
   outb (PIT_CTRL, (c << 6) + PIT_LATCH);
   i = inb (PIT_CTRL + c);
   i += inb (PIT_CTRL+c) << 8;
   return (i);
}

void __init__ init_timer (void)
{
   puts ("Initializing timer... ");
   init_pit (10, 0);
   set_interrupt_gate (0x20, int_timer);
   irq_enable (0);
   puts ("done.\n");
}

asm (
"  .text                \n"
"  .align   16          \n"
"  .globl   int_timer   \n"
"int_timer:             \n"
"  pushal               \n"
"  incl     clock_tick  \n"
"  int      $0x1C       \n"
"  movb     $0x20,%al   \n"
"  outb     %al,$0x20   \n"
"  popal                \n"
"  iret                 \n");
