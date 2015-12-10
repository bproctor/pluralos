
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
# $Id: Makefile,v 1.47 2003/02/16 18:46:40 fredlie Exp $
#

VERSION = 0.1.7

ROOT_DIR    = ~/test
INSTALL_DIR = /usr

AR      = ar
BISON   = bison
CC      = gcc
OBJCOPY = objcopy

CFLAGS  = -Wall -O2 -fomit-frame-pointer -DVERSION=\"$(VERSION)\"
CFLAGS += -march=`uname -m` -Ilib/ -D_GNU_SOURCE
LDFLAGS = -s

VPATH = src : src/batch

.PHONY: all install disclean clean test dummy

PROGS = asa        basename   bc         cal        cat        chgrp      \
	chmod      chown      chroot     cksum      cmp        colon      \
	comm       compress   cp         crontab    csplit     cut        \
	date       dd         decrypt    df         diff       dirname    \
	domainname du         echo       ed         encrypt    ex         \
	expand     expr       factor     false      file       find       \
	fmt        fold       fuser      gencat     getconf    grep       \
	head       hostid     hostname   iconv      id         ipcrm      \
	ipcs       join       kill       link       ln         locale     \
	localedef  logger     logname    lp         ls         mailx      \
	md5sum     mesg       mkdir      mkfifo     mknod      more       \
	mount      mv         newgrp     nice       nl         no         \
	od         paste      patch      pathchk    pax        pr         \
	prezip     printf     ps         pwd        pzip       qalter     \
	qdel       qhold      qmove      qmsg       qrerun     qrls       \
	qselect    qsig       qstat      qsub       renice     rm         \
	rmdir      rot13      sed        seq        shred      sleep      \
	sort       split      strings    stty       su         sum        \
	sync       tabs       tac        tail       talk       tar        \
	tee        times      touch      tr         trap       true       \
	tsort      tty        umount     uname      uncompress unexpand   \
	uniq       unlink     uptime     users      uucp       uudecode   \
	uuencode   uustat     uux        vi         wc         who        \
	whoami     write      xargs      yes        zcat

all: lib/lib.a $(PROGS)

% : %.c lib/lib.a
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^
	$(OBJCOPY) -R .note -R .comment -S $@

%.c: %.y
	$(BISON) -o $@ $<

%.o: %.c
	$(CC) -c -fPIC $(CFLAGS) -o $@ $<

LIB_FILES = lib/error.o lib/progname.o lib/terror.o lib/warning.o \
	    lib/getnum_ul.o lib/getnum_ull.o lib/getnum_l.o lib/getnum_ll.o \
	    lib/getnum_f.o lib/getnum_d.o lib/getnum_ld.o lib/getnum_hex.o \
	    lib/getnum_octal.o lib/yesno.o

lib/lib.a: $(LIB_FILES)
	$(AR) rcs $@ $(LIB_FILES)

punzip:
	@echo "#!/bin/sh" > $@
	@echo "$(INSTALL_DIR)/bin/pzip -d \$$@" >> $@
	chmod 0755 $@

test: $(PROGS)
	for p in $(PROGS); do \
		$(MAKE) -s test/$$p ; \
	done

test/%: % dummy
	@if [ ! -d test/$(notdir $@) ]; then \
		echo "No tests for '$(notdir $@)' yet" ; \
	else \
		cd test/$(notdir $@) && \
		echo -n "Testing '$(notdir $@)'..." && \
		sh $(notdir $@).test ; \
	fi

vtest: $(PROGS)
	for p in $(PROGS); do \
		$(MAKE) -s -DVERBOSE=1 vtest/$$p ; \
	done

vtest/%: % dummy
	@if [ ! -d test/$(notdir $@) ]; then \
		echo "No tests for '$(notdir $@)' yet" ; \
	else \
		cd test/$(notdir $@) && \
		echo -n "Testing '$(notdir $@)'..." && \
		sh $(notdir $@).test ; \
	fi

install:
	chmod 0755 $(PROGS)
	if [ ! $INSTALL_DIR = "/usr" ]; then \
		cp $(PROGS) $(ROOT_DIR)/$(INSTALL_DIR)/bin/ ; \
	else \
		cp $(PROGS) $(ROOT_DIR)/bin/ ; \
	fi
	if [ ! -d $(ROOT_DIR)/$(INSTALL_DIR)/man/utils/ ]; then \
		mkdir $(ROOT_DIR)/$(INSTALL_DIR)/man/utils/ ; \
	fi
	cp man/*.html $(ROOT_DIR)/$(INSTALL_DIR)/man/utils/
        

distclean: clean
	rm -f $(PROGS) lib/lib.a

clean:
	rm -f `find . -name *.o`

dummy:

