
/*
 *  string.h
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
 * $Id: string.h,v 1.4 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __STRING_H__
#define __STRING_H__

#ifndef __STDDEF_H__
#include <stddef.h>
#endif

void  *memchr  (const void *, int, size_t);
int    memcmp  (const void *, const void *, size_t);
void  *memcpy  (void *, const void *, size_t);
void  *memmove (void *, void *, size_t);
void  *memset  (void *, int, size_t);
char  *strcat  (char *, const char *);
char  *strchr  (const char *, int);
int    strcmp  (const char *, const char *);
int    strcoll (const char *, const char *);
char  *strcpy  (char *, const char *);
size_t strcspn (const char *, const char *);
char  *strerror (int);
size_t strlen  (const char *);
char  *strncat (char *, const char *, size_t);
int    strncmp (const char *, const char *, size_t);
char  *strncpy (char *, const char *, size_t);
char  *strpbrk (const char *, const char *);
char  *strrchr (const char *, int);
size_t strspn  (const char *, const char *);
char  *strstr  (const char *, const char *);
char  *strtok  (char *, char *);
size_t strxfrm (char *, const char *, size_t);

#ifdef __XOPEN__
void *memccpy  (void *, const void *, int, size_t);
char *strdup   (const char *);
char *strtok_r (char *, const char *, size_t);
#endif

#endif /* __STRING_H__ */
