
/*
 *  mv -- move files
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
 * $Id: mv.c,v 1.12 2003/02/10 20:46:14 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: mv long-option\n"
   "       mv [-fi] file ...\n"
   "Move files or directories.\n"
   "\n"
   "  -f         Force the move\n"
   "  -i         Prompt before moving\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_force = 0;      /* Force the move */
static char flag_prompt = 0;     /* Prompt before moving */

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
                  puts ("mv: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'f':
               flag_force = 1;
               break;
            case 'i':
               flag_prompt = 1;
               break;
         }
      }   
   }
   return (EXIT_SUCCESS);
}
