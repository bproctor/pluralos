
/*
 *  dirname -- return directory portion of a pathname
 *  Copyright (c) 2002-2003 Brad Proctor
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
 * $Id: dirname.c,v 1.11 2003/02/16 18:46:40 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

char *dirname (const char *);

static const char help_text[] =
{
   "Usage: dirname long-option\n"
   "       dirname string\n"
   "Return the directory compontents from a pathname.\n"
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
   else if (argc == 2)
   {
      if (!strcmp(argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("dirname: version "VERSION);
         return (EXIT_SUCCESS);
      }
   }
   else
      terror ("too many arguments");

   ptr = argv[1];
   while (*ptr == '/')
   {
      if (*(ptr + 1) == '\0')
      {
         puts ("/");
         return (EXIT_SUCCESS);
      }
      if (*(ptr + 1) != '/')
         break;
      ++ptr;
   }
   
   ptr1 = strrchr (ptr, '/');
   if (ptr1 == NULL)
   {
      puts (".");
      return (EXIT_SUCCESS);
   }

   while (*(ptr1 + 1) == '\0')
   {
      *ptr1 = '\0';
      ptr1 = strrchr (ptr, '/');
      if (ptr1 == NULL)
         break;
   }
   *(ptr1+1) = '\0';
   if (ptr1 > ptr)
   {
      while (*(ptr1 - 1) == '/')
         --ptr1;
      *ptr1 = '\0';
   }
   puts (ptr);
   
   return (EXIT_SUCCESS);
}
