
/*
 *  uucp -- unix to unix copy
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
 * $Id: uucp.c,v 1.7 2003/02/16 18:46:41 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: uucp long-option\n"
   "       uucp [-cCdfjmr][-n user] srcfile ... destfile\n"
   "Unix to Unix copy.\n"
   "\n"
   "  -c         Don't copy local files to the spool directory\n"
   "  -C         Force copy of local files to the spool directory\n"
   "  -d         Create directories necessary for the copy\n"
   "  -f         Don't make intermediate directories\n"
   "  -j         Write the job ID to standard output\n"
   "  -m         Send mail to the requester when copy is complete\n"
   "  -n user    Notify user on remote system when copy is complete\n"
   "  -r         Do not start transfer, just queue the job\n"
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
                  puts ("uucp: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'c':
               continue;
            case 'C':
               continue;
            case 'd':
               continue;
            case 'f':
               continue;
            case 'j':
               continue;
            case 'm':
               continue;
            case 'n':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-n' option");
               break;
            case 'r':
               continue;
         }
      }
   }
   return (EXIT_SUCCESS);
}
