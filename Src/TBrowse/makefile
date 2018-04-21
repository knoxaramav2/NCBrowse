#compiles TBrowser component

CFLAGS = $(COMMON) 
LFLAGS = -lm -ldl -lpthread -L$(BINPATH) \
-I../HTMD/headers/ -l:libhtmd.so  \
-I../FBrowse/headers/ -l:libfbrowse.so \
$(COMLIB) \
-Wl,-rpath=$(BINPATH)

OUT = $(OUTALIAS)
O_SRC = $(SRC:.cpp=.o)
SRC=main.cpp graphics.cpp

all:
	$(CC) $(SRC) $(CFLAGS) -o $(RUNPATH) $(LFLAGS) -lncurses

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	exec gdb -x $(RUNPATH) $(DBGFLAGS)
