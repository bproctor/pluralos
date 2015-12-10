
/*
 *  channel.c
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
 * $Id: channel.c,v 1.6 2002/12/06 13:27:53 fredlie Exp $
 */

#include <sys/errno.h>
#include <sys/types.h>
#include <sys/channel.h>
#include <string.h>
#include <config.h>
#include <thread.h>
#include <spinlock.h>

Spinlock channel_spinlock;

Channel channel_pool[CONFIG_CHANNELS];

/*
 * Create a channel, allocate it from the pool.
 */

ulong ChannelCreate (ulong *channel)
{
   ulong i;

   spin_lock (channel_spinlock);
   for (i = 0; i < CONFIG_CHANNELS; ++i)
      if (channel_pool[i].owner == 0)
      {
         channel_pool[i].owner = current->tid;
         channel_pool[i].limit = ~0UL;
         channel_pool[i].size = 0;
         channel_pool[i].flag_message = 0;
         channel_pool[i].head = NULL;
         *channel = i;
         return (EOK);
      }
   spin_unlock (channel_spinlock);
   return (EAGAIN);
}

/*
 * Destroy a channel, give it back to the pool.
 */

ulong ChannelDestroy (ulong channel)
{
   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);
   if (channel_pool[channel].owner != current->tid)
      return (EPERM);
   spin_lock (channel_spinlock);
   channel_pool[channel].owner = 0;
   spin_unlock (channel_spinlock);
   return (EOK);
}

/*
 * Set the maximum number of allowed threads or messages that
 * can wait on a channel.
 */

ulong ChannelSetLimit (ulong channel, ulong limit)
{
   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);
   if (channel_pool[channel].owner != current->tid)
      return (EPERM);
   if (channel_pool[channel].size >= limit)
      return (EAGAIN);
   spin_lock (channel_spinlock);
   channel_pool[channel].limit = limit;
   spin_unlock (channel_spinlock);
   return (EOK);
}

/*
 * Get the maximum number of allowed threads or messages that
 * can wait on a channel.
 */

ulong ChannelGetLimit (ulong channel, ulong *limit)
{
   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);
   if (channel_pool[channel].owner != current->tid)
      return (EPERM);
   *limit = channel_pool[channel].limit;
   return (EOK);
}

/*
 * Purge the channel, removing all threads and messages.
 */

ulong ChannelPurge (ulong channel)
{
   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);
   if (channel_pool[channel].owner != current->tid)
      return (EPERM);
   spin_lock (channel_spinlock);
   channel_pool[channel].size = 0;
   channel_pool[channel].head = 0;
   spin_unlock (channel_spinlock);
   return (EOK);
}

/*
 * Get the owner of the specified channel.
 */

ulong ChannelGetOwner (ulong channel, ulong *owner)
{
   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);
   *owner = channel_pool[channel].owner;
   return (EOK);
}

/*
 * Set the owner of the specified channel.
 *
 * This needs work!
 */

ulong ChannelSetOwner (ulong channel, ulong owner)
{
   if (channel >= CONFIG_CHANNELS)
      return (EINVAL);
   spin_lock (channel_spinlock);
   channel_pool[channel].owner = owner;
   spin_unlock (channel_spinlock);
   return (EOK);
}
