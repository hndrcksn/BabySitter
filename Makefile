.PHONY : all check

CC           = gcc
MKDIR_P      = mkdir -p
FLAGS        = -std=gnu99
LIBCFLAGS    = -c -Wall -Werror -fPIC  $(FLAGS)
LIBLDFLAGS   = -shared
CFLAGS       = -Wall -Werror $(FLAGS)
LIBCHECKLDFLAGS = -pthread -lrt -lm

LIBSRCDIR  = ./src/lib
TESTSRCDIR = ./src/tests
LIBCHECKDIR = /usr/lib/x86_64-linux-gnu/

OBJDIR = ./obj
BINDIR = ./bin
LDLIBPATHBIN  = LD_LIBRARY_PATH=bin

LIB        = BabySitterCalc
TESTTARGET = TestBabySitter
LIBSRC     = $(LIB).c
TESTSRC    = $(TESTTARGET).c
LIBOBJ     = $(LIB).o
TESTOBJ    = $(TESTTARGET).o
LIBTARGET  = lib$(LIB).so
LIBCHECK   = check

all : directories $(BINDIR) $(LIBTARGET) $(TESTTARGET)
	echo "Building all..."

directories : $(OBJDIR) $(BINDIR)

check: $(TESTTARGET)
	$(LDLIBPATHBIN) $(BINDIR)/$(TESTTARGET)

$(OBJDIR):
	$(MKDIR_P) $(OBJDIR)

$(BINDIR):
	$(MKDIR_P) $(BINDIR)

$(LIBSRC):
ifeq (,$(wildcard $(LIBSRCDIR)/$(LIBSRC)))
	$(error $(LIBSRCDIR)/$(LIBSRC) not found!)
endif

$(LIBOBJ) : directories $(LIBSRCDIR) $(LIBSRC)
	$(CC) $(LIBCFLAGS) $(LIBSRCDIR)/$(LIBSRC) -o $(OBJDIR)/$(LIBOBJ)

$(LIBTARGET) : directories $(OBJDIR) $(LIBOBJ)
	$(CC) $(LIBLDFLAGS) -o $(BINDIR)/$(LIBTARGET) $(OBJDIR)/$(LIBOBJ)

$(TESTSRC):
ifeq (,$(wildcard $(TESTSRCDIR)/$(TESTSRC)))
	$(error $(TESTSRCDIR)/$(TESTSRC) not found!)
endif

$(TESTTARGET) : directories $(TESTSRCDIR) $(TESTSRC) $(BINDIR) $(LIBTARGET)
	$(CC) -L$(BINDIR) -L$(LIBCHECKDIR) $(CFLAGS) $(TESTSRCDIR)/$(TESTSRC) -o $(BINDIR)/$(TESTTARGET) -l$(LIB) -l$(LIBCHECK) $(LIBCHECKLDFLAGS)

