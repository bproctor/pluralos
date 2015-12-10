
/*
 *  times -- Report total time for processes
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
 * $Id: times.c,v 1.6 2003/02/11 18:30:38 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: times [long-option]\n"
   "Report total time for processes.\n"
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
   progname = argv[0];

   if (argc >= 2)
   {
      if (!strcmp (argv[1], "--help"))
         puts (help_text);
      else if (!strcmp (argv[1], "--version"))
         puts ("times: version "VERSION);
      else
         terror ("too many arguments");
   }

   

   return (EXIT_SUCCESS);
}