
VERSION = 0.0.1

ROOT_DIR = ~/test
INSTALL_DIR = /usr

ARCH = `uname -m`
CC = gcc
CFLAGS = -Wall -O2 -fomit-frame-pointer -march=$(ARCH)
LDFLAGS = -s
OBJCOPY = objcopy

export CC CFLAGS LDFLAGS OBJCOPY

PROGS = ar ld lex make nm strip yacc

.PHONY: install distclean clean all

all: lib $(PROGS)

% : src/%
	$(MAKE) -C $<

lib:
	$(MAKE) -C lib

install:
	chmod 0755 $(PROGS)
	cp $(PROGS) $(ROOT_DIR)/$(INSTALL_DIR)/bin
	for i in $(PROGS); do \
		if [ ! -d $(ROOT_DIR)/$(INSTALL_DIR)/man/$$i ]; then \
			mkdir $(ROOT_DIR)/$(INSTALL_DIR)/man/$$i ; \
		fi \
	done
	cp man/*.html $(ROOT_DIR)/$(INSTALL_DIR)/man/$$i/

distclean: clean
	rm -f $(PROGS)

clean:
	rm -f `find -name *.o`

