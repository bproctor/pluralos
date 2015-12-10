
/*
 *  basename -- return non-directory portion of a pathname
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
 * $Id: basename.c,v 1.14 2003/02/10 20:45:50 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: basename long-option\n"
   "       basename string [suffix]\n"
   "Remove directory compontents from a pathname.\n"
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
   char *ptr, *ptr1;

   progname = argv[0];

   if (argc == 1)
      terror ("too few arguments");

   ptr = argv[1];
   if (!strcmp(ptr, "--help"))
   {
      puts (help_text);
      return (EXIT_SUCCESS);
   }
   else if (!strcmp (ptr, "--version"))
   {
      puts ("basename: version "VERSION);
      return (EXIT_SUCCESS);
   }

   /* 
    * There is probably a faster simpler way to do all this...
    *
    *       -- Brad
    */

   while (*ptr == '/')
      ++ptr;

   if (*ptr == '\0')
   {
      if (ptr > argv[1])
         putchar ('/');
      putchar ('\n');
      return (EXIT_SUCCESS);
   }

   ptr1 = strrchr (ptr, '/');
   if (ptr1)
      ptr = ptr1 + 1;

   while (*ptr == '\0')
   {
      *--ptr = '\0';
      ptr = strrchr (argv[1], '/');
      ++ptr;
   }
   
   if (argc > 2)
   {
      if (strcmp (argv[1], argv[2]) != 0)
      {
         ptr1 = strstr (ptr, argv[2]);
         if (strlen (ptr1) == strlen (argv[2]))
            *ptr1 = '\0';
      }
   }
   puts (ptr);
   return (EXIT_SUCCESS);
}
