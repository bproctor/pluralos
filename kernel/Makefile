
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
#  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
#

#
# $Id: Makefile,v 1.24 2003/01/19 19:26:14 fredlie Exp $
#

VERSION = 0.0.21
export VERSION

INSTALL_DIR = ~/test/

.PHONY: all plural build version dep dummy config clean distclean install

ifeq ($(wildcard .config), .config)
include .config
endif

OBJS = 	boot/init.o \
	kernel/kernel.o \
	lib/lib.a \
	fs/fs.o \
	drivers/drivers.o

all: build version plural

plural: dummy
	@$(MAKE) -C drivers
	@$(MAKE) -C kernel
	@$(MAKE) -C fs
	@$(MAKE) -C lib
	@$(MAKE) -C boot
	$(LD) -X -Tboot/plural.ld -o plural $(OBJS)
	$(OBJCOPY) -R .comment -R .note plural
	$(SIZE) --format=sysv plural > plural.sym
	$(NM) -n plural | grep -v '\(compiled\)' >> plural.sym
	$(OBJCOPY) -S -O binary plural
	@echo ""
	@echo -n "Microkernel Code Size: "
	@echo "`$(SIZE) kernel/kernel.o | tail -1 | cut -c-7` bytes"


#
# You may have to change this to meet your needs.
# Here, it compressed the kernel and puts it into
# /plural, which I have setup as a loopback device
# to be used with Bochs.
#
# It can also be copied into the /boot directory
# add it to your grub.conf file to boot the kernel.
#
install:
	gzip -c9 plural > plural-$(VERSION).gz
	mv plural.sym plural-$(VERSION).sym
	ln -sf plural-$(VERSION).gz plural.gz
	ln -sf plural-$(VERSION).sym plural.sym
	cp -P plural.sym plural.gz plural-$(VERSION).sym plural-$(VERSION).gz $(INSTALL_DIR)/boot/
	if [ ! -d $(INSTALL_DIR)/usr/man/kernel/ ]; then \
		mkdir $(INSTALL_DIR)/usr/man/kernel/ ; \
	fi
	cp man/*.html $(INSTALL_DIR)/usr/man/kernel/

dep: include/version.h
	@$(MAKE) -C tools dep
	@$(MAKE) -C tools mkdep
	@$(MAKE) -C boot mkdep
	@$(MAKE) -C drivers mkdep
	@$(MAKE) -C kernel mkdep
	@$(MAKE) -C lib mkdep

config:
	@$(MAKE) -C tools config
	sh tools/Menuconfig
	

clean:
	rm -f `find -name *.[oas] -o -name .depend`
	rm -f include/version.h plural plural.gz plural.sym

distclean: clean
	rm -f core plural.gz plural plural.sym boot/start drivers/pci/pci-class.h
	rm -f .menuconfig.log MCerror .config tools/dep drivers/pci/build
	rm -f .config.old plural.out.gz bochsout.txt drivers/pci/pci-dev.h
	rm -f .tmpconfig.h tools/lxdialog/lxdialog include/config.h
	rm -f plural-$(VERSION).sym plural-$(VERSION).gz
	rm -f `find . \( -not -type d \) -and \
		\( -name '*.orig' -o -name '*.rej' -o -name '*~' \
		-o -name '*.bak' -o -name '#*#' -o -name '.*.orig' \
		-o -name '.*.rej' -o -name '.SUMS' -o -size 0 \) -type f -print`

version: build include/version.h
include/version.h:
	echo "#ifndef __VERSION_H__" > include/version.h
	echo "#define __VERSION_H__" >> include/version.h
	echo "#define VERSION_STRING \"$(VERSION)\"" >> include/version.h
	echo "#define BUILD_DATE \"`date +%D`\"" >> include/version.h
	echo "#define BUILD_TIME \"`date +%T`\"" >> include/version.h
	echo "#define BUILD_BY \"`whoami`\"" >> include/version.h
	echo "#define BUILD_HOST \"`hostname`\"" >> include/version.h
	echo "#define BUILD_NUM \"`cat tools/.build`\"" >> include/version.h
	echo "#endif" >> include/version.h

build: dummy
	if [ -f tools/.build ]; then \
		expr `cat tools/.build` + 1 > tools/.build; \
	else \
		expr 1 > tools/.build; \
	fi
	rm -f include/version.h

dummy:

include Makefile.def
include Makefile.inc

