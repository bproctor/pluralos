
/*
 *  asa -- interpret carriage-control characters
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
 * $Id: asa.c,v 1.5 2003/02/10 20:45:49 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: asa long-option\n"
   "       asa [file ...]\n"
   "Interpret carriage-control characters.\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static FILE *in;

static void do_asa (void)
{
   int c;

   while (1)
   {   
      c = getc (in);
      switch (c)
      {
         case EOF:
            return;
         case '0':
            putchar ('\n');
            break;
         case '1':
            putchar ('\f');      /* This might be '\v', not sure... */
            break;
         case '+':
            putchar ('\r');
            break;
         case ' ':
            break;
      }
      while (c != '\n')
      {
         c = getc (in);
         if (c == EOF)
            return;
         putchar (c);
      }
   }
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   progname = argv[0];

   if (argc == 1)
   {
      in = stdin;
      do_asa ();
      return (EXIT_SUCCESS);
   }
   else if (argc >= 2)
   {
      if (!strcmp (argv[1], "--help"))
         puts (help_text);
      else if (!strcmp (argv[1], "--version"))
         puts ("asa: version "VERSION);
      else
      {
         for (i = 1; i < argc; ++i)
         {
            in = xfopen (argv[1], "r");
            do_asa ();
            fclose (in);
         }
      }
   }
   return (EXIT_SUCCESS);
}
