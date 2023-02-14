CFLAGS= -O2 -Wall -fomit-frame-pointer -pipe
LDFLAGS= -s

# The above flags are used by default; the debug flags are used when make
# is called with 'make debug'

# to get a list of the possible targets, try 'make help'

# All targets are available at the top level, which exports the
# variables to sub-makes.  Avoid makes in subdirectories; cd .. and
# make <target> instead.

DEBUGCFLAGS=-g -DDEBUG -Wall -fomit-frame-pointer -pipe
DEBUGLDFLAGS=-g

CC=gcc

# Where does the fortune program go?
FORTDIR=$(prefix)/usr/games
# Where do the data files (fortunes, or cookies) go?
COOKIEDIR=$(prefix)/usr/share/games/fortunes
# Offensive ones?
OCOOKIEDIR=$(COOKIEDIR)/off
# The ones with html tags?
WCOOKIEDIR=$(COOKIEDIR)/html
# Where do strfile and unstr go?
BINDIR=$(prefix)/usr/sbin
# What is the proper mode for strfile and unstr? 755= everyone, 700= root only
BINMODE=0755
#BINMODE=0700
# Where do the man pages for strfile and unstr go?
BINMANDIR=$(prefix)/usr/man/man8
# What is their proper extension?
BINMANEXT=8
# And the same for the fortune man page
FORTMANDIR=$(prefix)/usr/man/man6
FORTMANEXT=6
# Do we want to install the offensive files? (0 no, 1 yes)
OFFENSIVE=1
# Do we want to install files with html tags? (0 no, 1 yes)
WEB=0

SUBDIRS=fortune util datfiles

.EXPORT_ALL_VARIABLES:

# By default, compile optimized versions
all: fortune-bin util-bin cookies-z

# Create debugging versions
debug: fortune-debug util-debug

# Just create the fortune binary
fortune-bin:
	$(MAKE) -C fortune

fortune-debug:
	$(MAKE) -C fortune debug

util-bin:
	$(MAKE) -C util

# Not listed in help
randstr:
	$(MAKE) -C util randstr

# Not listed in help -- made when cookies are made, if offensive.
rot:
	$(MAKE) -C util rot

util-debug:
	$(MAKE) -C util debug

cookies:
	@echo "Try the kitchen, silly!" ; sleep 3
	@echo "Sorry, just joking."
	$(MAKE) -C datfiles

cookies-z:
	$(MAKE) -C datfiles

# Install everything
install: install-fortune install-util install-man install-cookie

# Install just the fortune program
install-fortune:
	install -d -g root -m 755 -o root $(FORTDIR)
	install -s -m 0755 fortune/fortune $(FORTDIR)

# Install just the utilities strfile and unstr
install-util:
	install -d -g root -m 755 -o root $(BINDIR)
	install -s -m $(BINMODE) util/strfile $(BINDIR)
	install -s -m $(BINMODE) util/unstr $(BINDIR)

# Install all the man pages
install-man: install-fman install-uman

# Install the fortune man pages
# Note: this also concatenates the parts of the man page with the locally
#       defined pathnames (which should reduce confusion).
install-fman:
	@cat fortune/fortune-man.part1 >fortune/fortune.man
	@echo "$(COOKIEDIR) \- Directory for inoffensive fortunes" >>fortune/fortune.man
	@echo ".br" >>fortune/fortune.man
	@echo "$(OCOOKIEDIR) \- Directory for offensive fortunes" >>fortune/fortune.man
	@cat fortune/fortune-man.part2 >>fortune/fortune.man
	install -d -g root -m 755 -o root $(FORTMANDIR)
	install -m 0644 -o man fortune/fortune.man $(FORTMANDIR)/fortune.$(FORTMANEXT)

# Install the utilities man pages
install-uman:
	install -d -g root -m 755 -o root $(BINMANDIR)
	install -m 0644 -o man util/strfile.man $(BINMANDIR)/strfile.$(BINMANEXT)
	(cd $(BINMANDIR) && ln -sf strfile.$(BINMANEXT).gz unstr.$(BINMANEXT).gz)

# Install the fortune cookie files
install-cookie:
	$(MAKE) -C datfiles install

.PHONY: clean
clean:
	for i in $(SUBDIRS) ; do $(MAKE) -C $$i clean ; done

.PHONY: love
love:
	@echo "Not war?" ; sleep 3
	@echo "Look, I'm not equipped for that, okay?" ; sleep 2
	@echo "Contact your hardware vendor for appropriate mods."

.PHONY: help
help:
	@echo "Targets:"
	@echo
	@echo "all:	make all the binaries and data files (the default target)"
	@echo " fortune-bin:	make the fortune binary"
	@echo " util-bin:	make the strfile and unstr binaries"
	@echo " cookies:	make the fortune-cookie data files"
	@echo
	@echo "debug:	make debugging versions of the binaries"
	@echo " fortune-debug:	Just the fortune program"
	@echo " util-debug:	Just strfile and unstr"
	@echo
	@echo "install:	install the files in locations specified in Makefile"
	@echo " install-fortune:	Just the fortune program"
	@echo " install-util:		Just strfile and unstr"
	@echo " install-cookie:	Just the fortune string and data files"
	@echo " install-man:		Just the man pages"
	@echo "  install-fman:		Just the fortune man page"
	@echo "  install-uman:		Just the strfile/unstr man page"
	@echo
	@echo "clean:	Remove object files and binaries"
	@echo 
	@echo "help:	This screen"
	@echo
	@echo "love:	What a *good* idea!  Let's!"
