
/*
 *  sleep.c -- sleep for specified time
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
 * $Id: sleep.c,v 1.8 2003/02/16 18:46:41 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: sleep long-option\n"
   "       sleep time_format\n"
   "Sleep for the specified time.\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Time Format:\n"
   "  time_format can be assembled using the suffixes 'd' for days, \n"
   "  'm' for minutes, 'h' for hours, and 's' for seconds attached to\n"
   "  the number.  Example: sleep 1d3h10m32s will sleep for 1 day, 3 hours\n"
   "  10 minutes, and 32 seconds.  Seconds is the default if no suffix is\n"
   "  used.\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i, t1, t2;
   char *ptr;
   
   progname = argv[0];
   
   if (argc == 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("sleep: version "VERSION);
         return (EXIT_SUCCESS);
      }
   }

   t1 = t2 = 0;  
   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      while (isdigit (*ptr))
         t1 = t1 * 10 + *ptr++ - '0';
         
      switch (*ptr)
      {
         case '\0':
         case 's': break;
         case 'm': t1 *= 60;           break;
         case 'h': t1 *= 60 * 60;      break;
         case 'd': t1 *= 60 * 60 * 24; break;
         default:
            error ("invalid time format");
      }
      t2 += t1;
      t1 = 0;
   }
   
   sleep (t2);
   return (EXIT_SUCCESS);
}
