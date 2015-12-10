
/*
 *  ide-disk.c
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
 * $Id: ide-disk.c,v 1.6 2002/12/02 04:16:28 fredlie Exp $
 */
 
#include <sys/types.h>
#include <sys/errno.h>
#include <system.h>
#include <device.h>
#include <stdio.h>

Device ide;

static ulong ide_stat (ulong s)
{
   return (0);
}

static ulong ide_op (ulong com)
{
   return (0);
}

static ulong ide_init (void)
{
   return (0);
}

void __init__ init_ide (void)
{
   puts ("Initializing IDE...");
   ide.init = ide_init;
   ide.op = ide_op;
   ide.stat = ide_stat;
   puts ("done\n");
}


asm (
"     .text                \n"
"     .globl   int_ide     \n"
"     .align   16          \n"
"int_ide:                  \n"
"     pushal               \n"
"     movb     $0x20,%al   \n"
"     outb     %al,$0x20   \n"
"     popal                \n"
"     iret                 \n");

