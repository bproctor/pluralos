
/*
 *  uncompress -- uncompress a file
 *  Copyright (c) 2002-2003 Brad Proctor
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
 * $Id: uncompress.c,v 1.4 2003/02/10 20:46:20 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: uncompress long-option\n"
   "Uncompress a file.\n"
   "\n"
   "  All regular options are ignored\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "The SUSV3 standard states that the `uncompress' utility use\n"
   "the Lempel-Ziv compression algorithm.  Lempel-Ziv is\n"
   "US Patent 4464650 and therefore is not supported in the\n"
   "Plural Operating System. Use `punzip' instead.\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   if (argc == 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("uncompress: version "VERSION);
         return (EXIT_SUCCESS);
      }
   }

   /* All other options are ignored */
   
   /* 
    * SUSV3: 
    * "On systems not supporting Lempel-Ziv coding algorithm, the
    *  input files shall not be changed and an error value greater
    *  than two shall be returned."
    */
    
    return (3);
}
