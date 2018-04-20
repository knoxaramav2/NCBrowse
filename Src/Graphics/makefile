#Compiles Graphics Modules

LFLAGS = $(COMLIB)
OUT = libgraphic.so
SRC = graphics.cpp

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
