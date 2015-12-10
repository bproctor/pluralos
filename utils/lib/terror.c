
/*
 *  terror.c -- ooh scary
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
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

/*
 * $Id: terror.c,v 1.2 2003/01/29 08:20:33 fredlie Exp $
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <libgen.h>
#include "utils.h"

/*
 * This is the same as error except that it
 * prints an extra message.
 */

void (terror)(const char *msg, ...)
{
   char *p = basename (progname);
   va_list ap;
   fprintf (stderr, "%s: ", p);
   va_start (ap, msg);
   vfprintf (stderr, msg, ap);
   va_end (ap);
   fprintf (stderr, "\nTry `%s --help' for more information\n", p);
   exit (EXIT_FAILURE); 
}
