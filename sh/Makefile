
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
# $Id: Makefile,v 1.11 2003/01/19 19:27:23 fredlie Exp $
#

VERSION = 0.0.5

ROOT_DIR = ~/test
INSTALL_DIR = /usr

CC = gcc
YACC = bison
CFLAGS = -Wall -O2 -fomit-frame-pointer -DVERSION=\"$(VERSION)\" -march=`uname -m`
LDFLAGS = -s

sh: src/sh.o src/parse.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) -c $(CFLAGS) -o $@ $<

src/parse.c src/parse.h: src/parse.y
	$(YACC) -dv src/parse.y -o src/parse.c

install:
	chmod 0755 sh
	if [ ! $(INSTALL_DIR) = "/usr" ]; then \
		cp sh $(ROOT_DIR)/$(INSTALL_DIR)/bin/ ; \
	else \
		cp sh $(ROOT_DIR)/bin/ ; \
	fi
	if [ ! -d $(ROOT_DIR)/$(INSTALL_DIR)/man/sh/ ]; then \
		mkdir $(ROOT_DIR)/$(INSTALL_DIR)/man/sh/ ; \
	fi
	cp man/*.html $(ROOT_DIR)/$(INSTALL_DIR)/man/sh/

distclean: clean
	rm -f sh
clean:
	rm -f src/*.o core src/parse.c src/parse.h src/parse.output
