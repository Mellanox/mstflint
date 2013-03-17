INCLUDES= -I$(top_srcdir)/include/mtcr_ul

bin_PROGRAMS = mstmread \
					mstmwrite \
					mstmcra \
					mstmtserver \
					mstvpd

bin_SCRIPTS = hca_self_test.ofed
					
mstmread_SOURCES = mread.c 

mstmwrite_SOURCES = mwrite.c

mstvpd_SOURCES = vpd.c

mstmcra_SOURCES  = mcra.c

mstmtserver_SOURCES = mtserver.c tcp.c tcp.h
mstmtserver_CFLAGS = -DMST_UL
