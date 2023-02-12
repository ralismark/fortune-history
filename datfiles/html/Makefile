all:
	-rm -f *.dat
	for i in * ; do if [ "$$i" != "Makefile" \
	-a -f $$i ] ; then ../../util/strfile $$i ; fi ; done

install:
	-mkdir $(WCOOKIEDIR)
	for i in * ; do if [ "$$i" != "Makefile" -a -f $$i ] ; \
	then install -m 0644 $$i $(WCOOKIEDIR) ; fi ; done

clean:
	-rm -f *.dat
