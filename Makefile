#default options
CFLAGS += -O2
CFLAGS += -g

mstflint: flint.cpp mtcr.h
	$(CXX) ${CFLAGS} -I. -fno-exceptions -Wall flint.cpp -o mstflint

clean:
	rm -f mstflint
