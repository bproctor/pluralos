
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
# $Id: Makefile,v 1.3 2002/12/02 04:16:28 fredlie Exp $
#

TOP = ../..
DIR_TARGET = block.o

include $(TOP)/.config

ifdef CONFIG_FLOPPY
DIRS += floppy
endif

ifdef CONFIG_IDE
DIRS += ide
endif

include $(TOP)/Makefile.def
