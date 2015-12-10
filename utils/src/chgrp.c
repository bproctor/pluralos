
/*
 *  chgrp -- change the file group ownership
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
 * $Id: chgrp.c,v 1.15 2003/02/10 20:45:54 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: chgrp long-option\n"
   "       chgrp [-hR] group file ...\n"
   "       chgrp -R [-H | -L | -P] file ...\n"
   "Change file group.\n"
   "\n"
   "  -h         Effect symbolic links instead of files\n"
   "  -H         Follow symbolicly linked directories\n"
   "  -L         Follow symbolicly linked directories\n"
   "  -P         Effect symbolic link, do not follow\n"
   "  -R         Recursively change file group IDs\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_recursive = 1;
static char *group = 0;

/*
 * Main
 */

int main (int argc, char **argv)
{
   int i;
   char *ptr;

   progname = argv[0];
   
   if (argc == 1)
      error ("too few arguments");
   
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
                  puts ("chgrp: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'h':
               continue;
            case 'H':
               continue;
            case 'L':
               continue;
            case 'P':
               continue;
            case 'R':
               flag_recursive = 1;
               continue;
         }
      }
      else if (!group)
         group = argv[i];
      else
      {
      }
   }
   return (EXIT_SUCCESS);
}
