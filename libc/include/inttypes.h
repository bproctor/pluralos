
/*
 *  inttypes.h -- fixed size integral types
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
 * $Id: inttypes.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __INTTYPES_H__
#define __INTTYPES_H__

typedef signed char        int8_t;
typedef signed short       int16_t;
typedef signed int         int32_t;
typedef signed long long   int64_t;
typedef unsigned char      uint8_t;
typedef unsigned short     uint16_t; 
typedef unsigned int       uint32_t;
typedef unsigned long long uint64_t;
typedef signed int         intptr_t;
typedef unsigned int       uintptr_t;

#endif /* __INTTYPES_H__ */
