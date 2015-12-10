
/*
 *  mknod -- create a node special file
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
 * $Id: mknod.c,v 1.15 2003/02/16 15:26:37 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: mknod long-option\n"
   "       mknod [-p][-m mode] name ...\n"
   "Create a node special file.\n"
   "\n"
   "  -m mode    Set permission bits\n"
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
   int i = 1, mode = 0775;

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
            puts ("mknod: version "VERSION);
            return (EXIT_SUCCESS);
         }
         else if (!strcmp (argv[1], "-m"))
         {
            if (argv[2] == NULL)
               terror ("missing operand to `-m' option");
            mode = getnum_octal (argv[2]);
            i = 3;
         }
      }
      for (; i < argc; ++i)
         if (mknod (argv[i], mode, 0))
            error ("cannot create `%s': %s",
               argv[i], strerror (errno));
   }
   return (EXIT_SUCCESS);
}
