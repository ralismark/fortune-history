rotated:
	$(MAKE) -C ../../../util rot
	for i in * ; do if [ "$$i" != "Makefile" ] ; then cat $$i \
	| ../../../util/rot >"../$$i" ; fi ; done
