
/*
 *  unexpand -- convert spaces to tabs
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
 * $Id: unexpand.c,v 1.19 2003/02/10 20:46:20 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: unexpand long-option\n"
   "       unexpand [-t tablist | -num] files ...\n"
   "Convert spaces to tabs.\n"
   "\n"
   "  -t tablist Set tab size to num\n"
   "  -num       Set tab size to num\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_done = 0;
static int num_tabs = 0;
static int tabs[20];
static FILE *in;

static void do_unexpand (void)
{
   int c, x;
   int tab_count = 0;

   if (num_tabs == 0)
      tabs[num_tabs++] = 8;

   while (1)
   {
      c = getc (in);
      switch (c)
      {
         case EOF:
            return;
         case ' ':
            if (num_tabs >= tab_count)
            {
               for (x = 0; x < tabs[tab_count]; ++x)
                  if ((c = getc (in)) != ' ')
                  {
                     while (x--)
                        putchar (' ');
                     putchar (c);
                     break;
                  }
               tab_count++;
            }
            else
               putchar ('\t');
            break;
         case '\n':
            tab_count = 0;
            putchar ('\n');
            break;
         default:
            putchar (c);   
      }
   }
   flag_done = 1;
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
         switch (*++ptr)
         {
            case '\0':
               in = stdin;
               continue;
            case '-':
               if (!strcmp (ptr, "-help"))
                  puts (help_text);
               else if (!strcmp (ptr, "-version"))
                  puts ("unexpand: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 't':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-t' option");
               /* Fall through */
            case '0':   case '1':   case '2':
            case '3':   case '4':   case '5':
            case '6':   case '7':   case '8':
            case '9':
               tabs[num_tabs++] = getnum_ul (ptr);
               break;
         }
      }
      else
      {
         fclose (in);
         in = xfopen (argv[i], "r");
      }
      do_unexpand ();
   }
   
   if (flag_done == 0)
      do_unexpand ();
      
   fclose (in);
   return (EXIT_SUCCESS);
}
