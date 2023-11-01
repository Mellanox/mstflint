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

CURL_LIBS = -lcurl  -lssl -lcrypto -lrt

AM_CPPFLAGS = \
    -I$(srcdir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/libmfa \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/common -I$(top_builddir)/common \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxfwops/lib \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/tools_layouts


AM_CPPFLAGS += $(JSON_CFLAGS)

noinst_LTLIBRARIES = libmstarchive.la

libmstarchive_la_SOURCES = \
              mlxarchive_mfa2_utils.h mlxarchive_mfa2_utils.cpp \
              mlxarchive_mfa2_common_header.h mlxarchive_mfa2_common_header.cpp \
              mlxarchive_mfa2_element.h mlxarchive_mfa2_element.cpp \
              mlxarchive_mfa2_extension.h mlxarchive_mfa2_extension.cpp \
              mlxarchive_mfa2_descriptor.h mlxarchive_mfa2_descriptor.cpp \
              mlxarchive_mfa2_component.h \
              mlxarchive_mfa2.h mlxarchive_mfa2.cpp \
              mlxarchive_mfa2_builder.h mlxarchive_mfa2_builder.cpp \
              mlxarchive_mfa2_package_gen.h mlxarchive_mfa2_package_gen.cpp \
              mfa2_buff.h mfa2_buff.cpp

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

bin_PROGRAMS = mstarchive

mstarchive_SOURCES = mlxarchive.cpp mlxarchive.h

mstarchive_CXXFLAGS =

mstarchive_LDADD = libmstarchive.la \
                   $(top_builddir)/mlxfwops/lib/libmlxfwops.a \
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
                   $(top_builddir)/tools_layouts/libmlxarchive_layouts.la \
                   $(top_builddir)/tools_layouts/libtools_layouts.la \
                   $(top_builddir)/xz_utils/libxz_utils.la \
                   $(top_builddir)/ext_libs/minixz/libminixz.la \
                   $(top_builddir)/xz_utils/libxz_utils.la \
                   $(CURL_LIBS) \
                   -llzma -lm ${LDL}

mstarchive_LDFLAGS = -static

if ENABLE_OPENSSL
mstarchive_LDADD += $(top_builddir)/mlxsign_lib/libmlxsign.la -lcrypto -lssl
else
endif

if ENABLE_CS
mstarchive_LDADD += $(top_builddir)/tools_crypto/libtools_crypto.a -lcrypto
else
endif

if ENABLE_INBAND
mstarchive_LDADD += $(top_builddir)/mad_ifc/libmad_ifc.la
else
endif

if ENABLE_DPA
mstarchive_CXXFLAGS += -DENABLE_DPA
mstarchive_LDADD += $(top_builddir)/mlxdpa/libmstdpa.a
endif
