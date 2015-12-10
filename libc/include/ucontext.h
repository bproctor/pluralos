
/*
 *  ucontext.h
 *  Copyright (c) 2001-2003 Brad Proctor
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 */

/*
 * $Id: ucontext.h,v 1.4 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __UCONTEXT_H__
#define __UCONTEXT_H__

#ifndef __SIGSETT
#define __SIGSETT
typedef int sigset_t;
#endif

#ifndef __MCONTEXTT
#define __MCONTEXTT
typedef unsigned int mcontext_t;
#endif

#ifndef __STACKT
#define __STACKT
typedef struct
{
   void  *ss_sp;        /* Stack base or pointer */
   size_t ss_size;      /* Stack size */
   int    ss_flags;     /* Flags */
} stack_t;
#endif

typedef struct
{
   struct ucontext_t *uc_link;      /* Pointer to the context that is resumed
                                       when this context returns */
   sigset_t           uc_sigmask;   /* The set of signals that are blocked
                                       when this context is active */
   stack_t            uc_stack;     /* The stack used by this context */
   mcontext_t         uc_mcontext;  /* A machine-specific representation
                                       of the saved context */
} ucontext_t;

int getcontext (ucontext_t *);
int setcontext (const ucontext_t *);
void makecontext (ucontext_t *, void (*)(void), int, ...);
int swapcontext (ucontext_t *restrict, const ucontext_t *restrict);

#endif /* __UCONTEXT_H__ */
