#compiles entire TBrowser project

CC = g++
SUBDIRS = Src/Common/ Src/HTMD/ Src/FBrowse/ Src/TBrowse/
BITVRS=64
BINPATH=$(shell pwd)/bin
DEBUG=false
COMMON= -Iheaders/ -std=c++17 -Wall -g -m$(BITVRS) -L$(BINPATH)
OUTALIAS=tbr
CLEANTEXT = o a so
O_SRC = $(SRC:.cpp=.o)
COMLIB = -l:libcommon.so -I../Common/headers/
DBGFLAGS = 

ifeq ($(shell uname), Linux)
	FixPath = $1
	PLATFORM = -D__LINUX
	OSMODE = -DBITMODE=$(BITVRS)
	EXT=
	COMMON += -fPIC
else
#Windows
	FixPath = $(subst /,\,$1)
	PLATFORM = -D__WINDOWS
	OSMODE = -DBITMODE=$(BITVRS)
	EXT=.exe
endif

RUNPATH=$(BINPATH)/$(OUTALIAS)$(EXT)

export CC
export BITVRS
export BINPATH
export DEBUG
export COMMON
export OUTALIAS
export O_SRC
export PLATFORM
export FixPath
export OSMODE
export CFLAGS
export RUNPATH
export COMLIB
export DBGFLAGS

subdirs:
	for dir in $(SUBDIRS); do \
	 $(MAKE) -C $$dir; \
	done

.PHONY: run
run:
	bin/$(OUTALIAS)$(EXT)

.PHONY: dbg
dbg:
	exec gdb bin/$(OUTALIAS)

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
	 $(MAKE) clean -C $$dir; \
	done
	 rm -f $@ bin/$(OUTALIAS)
	 rm -f $@ bin/*.so

build: clean subdirs run