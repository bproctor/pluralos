
/*
 *  tcp.c
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
 * $Id: tcp.c,v 1.2 2002/12/02 04:13:06 fredlie Exp $
 */

#include <sys/types.h>
#include <net.h>

ushort tcp_cksum (ushort *buf, int len)
{
   ulong i, sum = 0;
   
   if (len & 1)
      ((char *)buf)[len] = 0, ++len;
   len >>= 1;
   for (i = 0; i < len; ++i)
      sum += buf[i];
   sum = (sum >> 16) + (sum & 0xFFFF);
   sum += sum >> 16;
   
   return (~sum);
}
