bin_PROGRAMS = mstmread \
					mstmwrite \
					mstflint \
					mstregdump \
					mstvpd

mstmread_SOURCES = mread.c mtcr.h

mstmwrite_SOURCES = mwrite.c mtcr.h

mstflint_SOURCES = flint.cpp mtcr.h mflash.h mflash.c
mstflint_LDFLAGS = -lz

mstregdump_SOURCES = mread.c mtcr.h

mstvpd_SOURCES = vpd.c


EXTRA_DIST = \
	mstflint.spec

