
/*
 *  cat -- concatenate and print files
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
 * $Id: cat.c,v 1.15 2003/02/10 20:45:52 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: cat long-option\n"
   "       cat [-u][file ...]\n"
   "Concatenate files.\n"
   "\n"
   "  -u         Print without buffering\n"
   "\n"
   "Long Option\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static void do_cat (int in)
{
   int c;
   char *ptr;
   struct stat s;
   
   fstat (in, &s);
   ptr = xmalloc (s.st_blksize);
   while ((c = read (in, ptr, s.st_blksize)) > 0)
      write (STDOUT_FILENO, ptr, c);
   close (in);
}

/*
 * Main
 */

int main (int argc, char **argv)
{
   int i = 1, in;
   
   if (argc == 1)
   {
      do_cat (STDIN_FILENO);
      return (EXIT_SUCCESS);
   }
   else if (argc >= 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("cat: version "VERSION);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "-u"))     /* Ignored */
         ++i;
   }

   for (; i < argc; ++i)
   {
      if (!strcmp (argv[i], "-"))
         in = STDIN_FILENO;
      else
      {
         in = open (argv[i], O_RDONLY);
         if (!in)
            error ("cannot open file `%s' for reading: %s",
               argv[i], strerror (errno));
         close (in);
      }
      do_cat (in);
   }

   return (EXIT_SUCCESS);
}
