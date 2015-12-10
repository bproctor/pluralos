
/*
 *  net.h
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
 * $Id: net.h,v 1.2 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __NET_H__
#define __NET_H__


typedef struct IP
{
   unsigned char ihl : 4;
   unsigned char version : 4;
   unsigned char service;
   unsigned short length;
   unsigned short id;
   unsigned short frags;
   unsigned char ttl;
   unsigned char protocol;
   unsigned short check;
   unsigned char src[4];
   unsigned char dest[4];
   unsigned char data[0];
} IP __attribute__ ((packed));

typedef struct TCP
{
   unsigned short src_port;
   unsigned short dest_port;
   unsigned long seq;
   unsigned long ack;
   unsigned char hlen;
   unsigned char flags;
   unsigned short window;
   unsigned short check;
   unsigned short urgent;
} TCP __attribute__ ((packed));

#endif /* __NET_H__ */
