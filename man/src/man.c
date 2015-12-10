
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "man.h"

static const char help_text[] =
{
   "Usage: man\n"
   "\n"
   "  --help\n"
   "  --version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

extern int yydebug;

int lineno = 1;
char *progname;
char *inname;
FILE *infile = 0;

void error (const char *msg, ...)
{
   va_list ap;
   fprintf (stderr, "%s:%d: ", inname, lineno);
   va_start (ap, msg);
   vfprintf (stderr, msg, ap);
   va_end (ap);
   fputc ('\n', stderr);
}

void warning (const char *msg, ...)
{
   va_list ap;
   fprintf (stderr, "%s:%d: warning: ", inname, lineno);
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

   if (argc < 2)
      fatal ("no input file specified");

   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      if (*ptr == '-')
      {
         while (*++ptr)
         switch (*ptr)
         {
            case '-':
               if (!strcmp (ptr, "-help"))
               {
                  puts (help_text);
                  return (EXIT_SUCCESS);
               }
               else if (!strcmp (ptr, "-version"))
               {
                  puts ("man: version "VERSION);
                  return (EXIT_SUCCESS);
               }
            case 'd':
               yydebug = 1;
               break;
         }
      }
      else if (!infile)
      {
         inname = argv[i];
         infile = fopen (inname, "r");
         if (!infile)
            fatal ("could not open `%s' for reading", inname);
      }
   }
   
   if (!infile)
      infile = stdin;

   yyparse ();   
   return (0);
}
