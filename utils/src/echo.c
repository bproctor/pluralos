
/*
 *  echo -- write arguments to standard output
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
 * $Id: echo.c,v 1.11 2003/01/27 23:46:03 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: echo long-option\n"
   "       echo [-en] args...\n"
   "Print each argument to the standard output.\n"
   "\n"
   "  -e         Interpret control characters\n"
   "  -n         Do not output a final newline\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_newline = 1;
static char flag_control = 0;

/*
 * Main
 *
 * The echo command does not support the --help and --version
 * options.  They will be echoed like everything else.
 */

int main (int argc, char **argv)
{
   int i = 1, n;
   char *ptr;
   
   if (argc == 1)
      return (EXIT_SUCCESS);
   else if (argc >= 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("echo: version "VERSION);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "-n"))
         flag_newline = 0, i = 2;
      else if (!strcmp (argv[1], "-e"))
         flag_control = 1, i = 2;
   }      

   if (flag_control)
   {
      for (; i < argc; ++i)
      {
         ptr = argv[i];
         while (*ptr != '\0')
         {
            if (*ptr == '\\')
            {
               switch (*++ptr)
               {
                  case 'a': putchar ('\a'); break;
                  case 'b': putchar ('\b'); break;
                  case 'e': putchar ('\e'); break;
                  case 'f': putchar ('\f'); break;
                  case 'n': putchar ('\n'); break;
                  case 'r': putchar ('\r'); break;
                  case 't': putchar ('\t'); break;
                  case 'v': putchar ('\v'); break;
                  case 'x':
                     n = 0;
                     while (1)
                     {
                        if (isdigit (*++ptr))
                           n = (n << 4) + *ptr - '0';
                        else if (*ptr >= 'a' && *ptr <= 'f')
                           n = (n << 4) + *ptr - 'a' + 10;
                        else if (*ptr >= 'A' && *ptr <= 'F')
                           n = (n << 4) + *ptr - 'A' + 10;
                        else
                           break;
                     }
                     putchar (n);
                     --ptr;
                     break;
                  case '0':
                     n = 0;
                     while (1)
                     {
                        if (*++ptr >= '0' && *ptr <= '7')
                           n = (n << 3) + *ptr - '0';
                        else
                           break;
                     }
                     putchar (n);
                     --ptr;
                     break;
                  default:
                     putchar (*ptr);
                     break;
               }
            }
            else
               putchar (*ptr);
            ++ptr;
         }
      }
   }
   else
   {
      for (; i < argc; ++i)
      {
         fputs (argv[i], stdout);
         putchar (' ');
      }
   }

   if (flag_newline)
      putchar ('\n');
   
   return (EXIT_SUCCESS);
}
