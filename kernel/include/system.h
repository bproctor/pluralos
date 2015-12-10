
/*
 *  system.h
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
 * $Id: system.h,v 1.10 2002/12/05 06:23:26 fredlie Exp $
 */

#ifndef __SYSTEM_H__
#define __SYSTEM_H__

#define __init__        __attribute__ ((__section__ (".init.code")))
#define __init_data__   __attribute__ ((__section__ (".init.data")))

#define KERNEL_CS             (0x08)
#define KERNEL_DS             (0x10)
#define KERNEL_IDT            (0x00101000)
#define KERNEL_GDT            (0x00101800)
#define KERNEL_PDIR           (0x00104000)
#define KERNEL_PTBL0          (0x00105000)
#define KERNEL_PTBL1          (0x00106000)
#define KERNEL_ENTRY          (0x00107000)

#define USER_CS               (0x1B)   /* 0x18, DPL=3 */
#define USER_DS               (0x23)   /* 0x20, DPL=3 */
#define RESERVED1_CS          (0x2A)   /* 0x28, DPL=2 */
#define RESERVED1_DS          (0x32)   /* 0x30, DPL=2 */
#define RESERVED2_CS          (0x39)   /* 0x38, DPL=1 */
#define RESERVED2_DS          (0x41)   /* 0x40, DPL=1 */
#define RESERVED3_CS          (0x48)   /* 0x48, DPL=0 */
#define RESERVED3_DS          (0x50)   /* 0x50, DPL=0 */
#define RESERVED4_CS          (0x58)   /* 0x58 */
#define RESERVED4_DS          (0x60)   /* 0x60 */
#define FIRST_TSS_DESC        (0x68)   /* 0x68 */

#define NUM_PRIORITIES  32
#define NUM_POLICIES    1

#define cli()           __asm__ __volatile__ ("cli":::"memory")
#define clts()          __asm__ __volatile__ ("clts":::"memory")
#define nop()           __asm__ __volatile__ ("nop":::"memory")
#define sti()           __asm__ __volatile__ ("sti":::"memory")
#define halt()          __asm__ __volatile__ ("sti; hlt":::"memory")
#define rdmsr(m,a,b)    __asm__ __volatile__ ("rdmsr":"=a"(a),"=d"(b):"c"(m))
#define wrmsr(m,a,b)    __asm__ __volatile__ ("wrmsr"::"c"(m),"a"(a),"d"(b))
#define rdtsc(l,h)      __asm__ __volatile__ ("rdtsc":"=a"(l),"=d"(h))
#define rdpmc(c,l,h)    __asm__ __volatile__ ("rdpmc":"=a"(l),"=d"(h):"c"(c))
#define ltr(n)          __asm__ __volatile__ ("ltr %%ax"::"a" (FIRST_TSS_DESC+n))


static inline void cpuid (int op, unsigned long *eax, unsigned long *ebx,
   unsigned long *ecx, unsigned long *edx)
{
   __asm__ __volatile__ ("cpuid"
      : "=a" (*eax), "=b" (*ebx),
        "=c" (*ecx), "=d" (*edx)
      : "0" (op));
}

static inline void set_tss_desc (unsigned long n, void *addr)
{
   __asm__ __volatile__ (
      "movw %w3,0(%2)\n\t"
      "movw %%ax,2(%2)\n\t"
      "rorl $16,%%eax\n\t"
      "movb %%al,4(%2)\n\t"
      "movb %4,5(%2)\n\t"
      "movb $0,6(%2)\n\t"
      "movb %%ah,7(%2)\n\t"
      "rorl $16,%%eax\n\t"
      : "=m" (*(unsigned long *)(KERNEL_GDT+FIRST_TSS_DESC+n))
      : "a" (addr), "r" (KERNEL_GDT+FIRST_TSS_DESC+n), "ir" (0x67), "i" (0x89));
}

static inline unsigned short new_tss_desc (void *addr)
{
   unsigned long i, *ptr;
   
   ptr = (unsigned long *)(KERNEL_GDT + FIRST_TSS_DESC);
   for (i = 0; i < 1280*8; i += 8)
      if (*(ptr + i) == 0 && *(ptr + i + 4) == 0)
      {
         set_tss_desc (i, addr);
         return (i);
      }
   return (0);
}

static inline void set_interrupt_gate (unsigned char gate, void *addr)
{
   unsigned short *ptr = (unsigned short *)(KERNEL_IDT + (gate << 3));
   
   cli ();
   ptr[0] = (unsigned short)(((unsigned long)addr) & 0xFFFF);
   ptr[1] = 0x08;
   ptr[2] = 0x8E00;
   ptr[3] = (unsigned short)(((unsigned long)addr) >> 16);
   sti ();
}

static inline void set_trap_gate (unsigned char gate, void *addr)
{
   unsigned short *ptr = (unsigned short *)(KERNEL_IDT + (gate << 3));
   
   cli ();
   ptr[0] = (unsigned short)(((unsigned long)addr) & 0xFFFF);
   ptr[1] = 0x08;
   ptr[2] = 0xEF00;
   ptr[3] = (unsigned short)(((unsigned long)addr) >> 16);
   sti ();
}

#define load_debug(t, r)      __asm__ __volatile__ ("movl %0,%%db" #r :: "r" (t->debug[r]))

#endif /* __SYSTEM_H__ */
