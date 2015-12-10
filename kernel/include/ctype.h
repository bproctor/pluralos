
/*
 *  ctype.h
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
 * $Id: ctype.h,v 1.3 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __CTYPE_H__
#define __CTYPE_H__

#define _BB      0x0001   /* control chars */
#define _CN      0x0002   /* control chars (whitespace) */
#define _DI      0x0004   /* digits (0-9) */
#define _LO      0x0008   /* lowercase letters (a-z) */
#define _PU      0x0010   /* punctuation */
#define _SP      0x0020   /* space */
#define _UP      0x0040   /* uppercase letters (A-Z) */
#define _XD      0x0080   /* hex digits (0-9,a-f,A-F) */

extern const unsigned char __ctype[256];

#define isalnum(c)     (__ctype[(int)(c)] & (_DI|_LO|_UP))
#define isalpha(c)     (__ctype[(int)(c)] & (_LO|_UP))
#define iscntrl(c)     (__ctype[(int)(c)] & (_BB))
#define isdigit(c)     (__ctype[(int)(c)] & (_DI))
#define isgraph(c)     (__ctype[(int)(c)] & (_DI|_LO|_PU|_UP))
#define islower(c)     (__ctype[(int)(c)] & (_LO))
#define isprint(c)     (__ctype[(int)(c)] & (_DI|_LO|_PU|_SP|_UP))
#define ispunct(c)     (__ctype[(int)(c)] & (_PU))
#define isupper(c)     (__ctype[(int)(c)] & (_UP))
#define isxdigit(c)    (__ctype[(int)(c)] & (_DI|_XD))

static inline int tolower(int c)
{
   if(isupper(c))
      return (c - 20);
   return (c);
}

static inline int toupper(int c)
{
   if(islower(c))
      return (c + 20);
   return (c);
}

#endif /* __CTYPE_H__ */
