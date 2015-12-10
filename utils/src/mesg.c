
/*
 *  mesg -- allow or deny messages
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
 * $Id: mesg.c,v 1.6 2003/01/29 08:20:42 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: mesg long-option\n"
   "       mesg [y | n]\n"
   "Allow or deny messages.\n"
   "\n"
   " y           Allow write access to your terminal\n"
   " n           Deny write access to your terminal\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "If neither y or n is specified, mesg will display the current\n"
   "write state of your terminal\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   struct stat s;
   char *tty;
   
   progname = argv[0];

   tty = ttyname (STDERR_FILENO);
   if (tty == NULL)
      error ("ttyname failed: %s", strerror (errno));
   if (stat (tty, &s) < 0)
      error ("cannot stat tty: %s", strerror (errno));
   

   if (argc == 1)
   {
      if (s.st_mode & (S_IWGRP | S_IWOTH))
      {
         puts ("is y");
         return (EXIT_SUCCESS);
      }
      else
      {
         puts ("is n");
         return (EXIT_FAILURE);
      }
   }
   else if (argc == 2)
   {
      if (!strcmp (argv[1], "--help"))
         puts (help_text);
      else if (!strcmp (argv[1], "--version"))
         puts ("mesg: version "VERSION);
      else if (!strcmp (argv[1], "y"))
      {
         if (chmod (tty, s.st_mode | S_IWGRP) < 0)
            error ("cannot change mode: %s", strerror (errno));
      }
      else if (!strcmp (argv[1], "n"))
      {
         if (chmod (tty, s.st_mode & ~S_IWGRP) < 0)
            error ("cannot change mode: %s", strerror (errno));
      }
      else
         terror ("invalid option `%s'", argv[1]);
   }
   else
      terror ("too many arguments");

   return (EXIT_SUCCESS);
}
