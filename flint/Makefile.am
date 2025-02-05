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
    -I$(top_srcdir)/common -I$(top_builddir)/common \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/tools_layouts

bin_PROGRAMS = mstflint

mstflint_SOURCES = \
    cmd_line_parser.cpp \
    err_msgs.h \
    flint.cpp \
    flint.h \
    flint_params.cpp \
    flint_params.h \
    subcommands.cpp \
    subcommands.h \
    subcommands_linkx.cpp

mstflint_CXXFLAGS = -Wall -pthread -W -g -MP -MD -pipe -DEXTERNAL $(COMPILER_FPIC) \
                    -DUNIX -DOS_UNIX -DOS_LINUX

mstflint_DEPENDENCIES = \
     $(top_builddir)/mlxfwops/lib/libmlxfwops.a  \
     $(top_builddir)/cmdparser/libcmdparser.a \
     $(top_builddir)/mflash/libmflash.la \
     $(top_builddir)/tools_res_mgmt/libtools_res_mgmt.la \
     $(top_builddir)/cmdif/libcmdif.la \
     $(top_builddir)/reg_access/libreg_access.la  \
     $(top_builddir)/dev_mgt/libdev_mgt.la \
     $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
     $(top_builddir)/tools_layouts/libtools_layouts.la \
     $(top_builddir)/fw_comps_mgr/libfw_comps_mgr.la \
     $(top_builddir)/mft_utils/libmftutils.la

LDADD_mstflint = ${LDL}

#mstflint_LDFLAGS = -static

if ENABLE_DC
LDADD_mstflint += -lz
else
mstflint_CXXFLAGS += -DNO_ZLIB
endif

if ENABLE_CS
mstflint_DEPENDENCIES += $(top_builddir)/tools_crypto/libtools_crypto.a
LDADD_mstflint += -lcrypto
else
endif

if ENABLE_INBAND
mstflint_DEPENDENCIES += $(top_builddir)/mad_ifc/libmad_ifc.la
else
endif

if ENABLE_OPENSSL
mstflint_DEPENDENCIES += $(top_builddir)/mlxsign_lib/libmlxsign.la
LDADD_mstflint += -lcrypto -lssl
else
mstflint_CXXFLAGS += -DNO_OPEN_SSL
endif

if ENABLE_FWMGR
mstflint_DEPENDENCIES += \
    $(top_builddir)/libmfa/libmfa.la \
    $(top_builddir)/ext_libs/minixz/libminixz.la \
    $(top_builddir)/mlxarchive/libmstarchive.la \
    $(top_builddir)/tools_layouts/libmlxarchive_layouts.la \
    $(top_builddir)/xz_utils/libxz_utils.la
LDADD_mstflint += -llzma -lm
else
mstflint_CXXFLAGS += -DNO_MSTARCHIVE
endif

if ENABLE_DPA
mstflint_CXXFLAGS += -DENABLE_DPA
mstflint_DEPENDENCIES += $(top_builddir)/mlxdpa/libmstdpa.a
endif

mstflint_LDADD = $(mstflint_DEPENDENCIES) $(LDADD_mstflint)

# get mst device examples and tool name from makefile
mstflint_CXXFLAGS += -DFLINT_NAME=\"mstflint\" -DFLINT_DISPLAY_NAME=\"MstFlint\"
mstflint_CXXFLAGS += -DMST_DEV_EXAMPLE1=\"03:00.0\" -DMST_DEV_EXAMPLE2=\"mlx4_0\" -DMST_DEV_EXAMPLE3=\"03:00.0\" -DMST_DEV_EXAMPLE4=\"04:00.0\"
