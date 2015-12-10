
/*
 *  asm.h
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
 * $Id: asm.h,v 1.3 2002/12/05 05:58:36 fredlie Exp $
 */

#ifndef __ASM_H__
#define __ASM_H__

#ifndef __CONFIG_H__
#include <config.h>
#endif

#ifdef CONFIG_ALIGN16
#define ALIGN  .align 16
#else
#define ALIGN  .align 4
#endif

#define LOCAL(x)  ALIGN;x
#define ENTRY(x)  .globl x;ALIGN;x
#define GLOBAL(x) .globl x;x

#endif /* __ASM_H__ */
