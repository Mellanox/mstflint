bin_PROGRAMS = mstmread \
					mstmwrite \
					mstmcra \
					mstflint \
					mstregdump \
					mstvpd

mstmread_SOURCES = mread.c mtcr.h

mstmwrite_SOURCES = mwrite.c mtcr.h

mstflint_SOURCES = flint.cpp mtcr.h mflash.h mflash.c
mstflint_LDFLAGS = -lz

mstregdump_SOURCES = mstdump.c mtcr.h

mstvpd_SOURCES = vpd.c

mstmcra_SOURCES  = mcra.c mtcr.h

mstflintinclude_HEADERS = mtcr.h
mstflintincludedir = @includedir@

EXTRA_DIST = \
	mstflint.spec

