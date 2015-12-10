
#
#  Makefile
#  Copyright (c) 2001-2002 Brad Proctor
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#

#
# $Id: Makefile,v 1.9 2002/12/13 07:59:59 fredlie Exp $
#

TOP = ../..
TARGET = low.o

include $(TOP)/.config

ifdef CONFIG_DEBUGGER
SRC += debug.c
endif

ifdef CONFIG_SMP
SRC += smp.c
SRC += apic.c
endif

SRC += cpuid.c
SRC += delay.c
SRC += dma.c
SRC += error.c
SRC += except.S
SRC += pit.c
SRC += switch.c
SRC += syscall.S
SRC += time.c

include $(TOP)/Makefile.def
