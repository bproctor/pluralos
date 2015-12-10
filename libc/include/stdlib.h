
/*
 *  stdlib.h -- standard library definitions
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
 * $Id: stdlib.h,v 1.3 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __STDLIB_H__
#define __STDLIB_H__

#ifndef __STDDEF_H__
#include <stddef.h>
#endif

#ifndef __LIMITS_H__
#include <limits.h>
#endif

#ifndef __MATH_H__
#include <math.h>
#endif

#ifndef __SYS_WAIT_H__
#include <sys/wait.h>
#endif

#define EXIT_FAILURE    1
#define EXIT_SUCCESS    0
#define RAND_MAX        (INT_MAX-1)
#define MB_CUR_MAX      1

typedef struct div_t
{
   int quot;   /* quotient */
   int rem;    /* remainder */
} div_t;

typedef struct ldiv_t
{
   long quot;  /* quotient */
   long rem;   /* remainder */
} ldiv_t;

typedef struct lldiv_t
{
   long long quot;   /* quotient */
   long long rem;    /* remainder */
} lldiv_t;

long   a64l (const char *);
void   abort (void);
int    abs (int);
int    atexit (void (*)(void));
double atof (const char *);
int    atoi (const char *);
long   atol (const char *);
void  *bsearch (const void *, const void *, size_t, size_t,
         int (*)(const void *, const void *));
void  *calloc (size_t, size_t);
div_t  div (int, int);
double drand48 (void);
char  *ecvt (double, int, int *, int *);
double erand48 (unsigned short [3]);
void   exit (int);
char  *fcvt (double, int, int *, int *);
void   free (void *);
char  *gcvt (double, int, char *);
char  *getenv (const char *);
int    getsubopt (char **, char *const *, char **);
int    grantpt (int);
char  *initstate (unsigned, char *, size_t);
long   jrand48 (unsigned short [3]);
char  *l64a (long);
long   labs (long);
void   lcong48 (unsigned short [7]);
ldiv_t ldiv (long, long);
long   lrand48 (void);
void  *malloc (size_t);
int    mblen (const char *, size_t);
size_t mbstowcs (wchar_t *, const char *, size_t);
int    mbtowc (wchar_t *, const char *, size_t);
char  *mktemp (char *);
int    mkstemp (char *);
long   mrand48 (void);
long   nrand48 (unsigned short [3]);
char  *ptsname (int);
int    putenv (char *);
void   qsort (void *, size_t, size_t, int (*)(const void *,
         const void *));
int    rand (void);
int    rand_r (unsigned *);
long   random (void);
void  *realloc (void *, size_t);
char  *realpath (const char *, char *);
unsigned short seed48 (unsigned short [3]);
void   setkey (const char *);
char  *setstate (const char *);
void   srand (unsigned);
void   srand48 (long);
void   srandom (unsigned);
double strtod (const char *, char **);
long   strtol (const char *, char **, int);
unsigned long strtoul (const char *, char **, int);
int    system (const char *);
int    ttyslot (void);
int    unlockpt (int);
void  *valloc (size_t);
size_t wcstombs (char *, const wchar_t *, size_t);
int    wctomb (char *, wchar_t);

#define abs(i)    ((i) < 0 ? -i : i)
#define labs(i)   ((i) < 0 ? -i : i)

#endif /* __STDLIB_H__ */
