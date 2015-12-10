
/*
 *  except.S
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
 * $Id: except.S,v 1.4 2002/12/02 09:06:24 fredlie Exp $
 */

#include <asm.h>

LOCAL (error):
        pushal
        pushl   %ds
        pushl   %es
        pushl   %fs
        pushl   %gs
        pushl   %ss
        call    show_regs
        cli
        hlt

ENTRY (except00):
        pushl   $0
	pushl	$0
	pushl	$handle_exception_00
	jmp	error

ENTRY (except01):
        pushl   $0
	pushl	$1
	pushl	$handle_exception_01
	jmp	error

ENTRY (except02):
        pushl   $0
	pushl   $2
	pushl	$handle_exception_02
	jmp	error

ENTRY (except03):
        pushl   $0
	pushl   $3
	pushl	$handle_exception_03
	jmp	error

ENTRY (except04):
        pushl   $0
	pushl   $4
	pushl	$handle_exception_04
	jmp	error

ENTRY (except05):
        pushl   $0
	pushl   $5
	pushl	$handle_exception_05
	jmp	error

ENTRY (except06):
        pushl   $0
	pushl   $6
	pushl	$handle_exception_06
	jmp	error

ENTRY (except07):
        pushl   $0
	pushl   $7
	pushl	$handle_exception_07
	jmp	error

ENTRY (except08):
	pushl   $8
	pushl	$handle_exception_08
	jmp	error

ENTRY (except09):
        pushl   $0
	pushl   $9
	pushl   $handle_exception_09
	jmp     error

ENTRY (except10):
	pushl   $10
	pushl   $handle_exception_10
	jmp     error

ENTRY (except11):
	pushl   $11
	pushl   $handle_exception_11
	jmp     error

ENTRY (except12):
	pushl   $12
	pushl   $handle_exception_12
	jmp     error

ENTRY (except13):
	pushl   $13
	pushl   $handle_exception_13
	jmp     error

ENTRY (except14):
	pushl   $14
	pushl   $handle_exception_14
	jmp     error

ENTRY (except15):
        pushl   $0
	pushl   $15
	pushl   $handle_exception_15
	jmp     error

ENTRY (except16):
        pushl   $0
	pushl   $16
	pushl   $handle_exception_16
	jmp     error

ENTRY (except17):
	pushl   $17
	pushl   $handle_exception_17
	jmp     error

ENTRY (except18):
	pushl   $18
	pushl   $handle_exception_18
	jmp     error

ENTRY (except19):
        pushl   $19
        pushl   $handle_exception_19
        jmp     error

ENTRY (except_null):
        iret
        