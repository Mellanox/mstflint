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

docdir = $(INSTALL_BASEDIR)/etc/mstflint
dist_doc_DATA = certificate/ca-bundle.crt

AM_CPPFLAGS = \
    -I$(srcdir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/cmdparser \
    -I$(top_srcdir)/common -I$(top_builddir)/common \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/libmfa \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxfwops/lib \
    -I$(top_srcdir)/pldmlib \
    $(libxml2_CFLAGS) \
    $(libcurl_CFLAGS) \
    $(openssl_CFLAGS)

bin_PROGRAMS = mstfwmanager

mstfwmanager_CXXFLAGS = -g -MP -MD -Wall -W -DMSTFLINT $(INIPARSER_CFLAGS) $(JSON_CFLAGS)
mstfwmanager_CXXFLAGS += -DUSE_XML -DLIBXML_STATIC
mstfwmanager_CXXFLAGS += -DUSE_CURL -DCURL_STATICLIB

mstfwmanager_SOURCES = \
    cmd_line_params.cpp \
    cmd_line_params.h \
    cmd_line_parser.cpp \
    cmd_line_parser.h \
    err_msgs.h \
    fw_version_old_clp.cpp \
    fw_version_old_clp.h \
    fw_version_with_sub_build.cpp \
    fw_version_with_sub_build.h \
    image_access.cpp \
    image_access.h \
    img_version.cpp \
    img_version.h \
    menu.cpp \
    menu.h \
    mlnx_dev.cpp \
    mlnx_dev.h \
    mlxfwmanager.cpp \
    mlxfwmanager.h \
    mlxfwmanager_common.cpp \
    mlxfwmanager_common.h \
    output_fmts.cpp \
    output_fmts.h \
    psid_lookup_db.cpp \
    psid_lookup_db.h \
    psid_query_item.cpp \
    psid_query_item.h \
    server_request.cpp \
    server_request.h
                        
mstfwmanager_DEPENDENCIES = \
    $(top_builddir)/dev_mgt/libdev_mgt.la \
    $(top_builddir)/mvpd/libmvpd.la \
    $(top_builddir)/mlxfwops/lib/libmlxfwops.a \
    $(top_builddir)/pldmlib/libpldm.la \
    $(top_builddir)/mlxconfig/libmlxcfg.la \
    $(top_builddir)/libmfa/libmfa.la \
    $(top_builddir)/ext_libs/minixz/libminixz.la \
    $(top_builddir)/cmdparser/libcmdparser.a \
    $(top_builddir)/mflash/libmflash.la \
    $(top_builddir)/tools_res_mgmt/libtools_res_mgmt.la \
    $(top_builddir)/mft_utils/libmftutils.la \
    $(top_builddir)/cmdif/libcmdif.la \
    $(top_builddir)/reg_access/libreg_access.la \
    $(top_builddir)/tools_layouts/libtools_layouts.la \
    $(top_builddir)/fw_comps_mgr/libfw_comps_mgr.la \
    $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
    $(top_builddir)/common/libcommon.la \
    $(JSON_LIBS) \
    $(INIPARSER_LIBS) \
    $(MUPARSER_LIBS) \
    $(SQLITE_LIBS)

LDADD_mstfwmanager = $(libcurl_LIBS) $(libz_LIBS) $(liblzma_LIBS) $(libxml2_LIBS)

if ENABLE_OPENSSL
mstfwmanager_DEPENDENCIES += $(top_builddir)/mlxsign_lib/libmlxsign.la
LDADD_mstfwmanager += $(openssl_LIBS)
endif

if ENABLE_CS
mstfwmanager_DEPENDENCIES += $(top_builddir)/tools_crypto/libtools_crypto.a
LDADD_mstfwmanager += $(openssl_LIBS)
endif

if ENABLE_INBAND
mstfwmanager_DEPENDENCIES += $(top_builddir)/mad_ifc/libmad_ifc.la
endif

if ENABLE_DPA
mstfwmanager_CXXFLAGS += -DENABLE_DPA
mstfwmanager_DEPENDENCIES += $(top_builddir)/mlxdpa/libmstdpa.a
endif

mstfwmanager_LDADD = $(mstfwmanager_DEPENDENCIES) $(LDADD_mstfwmanager)
mstfwmanager_LDFLAGS = -static
