DEBUGDIR = Debug/
RELEASEDIR = Release/


ifeq ($(MODE), DEBUG)
	DEBUGFLAGS = -Wall -Wextra -g -fsanitize=address
	EXECDIR = $(DEBUGDIR)
else
	RELEASEFLAGS = -D NDEBUG
	EXECDIR = $(RELEASEDIR)
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

TESTSCRIPT= test/test_e2e
TESTDATADIR= test/test_data/


#----------------------------------BUILDING--------------------------------------------------
all: mkdir main
	$(CC) $(LDFLAGS) $(BUILDDIR)main.o $(BUILDDIR)libcache.o -o $(EXECDIR)$(EXECNAME)
	
mkdir:
	mkdir -p $(BUILDDIR) $(EXECDIR)
	
main: libcache
	$(CC) $(CFLAGS) $(SRCDIR)main.cc -o $(BUILDDIR)main.o


#----------------------------------libcache--------------------------------------------------
libcache:
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

#----------------------------------TESTING---------------------------------------------------
test_e2e:
	./$(TESTSCRIPT) $(EXECDIR)$(EXECNAME) $(TESTDATADIR)

#-----------------------------------CLEANING-------------------------------------------------
clean:
	rm -rf $(RELEASEDIR) $(DEBUGDIR) $(BUILDDIR)
