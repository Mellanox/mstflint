bin_PROGRAMS = mstmread \
					mstmwrite \
					mstmcra \
					mstflint \
					mstregdump \
					mstvpd

bin_SCRIPTS = hca_self_test.ofed
					
mstmread_SOURCES = mread.c mtcr.h

mstmwrite_SOURCES = mwrite.c mtcr.h

mstflint_SOURCES = flint.cpp mtcr.h mflash.h mflash.c tools_version.h

mstflint_LIBS = @mstflint_LIBS@
mstflint_CFLAGS   = -DNO_INBAND_ACCESS
mstflint_CXXFLAGS = -DDEV_MST_EXAMPLE1=\"03:00.0\" -DDEV_MST_EXAMPLE2=\"mlx4_0\"
mstflint_CXXFLAGS += @mstflint_CXXFLAGS@

mstregdump_SOURCES = mstdump.c mtcr.h \
					 tools_dev_types.h \
					 tools_dev_types.c \
                     MT23108.dat \
                     MT25204.dat \
                     MT25208.dat \
                     MT25408B0.dat \
                     MT25408.dat \
                     MT47396.dat \
                     MT48436.dat \
                     MT64102.dat \
                     MT64102safe.dat \
                     MT58100.dat \
                     MT2750.dat \
                     bit_slice.h

mstvpd_SOURCES = vpd.c

mstmcra_SOURCES  = mcra.c mtcr.h

mstflintinclude_HEADERS = mtcr.h
mstflintincludedir = @includedir@/mtcr_ul

EXTRA_DIST = \
	mstflint.spec \
	hca_self_test.ofed \
	gitversion.h
