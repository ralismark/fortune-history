SUBDIRS=strfile unstr fortune datfiles
flags="O=-O2 -fomit-frame-pointer -pipe" LDFLAGS=-s

all:
	for i in ${SUBDIRS}; do make -C $$i ${flags}; done

install:
	for i in ${SUBDIRS}; do make install -C $$i ${flags}; done

clean:
	for i in ${SUBDIRS}; do make clean -C $$i ${flags}; done

