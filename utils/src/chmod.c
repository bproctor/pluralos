
/*
 *  chmod -- change the file modes
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
 * $Id: chmod.c,v 1.13 2003/02/16 15:26:34 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: chmod long-option\n"
   "       chmod [-R] mode file ...\n"
   "Change file permissions.\n"
   "\n"
   "  -R         Recursively change file permission bits\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_recursive = 0;
static char flag_user = 0;
static char flag_owner = 0;
static char flag_group = 0;
static char flag_read = 0;
static char flag_write = 0;
static char flag_exec = 0;
static char flag_add = 0;
static char flag_remove = 0;
static char flag_equals = 0;

/*
 * Main
 */

int main (int argc, char **argv)
{
   int i = 1, mode, newmode;
   char *ptr;
   
   progname = argv[0];
   
   if (argc == 1)
      terror ("too few arguments");
   else if (argc == 2)
   {
      if (!strcmp (argv[1], "--help"))
         puts (help_text);
      else if (!strcmp (argv[1], "--version"))
         puts ("chmod: version "VERSION);
      else
         terror ("");
      return (EXIT_SUCCESS);
   }

   if (!strcmp (argv[1], "-R"))
      flag_recursive = 1, ++i;


   ptr = argv[i];
   if (isdigit (*ptr))
      mode = getnum_octal (argv[i]);

   else
   {
      int done = 0;
      while (!done)
      {
         switch (*ptr)
         {
            case 'g': flag_group = 1; break;
            case 'o': flag_owner = 1; break;
            case 'u': flag_user = 1; break;
            default:
               done = 1;
         }
         ++ptr;
      }
      if (*ptr == '-')
         flag_remove = 1;
      else if (*ptr == '+')
         flag_add = 1;
      else if (*ptr == '=')
         flag_equals = 1;
      else
         terror ("invalid character in mode field `%c'", *ptr);
      
      ++ptr, done = 0;
      while (!done)
      {
         switch (*ptr++)
         {
            case 'r': flag_read = 1; break;
            case 'w': flag_write = 1; break;
            case 'x': flag_exec = 1; break;
            default:
               done = 1;
         }
      }
      newmode = 0;
      mode = (flag_read << 2) | (flag_write << 1) | flag_exec;
      if (flag_user)
         newmode |= mode << 6;
      if (flag_group)
         newmode |= mode << 3;
      if (flag_owner)
         newmode |= mode;

      if (flag_equals)
      {
         if (chmod (argv[i+1], newmode))
            error ("cannot change permissions of `%s': %s",
               argv[i+1], strerror (errno));
         return (EXIT_SUCCESS);
      }
      
      if (flag_add)
         ;
      else if (flag_remove)
         ;
      
   }
   return (EXIT_SUCCESS);
}
