
/*
 *  stdlib.h
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
 * $Id: stdlib.h,v 1.4 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __STDLIB_H__
#define __STDLIB_H__

#ifndef __STDDEF_H__
#include <stddef.h>
#endif

void *calloc (size_t, size_t);
void *malloc (size_t);
void  free (void *);
void *realloc (void *, size_t);

#endif /* __STDLIB_H__ */
