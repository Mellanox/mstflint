#default options
CFLAGS += -O2
CFLAGS += -g

all: mstflint mread mwrite

mstflint: flint.cpp mtcr.h
	$(CXX) ${CFLAGS} -I. -fno-exceptions -Wall flint.cpp -o mstflint

mwrite: mwrite.c mtcr.h
	$(CC) ${CFLAGS} -I. -Wall mwrite.c -o mwrite

mread: mread.c mtcr.h
	$(CC) ${CFLAGS} -I. -Wall mread.c -o mread

clean:
	rm -f mstflint mread mwrite
