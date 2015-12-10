
/*
 *  md5sum -- print or check MD5 (128-bit) checksums
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
 * $Id: md5sum.c,v 1.6 2003/02/16 18:46:41 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: md5sum long-option\n"
   "       md5sum [-b | -t] [-cstw] [file ...]\n"
   "Print or check MD5 (128-bit) checksums.\n"
   "\n"
   "  -b         Read files in binary mode\n"
   "  -c         Check MD5 sum\n"
   "  -s         Silent, only exit with status code\n"
   "  -t         Read files in text mode\n"
   "  -w         Warn about improperly formated checksum lines\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_binary = 0;
static char flag_check = 0;
static char flag_silent = 0;
static char flag_text = 0;
static char flag_warn = 0;

static void do_md5sum (void)
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
   
   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      if (*ptr == '-')
      {
         switch (*++ptr)
         {
            case '-':
               if (!strcmp (ptr, "-help"))
                  puts (help_text);
               else if (!strcmp (ptr, "-version"))
                  puts ("md5sum: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'b':
               if (flag_text)
                  terror ("cannot specify both `-b' and `-t' options");
               flag_binary = 1;
               continue;
            case 'c':
               flag_check = 1;
               continue;
            case 's':
               flag_silent = 1;
               continue;
            case 't':
               if (flag_binary)
                  terror ("cannot specify both `-b' and `-t' options");
               flag_text = 1;
               continue;
            case 'w':
               flag_warn = 1;
               continue;
         }
      }
   }
   if (!flag_binary && !flag_text)
      flag_text = 1;

   do_md5sum ();
   return (EXIT_SUCCESS);
}
