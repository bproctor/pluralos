
/*
 *  dep.c -- Create makefile dependencies.
 *  Copyright (c) 2001-2002 Brad Proctor
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
 * $Id: dep.c,v 1.4 2002/12/02 04:16:28 fredlie Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../include/version.h"

#define  LINE_MAX    200      /* Maximum length of a line */

static const char help_text[] =
{
   "Usage: dep [option] [depfile]\n"
   "Create makefile dependencies\n"
   "\n"
   "  -Iincdir   Make `incdir' the include directory\n"
   "  -S         Ignore standard include files\n"
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
   int i, ignore_std = 0;
   char *ptr, buf[LINE_MAX];
   char *ptr1, buf1[50];
   char *incdir = 0;
   FILE *in = 0;

   if (argc < 2)
   {
      puts (help_text);
      return (EXIT_SUCCESS);
   }
   
   for (i = 1; i < argc; ++i)
   {
      ptr = argv[i];
      if (*ptr == '-')
      {
         switch (*++ptr)
         {
            case '-':
               if(!strcmp (++ptr, "help"))
               {
                  puts (help_text);
                  return (EXIT_SUCCESS);
               }
               else if (!strcmp (ptr, "version"))
               {
                  puts ("dep version "VERSION_STRING);
                  return (EXIT_SUCCESS);
               }
            case 'I':
               incdir = malloc (strlen (ptr)+1);
               if (!incdir)
               {
                  fputs ("Out of memory\n", stderr);
                  return (EXIT_FAILURE);
               }
               strcpy (incdir, ++ptr);
               ptr = strrchr (incdir, '/');
               if (!ptr)
                  ptr = strchr (incdir, '\0');
               if (*ptr != '/')
                  *ptr = '/';
               *++ptr = '\0';
               break;
            case 'S':
               if (*++ptr != '\0')
               {
                  fprintf (stderr, "%s: Invalid option: `%s'\n",   
                     argv[0], argv[i]);
                  return (1);
               }
               ignore_std = 1;
               break;
         }
      }
      else
      {
         if (in)
            fclose (in);
         in = fopen (argv[i], "r");
         if (!in)
         {
            fprintf (stderr, "%s: Could not open `%s' for reading\n",
               argv[0], argv[i]);
            return (EXIT_FAILURE);
         }
         ptr = buf;
         strcpy (ptr, argv[i]);
         ptr = strrchr (ptr, '.');
         *ptr++ = '.';
         *ptr++ = 'o';
         *ptr = '\0';
         printf ("\n%s : %s", buf, argv[i]);
         while (fgets (buf, LINE_MAX, in) > 0)
         {
            ptr = buf;
            if (*ptr == '#' || *ptr == '%')
            {
               int asm_flag = 0;
               if (*ptr == '%')
                  asm_flag = 1;
               while (isspace (*++ptr));
               if (!strncmp (ptr, "include", 7))
               {
                  ptr += 7;
                  while (isspace (*ptr)) 
                     ++ptr;
                  if (*ptr == '\"')
                  {
                     ++ptr;
                     ptr1 = buf1;
                     while (*ptr != '\"' && *ptr != '\0')
                        *ptr1++ = *ptr++;
                     *ptr1 = '\0';
                     putchar (' ');
                     if (asm_flag)
                        fputs (incdir, stdout);
                     fputs (buf1, stdout);
                  }
                  else if (*ptr == '<' && ignore_std == 0)
                  {
                     ++ptr;
                     ptr1 = buf1;
                     while (*ptr != '>' && *ptr != '\0')
                        *ptr1++ = *ptr++;
                     *ptr1 = '\0';
                     putchar (' ');
                     fputs (incdir, stdout);
                     fputs (buf1, stdout);
                  }
               }
            }
         }
      }   
   }
   return (EXIT_SUCCESS);
}
