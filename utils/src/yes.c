
/*
 *  yes -- print y or a message forever
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
 * $Id: yes.c,v 1.12 2003/01/29 08:20:45 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: yes long-option\n"
   "       yes [message]\n"
   "Print 'y' or a message forever.\n"
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
   if (argc == 1)
   {
      while (1)
         puts ("y");
      return (EXIT_SUCCESS);
   }

   else if (argc == 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("yes: version "VERSION);
         return (EXIT_SUCCESS);
      }
   }

   while (1)
   {
      int i;
      for (i = 1; i < argc; ++i)
      {
         fputs (argv[i], stdout);
         if (i == argc - 1)
            putchar ('\n');
         else
           putchar (' ');
      }
   }

   return (EXIT_SUCCESS);
}
