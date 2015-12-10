
/*
 *  unistd.h
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
 * $Id: unistd.h,v 1.2 2003/01/19 19:26:14 fredlie Exp $
 */

#ifndef __SYS_UNISTD_H__
#define __SYS_UNISTD_H__

#define __syscall_0(t, n) \
t n (void) \
{ \
   int x;
   __asm__ ("int $0x80" \
      : "=a" (x) \
      : "0" (__NR_##n)); \
   return (x); \
}

#define __syscall_1(t, n, t1, n1) \
t n (t1 n1) \
{ \
   int x;
   __asm__ ("int $0x80" \
      : "=a" (x) \
      : "0" (__NR_##n), \
        "b" ((int)(n1)); \
   return (x); \
}

#define __syscall_2(t, n, t1, n1, t2, n2) \
t n (t1 n1, t2 n2) \
{ \
   int x; \
   __asm__ ("int $0x80" \
      : "=a" (x) \
      : "0" (__NR_##n), \
        "b" ((int)(n1), \
        "c" ((int)(n2)); \
   return (x); \
}

#define __syscall_3(t, n, t1, n1, t2, n2, t3, n3) \
t n (t1 n1, t2 n2, t3 n3) \
{ \
   int x; \
   __asm__ ("int $0x80" \
      : "=a" (x) \
      : "0" (__NR_##n), \
        "b" ((int)(n1)), \
        "c" ((int)(n2)), \
        "d" ((int)(n3))); \
   return (x); \
}

#define __syscall_4(t, n, t1, n1, t2, n2, t3, n3, t4, n4) \
t n (t1 n1, t2 n2, t3 n3, t4 n4) \
{ \
   int x; \
   __asm__ ("int $0x80" \
      : "=a" (x) \
      : "0" (__NR_##n), \
        "b" ((int)(n1)), \
        "c" ((int)(n2)), \
        "d" ((int)(n3)), \
        "S" ((int)(n4))); \
   return (x); \
}

#define __syscall_5(t, n, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5) \
t n (t1 n1, t2 n2, t3 n3, t4 n4, t5 n5) \
{ \
   int x; \
   __asm__ ("int $0x80" \
      : "=a" (x) \
      : "0" (__NR_##n), \
        "b" ((int)(n1)), \
        "c" ((int)(n2)), \
        "d" ((int)(n3)), \
        "S" ((int)(n4)), \
        "D" ((int)(n5))); \
   return (x); \
}

#define __syscall_6(t, n, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6) \
t n (t1 n1, t2 n2, t3 n3, t4 n4, t5 n5, t6 n6) \
{ \
   int x; \
   __asm__ ("int $0x80" \
      : "=a" (x) \
      : "i" (__NR_##n), \
        "b" ((int)(n1)), \
        "c" ((int)(n2)), \
        "d" ((int)(n3)), \
        "S" ((int)(n4)), \
        "D" ((int)(n5)), \
        "0" ((int)(n6))); \
   return (x); \
}

#endif /* __SYS_UNISTD_H__ */
