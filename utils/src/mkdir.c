
/*
 *  mkdir -- make directories
 *  Copyright (c) 1999-2003 Brad Proctor
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
 * $Id: mkdir.c,v 1.16 2003/02/16 15:26:36 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: mkdir long-option\n"
   "       mkdir [-p][-m mode] dir...\n"
   "Create directories.\n"
   "\n"
   "  -m mode    Set permission bits\n"
   "  -p         Create missing pathname components\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "`mode' can be any of the following\n"
   "  b   block (buffered) special file\n"
   "  c   character (unbuffered) special file\n"
   "  p   FIFO special file\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

/*
 * Main
 */

int main (int argc, char **argv)
{
   int i = 1, mode = 0775, err;

   progname = argv[0];
   
   if (argc > 1)
   {
      if (argv[1][0] == '-')
      {
         if (!strcmp(argv[1], "--help"))
         {
            puts (help_text);
            return (EXIT_SUCCESS);
         }
         else if (!strcmp (argv[1], "--version"))
         {
            puts ("mkdir: version "VERSION);
            return (EXIT_SUCCESS);
         }
         else if (!strcmp (argv[1], "-p"))
            i = 2;
         else if (!strcmp (argv[1], "-m"))
         {
            if (argv[2] == NULL)
               terror ("missing operand to `-m' option");
            mode = getnum_octal (argv[2]);
            i = 3;
         }
      }
      for (; i < argc; ++i)
      {
         err = mkdir (argv[i], mode);
         if (err)
            error ("cannot create directory `%s': %s", argv[i], strerror (errno));
      }
   }
   return (EXIT_SUCCESS);
}
