
/*
 *  uustat -- 
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
 * $Id: uustat.c,v 1.4 2003/02/11 06:10:21 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: uustat long-option\n"
   "       uustat [-q | -k jobid | -r jobid]\n"
   "       uustat [-s system][-u user]\n"
   "uucp status inquery and job control.\n"
   "\n"
   "  -k jobid   \n"
   "  -q         \n"
   "  -r jobid   \n"
   "  -s system  \n"
   "  -u user    \n"
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
         switch (*++ptr)
         {
            case '-':
               if (!strcmp (ptr, "-help"))
                  puts (help_text);
               else if (!strcmp (ptr, "-version"))
                  puts ("uustat: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'k':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-%c' option", *(ptr-1));
               break;
            case 'q':
               break;
            case 'r':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-%c' option", *(ptr-1));
               break;
            case 's':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-%c' option", *(ptr-1));
               break;
            case 'u':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-%c' option", *(ptr-1));
               break;
         }
      }
   }
   return (EXIT_SUCCESS);
}
