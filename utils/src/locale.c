
/*
 *  locale -- Get locale specific information
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
 * $Id: locale.c,v 1.5 2003/02/10 20:46:09 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: locale long-option\n"
   "       locale [-a | -m]\n"
   "       locale [-ck] name ...\n"
   "Get locale specific information.\n"
   "\n"
   "  -a         \n"
   "  -c         \n"
   "  -k         \n"
   "  -m         \n"
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
                  puts ("locale: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'a':
               continue;
            case 'c':
               continue;
            case 'k':
               continue;
            case 'm':
               continue;
         }
      }
   }

   return (EXIT_SUCCESS);
}
