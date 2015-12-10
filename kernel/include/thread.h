
/*
 *  thread.h
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
 * $Id: thread.h,v 1.7 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __THREAD_H__
#define __THREAD_H__

#ifndef __SYS_TYPES_H__
#include <sys/types.h>
#endif

#define TSS_LIMIT    231

typedef struct tss_struct
{
   ushort   link, _link;
   ulong    esp0;
   ushort   ss0, _ss0;
   ulong    esp1;
   ushort   ss1, _ss1;
   ulong    esp2;
   ushort   ss2, _ss2;
   ulong    cr3;
   ulong    eip;
   ulong    eflags;
   ulong    eax;
   ulong    ecx;
   ulong    edx;
   ulong    ebx;
   ulong    esp;
   ulong    ebp;
   ulong    esi;
   ulong    edi;
   ushort   es, _es;
   ushort   cs, _cs;
   ushort   ss, _ss;
   ushort   ds, _ds;
   ushort   fs, _fs;
   ushort   gs, _gs;
   ushort   ldt, _ldt;
   ushort   trapbit;
   ushort   bitmap;
} tss_struct;


typedef struct Thread
{
   struct tss_struct tss;
   ulong    iomap[32];
   ulong    fpu[28];
   ulong    debug[8];

   struct Thread *next;    /* pointer to the next thread */
   struct Thread *prev;    /* pointer to the prev thread */
   ulong    tid;           /* Thread ID number for this thread */
   ulong    pid;           /* Process ID that this thread belongs to */
   ulong    ppid;          /* Parent process ID */
   ulong    uid;           /* User ID */
   ulong    gid;           /* Group ID */
   ulong    euid;
   ulong    egid;
   ulong    channel;       /* Primary channel for this thread */
   ulong    stack;         /* Address of the threads stack */
   ushort   tr;            /* Task register */
   uchar    priority;      /* Priority of this thread */
   uchar    real_priority; /* Real priority */
   uchar    used_math;     /* =1 if this thread has used the FPU */
   uchar    policy;        /* Scheduling policy */
} Thread __attribute__ ((packed));

static inline void thread_switch (Thread *from, Thread *to)
{
__asm__ __volatile__ (
   "pushl %%edi\n\t"
   "pushl %%ebp\n\t"
   "movl %%esp,%0\n\t"
   "movl %3,%%esp\n\t"
   "movl $1f,%1\n\t"
   "pushl %4\n\t"
   "jmp __thread_switch\n"
   "1:\t"
   "popl %%ebp\n\t"
   "popl %%edi\n\t"
   "popl %%esi\n\t"
   : "=m" (from->tss.esp), "=m" (from->tss.eip), "=b" (from)
   : "m" (to->tss.esp), "m" (to->tss.eip), "a" (from), "d" (to), "b" (from));
}


#define TID_KERNEL      1

extern Thread *current;

#endif /* __THREAD_H__ */
