
/*
 *  find -- Find files
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
 * $Id: find.c,v 1.6 2003/02/10 20:46:05 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: find long-option\n"
   "       find [-H | -L] path ... [expression]\n"
   "Find files.\n"
   "\n"
   "  -H         \n"
   "  -L         \n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the program version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

struct op
{
   char *name;
   int flag;
};

#define FLAG_A          1
#define FLAG_AMIN       2
#define FLAG_AND        3
#define FLAG_ANEWER     4
#define FLAG_ATIME      5
#define FLAG_CMIN       6
#define FLAG_CNEWER     7
#define FLAG_CTIME      8
#define FLAG_DAYSTART   9
#define FLAG_DEPTH      10
#define FLAG_EMPTY      11
#define FLAG_FALSE      12
#define FLAG_FSTYPE     13
#define FLAG_GID        14
#define FLAG_GROUP      15
#define FLAG_ILNAME     16
#define FLAG_INAME      17
#define FLAG_INUM       18
#define FLAG_IPATH      19
#define FLAG_IREGEX     20
#define FLAG_LNAME      21
#define FLAG_MAXDEPTH   22
#define FLAG_MINDEPTH   23
#define FLAG_MMIN       24
#define FLAG_MTIME      25
#define FLAG_MOUNT      26
#define FLAG_NAME       27
#define FLAG_NEWER      28
#define FLAG_NOGROUP    29
#define FLAG_NOLEAF     30
#define FLAG_NOT        31
#define FLAG_NOUSER     32
#define FLAG_O          33
#define FLAG_OR         34
#define FLAG_PATH       35
#define FLAG_PERM       36
#define FLAG_PRUNE      37
#define FLAG_REGEX      38
#define FLAG_TRUE       39
#define FLAG_TYPE       40
#define FLAG_UID        41
#define FLAG_USED       42
#define FLAG_USER       43
#define FLAG_XDEV       44
#define FLAG_XTYPE      45

static const struct op opt[] =
{
   {"a",       FLAG_A},
   {"amin",    FLAG_AMIN},
   {"and",     FLAG_AND},
   {"anewer",  FLAG_ANEWER},
   {"atime",   FLAG_ATIME},
   {"cmin",    FLAG_CMIN},
   {"cnewer",  FLAG_CNEWER},
   {"ctime",   FLAG_CTIME},
   {"daystart", FLAG_DAYSTART},
   {"depth",   FLAG_DEPTH},
   {"empty",   FLAG_EMPTY},
   {"false",   FLAG_FALSE},
   {"fstype",  FLAG_FSTYPE},
   {"gid",     FLAG_GID},
   {"group",   FLAG_GROUP},
   {"ilname",  FLAG_ILNAME},
   {"iname",   FLAG_INAME},
   {"inum",    FLAG_INUM},
   {"ipath",   FLAG_IPATH},
   {"iregex",  FLAG_IREGEX},
   {"lname",   FLAG_LNAME},
   {"maxdepth", FLAG_MAXDEPTH},
   {"mindepth", FLAG_MINDEPTH},
   {"mmin",    FLAG_MMIN},
   {"mtime",   FLAG_MTIME},
   {"mount",   FLAG_MOUNT},
   {"name",    FLAG_NAME},
   {"newer",   FLAG_NEWER},
   {"nogroup", FLAG_NOGROUP},
   {"noleaf",  FLAG_NOLEAF},
   {"not",     FLAG_NOT},
   {"nouser",  FLAG_NOUSER},
   {"o",       FLAG_O},
   {"or",      FLAG_OR},
   {"path",    FLAG_PATH},
   {"perm",    FLAG_PERM},
   {"prune",   FLAG_PRUNE},
   {"regex",   FLAG_REGEX},
   {"true",    FLAG_TRUE},
   {"type",    FLAG_TYPE},
   {"uid",     FLAG_UID},
   {"used",    FLAG_USED},
   {"user",    FLAG_USER},
   {"xdev",    FLAG_XDEV},
   {"xtype",   FLAG_XTYPE},
};


/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   char *ptr;
   
   progname = argv[0];
   
   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      if (*ptr == '-')
      {
         switch (*ptr)
         {
            case '-':
               if (!strcmp (ptr, "-help"))
                  puts (help_text);
               else if (!strcmp (ptr, "-version"))
                  puts ("find: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'H':
            case 'L':
               break;
         }
      }
   }
   return (EXIT_SUCCESS);
}
