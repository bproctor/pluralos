
/*
 *  fold -- filter for folding lines
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
 * $Id: fold.c,v 1.9 2003/02/10 20:46:06 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: fold long-option\n"
   "       fold [-bs][-w width] file ...\n"
   "Filter for folding lines.\n"
   "\n"
   "  -b         count bytes instead of columns\n"
   "  -s         Break at spaces\n"
   "  -w width   Width of a line\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_bytes = 0;
static char flag_spaces = 0;
static int width = 72;
static FILE *in;

static void do_fold (void)
{
   int c, count = 0;
   
   while (1)
   {
      c = fgetc (in);
      if (c == EOF)
         return;
      else if (c == '\t')
         count += 7;
      else if (c == '\n')
         count = 0;
      if (count >= width)
      {
         putchar ('\n');
         count = 0;
      }
      putchar (c);
      count++;
   }
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   char *ptr;

   progname = argv[0];
   in = stdin;
   
   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      if (*ptr == '-')
      {
         while (*++ptr)
         switch (*ptr)
         {
            case '\0':
               in = stdin;
               break;
            case '-':
               if (!strcmp (ptr, "-help"))
                  puts (help_text);
               else if (!strcmp (ptr, "-version"))
                  puts ("fold: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'b':
               flag_bytes = 1;
               continue;
            case 's':
               flag_spaces = 1;
               continue;
            case 'w':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-w' option");
               width = getnum_ul (ptr);
               break;
         }
      }
      else
         in = xfopen (argv[i], "r");
      do_fold ();
      fclose (in);
   }
   return (EXIT_SUCCESS);
}
