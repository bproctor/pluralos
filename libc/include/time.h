
/*
 *  time.h -- time types
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
 * $Id: time.h,v 1.4 2003/01/23 06:42:46 fredlie Exp $
 */
 
#ifndef __TIME_H__
#define __TIME_H__

#ifndef NULL
#define NULL   ((void *)0)
#endif

#ifndef __SIZET
#define __SIZET
typedef unsigned int size_t;
#endif

#ifndef __TIME_DEFS
#define __TIME_DEFS
typedef unsigned int clock_t;
typedef unsigned int clockid_t;
typedef unsigned int time_t;
typedef unsigned int timer_t;
#endif

#define CLK_TCK         100
#define CLOCKS_PER_SEC  1000000
#define CLOCK_REALTIME
#define TIMER_ABSTIME

struct tm
{
   int tm_sec;       /* seconds (0-61) */
   int tm_min;       /* minutes (0-59) */
   int tm_hour;      /* hour (0-23) */
   int tm_mday;      /* day of month (1-31) */
   int tm_mon;       /* month of year (0-11) */
   int tm_year;      /* year since 1900 */
   int tm_wday;      /* day of week (0-6) Sunday=0 */
   int tm_yday;      /* day of year (0-365) */
   int tm_isdst;     /* daylight savings flag */
};

struct timespec
{
   time_t tv_sec;    /* seconds */
   long tv_nsec;     /* nanoseconds */
};

struct itimerspec
{
   struct timespec it_interval;  /* time period */
   struct timespec it_value;     /* time expiration */
};

extern int daylight;
extern long timezone;
extern char *tzname[];

char      *asctime (const struct tm *);
char      *asctime_r (const struct tm *, char *);
clock_t    clock (void);
int        clock_getres (clockid_t, struct timespec *);
int        clock_gettime (clockid_t, struct timespec *);
int        clock_settime (clockid_t, struct timespec *);
char      *ctime (const time_t *);
char      *ctime_r (const time_t *, char *);
double     difftime (time_t, time_t);
struct tm *getdate (const char *);
struct tm *gmtime (const time_t *);
struct tm *gmtime_r (const time_t *, struct tm *);
struct tm *localtime (const time_t *);
struct tm *localtime_r (const time_t *, struct tm *);
time_t     mktime (struct tm *);
int        nanosleep (const struct timespec *, struct timespec *);
size_t     strftime (char *, size_t, const char *, const struct tm *);
char      *strptime (const char *, const char *, struct tm *);
time_t     time (time_t *);
int        timer_create (clockid_t, struct sigevent *, timer_t *);
int        timer_delete (timer_t);
int        timer_gettime (timer_t, struct itimerspec *);
int        timer_getoverrun (timer_t);
int        timer_settime (timer_t, int, const struct itimerspec *, 
               struct itimerspec *);
int        tzset (void);

#endif /* __TIME_H__ */
