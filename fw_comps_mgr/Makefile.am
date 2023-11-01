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
    -I$(top_srcdir)/cmdif \
    -I$(top_srcdir)/common -I$(top_builddir)/common \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/reg_access \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/tools_res_mgmt

AM_CFLAGS = -MD -pipe -Wall -W $(COMPILER_FPIC)

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LIBRARIES = libfw_comps_mgr.a

libfw_comps_mgr_a_SOURCES = \
    fw_comps_mgr.cpp \
    fw_comps_mgr.h \
    fw_comps_mgr_abstract_access.cpp \
    fw_comps_mgr_abstract_access.h \
    fw_comps_mgr_direct_access.cpp \
    fw_comps_mgr_direct_access.h \
    fw_comps_mgr_dma_access.cpp \
    fw_comps_mgr_dma_access.h

if ENABLE_INBAND
else
AM_CXXFLAGS += "-DNO_INBAND"
endif

libfw_comps_mgr_a_DEPENDENCIES = \
    $(top_builddir)/reg_access/libreg_access.la \
    $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
    $(top_builddir)/tools_res_mgmt/libtools_res_mgmt.a \
    $(top_builddir)/mft_utils/libmftutils.la


if ENABLE_INBAND
libfw_comps_mgr_a_DEPENDENCIES += $(top_builddir)/mad_ifc/libmad_ifc.la
endif

libfw_comps_mgr_a_LIBADD = $(libfw_comps_mgr_a_DEPENDENCIES)
