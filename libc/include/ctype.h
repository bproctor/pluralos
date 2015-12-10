
/*
 *  ctype.h -- character types
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
 * $Id: ctype.h,v 1.6 2003/01/23 06:42:46 fredlie Exp $
 */

#ifndef __CTYPE_H__
#define __CTYPE_H__

int isalnum (int), isalpha (int), isblank (int);
int iscntrl (int), isdigit (int), isgraph (int), islower (int);
int isprint (int), ispunct (int), isspace (int), isupper (int);
int isxdigit (int), tolower (int), toupper (int);

#define _BB      0x0001   /* control chars */
#define _CN      0x0002   /* control chars (whitespace) */
#define _DI      0x0004   /* digits (0-9) */
#define _LO      0x0008   /* lowercase letters (a-z) */
#define _PU      0x0010   /* punctuation */
#define _SP      0x0020   /* space */
#define _UP      0x0040   /* uppercase letters (A-Z) */
#define _XD      0x0080   /* hex digits (0-9,a-f,A-F) */

extern const unsigned char *__ctype;
extern const unsigned char *__tolower;
extern const unsigned char *__toupper;

#define isalnum(c)      (__ctype[(int)(c)] & (_DI|_LO|_UP))
#define isalpha(c)      (__ctype[(int)(c)] & (_LO|_UP))
#define isblank(c)      (__ctype[(int)(c)] & (_SP))
#define iscntrl(c)      (__ctype[(int)(c)] & (_BB))
#define isdigit(c)      (__ctype[(int)(c)] & (_DI))
#define isgraph(c)      (__ctype[(int)(c)] & (_DI|_LO|_PU|_UP))
#define islower(c)      (__ctype[(int)(c)] & (_LO))
#define isprint(c)      (__ctype[(int)(c)] & (_DI|_LO|_PU|_SP|_UP))
#define ispunct(c)      (__ctype[(int)(c)] & (_PU))
#define isspace(c)      (__ctype[(int)(c)] & (_CN))
#define isupper(c)      (__ctype[(int)(c)] & (_UP))
#define isxdigit(c)     (__ctype[(int)(c)] & (_DI|_XD))

#define tolower(c)      (__tolower[(int)(c)])
#define toupper(c)      (__toupper[(int)(c)])

#ifndef __STRICT_ANSI__
int isascii (int), toascii (int);

#define isascii(c)      (((c) & ~0x7F) == 0)
#define toascii(c)      ((c) & 0x7F)
#define _tolower(c)     (__tolower[(int)(c)])
#define _toupper(c)     (__toupper[(int)(c)])
#endif

#endif /* __CTYPE_H__ */
