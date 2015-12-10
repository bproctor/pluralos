
/*
 *  pwd -- print the working directory
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
 * $Id: pwd.c,v 1.10 2003/02/10 20:46:16 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: pwd long-option\n"
   "Print the working directory.\n"
   "\n"
   "  -L         \n"
   "  -P         \n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_L = 0;
static char flag_P = 0;

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   char *ptr, *d;

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
                  puts ("pwd: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'L':
               flag_L = 1, flag_P = 0;
               continue;
            case 'P':
               flag_P = 1, flag_L = 0;
               continue;
            default:
               terror ("invalid option `%s'", argv[i]);
         }
      }
   }
   if (!flag_L && !flag_P)
      flag_L = 1;
      
   d = getcwd (NULL, 0);
   if (d == NULL)
      error ("cannot get directory: %s", strerror (errno));
   puts (d);

   return (EXIT_SUCCESS);
}
