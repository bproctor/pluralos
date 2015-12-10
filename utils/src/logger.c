
/*
 *  logger -- log messages
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
 * $Id: logger.c,v 1.6 2003/02/10 20:46:10 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: logger long-option\n"
   "       logger [-f file] message\n"
   "Log messages.\n"
   "\n"
   "  -f file    Log messages to `file'\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static FILE *logfile = 0;

static void do_logger (const char *msg)
{
   char *t, *u;
   time_t now;
   
   u = getlogin ();
   if (!u)
      u = "<anonymous>";
   if (time (&now) < 0)
      error ("cannot get current time: %s", strerror (errno));
   t = ctime (&now);
   if (!t)
      error ("cannot get current time: %s", strerror (errno));
   fprintf (logfile, "%.24s:%s: %s\n", t, u, msg);
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i = 1;
   progname = argv[0];

   if (argc == 1)
      terror ("too few arguments");
   else if (argc >= 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("logger: version "VERSION);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "-f"))
      {
         if (argc >= 3)
            logfile = xfopen (argv[2], "w");
         i += 2;
      }
      
      if (logfile == NULL)
         logfile = xfopen ("/var/log/syslog", "w");
      fseek (logfile, 0, SEEK_END);
      
      for (; i < argc; ++i)
         do_logger (argv[i]);
   }
   return (EXIT_SUCCESS);
}
