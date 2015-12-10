
/*
 *  limits.h
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * $Id: limits.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __LIMITS_H__
#define __LIMITS_H__

#define MB_LEN_MAX      16
#define CHAR_BIT        8

#define SCHAR_MIN       (-0x80)
#define SCHAR_MAX       (0x7F)

#define CHAR_MIN        (-0x80)
#define CHAR_MAX        (0x7F)
#define UCHAR_MAX       (0xFF)

#define SHRT_MIN        (-0x8000)
#define SHRT_MAX        (0x7FFF)
#define USHRT_MAX       (0xFFFF)

#define INT_MIN         (-0x80000000)
#define INT_MAX         (0x7FFFFFFF)
#define UINT_MAX        (0xFFFFFFFF)

#define LONG_MIN        (-0x80000000)
#define LONG_MAX        (0x7FFFFFFF)
#define ULONG_MAX       (0xFFFFFFFF)

#endif /* __LIMITS_H__ */
