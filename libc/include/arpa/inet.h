
/*
 *  inet.h -- definitions for internet operations
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
 * $Id: inet.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __ARPA_INET_H__
#define __ARPA_INET_H__

#ifndef __NETINET_IN_H__
#include <netinet/in.h>
#endif

#ifndef __INTTYPES_H__
#include <inttypes.h>
#endif

uint32_t htonl (uint32_t);
uint16_t htons (uint16_t);
uint32_t ntohl (uint32_t);
uint16_t ntohs (uint16_t);

in_addr_t      inet_addr (const char *);
char          *inet_ntoa (struct in_addr);
const char    *inet_ntop (int, const void *restrict, char *restrict,
                  socklen_t);
int            inet_pton (int, const char *restrict, void *restrict);

#endif /* __ARPA_INET_H__ */
