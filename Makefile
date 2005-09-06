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
bin: mstflint mread mwrite

default: bin
static: bin
shared: bin

.PHONY: all bin clean static shared default
.DELETE_ON_ERROR:

default: EXTRA_LOADLIBES="$(shell $(CXX) -print-file-name=libz.a)" "$(shell $(CXX) -print-file-name=libstdc++.a)" 
default: LD=$(CC)
static: CFLAGS+=-static

mstflint: mstflint.o
	$(LD) ${LDFLAGS} ${CFLAGS} ${CXXFLAGS} mstflint.o -o mstflint ${LOADLIBES}

mstflint.o: flint.cpp mtcr.h
	$(CXX) ${CFLAGS} -c  flint.cpp -o mstflint.o

mwrite: mwrite.c mtcr.h
	$(CC) ${CFLAGS} mwrite.c -o mwrite

mread: mread.c mtcr.h
	$(CC) ${CFLAGS} mread.c -o mread

clean:
	rm -f mstflint mread mwrite
