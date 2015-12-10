
/*
 *  strings.h -- string operations
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
 * $Id: strings.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __STRINGS_H__
#define __STRINGS_H__

#ifndef __SIZET
#define __SIZET
typedef unsigned int size_t;
#endif

int   bcmp   (const void *, const void *, size_t);
void  bcopy  (const void *, void *, size_t);
void  bzero  (void *, size_t);
int   ffs    (int);
char *index  (const char *, int);
char *rindex (const char *, int);
int   strcasecmp (const char *, const char *);
int   strncasecmp (const char *, const char *, size_t);

#endif /* __STRINGS_H__ */
