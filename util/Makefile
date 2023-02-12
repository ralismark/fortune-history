# Note: this makefile should be called by the makefile in the parent
# directory, which will pass it a number of variables defined there.
# To make the files here properly, try make util-bin or make util-debug
# from there.  Install *only* works at the top level; do make install-util
# and make install-uman.  make clean will work properly if called in
# this directory.

all: strfile unstr

# Grr.  There oughta be a way to move DEBUG*FLAGS into *FLAGS and call
# make, but if there is, I don't know it.
debug:
	gcc $(DEBUGCFLAGS) -c strfile.c -o strfile.o
	gcc $(DEBUGCFLAGS) -c unstr.c -o unstr.o
	gcc $(DEBUGLDFLAGS) unstr.o -o unstr
	gcc $(DEBUGLDFLAGS) strfile.o -o strfile

strfile: strfile.o

unstr: unstr.o

randstr: randstr.o

rot: rot.o

ansify: ansify.o

clean:
	-rm -f *.o unstr strfile randstr rot ansify
