#Compiles HTML Decomposer

LFLAGS = $(COMLIB)
OUT = libhtmd.so
SRC = htmd.cpp

all:
	$(CC) $(COMMON) $(LFLAGS) $(SRC) -shared -o $(BINPATH)/$(OUT)

$(BINPATH)$(OUT) : $(O_SRC)
	$(CC) $(COMMON) $(PLATFORM) $(DBGFLAGS) -shared -o $@ $(O_SRC) $(LFLAGS)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
