#--
# Copyright (c) 2024-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

# Makefile.am -- Process this file with automake to produce Makefile.in

AM_CPPFLAGS = \
    -I$(srcdir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/common -I$(top_builddir)/common \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxfwops/lib \
    -I$(top_srcdir)/cmdparser \
    -I$(top_srcdir)/pldm_utils \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/tools_layouts

AM_CPPFLAGS += $(JSON_CFLAGS)

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES = libpldmgen.la

libpldmgen_la_SOURCES = \
    pldm.h pldm.cpp \
    pldm_arg_parser.h pldm_arg_parser.cpp \
    pldm_component.h pldm_component.cpp \
    pldm_descriptor.h pldm_descriptor.cpp \
    pldm_devicerecord.h pldm_devicerecord.cpp \
    pldm_params.h pldm_params.cpp \
    pldm_time.h pldm_time.cpp

bin_PROGRAMS = mstpldm_pkg_gen

mstpldm_pkg_gen_SOURCES = pldmgen.cpp

mstpldm_pkg_gen_CXXFLAGS =

mstpldm_pkg_gen_LDADD = libpldmgen.la \
                     $(top_builddir)/mlxfwops/lib/libmlxfwops.a \
                     $(top_builddir)/pldmlib/libpldm.la \
                     $(top_builddir)/pldm_utils/libpldm_utils.la \
                     $(top_builddir)/libmfa/libmfa.la \
                     $(top_builddir)/fw_comps_mgr/libfw_comps_mgr.la \
                     $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
                     $(top_builddir)/mflash/libmflash.la \
                     $(top_builddir)/tools_res_mgmt/libtools_res_mgmt.la \
                     $(top_builddir)/dev_mgt/libdev_mgt.la \
                     $(top_builddir)/cmdif/libcmdif.la \
                     $(top_builddir)/mft_utils/libmftutils.la \
                     $(JSON_LIBS) \
                     $(top_builddir)/cmdparser/libcmdparser.a \
                     $(top_builddir)/reg_access/libreg_access.la \
                     $(top_builddir)/tools_layouts/libtools_layouts.la \
                     $(top_builddir)/xz_utils/libxz_utils.la \
                     $(top_builddir)/ext_libs/minixz/libminixz.la \
                     $(top_builddir)/common/libcommon.la \
                     $(libcurl_LIBS) \
                     $(liblzma_LIBS) \
                     -lm ${LDL}

mstpldm_pkg_gen_LDFLAGS = -static

if ENABLE_OPENSSL
mstpldm_pkg_gen_LDADD += $(top_builddir)/mlxsign_lib/libmlxsign.la $(openssl_LIBS)
endif

if ENABLE_CS
mstpldm_pkg_gen_LDADD += $(top_builddir)/tools_crypto/libtools_crypto.a $(openssl_LIBS)
endif

if ENABLE_INBAND
mstpldm_pkg_gen_LDADD += $(top_builddir)/mad_ifc/libmad_ifc.la
endif

if ENABLE_DPA
mstpldm_pkg_gen_CXXFLAGS += -DENABLE_DPA
mstpldm_pkg_gen_LDADD += $(top_builddir)/mlxdpa/libmstdpa.a
endif
