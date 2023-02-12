CFLAGS=$(O) -I../strfile

fortune: fortune.o

install:
	install fortune /usr/bin/
	install -m 644 fortune.6 /usr/man/man6/

clean:
	rm -f fortune.o fortune

