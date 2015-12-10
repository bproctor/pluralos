
/*
 *  message.c
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
 * $Id: message.c,v 1.6 2002/12/22 18:22:27 fredlie Exp $
 */

#include <sys/errno.h>
#include <sys/types.h>
#include <sys/message.h>
#include <sys/channel.h>
#include <stddef.h>
#include <config.h>
#include <spinlock.h>
#include <thread.h>

Spinlock message_spinlock;

static Message message_pool[CONFIG_MESSAGES];
static Message *message_pool_head;
static Message *message_head;

/*
 * Initialize the pool of messages
 */

void init_messages (void)
{
   ulong i = 0;
   
   spin_lock (message_spinlock);
   while (i < CONFIG_MESSAGES-1)
   {
      message_pool[i].next = &message_pool[i+1];
      ++i;
   }
   message_pool[i].next = 0;
   spin_unlock (message_spinlock);
}

static Message *alloc_message (void)
{
   Message *ptr = message_pool_head;
   
   spin_lock (message_spinlock);
   while (ptr)
   {
      if (ptr->used == 0)
      {
         ptr->prev->next = ptr->next;  /* Take it from the pool */
         ptr->next = message_head;     /* Put at the front of the used pool */
         ptr->used = 1;
         message_head = ptr;
         break;
      }
      ptr = ptr->next;        /* Get next message */
   }      
   spin_unlock (message_spinlock);
   return (ptr);
}

ulong MessageCreate (void)
{
   return (ENOSYS);
}

ulong MessageDestroy (void)
{
   return (ENOSYS);
}

ulong MessageSend (ulong channel, ulong msg1, ulong msg2)
{
   Message *msg;

   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);

   if (channel_pool[channel].owner == 0
      || channel_pool[channel].flag_message == 0)
      return (EPERM);

   if (channel_pool[channel].limit <= channel_pool[channel].size)
      return (EAGAIN);

   msg = alloc_message ();
   if (msg == NULL)
      return (ENOMSG);
   msg->msg[1] = msg1;
   msg->msg[2] = msg2;
   return (EOK);
}

ulong MessageRecieve (ulong channel, ulong *msg1, ulong *msg2)
{
   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);

   if (channel_pool[channel].owner != current->tid
      || channel_pool[channel].flag_message == 0)
      return (EPERM);
   
   return (ENOSYS);
}

ulong MessageBroadcast (ulong channel, ulong msg1, ulong msg2)
{
   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);

   return (ENOSYS);
}

ulong MessageCheck (ulong channel, ulong *msg1, ulong *msg2)
{
   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);

   if (channel_pool[channel].owner != current->tid
      || channel_pool[channel].flag_message == 0)
      return (EPERM);

   return (ENOSYS);
}

ulong MessagePost (ulong channel, ulong msg1, ulong msg2)
{
   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);

   if (channel_pool[channel].owner == 0
      || channel_pool[channel].flag_message == 0)
      return (EPERM);

   if (channel_pool[channel].limit <= channel_pool[channel].size)
      return (EAGAIN);

   return (ENOSYS);
}
