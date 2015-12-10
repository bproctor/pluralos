
/*
 *  switch.c
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
 * $Id: switch.c,v 1.3 2002/12/02 09:06:24 fredlie Exp $
 */

#include <system.h>
#include <thread.h>

tss_struct init_tss;

void __thread_switch (Thread *tfrom, Thread *tto)
{
   tss_struct *from = &tfrom->tss;
   tss_struct *to = &tto->tss;
   tss_struct *tss = &init_tss;
   
   tss->esp0 = to->esp0;
   __asm__ __volatile__ ("movl %%fs,%0":"=m" (*(int *)&from->fs));
   __asm__ __volatile__ ("movl %%gs,%0":"=m" (*(int *)&from->gs));
   __asm__ __volatile__ ("movl %0,%%fs"::"m" (*(int *)&to->fs));
   __asm__ __volatile__ ("movl %0,%%gs"::"m" (*(int *)&to->gs));
   
   if (tto->debug[7])
   {
      load_debug (tto, 0);
      load_debug (tto, 1);
      load_debug (tto, 2);
      load_debug (tto, 3);
      load_debug (tto, 6);
      load_debug (tto, 7);
   }
}
