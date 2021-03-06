
/*
 *  newgrp -- change to a new group
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
 * $Id: newgrp.c,v 1.5 2003/01/29 08:20:42 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: newgrp long-option\n"
   "       newgrp [-l][group]\n"
   "Change to a new group.\n"
   "\n"
   "  -l         \n"
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
   struct passwd *pw;
   struct group *g;
   
   progname = argv[0];

   pw = getpwuid (getuid ());
   if (!pw)
      error ("cannot figure out who you are???");
   
   if (argc == 1)
   {
      if (setgid (pw->pw_gid) < 0)
         error ("setgid() failed: %s", strerror (errno));
   }
   else if (argc >= 2)
   {
      if (!strcmp (argv[1], "--help"))
      {
         puts (help_text);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "--version"))
      {
         puts ("newgrp: version "VERSION);
         return (EXIT_SUCCESS);
      }
      else if (!strcmp (argv[1], "-l"))
         ;
   }
   g = getgrnam(argv[1]);
   if (!g)
      error ("`%s' is not a group", argv[1]);

   if (setgid (g->gr_gid) < 0)
      error ("cannot set new group: %s", strerror (errno));
      
   return (EXIT_SUCCESS);
}
