
/*
 *  clock.c
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * $Id: clock.c,v 1.3 2002/12/06 13:27:53 fredlie Exp $
 */

#include <stddef.h>
#include <sys/types.h>
#include <sys/errno.h>

struct _time {
   ulong year;
   ulong month;
   ulong yday;
   ulong mday;
   ulong wday;
   ulong hour;
   ulong min;
   ulong sec;
};

const unsigned short __mon_yday[2][13] =
{
   {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365},
   {0, 31, 60, 91, 121, 152, 182, 213, 244, 274, 305, 335, 366},
};

static ulong get_time (struct _time *t)
{
   ulong days, rem, y;
   ulong x;
   const ushort *ip;
   x = get_cmos_time ();
   days = x / 86400;
   rem = x % 86400;
   while (rem < 0)
      rem += 86400, --days;
   while (rem >= 86400)
      rem -= 86400, ++days;
   t->hour = rem / 3600;
   rem %= 3600;
   t->min = rem / 60;
   t->sec = rem % 60;
   t->wday = (4 + days) % 7;
   if (t->wday < 0)
      t->wday += 7;
   y = 1970;

#define DIV(a, b)    ((a) / (b) - ((a) % (b) < 0))
#define LEAPS(y)     (DIV(y, 4) - DIV(y, 100) + DIV(y, 400))
#define __isleap(y)  ((y) % 4 == 0 && ((y) % 100 != 0 || (y) % 400 == 0))
   
   while (days < 0 || days >= (__isleap(y) ? 366 : 365))
   {
      ulong yg = y + days / 365 - (days % 365 < 0);
      days -= ((yg - y) * 365 + LEAPS (yg - 1) - LEAPS (y - 1));
      y = yg;
   }
   t->year = y - 1900;
   if (t->year != y - 1900)
      return (1);
   t->yday = days;
   ip = __mon_yday[__isleap(y)];
   for (y = 11; days < (ulong)ip[y]; --y)
      continue;
   days -= ip[y];
   t->month = y;
   t->mday = days + 1;
   return (EOK);
}

ulong ClockGetDate (ulong *year, ulong *month, ulong *day)
{
   struct _time t;
   get_time (&t);
   *year = t.year;
   *month = t.month;
   *day = t.mday;
   return (ENOSYS);
}

ulong ClockGetTime (ulong *hour, ulong *min, ulong *sec)
{
   struct _time t;
   get_time (&t);
   *hour = t.hour;
   *min = t.min;
   *sec = t.sec;
   return (EOK);
}

ulong ClockSetDate (void)
{
   return (ENOSYS);
}

ulong ClockSetTime (void)
{
   return (ENOSYS);
}
