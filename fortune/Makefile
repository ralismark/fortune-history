# Note: this makefile should be called by the makefile in the parent
# directory, which will pass it a number of variables.  Better to call
# make fortune-bin or make fortune-debug from there.  make install
# *only* works at the top level--do make install-fortune and make
# install-fman.  Make clean is an acceptable target called directly
# in this directory, though.

all: pathnames.h fortune

debug: pathnames.h
	gcc $(DEBUGCFLAGS) -c fortune.c -o fortune.o
	gcc $(DEBUGLDFLAGS) fortune.o -o fortune

fortune: fortune.o

pathnames.h:
	@echo "Creating pathnames.h"
	@echo '#define FORTDIR	"$(COOKIEDIR)"' >pathnames.h
	@echo '#define OFFDIR	"$(OCOOKIEDIR)"' >>pathnames.h


fortune: fortune.o

clean:
	-rm -f fortune.o fortune fortune.man pathnames.h


