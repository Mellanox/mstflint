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

SUBDIRS = mlxreg_lib

AM_CPPFLAGS = \
    -I$(srcdir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxreg

AM_CXXFLAGS = -Wall -W -DMST_UL -g -MP -MD -pipe

mstreg_SOURCES = mlxreg_ui.cpp mlxreg_ui.h

bin_PROGRAMS = mstreg

mstreg_DEPENDENCIES = \
    $(top_builddir)/mlxreg/mlxreg_lib/libmstreg_lib.la \
    $(top_builddir)/cmdparser/libcmdparser.a \
    $(top_builddir)/mft_utils/libmftutils.la \
    $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
    $(top_builddir)/adb_parser/libadb_parser.la \
    $(top_builddir)/cmdif/libcmdif.la \
    $(top_builddir)/dev_mgt/libdev_mgt.la \
    $(top_builddir)/reg_access/libreg_access.la \
    $(top_builddir)/tools_layouts/libtools_layouts.la \
    $(top_builddir)/xz_utils/libxz_utils.la \
    $(top_builddir)/ext_libs/minixz/libminixz.la \
    $(top_builddir)/common/libcommon.la

mstreg_LDADD = $(mstreg_DEPENDENCIES) -llzma ${LDL} -lexpat

#mstreg_LDFLAGS = -static
