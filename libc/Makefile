
#
#  Makefile
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
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

#
# $Id: Makefile,v 1.14 2003/01/29 08:35:38 fredlie Exp $
#

VERSION = 0.0.7

INSTALL_DIR = ~/test/

ANSI = 	ansi/assert/assert.o \
	ansi/ctype/ctype.o   \
	ansi/locale/locale.o \
	ansi/math/math.o     \
	ansi/setjmp/setjmp.o \
	ansi/signal/signal.o \
	ansi/stdio/stdio.o   \
	ansi/stdlib/stdlib.o \
	ansi/string/string.o \
	ansi/time/time.o

COMPAT = compat/stdlib/stdlib.o \
	 compat/string/string.o


SUS = sus/strings/strings.o

all:
	@$(MAKE) -C ansi
	@$(MAKE) -C compat
	@$(MAKE) -C sus
	$(LD) -shared -o libc-$(VERSION).so $(ANSI) $(COMPAT) $(SUS)

test:


install:
	ln -sf libc-$(VERSION).so libc.so
	cp libc.so libc-$(VERSION).so $(INSTALL_DIR)/lib
	if [ ! -d $(INSTALL_DIR)/usr/man/libc/ ]; then \
		mkdir $(INSTALL_DIR)/usr/man/libc/ ; \
	fi
	cp man/*.html $(INSTALL_DIR)/usr/man/libc/

distclean: clean
clean:
	rm -f `find -name *.o` libc.so libc-$(VERSION).so

include Makefile.def
