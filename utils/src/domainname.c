
/*
 *  domainname -- print of set the system domainname
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
 * $Id: domainname.c,v 1.1 2003/01/29 08:21:40 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/param.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: domainname long-option\n"
   "       domainname [name]\n"
   "Print or set the system domainname.\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   char domainname[MAXHOSTNAMELEN];

   progname = argv[0];
   
   if (argc == 1)
   {
      if (getdomainname (domainname, MAXHOSTNAMELEN) < 0)
         error ("cannot get domainname: %s", strerror (errno));
      puts (domainname);
      return (EXIT_SUCCESS);
   }
   else if (argc == 2)
   {
      if (!strcmp (argv[1], "--help"))
         puts (help_text);
      else if (!strcmp (argv[1], "--version"))
         puts ("domainname: version "VERSION);
      else
      {
         if (setdomainname (argv[1], strlen (argv[1])) < 0)
            error ("cannot set domainname: %s", strerror (errno));
      }
   }
   else
      terror ("too many arguments");
      
   return (EXIT_SUCCESS);
}
