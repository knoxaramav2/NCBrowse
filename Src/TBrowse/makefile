#compiles TBrowser component

CFLAGS = $(COMMON) 
LFLAGS = -lm -ldl -lpthread -L$(BINPATH) \
-I../HTMD/headers/ -l:libhtmd.so  \
-I../Graphics/headers/ -l:libgraphic.so \
$(COMLIB) \
-Wl,-rpath=$(BINPATH)

OUT = $(OUTALIAS)
O_SRC = $(SRC:.cpp=.o)
SRC=main.cpp

#all: $(RUNPATH)
#	echo $(OUT) Done

#.cpp.o:
#	$(CC) $(CFLAGS) -c -o $@ $< $(LFLAGS) -lncurses

#$(RUNPATH) : $(O_SRC)
#	$(CC) -o $@ $(O_SRC) $(CFLAGS) $(LFLAGS) -lncurses

all:
	$(CC) $(SRC) $(CFLAGS) -o $(RUNPATH) $(LFLAGS) -lncurses

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	exec gdb -x $(RUNPATH) $(DBGFLAGS)
