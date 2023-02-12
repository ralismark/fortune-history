all:
	if [ $(OFFENSIVE) = 1 ] ; then $(MAKE) -C off ; fi
	if [ $(WEB) = 1 ] ; then $(MAKE) -C html ; fi
	-rm -f *.dat
	for i in * ; do if [ "$$i" != "Makefile" \
	-a -f $$i ] ; then ../util/strfile $$i ; fi ; done

install:
	-mkdir $(COOKIEDIR)
	if [ $(OFFENSIVE) = 1 ] ; then $(MAKE) -C off install ; fi
	if [ $(WEB) = 1 ] ; then $(MAKE) -C html install ; fi
	for i in * ; do if [ "$$i" != "Makefile" -a -f $$i ] ; \
	then install -m 0644 $$i $(COOKIEDIR) ; fi ; done
# Is this hack necessary?
#	@echo "#!/bin/sh" >make-fortune-db
#	@echo -n "# A fortune-file data file creation script" >>make-fortune-db
#	@echo " -- Amy A. Lewis, September, 1995" >>make-fortune-db
#	@echo "#Syntax: make-fortune-db [c] filename " >>make-fortune-db
#	@echo "if [ \"\$$2\" != \"\" ] ; then $(BINDIR)/strfile -x \$$2" >>make-fortune-db
#	@echo "elif [ \"\$$1\" != \"\" ] ; then $(BINDIR)/strfile \$$1" >>make-fortune-db
#	@echo "else exit 1 ; fi" >>make-fortune-db
#	@echo "# This is a quick hack, so feel free to improve on it.">>make-fortune-db
#	install -m $(BINMODE) make-fortune-db $(COOKIEDIR)

clean:
	-rm -f *.dat make-fortune-db
	$(MAKE) -C off clean
	$(MAKE) -C html clean
