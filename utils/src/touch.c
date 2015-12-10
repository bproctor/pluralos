
/*
 *  touch -- change file access and modification times
 *  Copyright (c) 2003 Brad Proctor
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
 * $Id: touch.c,v 1.5 2003/02/10 20:46:19 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <utime.h>
#include <sys/stat.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: touch long-option\n"
   "Change file access and modification times.\n"
   "\n"
   "  -a         Change the access time of the file\n"
   "  -c         Do not create the file if it does not exist\n"
   "  -m         Change the modification time of the file\n"
   "  -r file    Use time of `file' to get times\n"
   "  -t time    Use specified `time' instead of the current time\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   " The time field for the -t option is in the following format:\n"
   " [[CC]YY]MMddhhmm.[ss]\n"
   " CC = century      YY = two digit year\n"
   " dd = day          hh = hour\n"
   " mm = minute       ss = second\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_access = 0;
static char flag_modification = 0;
static char flag_create = 1;
static struct stat s;
static long now = 0;

static struct utimbuf t = {0, 0};

static void do_touch (const char *name)
{
   if (flag_access)
   {
      lstat (name, &s);
      t.modtime = s.st_mtime;
   }
   else if (flag_modification)
   {
      lstat (name, &s);
      t.actime = s.st_atime;
   }
   utime (name, &t);
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   char *ptr, *c;
   struct tm *m;
   
   progname = argv[0];
   time (&now);
   t.actime = now;
   t.modtime = now;
   
   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      if (*ptr == '-')
      {
         while (*++ptr)
         switch (*ptr)
         {
            case '-':
               if (!strcmp (ptr, "-help"))
               {
                  puts (help_text);
                  return (EXIT_SUCCESS);
               }
               else if (!strcmp (ptr, "-version"))
               {
                  puts ("touch: version "VERSION);
                  return (EXIT_SUCCESS);
               }
            case 'a':
               flag_access = 1;
               continue;
            case 'c':
               flag_create = 0;
               continue;
            case 'm':
               flag_modification = 1;
               continue;
            case 'r':
               if (++i >= argc)
                  terror ("missing operand to `-r' option");
               lstat (argv[i], &s);
               t.actime = s.st_atime;
               t.modtime = s.st_mtime;
               break;
            case 't':
               if (++i >= argc)
                  terror ("missing operand to `-t' option");
               m = xmalloc (sizeof (struct tm));
               memset (m, '\0', sizeof (*m));
               c = strptime (argv[i], "%C%Y%m%d%H%M%S", m);
               t.actime = mktime (m);
               t.modtime = mktime (m);
               break;
         }
      }
      else
         do_touch (argv[i]);
   }

   return (EXIT_SUCCESS);
}
