
/*
 *  sched.c
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
 * $Id: sched.c,v 1.6 2002/12/06 13:27:53 fredlie Exp $
 */

#include <sys/types.h>
#include <sys/channel.h>
#include <sys/message.h>
#include <stddef.h>
#include <system.h>
#include <thread.h>
#include <config.h>
#include <stdio.h>

typedef struct ReadyQueue
{
   Thread *head;
   Thread *tail;
} ReadyQueue;

extern ulong *stack;

static void kernel_start (void);


ReadyQueue queue[CONFIG_PRIORITIES];
Thread *current;

Thread kernel =
{
   {                             /* struct tss_struct tss */
      0,0,                       /*   ushort link, _link  */
      (ulong)&stack,             /*   ulong  esp0         */
      0x10, 0x00,                /*   ushort ss0, _ss0    */
      (ulong)&stack,             /*   ulong  esp1         */
      0x10, 0x00,                /*   ushort ss1, _ss1    */
      (ulong)&stack,             /*   ulong  esp2         */
      0x10, 0x00,                /*   ushort ss2, _ss2    */
      KERNEL_PDIR,               /*   ulong  cr3          */
      (ulong)&kernel_start,      /*   ulong  eip          */
      0x02,                      /*   ulong  eflags       */
      0x00,                      /*   ulong  eax          */
      0x00,                      /*   ulong  ecx          */
      0x00,                      /*   ulong  edx          */
      0x00,                      /*   ulong  ebx          */
      0x00,                      /*   ulong  esp          */
      0x00,                      /*   ulong  ebp          */
      0x00,                      /*   ulong  esi          */
      0x00,                      /*   ulong  edi          */
      0x10, 0x00,                /*   ushort es, _es      */
      0x08, 0x00,                /*   ushort cs, _cs      */
      0x10, 0x00,                /*   ushort ss, _ss      */
      0x10, 0x00,                /*   ushort ds, _ds      */
      0x10, 0x00,                /*   ushort fs, _fs      */
      0x10, 0x00,                /*   ushort gs, _gs      */
      0x00, 0x00,                /*   ushort ldt, _ldt    */
      0x00,                      /*   ushort trapbit      */
      0x00,                      /*   ushort bitmap       */
   },
   {                             /* ulong iomap[32]       */
      0, 0, 0, 0, 0, 0, 0, 0,    /*   0x00 - 0x07         */
      0, 0, 0, 0, 0, 0, 0, 0,    /*   0x08 - 0x0F         */
      0, 0, 0, 0, 0, 0, 0, 0,    /*   0x10 - 0x17         */
      0, 0, 0, 0, 0, 0, 0, 0,    /*   0x18 - 0x1F         */
   },
   {                             /* ulong fpu[28]         */
      0, 0, 0, 0, 0, 0, 0, 0,    /*   0x00 - 0x07         */
      0, 0, 0, 0, 0, 0, 0, 0,    /*   0x08 - 0x0F         */
      0, 0, 0, 0, 0, 0, 0, 0,    /*   0x10 - 0x17         */
      0, 0, 0, 0,                /*   0x18 - 0x1B         */
   },
   {                             /* ulong debug[8]        */
      0, 0, 0, 0, 0, 0, 0, 0,    /*   0x00 - 0x07         */
   },
   NULL,                         /* struct Thread *next   */
   NULL,                         /* struct Thread *prev   */
   1,                            /* ulong tid             */
   1,                            /* ulong pid             */
   1,                            /* ulong ppid            */
   0,                            /* ulong uid             */
   0,                            /* ulong gid             */
   0,                            /* ulong euid            */
   0,                            /* ulong egid            */
   0,                            /* ulong channel         */
   0,                            /* ulong stack           */
   0,                            /* ushort tr             */
   0,                            /* uchar priority        */
   0,                            /* uchar real_priority   */
   0,                            /* uchar used_math       */
   0,                            /* uchar policy          */   
};

static inline void enqueue_msg (Channel *c, Message *m)
{
   m->next = NULL;
   if (c->head == NULL)
      c->head = (void *)m, c->tail = (void *)m;
   else
      ((Message *)c->tail)->next = m, c->tail = (void *)m;
   c->flag_message = 1;
}

static inline Message *dequeue_msg (Channel *c)
{
   if (c->flag_message == 0 || c->head == NULL)
      return (NULL);
   ((Message *)c->head)->next = c->head;
   return ((Message *)c->head);   
}

static inline void enqueue_ready (Thread *t)
{
   if (t == NULL)
      return;
   t->next = NULL;
   if (queue[t->priority].head == NULL)
      queue[t->priority].head = t,  queue[t->priority].tail = t;
   else
   {
      ((Thread *)queue[t->priority].tail)->next = t;
      queue[t->priority].tail = t;
   }
}

static inline void dequeue_ready (Thread *t)
{
   ulong i;
   for (i = CONFIG_PRIORITIES; i > 0; ++i)
   {
      if (queue[i].head != NULL)
      {
         queue[i].head->next = queue[i].head;
         return;
      }
   }
}

void schedule (void)
{
   ulong i;
   
   for (i = 0; i < CONFIG_PRIORITIES; ++i)
   {
      if (queue[i].head != NULL)
      {
         ReadyQueue *q = &queue[current->priority];
         q->tail->next = current;
         q->head = current->next;
         current->next = NULL;
         current = queue[i].head;
         thread_switch (q->tail->next, current);
      }
   }
}

static void kernel_start (void)
{
   puts ("A");
}

void __init__ init_sched (void)
{
   ltr (new_tss_desc (&kernel.tss));
}
