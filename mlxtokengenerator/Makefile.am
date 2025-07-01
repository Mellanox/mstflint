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
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/common -I$(top_builddir)/common \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/cmdif \
    -I$(top_srcdir)/tools_res_mgmt \
    $(libxml2_CFLAGS) \
    $(openssl_CFLAGS)

AM_CPPFLAGS += $(MUPARSER_CFLAGS) $(SQLITE_CFLAGS) $(COMPILER_FPIC)

AM_CXXFLAGS = -pthread -Wall -W -g -MP -MD -pipe $(JSON_CFLAGS) -Wno-deprecated-declarations  $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"

bin_PROGRAMS = msttokengenerator

msttokengenerator_SOURCES = mlxtkngenerator_utils.h mlxtkngenerator_utils.cpp \
                            mlxtoken.h mlxtoken.cpp \
                            mlxtkngenerator.h mlxtkngenerator.cpp

msttokengenerator_DEPENDENCIES = \
                                $(top_builddir)/mlxconfig/libmlxcfg.la \
                                $(top_builddir)/mlxfwops/lib/libmlxfwops.a  \
                                $(top_builddir)/pldmlib/libpldm.la \
							    $(top_builddir)/mflash/libmflash.la \
                                $(top_builddir)/cmdparser/libcmdparser.a \
                                $(top_builddir)/tools_layouts/libtools_layouts.la \
                                $(top_builddir)/mft_utils/libmftutils.la \
							    $(top_builddir)/libmfa/libmfa.la \
                                $(top_builddir)/cmdif/libcmdif.la \
							    $(top_builddir)/dev_mgt/libdev_mgt.la \
                                $(top_builddir)/fw_comps_mgr/libfw_comps_mgr.la \
                                $(SQLITE_LIBS) \
                                $(JSON_LIBS) \
                                $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la


msttokengenerator_LDFLAGS = -static

if ENABLE_OPENSSL
else
AM_CXXFLAGS += -DNO_OPEN_SSL
endif

if ENABLE_FWMGR
msttokengenerator_DEPENDENCIES += \
    $(top_builddir)/ext_libs/minixz/libminixz.la
endif

msttokengenerator_LDADD = $(msttokengenerator_DEPENDENCIES) ${LDL}

if DISABLE_XML2
AM_CXXFLAGS += -DDISABLE_XML2
else
msttokengenerator_LDADD += -lxml2
endif

if ENABLE_CS
AM_CPPFLAGS += $(openssl_CFLAGS)
msttokengenerator_LDADD += $(openssl_LIBS)
msttokengenerator_DEPENDENCIES += $(top_builddir)/tools_crypto/libtools_crypto.a
else
endif
