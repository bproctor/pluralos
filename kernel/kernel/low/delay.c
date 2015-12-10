
/*
 *  delay.c
 *  Modified from Linux by Brad Proctor
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
 * $Id: delay.c,v 1.5 2001/11/01 09:10:54 fredlie Exp $
 */

#include <stdio.h>
#include <sys/types.h>
#include <irq.h>
#include <io.h>
#include <config.h>
#include <system.h>
#include <pit.h>

extern void calibrate_delay_isr (void);

static ulong delay_count = 1;
static volatile ulong ticks = 0;

static void __delay (ulong loops)
{
   ulong i;   
   for (i = 0; i < loops; ++i);
}

void delay (ulong ms)
{
   __delay (ms * delay_count);
}

static ulong __init__ calibrate_delay (void)
{
   ulong prevtick, i, calib_bit;

   init_pit (10, 0);   
   set_interrupt_gate (0x20, calibrate_delay_isr);
   irq_enable (0);
   
   do {
      delay_count <<= 1;
      prevtick = ticks;
      while (prevtick == ticks);
      prevtick = ticks;
      __delay (delay_count);
   } while (prevtick == ticks);
   delay_count >>= 1;
   calib_bit = delay_count;
   for (i = 0; i < CONFIG_DELAY_PRECISION; ++i)
   {
      calib_bit >>= 1;
      if (!calib_bit)
         break;
      delay_count |= calib_bit;
      prevtick = ticks;
      while (prevtick == ticks);
      prevtick = ticks;
      __delay (delay_count);
      if (prevtick != ticks)
         delay_count &= ~calib_bit;
   }
   irq_disable (0);
   delay_count /= 10;
   return (delay_count);
}

ulong __init__ init_delay (void)
{
   uint i;
   
   puts ("Calibrating delay loop... ");
   i = calibrate_delay ();
   printf ("(%u)\n", i);
   return (i);
}

asm (
".section .init                  \n"
"  .align   16                   \n"
"  .globl   calibrate_delay_isr  \n"
"calibrate_delay_isr:            \n"
"  pushal                        \n"
"  incl     ticks                \n"
"  movb     $0x20,%al            \n"
"  outb     %al,$0x20            \n"
"  popal                         \n"
"  iret                          \n");
