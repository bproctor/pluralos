
/*
 *  paste -- merge corresponding or subsequent lines of files
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
 * $Id: paste.c,v 1.6 2003/02/10 20:46:15 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: paste long-option\n"
   "       paste [-s] [-d list] [file ...]\n"
   "Merge corresponding or subsequent lines of files.\n"
   "\n"
   "  -d list    Use charaters from `list' instead of tabs\n"
   "  -s         Paste one file at a time instead of in parallel\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static FILE *in;
static char flag_serial = 0;
static char *flag_delimiter = "\t";

static void do_paste (void)
{
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i = 1;

   progname = argv[0];

   if (argc == 1)
   {
      in = stdin;
      do_paste ();
      return (EXIT_SUCCESS);
   }
   else if (argc >= 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("paste: version "VERSION);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "-s"))
      {
         ++i;
         flag_serial = 1;
      }
      else if (!strcmp (argv[1], "-d"))
      {
         ++i;
         if (argc > 2)
            flag_delimiter = argv[2];
         else
            terror ("`-d' option requires an argument");
      }
   }

   for (; i < argc; ++i)
   {
      in = xfopen (argv[i], "r");
      do_paste ();
      fclose (in);
   }

   return (EXIT_SUCCESS);
}
