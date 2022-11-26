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

LFUEXECNAME = lfu-cache
PRSCEXECNAME = prsc-cache

TESTSCRIPT= test/test_e2e
LFUTESTDATADIR= test/lfu_testdata/
PRSCTESTDATADIR= test/prescient_testdata/


#----------------------------------BUILDING------------------------------------------------------
all: lfu-cache prescient-cache
	
mkdir:
	mkdir -p $(BUILDDIR) $(EXECDIR)

#----------------------------------lfu_cache-----------------------------------------------------
lfu-cache: mkdir
	$(CC) $(LDLAGS) $(SRCDIR)lfu_cache.cc -o $(EXECDIR)$(LFUEXECNAME)

#----------------------------------prescient_cache-----------------------------------------------
prescient-cache: mkdir
	$(CC) $(LDLAGS) $(SRCDIR)prescient_cache.cc -o $(EXECDIR)$(PRSCEXECNAME)


#----------------------------------INSTALLING DEPENDENCIES---------------------------------------
install-dependencies-src:
	cd .. && git clone $(SRCDEPENDENCIES)

install-dependencies-pkg:
	sudo $(PACKAGEMANAGER) install $(PKGDEPENDENCIES)

install-dependencies-all: install-dependencies-src install-dependencies-pkg


#----------------------------------RUNNING-------------------------------------------------------
run-lfu:
	./$(EXECDIR)$(LFUEXECNAME)

rund-lfu:
	valgrind --leak-check=full ./$(EXECDIR)$(LFUEXECNAME)

run-prescient:
	./$(EXECDIR)$(PRSCEXECNAME)

rund-prescient:
	valgrind --leak-check=full ./$(EXECDIR)$(PRSCEXECNAME)


#----------------------------------TESTING-------------------------------------------------------
test-lfu:
	./$(TESTSCRIPT) $(EXECDIR)$(LFUEXECNAME) $(LFUTESTDATADIR)

test-prescient:
	./$(TESTSCRIPT) $(EXECDIR)$(PRSCEXECNAME) $(PRSCTESTDATADIR)


#-----------------------------------CLEANING-----------------------------------------------------
clean:
	rm -rf $(RELEASEDIR) $(DEBUGDIR) $(BUILDDIR)
