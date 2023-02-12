
WCOOKIES=

STRFILE=../util/strfile


all: wcookies-stamp

wcookies-stamp:
	rm -f *.dat
	for i in $(WCOOKIES) ; do $(STRFILE) $$i ; done
	touch cookies-stamp

install: wcookies-stamp
	install -m 0755 -d $(WCOOKIEDIR)
	for i in $(WCOOKIES) ; do \
		install -m 0644 $$i $$i.dat $(WCOOKIEDIR) ; done

clean:
	rm -f wcookies-stamp *.dat
