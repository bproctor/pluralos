
/*
 *  error.c
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
 * $Id: error.c,v 1.7 2002/12/02 09:06:24 fredlie Exp $
 */

#include <sys/types.h>
#include <stdio.h>
#include <system.h>
#include <thread.h>

static const char *names[] =
{
   "Division by Zero",              /* 0x00 */
   "Single step",                   /* 0x01 */
   "Nonmaskable interrupt",         /* 0x02 */
   "Debug",                         /* 0x03 */
   "Overflow",                      /* 0x04 */
   "Bounds check",                  /* 0x05 */
   "Invalid operand",               /* 0x06 */
   "Coprocessor not available",     /* 0x07 */
   "Double fault",                  /* 0x08 */
   "Coprocessor segment overrun",   /* 0x09 */
   "Invalid TSS",                   /* 0x0A */
   "Segment not present",           /* 0x0B */
   "Stack exception",               /* 0x0C */
   "General protection fault",      /* 0x0D */
   "Page fault",                    /* 0x0E */
   "Unknown interrupt",             /* 0x0F */
   "Coprocessor error",             /* 0x10 */
   "Alignment check",               /* 0x11 */
   "Machine check",                 /* 0x12 */
   "SIMD Floating-point",           /* 0x13 */
};

struct Registers
{
   ulong ss, gs, fs, es, ds;
   ulong edi, esi, ebp, esp;
   ulong ebx, edx, ecx, eax;
   ulong handler, except, error;
   ulong eip, cs, eflags;
};

extern ulong _etext;
extern ulong _text;

static void show_trace (ulong *esp)
{
   ulong i, addr;
   
   puts ("Calls: ");
   if (!esp)
      esp = (ulong *)&esp;
   i = 1;
   while (((long)esp & 0x1FFF) != 0)
   {
      addr = *esp++;
      if (addr >= (ulong)&_text && addr <= (ulong)&_etext)
      {
         if (i && (i % 8) == 0)
            puts ("\n       ");
         printf ("%08lX ", addr);
      }
   }
   puts ("\n");
}

static void show_stack (ulong *esp)
{
   ulong i, *stack;
   
   puts ("\nStack: ");
   if (esp == NULL)
      esp = (ulong *)&esp;
   stack = esp;
   for (i = 0; i < 24; ++i)
   {
      if (i && (i % 8) == 0)
         puts ("\n       ");
      printf ("%08lx ", *stack++);
   }
   puts ("\n");
}

void show_regs (struct Registers regs)
{
   printf ("\nException %ld (%s) error: %ld\n",
      regs.except, names[regs.except], regs.error);
   printf ("eax: %08lX  ebx: %08lX  ecx: %08lX  edx: %08lX\n",
      regs.eax, regs.ebx, regs.ecx, regs.edx);
   printf ("esp: %08lX  ebp: %08lX  esi: %08lX  edi: %08lX\n",
      regs.esp, regs.ebp, regs.esi, regs.edi);
   printf ("cs:  %04lX      ds:  %04lX      es:  %04lX\n",
      regs.cs, regs.ds, regs.es);
   printf ("fs:  %04lX      gs:  %04lX      ss:  %04lX\n",
      regs.fs, regs.gs, regs.ss);
   printf ("eip: %08lX  eflags: %08lX\n",
      regs.eip, regs.eflags);
   printf ("\nProcess: pid: %8ld tid: %8ld", current->pid, current->tid);
   show_stack ((ulong *)regs.esp);
   show_trace ((ulong *)regs.esp);   
}

/* 
 * Division by Zero
 */
void handle_exception_00 (void)
{
}

/*
 * Single Step
 */
void handle_exception_01 (void)
{
}

/*
 * Nonmaskable Interrupt
 */
void handle_exception_02 (void)
{
}

/*
 * Debug
 */
void handle_exception_03 (void)
{
}

/*
 * Overflow
 */
void handle_exception_04 (void)
{
}

/*
 * Bounds Check
 */
void handle_exception_05 (void)
{
}

/*
 * Invalid Operand
 */
void handle_exception_06 (void)
{
}

/*
 * Coprocessor Not Available
 */
void handle_exception_07 (void)
{
}

/*
 * Double Fault
 */
void handle_exception_08 (void)
{
}

/*
 * Coprocessor Segment Overrun
 */

void handle_exception_09 (void)
{
}

/*
 * Invalid TSS
 */
void handle_exception_10 (void)
{
}

/*
 * Segment Not Present
 */
void handle_exception_11 (void)
{
}

/*
 * Stack Fault
 */
void handle_exception_12 (void)
{
}

/*
 * General Protection Fault
 */
void handle_exception_13 (void)
{
}

/*
 * Page Fault
 */
void handle_exception_14 (void)
{
}

/*
 * Unknown Interrupt
 */
void handle_exception_15 (void)
{
}

/*
 * Coprocessor Error
 */
void handle_exception_16 (void)
{
}

/*
 * Alignment Check
 */
void handle_exception_17 (void)
{
}

/*
 * Machine Check
 */
void handle_exception_18 (void)
{
}

/*
 * SIMD Floating-Point
 */
void handle_exception_19 (void)
{
}
