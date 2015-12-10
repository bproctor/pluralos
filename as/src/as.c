
/*
 *  as.c
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
 * $Id: as.c,v 1.3 2003/01/15 21:33:26 fredlie Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "as.h"

int code_bits = 32;
int lineno = 1;
int error_count = 0;
int warning_count = 0;
int errors_max = 20;
int warnings_max = 40;
char *inname = 0;
char *outname = 0;
char *progname;
FILE *infile;
FILE *outfile;

unsigned long pc = 0;
unsigned long outsize = 0;
void *outbin;

extern int yydebug;

/*
 * Report an error message
 */

void error (const char *msg, ...)
{
   va_list ap;
   fprintf (stderr, "%s:%d: ", inname, lineno);
   va_start (ap, msg);
   vfprintf (stderr, msg, ap);
   va_end (ap);
   fputc ('\n', stderr);
   if (++error_count >= errors_max)
      fatal_error ("Too many errors");
}

/*
 * Report a warning message
 */
 
void warning (const char *msg, ...)
{
   va_list ap;
   fprintf (stderr, "%s:%d: warning: ", inname, lineno);
   va_start (ap, msg);
   vfprintf (stderr, msg, ap);
   va_end (ap);
   fputc ('\n', stderr);
   if (++warning_count >= warnings_max)
      fatal_error ("Too many warnings");
}

/*
 * Report a fatal error
 */

void fatal_error (const char *msg, ...)
{
   va_list ap;
   fprintf (stderr, "%s: ", progname);
   va_start (ap, msg);
   vfprintf (stderr, msg, ap);
   va_end (ap);
   fputc ('\n', stderr);
   exit (EXIT_FAILURE);
}

/*
 * Main
 */

int main (int argc, char **argv)
{
   int i;
   char *ptr;

   progname = argv[0];

   if (argc < 2)
      fatal_error ("no input file specified");
   
   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      if (*ptr == '-')
      {
         switch (*++ptr)
         {
            case '-':
               ++ptr;
               if (!strcmp (ptr, "help"))
               {
                  puts ("Usage: as [options] infile [outfile]\n"
                        "Compiles assembly language programs\n"
                        "\n"
                        "    --help     Prints this help message\n"
                        "    --version  Prints the program version\n"
                        "\n"
                        "Report bugs to <bugs@plural-os.org>.");
                  return (EXIT_SUCCESS);
               }
               else if (!strcmp (ptr, "version"))
               {
                  puts ("as version "VERSION);
                  return (EXIT_SUCCESS);
               }
            case 'd':
               yydebug = 1;
               break;
            
            case 'e':
            case 'f':
            case 'w':
            case 'D':
            case 'U':
               fatal_error ("`-%c' option not implemented yet", *ptr);
         }
      }
      else if (!inname)
      {
         inname = (char *)malloc (strlen (ptr));
         if (!inname)
            fatal_error ("Out of memory");
         strcpy (inname, ptr);
         infile = fopen (inname, "r");
         if (!infile)
            fatal_error ("could not open %s for reading", inname);
      }
      else if (!outname)
      {
         outname = (char *)malloc (strlen (ptr));
         if (!outname)
            fatal_error ("Out of memory");
         strcpy (outname, ptr);
         outfile = fopen (outname, "w");
         if (!outfile)
            fatal_error ("could not open %s for writing", outname);
      }
   }
   if (!inname)
      fatal_error ("no input file specified");
   if (!outname)
   {
      outname = (char *)malloc (strlen (inname) + 4);
      if (!outname)
         fatal_error ("Out of memory");
      strcpy (outname, inname);
      strcpy (strrchr(outname, '.'), ".o");
      outfile = fopen (outname, "w");
      if (!outfile)
         fatal_error ("could not open file %s for writing", outname);
   }
   yyparse ();   
   fclose (infile);
   fclose (outfile);
   return (EXIT_SUCCESS);
}
