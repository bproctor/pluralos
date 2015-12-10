
/*
 *  monitor.c
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
 * $Id: monitor.c,v 1.3 2002/12/02 09:06:24 fredlie Exp $
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/clock.h>
#include <console.h>

char *stat_line =
"    Plural System Monitor                                     ";

void monitor (void)
{
   char dt[18];
   ulong i, m, d, y, h, min, s;
   ushort *vid = (ushort *)0xB8000;
   
   for (i = 0; i < 4000; i += 2)
      vid[i] = BLUE|BGBLACK, vid[i+1] = 196;

   ClockGetDate (&y, &m, &d);
   ClockGetTime (&h, &min, &s);   

   sprintf (dt, "%0lu/%0lu/%0lu  %0lu:%0lu:%0lu", m, d, y, h, min, s);

   con_puts (0, 0, BLUE|BGWHITE, dt);
   con_puts (18, 0, BLUE|BGWHITE, stat_line);
   
   while (1)
   {
      /* Main control loop */
   }
}
