
/*
 *  stdarg.h
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
 * $Id: stdarg.h,v 1.3 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __STDARG_H__
#define __STDARG_H__

typedef char *va_list;

#define va_arg(a,b)     (*(b *)(((a) += _B(b, 3)) - _B(b, 3)))
#define va_end(a)       (void)0
#define va_start(a,b)   (void)((a) = (char *)&(b) + _B(b, 3))
#define _B(a,b)         ((sizeof(a) + (b)) & ~(b))

#endif /* __STDARG_H__ */
