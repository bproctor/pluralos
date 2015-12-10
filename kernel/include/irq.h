
/*
 *  irq.h
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
 * $Id: irq.h,v 1.5 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __IRQ_H__
#define __IRQ_H__

#ifndef __IO_H__
#include <io.h>
#endif

extern unsigned short irq_mask;

static inline void irq_enable (unsigned int irq)
{
   irq_mask &= ~(1 << irq);
   if (irq & 8)
      outb (0xA1, irq_mask >> 8);
   else
      outb (0x21, irq_mask);
}

static inline void irq_disable (unsigned int irq)
{
   irq_mask |= (1 << irq);
   if (irq & 8)
      outb (0xA1, (irq_mask >> 8));
   else
      outb (0x21, irq_mask);
}

static inline void irq_mask_and_ack (unsigned int irq)
{
   irq_mask |= (1 << irq);
   if (irq & 8)
   {
      inb (0xA1);
      outb (0xA1, (irq_mask >> 8));
      outb (0x20, 0x62);
      outb (0xA0, 0x20);
   }
   else
   {
      inb (0x21);
      outb (0x21, irq_mask);
      outb (0x20, 0x20);
   }
}

#endif /* __IRQ_H__ */
