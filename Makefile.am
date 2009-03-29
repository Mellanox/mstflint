bin_PROGRAMS = mstmread \
					mstmwrite \
					mstmcra \
					mstflint \
					mstregdump \
					mstvpd

bin_SCRIPTS = hca_self_test.ofed
					
mstmread_SOURCES = mread.c mtcr.h

mstmwrite_SOURCES = mwrite.c mtcr.h

mstflint_SOURCES = flint.cpp mtcr.h mflash.h mflash.c

mstflint_LIBS = @mstflint_LIBS@
mstflint_CXXFLAGS = @mstflint_CXXFLAGS@

mstregdump_SOURCES = mstdump.c mtcr.h

mstvpd_SOURCES = vpd.c

mstmcra_SOURCES  = mcra.c mtcr.h

mstflintinclude_HEADERS = mtcr.h
mstflintincludedir = @includedir@/mtcr_ul

EXTRA_DIST = \
	mstflint.spec \
    hca_self_test.ofed
