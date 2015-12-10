
/*
 *  uname -- print information about the system
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
 * $Id: uname.c,v 1.4 2003/02/10 20:46:20 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <sys/utsname.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: uname long-option\n"
   "       uname [-amnrsv]\n"
   "Print info about the system.\n"
   "  -a         Behave as if all options (-mnrsv) where specified\n"
   "  -m         Print the machine type on which the system is running\n"
   "  -n         Print the name of this node\n"
   "  -r         Print the release level of the operating system\n"
   "  -s         Print the name of the implementation of the operating system\n"
   "  -v         Print the version of the operating system\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

#define FLAG_M    0x01
#define FLAG_N    0x02
#define FLAG_R    0x04
#define FLAG_S    0x08
#define FLAG_V    0x10

static int flag = 0;

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   char *ptr;
   struct utsname u;
   
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
                  puts ("uname: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'a': flag |= FLAG_M|FLAG_N|FLAG_R|FLAG_S|FLAG_V; continue;
            case 'm': flag |= FLAG_M; continue;
            case 'n': flag |= FLAG_N; continue;
            case 'r': flag |= FLAG_R; continue;
            case 's': flag |= FLAG_S; continue;
            case 'v': flag |= FLAG_V; continue;
            default:
               terror ("invalid option `-%c'", *ptr);
         }
      }
   }
   if (uname (&u) == -1)
      error ("cannot get system information: %s", strerror (errno));

   if (flag & FLAG_S || flag == 0)
   {
      fputs (u.sysname, stdout);
      flag &= ~FLAG_S;
      if (flag)
         putchar (' ');
   }
   if (flag & FLAG_N)
   {
      fputs (u.nodename, stdout);
      flag &= ~FLAG_N;
      if (flag)
         putchar (' ');
   }
   if (flag & FLAG_R)
   {
      fputs (u.release, stdout);
      flag &= ~FLAG_R;
      if (flag)
         putchar (' ');
   }
   if (flag & FLAG_V)
   {
      fputs (u.version, stdout);
      flag &= ~FLAG_V;
      if (flag)
         putchar (' ');
   }
   if (flag & FLAG_M)
      fputs (u.machine, stdout);
   putchar ('\n');
   
   return (EXIT_SUCCESS);
}
