mstflint: flint.cpp mtcr.h
	$(CXX) -g -I. -fno-exceptions -Wall -O2 flint.cpp -o mstflint
clean:
	rm -f mstflint
