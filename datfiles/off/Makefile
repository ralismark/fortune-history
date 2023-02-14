all:
	$(MAKE) -C unrotated rotated
	-rm -f *.dat
	for i in * ; do if [ "$$i" != "Makefile" \
	-a -f $$i ] ; then ../../util/strfile -x $$i ; fi ; done

install:
	-mkdir -p $(OCOOKIEDIR)
	for i in * ; do if [ "$$i" != "Makefile" -a -f $$i ] ; \
	then install -m 0644 $$i $(OCOOKIEDIR) ; fi ; done

clean:
	for i in * ; do if [ "$$i" != "Makefile" -a -f $$i ] ;\
	then rm -f $$i ; fi; done
