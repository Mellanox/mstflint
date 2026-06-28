#--
# Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#--

# Override automake's default -I. -I$(srcdir) to avoid picking up the
# Windows-only inttypes.h / stdint.h stubs that live in this directory.
DEFAULT_INCLUDES = -I$(top_builddir)
AM_CPPFLAGS = \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/cmdif \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/common

AM_CFLAGS = -W -Wall -g -MP -MD -DWITH_MSTFLINT -DMST_UL $(COMPILER_FPIC) \
    -DPACKAGE_VERSION_STR=\"$(PACKAGE_VERSION)\"

bin_SCRIPTS = vpi_tcpdump
bin_PROGRAMS = ibdump
ibdump_SOURCES = ibdump.c
ibdump_DEPENDENCIES = \
    $(top_builddir)/cmdif/libcmdif.la \
    $(top_builddir)/dev_mgt/libdev_mgt.la \
    $(top_builddir)/reg_access/libreg_access.la \
    $(top_builddir)/tools_layouts/libtools_layouts.la \
    $(top_builddir)/$(MTCR_CONF_DIR)/libmtcr_ul.la

ibdump_LDADD = \
    $(ibdump_DEPENDENCIES) \
    -libverbs \
    -lpthread \
    $(LDL) \
    -lm
