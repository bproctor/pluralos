
/*
 *  stddef.h
 *  Copyright (c) 2001 Brad Proctor
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
 * $Id: stddef.h,v 1.3 2001/10/28 21:17:33 fredlie Exp $
 */

#ifndef __STDDEF_H__
#define __STDDEF_H__

#ifndef NULL
#define NULL   ((void *)0)
#endif

#ifndef __SIZET
#define __SIZET
typedef unsigned int size_t;
#endif

#endif /* __STDDEF_H__ */
