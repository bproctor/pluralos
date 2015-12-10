
/*
 *  ex -- Line editor
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
 * $Id: ex.c,v 1.6 2003/02/10 20:46:03 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: ex long-option\n"
   "       ex [-rR][-s | -v][-c command][-t tag][-w size][file ...]\n"
   "Line editor.\n"
   "\n"
   "  -c command \n"
   "  -r         \n"
   "  -R         \n"
   "  -s         \n"
   "  -t tag     \n"
   "  -v         \n"
   "  -w size    \n"
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
               {
                  puts (help_text);
                  return (EXIT_SUCCESS);
               }
               else if (!strcmp (ptr, "-version"))
               {
                  puts ("ex: version "VERSION);
                  return (EXIT_SUCCESS);
               }
            case 'c':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-c' option");
               break;
            case 'r':
            case 'R':
            case 's':
               continue;
            case 't':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-t' option");
               break;
            case 'v':
               continue;
            case 'w':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-w' option");
               break;
         }
      }
   }
   return (EXIT_SUCCESS);
}
