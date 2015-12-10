
/*
 *  rmdir -- remove directories
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
 * $Id: rmdir.c,v 1.14 2003/02/10 20:46:16 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: rmdir long-option\n"
   "       rmdir [-p] dir...\n"
   "Remove directories.\n"
   "\n"
   "  -p         Remove all directories in a pathname\n"
   "  -v         Verbose\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_verbose = 0;
static char flag_parent = 0;

static void do_rmdir (const char *dir)
{
   if (flag_parent)
   {
      while (1)
      {
         char *s;
         if (rmdir (dir) != 0)
            error ("cannot remove directory `%s': %s", dir, strerror (errno));
         else if (flag_verbose)
            printf ("removed: `%s'\n", dir);
         if ((s = strrchr (dir, '/')) == NULL)
            break;
         while (s > dir && *s == '/')
            --s;
         s[1] = 0;
      }
   }
   else
   {
      if (rmdir (dir) != 0)
         error ("cannot remove directory `%s': %s", dir, strerror (errno));
      else if (flag_verbose)
         printf ("removed: `%s'\n", dir);
   }
}

/*
 * Main
 */

int main (int argc, char **argv)
{
   int i;
   char *ptr;

   progname = argv[0];

   if (argc == 1)
      do_rmdir (argv[1]);

   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      if (*ptr == '-')
      {
         while (*++ptr)
         switch (*ptr)
         {
            case '-':   
               if (!strcmp (ptr, "-help"))
                  puts (help_text);
               else if (!strcmp (ptr, "-version"))
                  puts ("rmdir: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'p':
               flag_parent = 1;
               continue;
            case 'v':
               flag_verbose = 1;
               continue;
         }
      }
      else
         do_rmdir (argv[i]);
   }
   return (EXIT_SUCCESS);
}
