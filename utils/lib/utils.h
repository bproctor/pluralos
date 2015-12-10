
/*
 *  utils.h
 *  Copyright (c) 2002-2003 Brad Proctor
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
 * $Id: utils.h,v 1.11 2003/02/16 18:46:40 fredlie Exp $
 */

#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

void               warning (const char *, ...);
void               error (const char *, ...);
void               terror (const char *, ...);
long               getnum_l (const char *);
long long          getnum_ll (const char *);
unsigned long      getnum_ul (const char *);
unsigned long long getnum_ull (const char *);
float              getnum_f (const char *);
double             getnum_d (const char *);
long double        getnum_ld (const char *);
long long          getnum_hex (const char *);
long long          getnum_octal (const char *);
int                yesno (int);

extern char *progname;

static inline void *(xmalloc)(int n)
{
   void *x = malloc (n);
   if (x == NULL)
      error ("could not allocate memory");
   return (x);
}

static inline void *(xrealloc)(void *x, int n)
{
   void *y = realloc (x, n);
   if (y == NULL)
      error ("could not reallocate memory");
   return (x);
}

static inline void *(xcalloc)(int n)
{
   void *x = malloc (n);
   if (x == NULL)
      error ("could not allocate memory");
   return (x);
}

static inline FILE *(xfopen)(const char *name, const char *mode)
{
   FILE *f = fopen (name, mode);
   if (!f)
      error ("cannot open file `%s' %s: %s", name,
         *mode == 'r' ? "for reading" : "for writing", strerror (errno));
   return (f);
}

#endif /* __UTILS_H__ */
