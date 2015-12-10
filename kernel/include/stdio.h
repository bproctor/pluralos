
/*
 *  stdio.h
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
 * $Id: stdio.h,v 1.5 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __STDIO_H__
#define __STDIO_H__

#ifndef __STDDEF_H__
#include <stddef.h>
#endif

#define BLINK           0x80
#define BLACK           0x00
#define BLUE            0x01
#define CYAN            0x02
#define RED             0x03
#define MAGENTA         0x04
#define BROWN           0x05
#define WHITE           0x06
#define GRAY            0x07
#define LTBLUE          0x08
#define LTGREEN         0x09
#define LTCYAN          0x0A
#define LTRED           0x0B
#define LTMAGENTA       0x0C
#define YELLOW          0x0D
#define BRIGHTWHITE     0x0E
#define BGBLACK         0x00
#define BGBLUE          0x10
#define BGGREEN         0x20
#define BGCYAN          0x30
#define BGRED           0x40
#define BGMAGENTA       0x50
#define BGBROWN         0x60
#define BGWHITE         0x70

#define puts(s)      cputs (7, s)

int vsprintf (char *, const char *, char *);
int sprintf (char *, const char *, ...);
int cprintf (int, const char *, ...);
int printf (const char *, ...);
void cputs (int, const char *);
void clear_screen (void);

#endif /* __STDIO_H__ */
