
/*
 *  plural.ld
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
 * $Id: plural.ld,v 1.8 2002/12/02 04:06:55 fredlie Exp $
 */

OUTPUT_FORMAT("elf32-i386", "elf32-i386", "elf32-i386")
OUTPUT_ARCH(i386)
ENTRY(_start)
SECTIONS
{
	. = 0x00100000;
	.text : {
		_text = .;
		*(.text)
		*(.text.*)
		_etext = .;
	}
	.data : {
		_data = .;
		*(.data)
		_edata = .;
	}
	.rodata : {
		_rodata = .;
		*(.rodata)
		*(.rodata.*)
		_erodata = .;
	}
	.init : {
		. = ALIGN(4096);
		_init = .;
		*(.init)
		*(.init.*);
		_einit = .;
		. = ALIGN(4096);
	}
	.bss : 	{
		_bss = .;
		*(.bss)
		_ebss = .;
		. = ALIGN(4096);
		_end = .;
	}
}

