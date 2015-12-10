
/*
 *  more -- Print files on page at a time
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
 * $Id: more.c,v 1.5 2003/02/10 20:46:14 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: more long-option\n"
   "Print files one page at a time.\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static int max_lines = 24;

static void do_more (FILE *in)
{
   int c, lines = 0;
   
   while (1)
   {
      c = getc (in);
      if (c == EOF)
         break;
      else if (c == '\n')
      {
         if (++lines >= max_lines)
         {
            lines = 0;
            fputs ("\n--MORE--", stdout);
            getc (stdin);
         }
         else
            putchar (c);
      }
      else
         putchar (c);
   }
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   FILE *in;
   
   if (argc == 1)
      do_more (stdin);
   else if (argc == 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("more: version "VERSION);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "-"))
      {
         do_more (stdin);
         return (EXIT_SUCCESS);
      }
   }

   for (i = 1; i < argc; ++i)
   {
      in = xfopen (argv[i], "r");
      do_more (in);
      fclose (in);
   }

   return (EXIT_SUCCESS);
}
