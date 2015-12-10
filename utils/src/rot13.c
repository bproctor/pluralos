
/*
 *  rot13 -- encrypt a file with a simple ROT-13 algorithm
 *  Copyright (c) 2002-2003 Brad Proctor
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
 * $Id: rot13.c,v 1.9 2003/02/10 20:46:17 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

#define  LINE_MAX    1024

static const char help_text[] =
{
   "Usage: rot13 long-option\n"
   "       rot13 [-a][-r n]file ...\n"
   "Encrypt a file with a simple ROT-13 algorithm.\n"
   "\n"
   "  -a          Rotate all characters\n"
   "  -r n        Rotate by 'n' characters\n"
   "\n"
   "Long Options:\n"
   "  --help      Print this help message\n"
   "  --version   Print the prgram version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_done = 0;
static char flag_ascii = 0;
static char buf[LINE_MAX];
static FILE *in;

static void do_rot13 (int rotate)
{
   int x;
   if (flag_ascii)
   {
      while ((fgets (buf, LINE_MAX, in)) != 0)
      {
         for (x = 0; buf[x] != 0; ++x)
            buf[x] = buf[x] + rotate;
         fputs (buf, stdout);
      }
   }
   else
   {
      while ((fgets (buf, LINE_MAX, in)) != 0)
      {
         for (x = 0; buf[x] != 0; ++x)
         {
            if (islower (buf[x]))
               buf[x] = ((buf[x] + rotate - 'a') % 26) + 'a';
            else if (isupper (buf[x]))
               buf[x] = ((buf[x] + rotate - 'A') % 26) + 'A';
            else if (isdigit (buf[x]))
               buf[x] = ((buf[x] + rotate - '0') % 10) + '0';
         }
         fputs (buf, stdout);
      }
   }
   flag_done = 1;
}

/*
 * Main
 */

int main (int argc, char **argv)
{
   int i, rotate = 13;
   char *ptr;

   progname = argv[0];
   in = stdin;
   
   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      if (*ptr == '-')
      {
         switch (*++ptr)
         {
            case '\0':
               in = stdin;
               break;
            case '-':
               if (!strcmp (ptr, "-help"))
                  puts (help_text);
               else if (!strcmp (ptr, "-version"))
                  puts ("rot13: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'a':
               flag_ascii = 1;
               break;
            case 'r':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-r' option");
               rotate = getnum_ul (ptr);
               break;
         }
      }
      else
      {
         fclose (in);
         in = xfopen (argv[i], "r");
      }
      do_rot13 (rotate);
   }
   
   if (flag_done == 0)
      do_rot13 (rotate);
   
   fclose (in);
   return (EXIT_SUCCESS);
}
