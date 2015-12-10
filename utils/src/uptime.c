
/*
 *  uptime -- print how long the system has been running
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
 * $Id: uptime.c,v 1.9 2003/02/16 18:46:41 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: uptime [long-option]\n"
   "Print how long the system has been running.\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   double uptime;
   unsigned long i, x, d, h, m, s;
   FILE *f;
   
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
         puts ("uptime: version "VERSION);
         return (EXIT_SUCCESS);
      }
   }

   f = xfopen ("/proc/uptime", "r");
   fscanf (f, "%f", &uptime);
   i = (unsigned long)uptime;
   x = (unsigned long)((double)(uptime * 100) - (double)(i * 100));
   d = i / 86400;
   h = (i - (d * 86400)) / 3600;
   m = (i - (d * 86400) - (h * 3600)) / 60;
   s = i % 60;
   
   if (i < 60)
      printf ("%lu.%lu seconds\n", s, x);
   else if (i < 3600)
      printf ("%lu minutes, %lu.%lu seconds\n", m, s, x);
   else if (i < 86400)
      printf ("%lu hours, %lu minutes, %lu.%lu seconds\n", h, m, s, x);
   else
      printf ("%lu days, %lu hours, %lu minutes, %lu.%lu seconds\n",
         d, h, m, s, x);
               
   return (EXIT_SUCCESS);
}
