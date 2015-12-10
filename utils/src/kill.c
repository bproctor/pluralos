
/*
 *  kill -- terminate the specified process
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
 * $Id: kill.c,v 1.6 2003/01/28 04:00:51 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <signal.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: kill long-option\n"
   "       kill [-9] pid\n"
   "Terminate the specified process using SIGTERM.\n"
   "\n"
   "  -9         Terminate the process immediately (SIGKILL)\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_kill9 = 0;

static void do_kill (char *s)
{
   int pid = 0, err;
   char *ptr = s;
   
   while (isdigit (*ptr))
      pid = pid * 10 + *ptr++ - '0';
      
   if (*ptr != '\0')
      error ("argument must be a valid PID");
   
   if (flag_kill9)
      err = kill (pid, SIGKILL);
   else
      err = kill (pid, SIGTERM);
      
   if (err)
      error ("cannot kill %d: %s", pid, strerror (errno));
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   
   progname = argv[0];

   if (argc == 1)
      terror ("too few arguments");   
   else if (argc == 2)
   {
      if (!strcmp (argv[1], "--help"))
         puts (help_text);
      else if (!strcmp (argv[1], "--version"))
         puts ("kill: version "VERSION);
      else
         do_kill (argv[1]);
   }
   else if (argc >= 3)
   {
      if (!strcmp (argv[1], "-9"))
         flag_kill9 = 1;
         
      for (i = flag_kill9 ? 2 : 1; i < argc; ++i)
         do_kill (argv[i]);
   }
         
   return (EXIT_SUCCESS);
}
