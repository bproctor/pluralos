
/*
 *  spinlock.h
 *  Modified for Plural by Brad Proctor
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
 * $Id: spinlock.h,v 1.2 2001/10/26 20:32:09 fredlie Exp $
 */

#ifndef __SPINLOCK_H__
#define __SPINLOCK_H__

typedef volatile unsigned long Spinlock;

static inline void spin_lock (Spinlock x)
{
   __asm__ __volatile__ (
      "1:\n\t"
      "lock\n\t"
      "decb %0\n\t"
      "js   2f\n\t"
      ".section .text.lock,\"ax\"\n"
      "2:\n\t"
      "cmp  $0,%0\n\t"
      "jle  2b\n\t"
      "jmp  1b\n"
      ".previous"
      : "=m" (x) :: "memory");
}

static inline int spin_trylock (Spinlock x)
{
   char old;
   __asm__ __volatile__ (
      "xchgb   %b0,%1\n"
      : "=q" (old), "=m" (x)
      : "0" (0)
      : "memory");
   return (old > 0);
}

static inline void spin_unlock (Spinlock x)
{
   __asm__ __volatile__ (
      "movb $1,%0\n"
      : "=m" (x) :: "memory");
}

#endif /* __SPINLOCK_H__ */
