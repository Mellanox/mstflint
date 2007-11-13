#default options
CFLAGS += -O2
CFLAGS += -g
CFLAGS += -Wall
CXXFLAGS += -fno-exceptions
CFLAGS += -I.
LD=$(CXX)
EXTRA_LOADLIBES=-lz
LOADLIBES+=${EXTRA_LOADLIBES}

all: default
bin: mstflint mstmread mstmwrite mstmcra mstregdump mstvpd

default: bin
static: bin
shared: bin

.PHONY: all bin clean static shared default
.DELETE_ON_ERROR:

default: EXTRA_LOADLIBES="$(shell $(CXX) ${LDFLAGS} ${CFLAGS} ${CXXFLAGS} -print-file-name=libz.a)" "$(shell $(CXX)  ${LDFLAGS} ${CFLAGS} ${CXXFLAGS} -print-file-name=libstdc++.a)"
default: LD=$(CC)
static: CFLAGS+=-static

mstflint: mstflint.o mflash.o
	$(LD) ${LDFLAGS} ${CFLAGS} ${CXXFLAGS} mstflint.o mflash.o -o mstflint ${LOADLIBES}

mstflint.o: flint.cpp mflash.h
	$(CXX) ${CFLAGS} ${CXXFLAGS} -c flint.cpp -o mstflint.o

mflash.o: mtcr.h mflash.c mflash.h
	$(CC) ${CFLAGS} -c mflash.c -o mflash.o

mstmwrite: mwrite.c mtcr.h
	$(CC) ${CFLAGS} mwrite.c -o mstmwrite

mstmread: mread.c mtcr.h
	$(CC) ${CFLAGS} mread.c -o mstmread

mstmcra: mcra.c mtcr.h
	$(CC) ${CFLAGS} mcra.c -o mstmcra
	
mstregdump: mstdump.c mtcr.h
	$(CC) ${CFLAGS} mstdump.c -o mstregdump

mstvpd: vpd.c
	$(CC) ${CFLAGS} vpd.c -o mstvpd

clean:
	rm -f mstvpd mstregdump mstflint mstmread mstmwrite mstmcra mstflint.o mflash.o
