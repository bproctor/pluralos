
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
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#

#
# $Id: Makefile,v 1.15 2003/01/15 21:31:31 fredlie Exp $
#

VERSION = 0.0.5

ROOT_DIR = ~/test
INSTALL_DIR = /usr

CC = gcc
YACC = bison
LEX = flex
CFLAGS = -Wall -O2 -fomit-frame-pointer -DVERSION=\"$(VERSION)\"
LDFLAGS = -s

cc: src/lex.o src/parse.o src/cc.o src/asm.o
	$(CC) $(LDFLAGS) -o $@ $^
	objcopy -R .note -R .comment -S $@

src/cc.o: src/cc.c src/cc.h
src/lex.o: src/lex.c src/cc.h src/parse.h
src/parse.o: src/parse.c src/parse.h
src/parse.c src/parse.h: src/parse.y
src/asm.o: src/asm.c src/cc.h

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

%.c %.h : %.y
	$(YACC) -tdv -o $(addsuffix .c, $(basename $@)) $<

%.c : %.l
	$(LEX) $<
	mv lex.yy.c lex.c

install:
	chmod 0755 cc
	ln -sf cc c89
	ln -sf cc c99
	cp -P cc c89 c99 $(ROOT_DIR)/$(INSTALL_DIR)/bin/
	if [ ! -d $(ROOT_DIR)/$(INSTALL_DIR)/man/cc ]; then \
		mkdir $(ROOT_DIR)/$(INSTALL_DIR)/man/cc/ ; \
	fi
	cp man/*.html $(ROOT_DIR)/$(INSTALL_DIR)/man/cc/

distclean: clean
clean:
	rm -f src/*.o cc src/parse.c src/parse.h src/parse.output 
	rm -f core test.asm c89 c99
