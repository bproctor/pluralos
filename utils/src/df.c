
/*
 *  df -- print disk usage on mounted partitions
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
 * $Id: df.c,v 1.7 2003/02/16 15:26:34 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: df long-option\n"
   "       df [-b size] [-ikT] [-P | -t] [file ...]\n"
   "Print disk usage on mounted partitions.\n"
   "\n"
   "  -b size    Set block size to 'size'\n"
   "  -i         Print inode information\n"
   "  -k         Print numbers in kilobytes\n"
   "  -l         Limit listings to local filesystems\n"
   "  -t         \n"
   "  -T         Print filesystem type\n"
   "  -P         \n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_local = 0;
static char flag_type = 0;
static char flag_kilo = 0;
static char flag_inode = 0;
static int block_size = 1024;

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
         while (*++ptr)
         switch (*ptr)
         {
            case '-':
               if (!strcmp (ptr, "-help"))
                  puts (help_text);
               else if (!strcmp (ptr, "-version"))
                  puts ("df: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'b':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-b' option");
               block_size = getnum_ul (ptr);
               break;
            case 'i':
               flag_inode = 1;
               break;
            case 'k':
               flag_kilo = 1;
               continue;
            case 'l':
               flag_local = 1;
               continue;
            case 't':
               continue;
            case 'T':
               flag_type = 1;
               continue;
            case 'P':
               continue;
         }
      }
   }
   return (EXIT_SUCCESS);
}
