bin_PROGRAMS = 	mstflint 

INCLUDES  = -I$(top_srcdir)/mflash -I$(top_srcdir)/include/mtcr_ul -I$(top_srcdir)/common -I$(top_srcdir)/dev_mgt

mstflint_SOURCES = flint.cpp  \
				   flint_base.cpp \
				   flint_io.cpp \
				   flint_ops.cpp \
				   flint_base.h \
				   flint_io.h \
				   flint_ops.h \
				   cibfw_layouts.c \
				   cibfw_layouts.h \
				   adb_to_c_utils.c \
				   adb_to_c_utils.h

mstflint_LDADD =  ../mflash/libmflash.a

mstflint_LIBS = @mstflint_LIBS@
mstflint_CXXFLAGS = -DDEV_MST_EXAMPLE1=\"03:00.0\" -DDEV_MST_EXAMPLE2=\"mlx4_0\" -DEXTERNAL
mstflint_CXXFLAGS += @mstflint_CXXFLAGS@

mstflintinclude_HEADERS = $(top_srcdir)/include/mtcr_ul/mtcr.h
mstflintincludedir = @includedir@/mtcr_ul
