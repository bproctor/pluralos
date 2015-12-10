
/*
 *  uuencode -- UU encode a binary file
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
 * $Id: uuencode.c,v 1.7 2003/02/16 18:46:41 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: uuencode long-option\n"
   "       uuencode [-a type][-m mode] file [path]\n"
   "UU encode a file.\n"
   "\n"
   "  -b type    Specify the encoding algorithm\n"
   "  -m mode    Set the permission bits\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

#define FLAG_HISTORIC   0
#define FLAG_64BIT      1

static FILE *in = 0;
static char *mode = 0;
static char *decode_path = 0;
static char flag_algorithm = FLAG_HISTORIC;

static void do_uuencode (void)
{
   int a, b, c, i = 0;
   printf ("begin\t%s\t%s\n", mode, decode_path);
   while (1)
   {
      if ((a = getc (in)) == EOF)
         break;
      if ((b = getc (in)) == EOF)
         break;
      if ((c = getc (in)) == EOF)
         break;
      putchar(0x20 + (( a >> 2                    ) & 0x3F));
      putchar(0x20 + (((a << 4) | ((b >> 4) & 0xF)) & 0x3F));
      putchar(0x20 + (((b << 2) | ((c >> 6) & 0x3)) & 0x3F));
      putchar(0x20 + (( c                         ) & 0x3F));
      if (++i >= 15)
      {
         i = 0;
         putchar ('\n');
         putchar (0x20 + 45);
      }
   }
   puts ("\nend");
}

static void do_uuencode_64 (void)
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

   if (argc == 1)
      terror ("too few arguments");
   
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
                  puts ("uuencode: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'a':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-%c' option", *(ptr-1));
               if (!strcmp (ptr, "64bit"))
                  flag_algorithm = FLAG_64BIT;
               else if (!strcmp (ptr, "historic"))
                  flag_algorithm = FLAG_HISTORIC;
            case 'm':
               if (*++ptr != '\0')
                  ;
               else if (++i < argc)
                  ptr = argv[i];
               else
                  terror ("missing operand to `-%c' option", *(ptr-1));
               mode = ptr;
               break;
         }
      }
      else if (!in)
         in = xfopen (argv[i], "r");
      else if (!decode_path)
         decode_path = argv[i];
      else
         terror ("too many arguments");
   }
   
   if (flag_algorithm == FLAG_64BIT)
      do_uuencode_64 ();
   else
      do_uuencode ();
   
   return (EXIT_SUCCESS);
}
