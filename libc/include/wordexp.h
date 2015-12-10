
/*
 *  wordexp.h
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
 * $Id: wordexp.h,v 1.4 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __WORDEXP_H__
#define __WORDEXP_H__

typedef struct
{
   size_t   we_wordc;
   char   **we_wordv;
   size_t   we_offs;
} wordexp_t;

#define WRDE_APPEND     0x0001
#define WRDE_DOOFFS     0x0002
#define WRDE_NOCMD      0x0004
#define WRDE_REUSE      0x0008
#define WRDE_SHOWERR    0x0010
#define WRDE_UNDEF      0x0020
#define WRDE_BADCHAR    0x0040
#define WRDE_BADVAL     0x0080
#define WRDE_CMDSUB     0x0100
#define WRDE_NOSPACE    0x0200
#define WRDE_NOSYS      0x0400
#define WRDE_SYNTAX     0x0800

#ifndef __SIZET
#define __SIZET
typedef unsigned int size_t;
#endif

int   wordexp (const char *restrict, wordexp_t *restrict, int);
void  wordfree (wordexp_t *);

#endif /* __WORDEXP_H__ */
