
/*
 *  message.h
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
 * $Id: message.h,v 1.2 2002/12/02 09:06:24 fredlie Exp $
 */

#ifndef __SYS_MESSAGE_H__
#define __SYS_MESSAGE_H__

#ifndef __SYS_TYPES_H__
#include <sys/types.h>
#endif 

typedef struct Message
{
   ulong msg[2];
   ulong used;
   struct Message *next;
   struct Message *prev;
} Message;

ulong MessageCreate     (void);
ulong MessageDestroy    (void);
ulong MessageBroadcast  (ulong, ulong,   ulong);
ulong MessageCheck      (ulong, ulong *, ulong *);
ulong MessagePost       (ulong, ulong,   ulong);
ulong MessageRecieve    (ulong, ulong *, ulong *);
ulong MessageSend       (ulong, ulong,   ulong);

#endif /* __SYS_MESSAGE_H__ */
