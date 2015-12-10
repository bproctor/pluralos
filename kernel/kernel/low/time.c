
/*
 *  time.c
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
 * $Id: time.c,v 1.2 2002/12/02 09:06:25 fredlie Exp $
 */

#include <io.h>
#include <rtc.h>
#include <sys/types.h>


ulong get_cmos_time (void)
{
   ulong i, year, mon, day, hour, min, sec;
   for (i = 0; i < 1000000; ++i)
      if (cmos_read (RTC_FREQ_SELECT) & RTC_UIP)
         break;
   for (i = 0; i < 1000000; ++i)
      if (!(cmos_read (RTC_FREQ_SELECT) & RTC_UIP))
         break;
   do {
      sec  = cmos_read (RTC_SECONDS);
      min  = cmos_read (RTC_MINUTES);
      hour = cmos_read (RTC_HOURS);
      day  = cmos_read (RTC_DAY_OF_MONTH);
      mon  = cmos_read (RTC_MONTH);
      year = cmos_read (RTC_YEAR);
   } while (sec != cmos_read (RTC_SECONDS));
   if (!(cmos_read (RTC_CONTROL) & RTC_DM_BINARY))
   {
      bcd_to_bin (sec);
      bcd_to_bin (min);
      bcd_to_bin (hour);
      bcd_to_bin (day);
      bcd_to_bin (mon);
      bcd_to_bin (year);
   }
   if ((year += 1900) < 1970)
      year += 100;

   if ((int)(mon -= 2) <= 0)
      mon += 12, --year;
   return (((((ulong)(year/4 - year/100 + year/400 + 367*mon/12 + day) +
      year*365 - 719499) * 24 + hour) * 60 + min) * 60 + sec);
}

#ifdef CONFIG_X86_TSC
static __init__ ulong calibate_tsc (void)
{
   ulong startlow, starthigh;
   ulong endlow, endhigh;
   ulong count;

   outb (0x61, (inb (0x61) & ~2 | 0x01);
   outb (0x43, 0xB0);
   outb (0x42, (5 * LATCH) & 0xFF);
   outb (0x42, (5 * LATCH) >> 8);

   rdtsc (startlow, starthigh);
   count = 0;
   do { ++count } while ((inb (0x61) & 0x20) == 0);
   rdtsc (endlow, endhigh);
   if (count <= 1)
      return (0);
   __asm__ (
      "subl %2,%0\n\t"
      "sbbl %3,%1\n\t"
      : "=a" (endlow), "=d" (endhigh)
      : "g" (startlow), "g" (starthigh),
        "0" (endlow), "1" (endhigh));
   if (endhigh || endlow <= (5 * 1000020/11932))
      return (0);
   __asm__ (
      "divl %2"
      : "=a" (endlow), "=d" (endhigh)
      : "r" (endlow), "0" (0), "1" (5 * 1000020/11932));         
   return (endlow);
}
#endif
