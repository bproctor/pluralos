
/*
 *  cc.c
 *  Copyright (c) 2001-2002 Brad Proctor
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
 * $Id: cc.c,v 1.1 2002/12/18 06:10:47 fredlie Exp $
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <libgen.h>
#include "cc.h"

static const char help_screen[] =
{
   "Usage: cc [options] infile\n"
   "\n"
   "    --help       Display the help message\n"
   "    --version    Display version information\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

flag_type flags =
{
   0,    /* -fansi */
   0,    /* -fwarn_ansi */
};

int lineno = 1;
int error_count = 0;
int warning_count = 0;
int errors_max = 20;
int warnings_max = 40;
char *inname = 0;
char *outname = 0;
char *tempname = 0;
char *progname;
FILE *infile;
FILE *outfile;
FILE *tempfile;

extern FILE *yyin;

extern int yydebug;

void error (const char *msg, ...)
{
   va_list ap;
   fprintf (stderr, "%s:%d: ", inname, lineno);
   va_start (ap, msg);
   vfprintf (stderr, msg, ap);
   va_end (ap);
   fputc ('\n', stderr);
   if (++error_count >= errors_max)
      fatal_error ("too many errors");
}

void warning (const char *msg, ...)
{
   va_list ap;
   fprintf (stderr, "%s:%d: warning: ", inname, lineno);
   va_start (ap, msg);
   vfprintf (stderr, msg, ap);
   va_end (ap);
   fputc ('\n', stderr);
   if (++warning_count >= warnings_max)
      fatal_error ("too many warnings");
}

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

int main (int argc, char **argv)
{
   int i;
   char *ptr;
   
   progname = argv[0];   

   if (!strcmp (basename (progname), "c89"))
      flags.ansi89 = 1;

   if (!strcmp (basename (progname), "c99"))
      flags.ansi99 = 1;

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
                  puts (help_screen);
                  return (EXIT_FAILURE);
               }
               else if (!strcmp (ptr, "version"))
               {
                  puts ("cc version "VERSION);
                  return (EXIT_SUCCESS);
               }
               break;
            case 'c':
               break;
            case 'd':
               if (*++ptr == 0)
                  yydebug = 1;
               else
                  fatal_error ("invalid option: `%s'", ptr-2);
               break;
            case 'e':
               if (!strncmp (ptr, "errors=", 7))
                  sscanf (ptr+7, "%d", &errors_max);
               else
                  fatal_error ("invalid option: `%s'", ptr-1);
               break;
            case 'f':
               ++ptr;
               if (!strcmp (ptr, "ansi"))
                  flags.ansi99 = 1;
               else if (!strcmp (ptr, "no-ansi"))
                  flags.ansi99 = 0;
               else if (!strcmp (ptr, "ansi89"))
                  flags.ansi89 = 1;
               else if (!strcmp (ptr, "no-ansi89"))
                  flags.ansi89 = 0;
               else if (!strcmp (ptr, "ansi99"))
                  flags.ansi99 = 1;
               else if (!strcmp (ptr, "no-ansi99"))
                  flags.ansi99 = 0;
               else
                  fatal_error ("invalid option: `%s'", ptr-2);
               break;
            case 'g':
            case 'l':
               break;
            case 'o':
               if (*ptr+1 != '\0')
                  fatal_error ("invalid option: `%s'", ptr-1);
               ptr = argv[++i];
               outname = (char *)malloc (strlen (ptr));
               if (!outname)
                  fatal_error ("out of memory");
               strcpy (outname, ptr);
               outfile = fopen (outname, "w");
               if (!outfile)
                  fatal_error ("could not open file `%s' for writing", outname);
               break;
            case 's':
               break;
            case 'w':
               if (!strncmp (ptr, "warnings=", 9))
                  sscanf (ptr+7, "%d", &errors_max);
               else
                  fatal_error ("invalid option: `%s'", ptr-1);
            case 'D':
            case 'E':
            case 'I':
            case 'L':
            case 'O':
               if (!strcmp (ptr, "O0"))
                  ;
               else if (!strcmp (ptr, "O1"))
                  ;
               else if (!strcmp (ptr, "O2"))
                  ;
               else if (!strcmp (ptr, "O3"))
                  ;
               else
                  fatal_error ("invalid option: `%s'", ptr-1);
               break;
            case 'U':
               break;
            case 'W':
               ++ptr;
               if (!strcmp (ptr, "ansi"))
                  flags.warn_ansi99 = 1;
               else if (!strcmp (ptr, "no-ansi"))
                  flags.warn_ansi99 = 0;
               else if (!strcmp (ptr, "ansi89"))
                  flags.warn_ansi89 = 1;
               else if (!strcmp (ptr, "no-ansi89"))
                  flags.warn_ansi89 = 0;
               else if (!strcmp (ptr, "ansi99"))
                  flags.warn_ansi99 = 1;
               else if (!strcmp (ptr, "no-ansi99"))
                  flags.warn_ansi99 = 0;
               else
                  fatal_error ("invalid option: `%s'", ptr-1);
               break;
         }
      }
      else if (!inname)
      {
         inname = (char *)malloc (strlen (ptr));
         if (!inname)
            fatal_error ("out of memory");
         strcpy (inname, ptr);
         infile = fopen (inname, "r");
         if (!infile)
            fatal_error ("could not open file `%s' for reading", inname);
      }
      else if (!outname)
      {
         outname = (char *)malloc (strlen (ptr));
         if (!outname)
            fatal_error ("out of memory");
         strcpy (outname, ptr);
         outfile = fopen (outname, "w");
         if (!outfile)
            fatal_error ("could not open file `%s' for writing", outname);
      }
   }
   if (!inname)
      fatal_error ("no input file specified");
   if (!outname)
   {
      outname = (char *)malloc (strlen (inname) + 4);
      if (!outname)
         fatal_error ("out of memory");
      strcpy (outname, inname);
      strcpy (strrchr(outname, '.'), ".asm");
      outfile = fopen (outname, "w");
      if (!outfile)
         fatal_error ("could not open file `%s' for writing", outname);
   }
   asm_start_file ();
   yyparse ();
   asm_finish_file ();
   fclose (infile);
   fclose (outfile);
   return (EXIT_SUCCESS);
}
