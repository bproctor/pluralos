
#
#  Makefile.inc
#  Copyright (c) 2001-2003 Brad Proctor
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
# $Id: Makefile.inc,v 1.7 2003/01/19 19:26:14 fredlie Exp $
#

CFLAGS = -Wall -Wno-trigraphs -O2 -fomit-frame-pointer -pipe -nostdinc -fno-common -fno-builtin

ifdef CONFIG_RTD
CFLAGS += -mrtd
endif

ifdef CONFIG_I386
CFLAGS += $(shell if $(CC) -march=i386 -S -o /dev/null -xc /dev/null 2>&1; then echo "-march=i386"; else echo "-m386"; fi)
endif

ifdef CONFIG_I486
CFLAGS += $(shell if $(CC) -march=i486 -S -o /dev/null -xc /dev/null 2>&1; then echo "-march=i486"; else echo "-m486"; fi)
endif

ifdef CONFIG_I586
CFLAGS += $(shell if $(CC) -march=i586 -S -o /dev/null -xc /dev/null 2>&1; then echo "-march=i586"; fi)
endif

ifdef CONFIG_I586TSC
CFLAGS += $(shell if $(CC) -march=i586 -S -o /dev/null -xc /dev/null 2>&1; then echo "-march=i586"; fi)
endif

ifdef CONFIG_I586MMX
CFLAGS += $(shell if $(CC) -march=i586 -S -o /dev/null -xc /dev/null 2>&1; then echo "-march=i586"; fi)
endif

ifdef CONFIG_I686
CFLAGS += $(shell if $(CC) -march=i686 -S -o /dev/null -xc /dev/null 2>&1; then echo "-march=i686"; fi)
endif

ifdef CONFIG_IP3
CFLAGS += $(shell if $(CC) -march=pentium3 -S -o /dev/null -xc /dev/null 2>&1; then echo "-march=i686"; fi)
endif

ifdef CONFIG_IP4
CFLAGS += $(shell if $(CC) -march=pentium4 -S -o /dev/null -xc /dev/null 2>&1; then echo "-march=i686"; fi)
endif

ifdef CONFIG_IK6
CFLAGS += $(shell if $(CC) -march=k6 -S -o /dev/null -xc /dev/null 2>&1; then echo "-march=k6"; else echo "-march=i586"; fi)
endif

ifdef CONFIG_IK7
CFLAGS += $(shell if $(CC) -march=athlon -S -o /dev/null -xc /dev/null 2>&1; then echo "-march=athlon"; else echo "-march=i586"; fi)
endif

CFLAGS += $(shell if $(CC) -mpreferred-stack-boundary=2 -S -o /dev/null -xc /dev/null 2>&1; then echo "-mpreferred-stack-boundary=2"; fi)
CFLAGS += -D__KERNEL__

export AR = ar
export CC = gcc
export LD = ld
export NM = nm
export OBJCOPY = objcopy
export SIZE = size
export CFLAGS
