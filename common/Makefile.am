# Copyright (c) 2023-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

noinst_LTLIBRARIES = libcommon.la

AM_CPPFLAGS = $(JSON_CFLAGS) -I$(top_srcdir) -I$(top_srcdir)/include/mtcr_ul

libcommon_la_SOURCES = \
    bit_slice.h \
    compatibility.h \
    tools_algorithm.h \
    tools_filesystem.cpp \
    tools_filesystem.h \
    tools_regex.cpp \
    tools_regex.h \
    tools_time.h \
    tools_utils.h \
    tools_utils.h \
    tools_version.h \
    tools_string.h \
    tools_string.cpp \
    PCILibrary.cpp \
    PCILibrary.h

libcommon_la_LIBADD = $(top_builddir)/dev_mgt/libdev_mgt.la

commonincludedir = $(includedir)/mstflint/common/
commoninclude_HEADERS = compatibility.h

update_prefix = sed -e 's,[@]MST_LIB_DIR[@]${CONF_DISABLE_PATH_UPDATE},$(libdir),g'\
                    -e 's,[@]MST_BIN_DIR[@]${CONF_DISABLE_PATH_UPDATE},$(bindir),g'\
                    -e 's,[@]MFTCONF_PREFIX[@],$(prefix),g'

update_tools_version = sed -e 's,[@]MSTFLINT_VERSION_STR[@],${MSTFLINT_VERSION_STR},g' \
     	          	-e 's,[@]TOOLS_BUILD_TIME[@],${TOOLS_BUILD_TIME},g' \
                    -e 's,[@]TOOLS_GIT_SHA[@],${TOOLS_GIT_SHA},g'

all: python_wrapper.sh tools_version.py tools_version.h mft_logger.py
	$(update_prefix) < $(srcdir)/python_wrapper.sh > python_wrapper
	chmod +x python_wrapper

tools_version.py:
	$(update_tools_version) < $(srcdir)/tools_version.py.in > tools_version.py

tools_version.h:
	$(update_tools_version) < $(srcdir)/tools_version.h.in > tools_version.h

tools_version_pylibdir=$(libdir)/mstflint/python_tools/
tools_version_pylib_DATA = tools_version.py

mft_logger_pylibdir=$(libdir)/mstflint/python_tools/
mft_logger_pylib_DATA = mft_logger.py

EXTRA_DIST = tools_version.py.in python_wrapper.sh

CLEANFILES = python_wrapper tools_version.py

#SUBDIRS = autocomplete
