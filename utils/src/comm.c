
/*
 *  comm -- select or reject lines common to two files
 *  Copyright (c) 1999-2003 Brad Proctor
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
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * $Id: comm.c,v 1.15 2003/02/10 20:45:56 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

#define  BUF_SIZE    8192

static const char help_text[] =
{
   "Usage: comm long-option\n"
   "       comm [-123] file1 file2\n"
   "Compare files line by line.\n"
   "\n"
   "  -1         Suppress lines unique to file1\n"
   "  -2         Suppress lines unique to file2\n"
   "  -3         Suppress lines duplicated in file1 and file2\n"
   "\n"
   "Long Option:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_1 = 1;
static char flag_2 = 1;
static char flag_3 = 1;
static FILE *file1 = 0;
static FILE *file2 = 0;
static char buf1[BUF_SIZE];
static char buf2[BUF_SIZE];

static int read_line (char *buf, FILE *file)
{
   char *ptr = buf;
   int c;
   
   while (1)
   {
      c = getc (file);
      if (c == '\n' || c == EOF)
         break;
      *ptr++ = c;
   }
   *ptr = '\0';
   if (c == '\n')
      return (0);
   return (1);
}

/*
 * Main
 */

int main (int argc, char **argv)
{
   int i, end1, end2;
   char *ptr;

   progname = argv[0];
   
   if (argc == 1)
      terror ("too few arguments");
   
   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      if (*ptr == '-')
      {
         while (*++ptr)
         switch (*ptr)
         {
            case '\0':
               file1 = stdin;
               break;
            case '-':
               if (!strcmp (ptr, "-help"))
               {
                  puts (help_text);
                  return (EXIT_SUCCESS);
               }
               else if (!strcmp (ptr, "-version"))
               {
                  puts ("comm: version "VERSION);
                  return (EXIT_SUCCESS);
               }
               else if (*ptr == '\0')
               {
                  if (!file1)
                     file1 = stdin;
                  else if (!file2)
                     file2 = stdin;
                  else
                     terror ("too many arguments");
               }
               break;
            case '1': flag_1 = 0; continue;
            case '2': flag_2 = 0; continue;
            case '3': flag_3 = 0; continue;
            default:
               error ("invalid option `%s'", argv[i]);
         }
      }
      else if (!file1)
         file1 = xfopen (argv[i], "r");
      else if (!file2)
         file2 = xfopen (argv[i], "r");
   }

   /* Same as no output */
   if (!flag_1 && !flag_2 && !flag_3)
      return (EXIT_SUCCESS);

   end1 = read_line (buf1, file1);
   end2 = read_line (buf2, file2);
   
   while (!end1 || !end2)
   {
      i = strcmp (buf1, buf2);

      if (i == 0)
      {
         if (flag_3)
         {
            if (flag_1)
               putchar ('\t');
            if (flag_2)
               putchar ('\t');
            puts (buf2);
         }
      }
      else if (i > 0)
      {
         if (flag_2)
         {
            if (flag_1)
               putchar ('\t');
            puts (buf2);
         }
      }
      else
         if (flag_1)
            puts (buf1);
         
         
      if (i <= 0)
         end1 = read_line (buf1, file1);
      if (i >= 0)
         end2 = read_line (buf2, file2);
   }
   fclose (file1);
   fclose (file2);
   return (EXIT_SUCCESS);
}
