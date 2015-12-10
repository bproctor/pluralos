
/*
 *  id -- Return user's identity
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
 * $Id: id.c,v 1.5 2003/02/10 20:46:08 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: id long-option\n"
   "       id [-g | -u][-nr][user]\n"
   "       id -G [-n][user]\n"
   "Return user's identity.\n"
   "\n"
   "  -g         Print the effective group ID\n"
   "  -G         Print all group IDs\n"
   "  -n         Print names instead of ID numbers\n"
   "  -r         Print real IDs instead of effective IDs\n"
   "  -u         Print the effective user ID\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_group = 0;
static char flag_agroups = 0;
static char flag_name = 0;
static char flag_real = 0;
static char flag_user = 0;

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i, uid, gid;
   char *ptr, **look, *group_name = 0;
   char *user_name = 0;
   
   struct passwd *pw;
   struct group *gr;
   
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
                  puts ("id: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'g':
               flag_group = 1;
               continue;
            case 'G':
               flag_agroups = 1;
               continue;
            case 'n':
               flag_name = 1;
               continue;
            case 'r':
               flag_real = 1;
               continue;
            case 'u':
               flag_user = 1;
               continue;
         }
      }
      else
         user_name = argv[i];
   }
   
   if (!user_name)
   {
         user_name = xmalloc (L_cuserid);
         if (cuserid (user_name) == NULL)
            error ("cannot get user name: %s", strerror (errno));
         uid = flag_real ? getuid () : geteuid ();
         gid = flag_real ? getgid () : getegid ();
         gr = getgrgid (gid);
         group_name = gr->gr_name;
   }
   else
   {
      pw = getpwnam (user_name);
      uid = pw->pw_uid;
      gr = getgrgid (pw->pw_gid);
      gid = gr->gr_gid;
      group_name = gr->gr_name;
   }

   if (flag_user)
   {
      if (flag_name)
         printf ("%s\n", user_name);
      else
         printf ("%u\n", uid);
   }
   else if (flag_group)
   {
      if (flag_name)
         printf ("%s\n", group_name);
      else
         printf ("%u\n", gid);
   }
   else   
      printf ("uid=%u(%s) gid=%u(%s) groups=", uid, user_name, gid, group_name);

   setgrent ();
   gr = getgrent ();
   while (gr)
   {
      look = gr->gr_mem;
      while (*look)
      {
         if (!strcmp (*look, user_name))
            printf ("%u(%s), ", gr->gr_gid, *look);
         *look++;
      }
      gr = getgrent ();
   }
   endgrent ();
   fputs ("\b\b\n", stdout);

   return (EXIT_SUCCESS);
}
