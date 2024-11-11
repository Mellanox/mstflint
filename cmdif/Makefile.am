# Copyright (c) 2023 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
    -I$(top_srcdir)/common -I$(top_builddir)/common\
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/tools_layouts

CCMDIF_SO = ccmdif.so

AM_CFLAGS = -W -Wall  -g -MP -MD $(COMPILER_FPIC) -DCMDIF_EXPORTS

noinst_LTLIBRARIES = libcmdif.la

cmdifincludedir = $(includedir)/mstflint/cmdif/

cmdifinclude_HEADERS = icmd_cif_common.h icmd_cif_open.h

libcmdif_la_SOURCES = tools_cif.c tools_cif.h icmd_cif_common.c icmd_cif_common.h icmd_cif_open.c icmd_cif_open.h

cmdif_pylibdir = $(libdir)/mstflint/python_tools/
cmdif_pylib_DATA = ${CCMDIF_SO} cmdif.py
${CCMDIF_SO}: libcmdif.la
	$(CC) -g -Wall -pthread -shared ${CFLAGS} .libs/*.o -o ${CCMDIF_SO} \
	$(top_builddir)/tools_layouts/.libs/libtools_layouts.a $(top_builddir)/${MTCR_CONF_DIR}/.libs/libmtcr_ul.so

CLEANFILES = ${CCMDIF_SO}
