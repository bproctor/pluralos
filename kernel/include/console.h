
/*
 *  console.h
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
 * $Id: console.h,v 1.3 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __CONSOLE_H__
#define __CONSOLE_H__

void con_set_xy (int, int);
void con_putc (int, int, int, char);
void con_puts (int, int, int, const char *);
void con_clear_screen (void);
int con_printf (int, int, int, const char *, ...);

#endif /* __CONSOLE_H__ */
