
/*
 *  patch -- apply changes to files
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
 * $Id: patch.c,v 1.4 2003/02/10 20:46:15 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: patch long-option\n"
   "Apply changes to files.\n"
   "\n"
   "  -b         \n"
   "  -c         \n"
   "  -d         \n"
   "  -e         \n"
   "  -n         \n"
   "  -pn        \n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static int level = 0;

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
                  puts ("patch: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'b':
               continue;
            case 'c':
               continue;
            case 'd':
               continue;
            case 'e':
               continue;
            case 'n':
               continue;
            case 'p':
               if (*++ptr == '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("`-p' option requires an argument");
               level = getnum_ul (ptr);
               break;
         }
      }
   }
   return (EXIT_SUCCESS);
}
