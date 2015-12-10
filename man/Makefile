
VERSION = 0.0.1

ROOT_DIR = ~/test
INSTALL_DIR = /usr

CC = gcc
YACC = bison

CFLAGS = -Wall -fomit-frame-pointer -O2 -DVERSION=\"$(VERSION)\"
LDFLAGS = -s

all: man-display man-script

man-display: src/man.o src/lex.o src/parse.o
	$(CC) $(LDFLAGS) -o $@ $^

src/man.o: src/man.c
src/parse.o: src/parse.c src/parse.h
src/parse.c src/parse.h: src/parse.y
src/lex.o: src/lex.c src/parse.h

%.o : %.c
	$(CC) -c $(CFLAGS) -o $@ $<

%.c %.h : %.y
	$(YACC) -tdv -o $(addsuffix .c, $(basename $<)) $<


install:
	chmod 0755 man-script man-display
	if [ ! $(INSTALL_DIR) = "/usr" ]; then \
		cp man-script $(ROOT_DIR)/$(INSTALL_DIR)/bin/man ; \
		cp man-display $(ROOT_DIR)/bin/
	else
		cp man-script $(ROOT_DIR)/bin/man
		cp man-display $(ROOT_DIR)/bin/
	fi
	if [ ! -d $(ROOT_DIR)/$(INSTALL_DIR)/man/ ]; then \
		mkdir $(ROOT_DIR)/$(INSTALL_DIR)/man/ ; \
	fi
	cp man/*.html $(ROOT_DIR)/$(INSTALL_DIR)/man/

man-script:
	echo "#!/bin/sh"				 > $@
	echo ""						>> $@
	echo "if [ \$$# = \"0\" ]; then" 		>> $@
	echo "	echo \"no manual page specified\"" 	>> $@
	echo "	exit 1" 				>> $@
	echo "fi" 					>> $@
	echo "" 					>> $@
	echo "PAGE=\`find /usr/man -name \$$1.html\`" 	>> $@
	echo "" 					>> $@
	echo "if [ -f \"\$$PAGE\" ]; then" 		>> $@
	echo "	./man-display \$$PAGE" 			>> $@
	echo "else" 					>> $@
	echo "	echo \"no manual page for '\$$1'\"" 	>> $@
	echo "fi" 					>> $@
	echo "" 					>> $@
	echo "exit 0" 					>> $@
	chmod 0755 $@	


distclean: clean
	rm -f man-display man-script

clean:
	rm -f src/*.o src/parse.c src/parse.h src/parse.output
