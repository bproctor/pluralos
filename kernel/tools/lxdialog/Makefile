
#
# $Id: Makefile,v 1.3 2001/10/29 02:42:17 fredlie Exp $
#

HOST_CFLAGS += -DLOCALE 
LIBS = -lncurses

ifeq (/usr/include/ncurses/ncurses.h, $(wildcard /usr/include/ncurses/ncurses.h))
        HOST_CFLAGS += -I/usr/include/ncurses -DCURSES_LOC="<ncurses.h>"
else
ifeq (/usr/include/ncurses/curses.h, $(wildcard /usr/include/ncurses/curses.h))
        HOST_CFLAGS += -I/usr/include/ncurses -DCURSES_LOC="<ncurses/curses.h>"
else
ifeq (/usr/include/ncurses.h, $(wildcard /usr/include/ncurses.h))
        HOST_CFLAGS += -DCURSES_LOC="<ncurses.h>"
else
	HOST_CFLAGS += -DCURSES_LOC="<curses.h>"
endif
endif
endif

all: ncurses lxdialog

lxdialog: lxdialog.c
	gcc -s -Wall -O2 -fomit-frame-pointer $(HOST_CFLAGS) -o $@ $< $(LIBS)

ncurses:
	@echo "main() {}" > lxtemp.c
	@if gcc -lncurses lxtemp.c ; then \
		rm -f lxtemp.c a.out; \
	else \
		rm -f lxtemp.c; \
		echo -e "\007" ;\
		echo ">> Unable to find the Ncurses libraries." ;\
		echo ">>" ;\
		echo ">> You must have Ncurses installed in order" ;\
		echo ">> to use 'make config'" ;\
		echo ;\
		exit 1 ;\
	fi

clean:
	rm -f core *.o *~ lxdialog
