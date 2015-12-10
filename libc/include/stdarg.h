
/*
 *  stdarg.h -- handle variable argument lists
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
 * $Id: stdarg.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __STDARG_H__
#define __STDARG_H__

#ifndef __VA_LIST
#define __VA_LIST
typedef char *va_list;
#endif

#define va_arg(a,b)     (*(b *)(((a) += _B(b, 3)) - _B(b, 3)))
#define va_end(a)       (void)0
#define va_start(a,b)   (void)((a) = (char *)&(b) + _B(b, 3))
#define _B(a,b)         ((sizeof(a) + (b)) & ~(b))

#endif /* __STDARG_H__ */
