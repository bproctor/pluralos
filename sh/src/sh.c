
/*
 *  sh.c
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
 * $Id: sh.c,v 1.3 2003/01/23 06:44:08 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdarg.h>
#include "sh.h"

static char help_text[] =
{
   "Usage: sh long_option\n"
   "The Plural Shell\n"
   "\n"
   "Long Options:\n"
   "  --help   Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>"
};

char *progname;

void error (const char *msg, ...)
{
   va_list ap;
   fprintf (stderr, "%s: ", progname);
   va_start (ap, msg);
   vfprintf (stderr, msg, ap);
   va_end (ap);
   fputc ('\n', stderr);
}

void warning (const char *msg, ...)
{
   va_list ap;
   fprintf (stderr, "%s: warning: ", progname);
   va_start (ap, msg);
   vfprintf (stderr, msg, ap);
   va_end (ap);
   fputc ('\n', stderr);
}

void fatal (const char *msg, ...)
{
   va_list ap;
   fprintf (stderr, "%s: ", progname);
   va_start (ap, msg);
   vfprintf (stderr, msg, ap);
   va_end (ap);
   fputc ('\n', stderr);
   exit (EXIT_FAILURE);
}

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
               if (!strcmp (++ptr, "help"))
               {
                  puts (help_text);
                  return (EXIT_SUCCESS);
               }
               else if (!strcmp (ptr, "version"))
               {
                  puts ("sh version "VERSION);
                  return (EXIT_SUCCESS);
               }
               else
                  fatal ("invalid option");
         }
      }
   }   
   yyparse ();   
   return (EXIT_SUCCESS);
}
