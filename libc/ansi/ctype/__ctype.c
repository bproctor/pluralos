
/*
 *  __ctype.c
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
 * $Id: __ctype.c,v 1.3 2003/01/20 04:23:26 fredlie Exp $
 */

#include <ctype.h>
#include <stdio.h>

#define  XSP   (_BB|_CN)
#define  XSA   (_CN|_SP)
#define  XLO   (_LO|_XD)
#define  XUP   (_UP|_XD)

static const unsigned char ctype_table[257] =
{
   EOF,
   _BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,   /* 0x00 - 0x07 */
   _BB, XSP, XSP, XSP, XSP, XSP, _BB, _BB,   /* 0x08 - 0x0F */
   _BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,   /* 0x10 - 0x17 */
   _BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,   /* 0x18 - 0x1F */
   XSA, _PU, _PU, _PU, _PU, _PU, _PU, _PU,   /* 0x20 - 0x27 */
   _PU, _PU, _PU, _PU, _PU, _PU, _PU, _PU,   /* 0x28 - 0x2F */
   _DI, _DI, _DI, _DI, _DI, _DI, _DI, _DI,   /* 0x30 - 0x37 */
   _DI, _DI, _PU, _PU, _PU, _PU, _PU, _PU,   /* 0x38 - 0x3F */
   _PU, XUP, XUP, XUP, XUP, XUP, XUP, _UP,   /* 0x40 - 0x47 */
   _UP, _UP, _UP, _UP, _UP, _UP, _UP, _UP,   /* 0x48 - 0x4F */
   _UP, _UP, _UP, _UP, _UP, _UP, _UP, _UP,   /* 0x50 - 0x57 */
   _UP, _UP, _UP, _PU, _PU, _PU, _PU, _PU,   /* 0x58 - 0x5F */
   _PU, XLO, XLO, XLO, XLO, XLO, XLO, _LO,   /* 0x60 - 0x67 */
   _LO, _LO, _LO, _LO, _LO, _LO, _LO, _LO,   /* 0x68 - 0x6F */
   _LO, _LO, _LO, _LO, _LO, _LO, _LO, _LO,   /* 0x70 - 0x77 */
   _LO, _LO, _LO, _PU, _PU, _PU, _PU, _BB,   /* 0x78 - 0x7F */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0x80 - 0x87 */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0x88 - 0x8F */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0x90 - 0x97 */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0x98 - 0x9F */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xA0 - 0xA7 */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xA8 - 0xAF */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xB0 - 0xB7 */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xB8 - 0xBF */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xC0 - 0xC7 */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xC8 - 0xCF */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xD0 - 0xD7 */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xD8 - 0xDF */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xE0 - 0xE7 */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xE8 - 0xEF */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xF0 - 0xF7 */
     0,   0,   0,   0,   0,   0,   0,   0,   /* 0xF8 - 0xFF */
};

const unsigned char *__ctype = &ctype_table[1];
