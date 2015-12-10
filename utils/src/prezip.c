
/*
 *  prezip.c -- process multimedia files for better compression
 *  Copyright (c) 2001-2003 Brad Proctor
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
 * $Id: prezip.c,v 1.13 2003/02/10 20:46:16 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include "utils.h"

static const char help_text[] =
{
   "Usage: prezip long-option\n"
   "       prezip [-cd] infile [outfile]\n"
   "Process multimedia files for better compression"
   "\n"
   "  -c         Output to standard output\n"
   "  -d         Decode\n"
   "\n"
   "Long Options:\n"
   "  --help     Print this help message\n"
   "  --version  Print the version\n"
   "\n"
   "Report bugs to <bugs@plural-os.org>."
};

static char flag_decode = 0;
static char *inname;
static char *outname;
static FILE *infile;
static FILE *outfile;
static char *inbuf, *inptr;
static char *outbuf, *outptr;
static unsigned int incount;

static void encode (void)
{
   incount = fread (inbuf, 1, 65535, infile);
   inptr = inbuf;
   if (!incount)
      error ("cannot encode empty file");
   *outptr++ = *inptr++;
   while (1)
   {
      while (--incount)
         *outptr = *inptr - *(inptr-1), ++inptr, ++outptr;
      fwrite (outbuf, 1, outptr - outbuf, outfile);
      outptr = outbuf;
      incount = fread (inbuf, 1, 65535, infile);
      inptr = inbuf;
      if (!incount)
         break;
   }
}

static void decode (void)
{
   incount = fread (inbuf, 1, 65535, infile);
   inptr = inbuf;
   if (!incount)
      error ("cannot decode empty file");
   *outptr++ = *inptr++;
   while (1)
   {
      while (--incount)
         *outptr = *(outptr-1) + *inptr, ++inptr, ++outptr;
      fwrite (outbuf, 1, outptr - outbuf, outfile);
      outptr = outbuf;
      incount = fread (inbuf, 1, 65535, infile);
      inptr = inbuf;
      if (!incount)
         break;
   }
}

/*
 * Main
 */
 
int main (int argc, char **argv)
{
   int i;
   char *ptr;
   
   if (argc < 2)
      error ("no input file specified");
   
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
                  puts ("prezip: version "VERSION);
               else
                  terror ("invalid option `%s'", argv[i]);
               return (EXIT_SUCCESS);
            case 'c':
               continue;
            case 'd':
               flag_decode = 1;
               continue;
         }
      }
      else if (!infile)
      {
         inname = xmalloc (strlen (argv[i]));
         strcpy (inname, argv[i]);
         infile = xfopen (inname, "r");
      }
      else if (!outfile)
      {
         outname = xmalloc (strlen (argv[i]));
         strcpy (outname, argv[i]);
         outfile = xfopen (outname, "w");
      }
   }   
   if (!infile)
      terror ("no input file specified");
   if (!outfile)
   {
      if (!strcmp (strrchr (inname, '.'), ".pz"))
      {
         if (flag_decode)
         {
            outname = xmalloc (strlen (inname));
            strcpy (outname, inname);
            strcat (strrchr (outname, '.'), "");
            outfile = xfopen (outname, "w");
         }
         else
            error ("file already has .pz extention");
      }
      else
      {   
         outname = xmalloc (strlen (inname)+3);
         strcpy (outname, inname);
         strcat (outname, ".pz");
         outfile = xfopen (outname, "w");
      }
   }
   inbuf = xmalloc (65536);
   outbuf = xmalloc (65536);
   inptr = inbuf;
   outptr = outbuf;   

   if (flag_decode)
      decode ();
   else
      encode ();   

   free (inbuf);
   free (outbuf);
   fclose (infile);
   fclose (outfile);
   return (EXIT_SUCCESS);
}
