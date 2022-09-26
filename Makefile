DEBUGDIR = Debug/
RELEASEDIR = Release/


ifeq ($(MODE), DEBUG)
	DEBUGFLAGS = -Wall -Wextra -g -fsanitize=address
	EXECDIR = $(RELEASEDIR)
else
	RELEASEFLAGS = -D NDEBUG
	EXECDIR = $(DEBUGDIR)
endif

ifndef PACKAGEMANAGER
	PACKAGEMANAGER = apt
endif


SRCDEPENDENCIES =
PKGDEPENDENCIES = build-essential valgrind

CC = g++ -std=c++20
CFLAGS = -c $(DEBUGFLAGS) $(RELEASEFLAGS)
LDFLAGS = $(DEBUGFLAGS)
BUILDDIR = $(EXECDIR)
SRCDIR = source/

EXECNAME = hwc-cache


#----------------------------------BUILDING--------------------------------------------------
all: mkdir main
	$(CC) $(LDFLAGS) $(BUILDDIR)main.o $(BUILDDIR)libcache.o -o $(EXECDIR)$(EXECNAME)
	
mkdir:
	mkdir -p $(BUILDDIR) $(EXECDIR)
	
main: libcache
	$(CC) $(CFLAGS) $(SRCDIR)main.cc -o $(BUILDDIR)main.o


#----------------------------------libcache--------------------------------------------------
libht_fdict:
	$(CC) $(CFLAGS) $(SRCDIR)cache.cc -o $(BUILDDIR)libcache.o


#----------------------------------INSTALLING DEPENDENCIES-----------------------------------
install-dependencies-src:
	cd .. && git clone $(SRCDEPENDENCIES)

install-dependencies-pkg:
	sudo $(PACKAGEMANAGER) install $(PKGDEPENDENCIES)

install-dependencies-all: install-dependencies-src install-dependencies-pkg


#----------------------------------RUNNING---------------------------------------------------
run:
	./$(EXECDIR)$(EXECNAME)

rund:
	valgrind --leak-check=full ./$(EXECDIR)$(EXECNAME)


#-----------------------------------CLEANING-------------------------------------------------
clean:
	rm -rf $(RELEASEDIR) $(DEBUGDIR) $(BUILDDIR)
