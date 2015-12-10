
/*
 *  stdio.h -- standard buffered input/output
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * $Id: stdio.h,v 1.2 2002/12/12 18:23:53 fredlie Exp $
 */

#ifndef __STDIO_H__
#define __STDIO_H__

#ifndef __STDDEF_H__
#include <stddef.h>
#endif

#define BUFSIZ          4096
#define FILENAME_MAX    255
#define FOPEN_MAX       
#define _IOFBF          0
#define _IOLBF          1
#define _IONBF          2
#define L_ctermid
#define L_cuserid
#define L_tmpnam
#define SEEK_CUR
#define SEEK_END
#define SEEK_SET
#define TMP_MAX
#define EOF             (-1)
#define P_tmpdir
#define stderr          0
#define stdin           1
#define stdout          2

typedef unsigned int FILE;
typedef unsigned int fpos_t;

#ifndef __VA_LIST
#define __VA_LIST
typedef char *va_list;
#endif

void   clearerr (FILE *);
char  *ctermid (char *);
char  *cuserid (char *);
int    fclose (FILE *);
FILE  *fdopen (int, const char *);
int    feof (FILE *);
int    ferror (FILE *);
int    fflush (FILE *);
int    fgetc (FILE *);
int    fgetpos (FILE *, fpos_t *);
char  *fgets (char *, int, FILE *);
int    fileno (FILE *);
void   flockfile (FILE *);
FILE  *fopen (const char *, const char *);
int    fprintf (FILE *, const char *, ...);
int    fputc (int, FILE *);
int    fputs (const char *, FILE *);
size_t fread (void *, size_t, size_t, FILE *);
FILE  *freopen (const char *, const char *, FILE *);
int    fscanf (FILE *, const char *);
int    fseek (FILE *, long, int);
int    fseeko (FILE *, off_t, int);
int    fsetpos (FILE *, const fpos_t *);
long   ftell (FILE *);
off_t  ftello (FILE *);
int    ftrylockfile (FILE *);
void   funlockfile (FILE *);
size_t fwrite (const void *, size_t, size_t, FILE *);
int    getc (FILE *);
int    getchar (void);
int    getc_unlocked (FILE *);
int    getchar_unlocked (void);
int    getopt (int, char *const [], const char);
char  *gets (char *);
int    getw (FILE *);
int    pclose (FILE *);
void   perror (const char *);
FILE  *popen (const char *, const char *);
int    printf (const char *, ...);
int    putc (int, FILE *);
int    putchar (int);
int    putc_unlocked (int, FILE *);
int    putchar_unlocked (int);
int    puts (const char *);
int    putw (int, FILE *);
int    remove (const char *);
int    rename (const char *, const char *);
void   rewind (FILE *);
int    scanf (const char *, ...);
void   setbuf (FILE *, char *);
int    setvbuf (FILE *, char *, int, size_t);
int    snprintf (char *, size_t, const char *, ...);
int    sprintf (char *, const char *, ...);
int    sscanf (const char *, const char *, int, ...);
char  *tempnam (const char *, const char *);
FILE  *tmpfile (void);
char  *tmpnam (char *);
int    ungetc (int, FILE *);
int    vfprintf (FILE *, const char *, va_list);
int    vprintf (const char *, va_list);
int    vsnprintf (char *, size_t, const char *, va_list);
int    vsprintf (char *, const char *, va_list);

extern char *optarg;
extern int   opterr;
extern int   optind;
extern int   optopt;

#endif /* __STDIO_H__ */
