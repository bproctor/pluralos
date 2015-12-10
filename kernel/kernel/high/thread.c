
/*
 *  thread.c
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
 * $Id: thread.c,v 1.6 2002/12/06 13:27:53 fredlie Exp $
 */

#include <sys/types.h>
#include <sys/errno.h>
#include <thread.h>
#include <spinlock.h>

Spinlock thread_spinlock;

ulong ThreadSetPolicy (ulong policy)
{
   spin_lock (thread_spinlock);
   current->policy = policy;
   spin_unlock (thread_spinlock);
   return (EOK);
}

ulong ThreadGetPolicy (ulong *policy)
{
   *policy = current->policy;
   return (EOK);
}

ulong ThreadSetPriority (ulong pri)
{
   spin_lock (thread_spinlock);
   current->priority = pri;
   spin_unlock (thread_spinlock);
   return (EOK);
}

ulong ThreadGetPriority (ulong *pri)
{
   *pri = current->priority;
   return (EOK);
}

ulong ThreadSetChannel (ulong channel)
{
   spin_lock (thread_spinlock);
   current->channel = channel;
   spin_unlock (thread_spinlock);
   return (EOK);
}

ulong ThreadGetChannel (ulong *channel)
{
   *channel = current->channel;
   return (EOK);
}

ulong ThreadSetStack (void)
{
   return (ENOSYS);
}

ulong ThreadGetStack (void)
{
   return (ENOSYS);
}

ulong ThreadContext (void)
{
   return (ENOSYS);
}

ulong ThreadCancel (void)
{
   return (ENOSYS);
}

ulong ThreadDetach (void)
{
   return (ENOSYS);
}

ulong ThreadSelf (void)
{
   return (ENOSYS);
}

ulong ThreadYield (void)
{
   return (ENOSYS);
}

ulong ThreadCreate (void *eip, void *esp)
{
   Thread *t;
   t->tss.eip = (ulong)eip;
   t->tss.esp = (ulong)esp;
   return (ENOSYS);
}

ulong ThreadDestroy (void)
{
   return (ENOSYS);
}
