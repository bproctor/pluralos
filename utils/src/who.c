
/*
 *  who -- List who is on the system
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
 * $Id: who.c,v 1.6 2003/02/10 20:46:21 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: who long-option\n"
   "       who [am i]\n"
   "List who is on the system.\n"
   "\n"
   "  am i       Print current user name\n"
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
   int i;
   char *ptr;
   struct passwd *p;
   uid_t uid;
   
   progname = argv[0];
   
   if (argc == 3)
   {
      if (!strcmp (argv[1], "am") && !strcmp (argv[2], "i"))
      {
         uid = geteuid ();
         if (uid == -1)
            error ("cannot get effective UID: %s", strerror (errno));
         p = getpwuid (uid);
         if (!p)
            error ("cannot find username for UID %u: %s",
               (unsigned int)uid, strerror (errno));
         puts (p->pw_name);
         return (EXIT_SUCCESS);
      }
   }

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
                  puts ("who: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
         }
      }
   }
   return (EXIT_SUCCESS);
}
