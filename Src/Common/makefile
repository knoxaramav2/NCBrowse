#Compiles Commons library

OUT = libcommon.so
SRC=common.cpp util.cpp

all:
	$(CC) $(COMMON) $(SRC) -shared -o $(BINPATH)/$(OUT) $(OSMODE) $(PLATFORM)

.PHONY: clean
clean:
	rm -f $@ *.o

.PHONY: dbg
dbg: $(OUT)
	$(RUNPATH) $(DBGFLAGS)
