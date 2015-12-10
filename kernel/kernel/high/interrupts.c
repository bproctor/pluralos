
/*
 *  interrupts.c
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
 * $Id: interrupts.c,v 1.5 2002/12/06 13:27:53 fredlie Exp $
 */

#include <sys/types.h>
#include <sys/errno.h>
#include <string.h>
#include <stdlib.h>
#include <thread.h>
#include <irq.h>
#include <spinlock.h>

typedef struct IntType
{
   ulong tid;
   void *handler;
   char *name;
} IntType;

Spinlock interrupt_spinlock;

static IntType int_pool[16];     /* 16 IRQs */

ulong InterruptAttach (ulong irq, void *handler, const char *devname)
{
   if (irq >= 16)
      return (EINVAL);
   if (int_pool[irq].tid != current->tid)
      return (EACCES);
   spin_lock (interrupt_spinlock);
   int_pool[irq].tid = current->tid;
   int_pool[irq].handler = handler;
   int_pool[irq].name = malloc (strlen (devname));
   strcpy (int_pool[irq].name, devname);
   spin_unlock (interrupt_spinlock);
   return (EOK);
}

ulong InterruptDetach (ulong irq)
{
   if (irq >= 16)
      return (EINVAL);
   if (int_pool[irq].tid != current->tid)
      return (EACCES);
   spin_lock (interrupt_spinlock);
   int_pool[irq].tid = 0;
   int_pool[irq].handler = 0;
   free (int_pool[irq].name);
   int_pool[irq].name = 0;
   spin_unlock (interrupt_spinlock);
   return (EOK);
}

ulong InterruptDisable (ulong irq)
{
   if (irq >= 16)
      return (EINVAL);
   if (int_pool[irq].tid != current->tid)
      return (EACCES);
   irq_disable (irq);
   return (EOK);
}

ulong InterruptEnable (ulong irq)
{
   if (irq >= 16)
      return (EINVAL);
   if (int_pool[irq].tid != current->tid)
      return (EACCES);
   irq_enable (irq);
   return (EOK);
}

ulong InterruptLock (void)
{
   return (ENOSYS);
}

ulong InterruptMask (void)
{
   return (ENOSYS);
}

ulong InterruptUnlock (void)
{
   return (ENOSYS);
}

ulong InterruptUnmask (void)
{
   return (ENOSYS);
}

ulong InterruptWait (void)
{
   return (ENOSYS);
}
