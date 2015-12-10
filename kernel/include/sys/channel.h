
/*
 *  channel.h
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
 * $Id: channel.h,v 1.3 2002/12/02 09:06:24 fredlie Exp $
 */

#ifndef __SYS_CHANNEL_H__
#define __SYS_CHANNEL_H__

#ifndef __SYS_TYPES_H__
#include <sys/types.h>
#endif

typedef struct Channel
{
   ulong owner;         /* Owner of the channel */
   ulong limit;         /* Message/thread limit */
   ulong size;          /* # of messages/threads on the channel */
   ulong flag_message;  /* =1 if this channel is for messages */
   void *head;          /* Pointer to head of message or thread list */
   void *tail;          /* Pointer to tail of message or thread list */
} Channel;

ulong ChannelCreate   (ulong *);
ulong ChannelDestroy  (ulong);
ulong ChannelPurge    (ulong);
ulong ChannelGetOwner (ulong, ulong *);
ulong ChannelSetOwner (ulong, ulong);
ulong ChannelGetLimit (ulong, ulong *);
ulong ChannelSetLimit (ulong, ulong);

#ifdef __KERNEL__
extern Channel channel_pool[];
#endif

#endif /* __SYS_CHANNEL_H__ */
