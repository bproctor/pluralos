
/*
 *  grep -- search a file for a pattern
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
 * $Id: grep.c,v 1.6 2003/02/16 15:26:36 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: grep long-option\n"
   "       grep [-E | -F][-c | -l | -q][-inrsvx] -e list ...\n"
   "            [-f file] ... [file ...]\n"
   "       grep [-E | -F][-c | -l | -q][-inrsvx][-e list] ...\n"
   "             -f file ... [file ...]\n"
   "       grep [-E | -F][-c | -l | -q][-inrsvx] list [file ...]\n"
   "Search a file for a pattern.\n"
   "\n"
   "  -c         \n"
   "  -e list    \n"
   "  -E         \n"
   "  -f file    \n"
   "  -F         \n"
   "  -i         \n"
   "  -l         \n"
   "  -n         \n"
   "  -q         \n"
   "  -r         \n"
   "  -s         \n"
   "  -v         \n"
   "  -x         \n"
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
                  puts ("grep: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'c':
               continue;
            case 'e':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-e' option");
               break;
            case 'E':
               continue;
            case 'f':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-f' option");
               break;
            case 'F':
               continue;
            case 'i':
               continue;
            case 'l':
               continue;
            case 'n':
               continue;
            case 'q':
               continue;
            case 's':
               continue;
            case 'v':
               continue;
            case 'x':
               continue;
         }
      }
   }
   return (EXIT_SUCCESS);
}
