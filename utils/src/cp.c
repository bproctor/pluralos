
/*
 *  cp -- Copy files
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
 * $Id: cp.c,v 1.7 2003/02/12 03:13:17 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: cp long-option\n"
   "       cp [-fip] src[...] dest\n"
   "       cp [-r | -R][-H | -L | -P][-fip] src... dest\n"
   "Copies files, src to dest.\n"
   "\n"
   "  -f         Force\n"
   "  -H         \n"
   "  -i         Interactive\n"
   "  -L         \n"
   "  -p         \n"
   "  -P         \n"
   "  -r         Recursive\n"
   "  -R         \n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_force = 0;
static char flag_interactive = 0;
static char flag_recursive = 0;

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   char *ptr;
   
   progname = argv[0];
   
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
                  puts ("cp: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'f':
               flag_force = 1;
               continue;
            case 'H':
               continue;
            case 'i':
               flag_interactive = 1;
               continue;
            case 'L':
               continue;
            case 'p':
               continue;
            case 'P':
               continue;
            case 'r':
               flag_recursive = 1;
               continue;
            case 'R':
               continue;
         }
      }
   }
   return (EXIT_SUCCESS);
}
