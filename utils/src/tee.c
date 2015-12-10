
/*
 *  tee -- copy standard input to standard output
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
 * $Id: tee.c,v 1.8 2003/02/10 20:46:19 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: tee long-option\n"
   "       tee [-ai] [file ...]\n"
   "Copy standard input to standard output.\n"
   "\n"
   "  -a         Append to the given file, do not overwrite\n"
   "  -i         Ignore signals\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_append = 0;
static char flag_ignore = 0;

static void do_tee (int in, int out)
{
   int c;
   char *ptr;
   struct stat s;
   
   fstat (STDIN_FILENO, &s);
   ptr = xmalloc (s.st_blksize);
   while ((c = read (in, ptr, s.st_blksize)) > 0)
      write (out, ptr, c);
}


/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i, in, out;
   char *ptr;

   in = STDIN_FILENO;
   out = STDOUT_FILENO;
   progname = argv[0];

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
                  puts ("tee: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'a':
               flag_append = 1;
               continue;
            case 'i':
               flag_ignore = 1;
               continue;
         }
      }
      else
      {
         
      }
   }
   do_tee (in, out);
   return (EXIT_SUCCESS);
}
