#compiles TBrowser component

$(info $$var TB  [${COMMON}])

CFLAGS = $(COMMON) 
LFLAGS = -lm -ldl -lpthread -L$(BINPATH) \
-I../HTMD/headers/ -l:libhtmd.so  \
$(COMLIB) \
-Wl,-rpath=$(BINPATH)

OUT = tbr
O_SRC = $(SRC:.cpp=.o)
SRC=main.cpp

all: $(RUNPATH)
	echo $(OUT) Done

.cpp.o:
	$(CC) $(CFLAGS) -c -o $@ $< $(LFLAGS)

$(RUNPATH) : $(O_SRC)
	$(CC) $(CFLAGS) -o $@ $(O_SRC) $(LFLAGS)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	exec gdb -x $(RUNPATH) $(DBGFLAGS)
