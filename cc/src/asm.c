
/*
 *  asm.c
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
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * $Id: asm.c,v 1.1 2002/12/18 06:10:46 fredlie Exp $
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cc.h"

#define  out(x)      fputs (x, outfile)

extern char *inname;
extern FILE *outfile;

void asm_start_file (void)
{
   fprintf (outfile, "; '%s' compiled by cc\n", inname);
   out ("section     .text\n");
}

void asm_finish_file (void)
{
}
