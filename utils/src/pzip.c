
/*
 *  pzip -- compress files
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
 * $Id: pzip.c,v 1.11 2003/02/16 18:46:41 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <libgen.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: pzip long-option\n"
   "       pzip [-1:-9][-cdf] file ...\n"
   "Compress files.\n"
   "\n"
   "  -1..9      Compression level\n"
   "  -c         Compress to standard output\n"
   "  -d         Decompress\n"
   "  -f         Force overwrite\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_level = 4;
static char flag_compress = 1;
static char flag_force = 0;

static FILE *infile = 0;
static FILE *outfile = 0;
static char *inname;
static char *outname;

static void do_compress (void)
{
}

static void do_decompress (void)
{
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   char *ptr;

   progname = argv[0];

   if (!strcmp ((char *)basename (argv[0]), "punzip"))
      flag_compress = 0;
   
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
                  puts (help_text);
               else if (!strcmp (ptr, "-version"))
                  puts ("pzip: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case '1': case '2': case '3':
            case '4': case '5': case '6':
            case '7': case '8': case '9':
               flag_level = *ptr - '0';
               continue;
            case 'c':
               outfile = stdout;
               continue;
            case 'd':
               flag_compress = 0;
               continue;
            case 'f':
               flag_force = 1;
               continue;
         }
      }
      else if (!infile)
      {
         inname = argv[i];
         infile = xfopen (inname, "r");
      }
      else if (!outfile)
      {
         outname = argv[i];
         outfile = xfopen (outname, "r");
      }
   }
   if (!infile)
      error ("no input file specified");
   if (!outfile)
   {
   }
   if (flag_compress)
      do_compress ();
   else
      do_decompress ();
   return (EXIT_SUCCESS);
}
