# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software is available to you under a choice of one of two
# licenses.  You may choose to be licensed under the terms of the GNU
# General Public License (GPL) Version 2, available from the file
# COPYING in the main directory of this source tree, or the
# OpenIB.org BSD license below:
#
#     Redistribution and use in source and binary forms, with or
#     without modification, are permitted provided that the following
#     conditions are met:
#
#      - Redistributions of source code must retain the above
#        copyright notice, this list of conditions and the following
#        disclaimer.
#
#      - Redistributions in binary form must reproduce the above
#        copyright notice, this list of conditions and the following
#        disclaimer in the documentation and/or other materials
#        provided with the distribution.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
# BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
# ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
# CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

# Makefile.am -- Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
    -I$(srcdir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/common -I$(top_builddir)/common \
    -I$(top_srcdir)/adb_parser \
    -I$(top_builddir)/mft_core/device/device_info

AM_CXXFLAGS = -Wall -W -DMST_UL -g -MP -MD -pipe $(COMPILER_FPIC) \
              -DDATA_PATH=\"$(pkgdatadir)\"

# The decode is reached from python over ctypes, so it is delivered as a module
# loaded by its own path next to the entry point rather than off the loader path.
cltssmdir = $(libdir)/mstflint/python_tools/mstltssm

noinst_LTLIBRARIES = libcltssm_trace.la

libcltssm_trace_la_SOURCES = \
    ltssm_reader.cpp ltssm_reader.h \
    ltssm_trace_exception.cpp ltssm_trace_exception.h \
    ltssm_trace_sdk.cpp ltssm_trace_sdk.h

CLTSSM_SO = cltssm_trace.so

if USE_LOCAL_SQLITE
CLTSSM_SQLITE_LIB = $(top_builddir)/ext_libs/sqlite/.libs/libsqlite3.a
else
CLTSSM_SQLITE_LIB =
endif

CLTSSM_WHOLE_ARCHIVE_LIBS = \
    .libs/libcltssm_trace.a \
    $(top_builddir)/mlxparsebin/.libs/libmstparsebin.a \
    $(top_builddir)/mft_core/device/device_info/.libs/libdevice_info.a \
    $(top_builddir)/adb_parser/.libs/libadb_parser.a \
    $(top_builddir)/dev_mgt/.libs/libdev_mgt.a \
    $(top_builddir)/reg_access/.libs/libreg_access.a \
    $(top_builddir)/tools_layouts/.libs/libtools_layouts.a \
    $(top_builddir)/mft_utils/.libs/libmftutils.a \
    $(top_builddir)/xz_utils/.libs/libxz_utils.a \
    $(top_builddir)/ext_libs/minixz/.libs/libminixz.a \
    $(top_builddir)/common/.libs/libcommon.a

$(CLTSSM_SO): libcltssm_trace.la
	$(CXX) -shared -pthread $(CXXFLAGS) $(LDFLAGS) $(COMPILER_FPIC) -o $@ \
	  -Wl,--whole-archive $(CLTSSM_WHOLE_ARCHIVE_LIBS) -Wl,--no-whole-archive \
	  $(top_builddir)/${MTCR_CONF_DIR}/.libs/libmtcr_ul.a \
	  $(CLTSSM_SQLITE_LIB) $(liblzma_LIBS) $(expat_LIBS) $(LDL) $(LIBS) \
	  -Wl,--allow-multiple-definition -Wl,--no-undefined

all-local: $(CLTSSM_SO)

cltssm_DATA = $(CLTSSM_SO)

install-data-hook:
	chmod +x $(DESTDIR)$(cltssmdir)/$(CLTSSM_SO)

USER_DIR = $(top_builddir)

bin_SCRIPTS = mstltssm

PYTHON_WRAPPER=mstltssm
PYTHON_WRAPPER_SCRIPT=$(USER_DIR)/common/python_wrapper
${PYTHON_WRAPPER}: $(PYTHON_WRAPPER_SCRIPT)
	cp $(PYTHON_WRAPPER_SCRIPT) $@

pythonlibdir=$(libdir)/mstflint/python_tools/mstltssm
dist_pythonlib_SCRIPTS = mstltssm.py

libpythonlibdir=$(libdir)/mstflint/python_tools/mstltssm/nvltssm_lib
dist_libpythonlib_DATA = $(srcdir)/nvltssm_lib/*.py

cpythonlibdir=$(libdir)/mstflint/python_tools/mstltssm/nvltssm_lib/cnvltssm
dist_cpythonlib_DATA = $(srcdir)/nvltssm_lib/cnvltssm/*.py

formatterspythonlibdir=$(libdir)/mstflint/python_tools/mstltssm/nvltssm_lib/formatters
dist_formatterspythonlib_DATA = $(srcdir)/nvltssm_lib/formatters/*.py

# the reduced per-device ADBs the ring logger is decoded against, resolved at
# run time out of DATA_PATH
ltssmdbdir = $(pkgdatadir)/ltssm_dbs
dist_ltssmdb_DATA = $(srcdir)/data/*.adb

CLEANFILES = ${PYTHON_WRAPPER} $(CLTSSM_SO)
