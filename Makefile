#default options
OPTIMIZE=1
DEBUG=1

ifeq (${STATIC},1)
MSTCFLAGS += -static
endif

ifeq (${OPTIMIZE},1)
MSTCFLAGS += -O2
endif

ifeq (${DEBUG},1)
MSTCFLAGS += -g
endif

ifeq (${BITS64},1)
MSTCFLAGS += -m64
endif

mstflint: flint.cpp mtcr.h
	$(CXX) ${MSTCFLAGS} -I. -fno-exceptions -Wall flint.cpp -o mstflint
ifeq (${STRIP},1)
	strip mstflint
endif

clean:
	rm -f mstflint
