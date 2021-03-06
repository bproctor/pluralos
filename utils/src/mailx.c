
/*
 *  mailx -- process messages
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
 * $Id: mailx.c,v 1.6 2003/02/16 18:46:41 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: mailx long-option\n"
   "       mailx [-s subject] address...\n"
   "       mailx -e\n"
   "       mailx [-HinN][-F][-u user]\n"
   "       mailx -f [-HinN][-F][file]\n"
   "Process messages.\n"
   "\n"
   "  -e         \n"
   "  -f         \n"
   "  -F         \n"
   "  -i         \n"
   "  -n         \n"
   "  -N         \n"
   "  -s subject \n"
   "  -u         \n"
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
         switch (*ptr)
         {
            case '-':
               if (!strcmp (ptr, "-help"))
                  puts (help_text);
               else if (!strcmp (ptr, "-version"))
                  puts ("mailx: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'e':
               continue;
            case 'f':
               continue;
            case 'F':
               continue;
            case 'i':
               continue;
            case 'n':
               continue;
            case 'N':
               continue;
            case 's':
               if (*++ptr == '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-d' option");
               break;
            case 'u':
               continue;
         }
      }
   }

   return (EXIT_SUCCESS);
}
