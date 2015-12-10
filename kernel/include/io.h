
/*
 *  io.h
 *  Copyright (c) 2001 Brad Proctor
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
 * $Id: io.h,v 1.3 2001/10/29 02:42:17 fredlie Exp $
 */

#ifndef __IO_H__
#define __IO_H__

static inline unsigned char inb(unsigned short port)
{
   unsigned char x;
   __asm__ __volatile__ ("inb %w1,%0" : "=a" (x) : "Nd" (port));
   return (x);
}

static inline unsigned short inw (unsigned short port)
{
   unsigned short x;
   __asm__ __volatile__ ("inw %w1,%0" : "=a" (x) : "Nd" (port));
   return (x);
}

static inline unsigned int inl (unsigned short port)
{
   unsigned int x;
   __asm__ __volatile__ ("inl %w1,%0" : "=a" (x) : "Nd" (port));
   return (x);
}

static inline void outb (unsigned short port, unsigned char value)
{
   __asm__ __volatile__ ("outb %b0,%w1" :: "a" (value), "Nd" (port));
}

static inline void outw (unsigned short port, unsigned short value)
{
   __asm__ __volatile__ ("outw %w0,%w1" :: "a" (value), "Nd" (port));
}

static inline void outl (unsigned short port, unsigned int value)
{
   __asm__ __volatile__ ("outl %0,%w1" :: "a" (value), "Nd" (port));
}

static inline unsigned char cmos_read (unsigned int addr)
{
   outb (0x70, addr);
   return (inb (0x71));
}

static inline void cmos_write (unsigned int addr, unsigned int value)
{
   outb (0x70, addr);
   outb (0x71, value);
}

#endif /* __IO_H__ */
