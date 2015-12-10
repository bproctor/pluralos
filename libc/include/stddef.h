
/*
 *  stddef.h -- standard type definitions
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
 * $Id: stddef.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __STDDEF_H__
#define __STDDEF_H__

#ifndef NULL
#define NULL      ((void *)0)
#endif

#ifndef __SIZET
#define __SIZET
typedef unsigned int size_t;
#endif

typedef int offsetof_t;
typedef int ptrdiff_t;
typedef int wchar_t;

typedef int off_t;

#endif /* __STDDEF_H__ */