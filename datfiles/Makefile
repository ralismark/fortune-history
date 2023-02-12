SRCS=	fortunes fortunes2 startrek zippy
BLDS=	fortunes.dat fortunes2.dat startrek.dat zippy.dat \
	fortunes-o fortunes-o.dat

# TO INSTALL THE POTENTIALLY OFFENSIVE FORTUNES, UNCOMMENT THE THREE
# LINES AND COMMENT OUT THE FOURTH LINE.

# THE THREE LINES
SRCS+=	fortunes2-o limerick
BLDS+=	fortunes2-o.dat limerick.dat
TYPE=	real

# THE FOURTH LINE
#TYPE=	fake

all: ${BLDS}

install: ${SRCS} ${BLDS}
	install -m 444 ${SRCS} /usr/share/fortune/
	install -m 444 ${BLDS} /usr/share/fortune/

fortunes-o.dat: fortunes-o
	../strfile/strfile -rsx fortunes-o fortunes-o.dat

%.dat: %
	../strfile/strfile -rs $< $@

#fortunes-o: fortunes-o.${TYPE}
#	/usr/games/caesar 13 < ${.ALLSRC} > ${.TARGET}

fortunes-o: fortunes-o.${TYPE}.rot13
	cat fortunes-o.${TYPE}.rot13 > fortunes-o

clean:
	rm -f ${BLDS}

