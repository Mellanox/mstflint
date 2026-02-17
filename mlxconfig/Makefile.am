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

PYTHON_WRAPPER_SCRIPT = ../common/python_wrapper

SUBDIRS = mlxconfig_dbs

AM_CPPFLAGS = \
    -I$(srcdir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/common -I$(top_builddir)/common \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/cmdif \
    -I$(top_srcdir)/tools_res_mgmt \
    $(libxml2_CFLAGS) \
    $(openssl_CFLAGS)

AM_CPPFLAGS += $(MUPARSER_CFLAGS) $(SQLITE_CFLAGS) $(COMPILER_FPIC)

AM_CXXFLAGS = -pthread -Wall -W -g -MP -MD -pipe  $(JSON_CFLAGS) -Wno-deprecated-declarations  $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"

bin_PROGRAMS = mstconfig

if ADB_GENERIC_TOOLS_ENABLED
MLXPRIVHOST_PYTHON_WRAPPER = mstprivhost
bin_SCRIPTS = ${MLXPRIVHOST_PYTHON_WRAPPER}
${MLXPRIVHOST_PYTHON_WRAPPER}: $(PYTHON_WRAPPER_SCRIPT)
	cp $(PYTHON_WRAPPER_SCRIPT) $@

mlxprivhostlibdir = $(libdir)/mstflint/python_tools/$(MLXPRIVHOST_PYTHON_WRAPPER)
mlxprivhostlib_DATA = $(MLXPRIVHOST_PYTHON_WRAPPER).py
endif

noinst_LTLIBRARIES = libmlxcfg.la

libmlxcfg_la_SOURCES = mlxcfg_status.h mlxcfg_utils.h mlxcfg_utils.cpp mlxcfg_view.h \
        mlxcfg_expression.h mlxcfg_expression.cpp \
        mlxcfg_db_items.h mlxcfg_db_items.cpp \
        mlxcfg_db_manager.h mlxcfg_db_manager.cpp mlxcfg_param.h mlxcfg_param.cpp mlxcfg_tlv.h mlxcfg_tlv.cpp \
        mlxcfg_commander.h mlxcfg_commander.cpp mlxcfg_generic_commander.h mlxcfg_generic_commander.cpp \
        mlxcfg_ui_tokens.h mlxcfg_ui_tokens.cpp mlxcfg_configuration.h mlxcfg_configuration.cpp

libmlxcfg_la_DEPENDENCIES = \
    $(top_builddir)/mft_utils/libmftutils.la \
    $(top_builddir)/cmdif/libcmdif.la \
    $(top_builddir)/reg_access/libreg_access.la \
    $(top_builddir)/tools_layouts/libtools_layouts.la \
    $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
    $(top_builddir)/dev_mgt/libdev_mgt.la \
    $(top_builddir)/fw_comps_mgr/libfw_comps_mgr.la \
    $(top_builddir)/tools_res_mgmt/libtools_res_mgmt.la \
    $(JSON_LIBS) \
    $(MUPARSER_LIBS) \
    $(SQLITE_LIBS)

libmlxcfg_la_LIBADD = $(libmlxcfg_la_DEPENDENCIES) ${LDL}

mstconfig_DEPENDENCIES = \
    libmlxcfg.la \
    $(top_builddir)/mft_utils/libmftutils.la \
    $(top_builddir)/cmdif/libcmdif.la \
    $(top_builddir)/reg_access/libreg_access.la \
    $(top_builddir)/tools_layouts/libtools_layouts.la \
    $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
    $(top_builddir)/dev_mgt/libdev_mgt.la \
    $(top_builddir)/fw_comps_mgr/libfw_comps_mgr.la \
    $(top_builddir)/tools_res_mgmt/libtools_res_mgmt.la \
    $(top_builddir)/common/libcommon.la \
    $(MUPARSER_LIBS) \
    $(SQLITE_LIBS)

mstconfig_LDADD = $(mstconfig_DEPENDENCIES) ${LDL}

mstconfig_LDFLAGS = -static

if DISABLE_XML2
AM_CXXFLAGS += -DDISABLE_XML2
else
AM_CPPFLAGS += $(libxml2_CFLAGS)
mstconfig_LDADD += $(libxml2_LIBS)
libmlxcfg_la_LIBADD += $(libxml2_LIBS)
endif

if ENABLE_INBAND
mstconfig_LDADD += $(top_builddir)/mad_ifc/libmad_ifc.la
libmlxcfg_la_LIBADD += $(top_builddir)/mad_ifc/libmad_ifc.la
else
endif

if ENABLE_OPENSSL
AM_CPPFLAGS += $(openssl_CFLAGS)
mstconfig_LDADD += $(top_builddir)/mlxsign_lib/libmlxsign.la $(openssl_LIBS)
libmlxcfg_la_LIBADD += $(top_builddir)/mlxsign_lib/libmlxsign.la $(openssl_LIBS)
else
AM_CXXFLAGS += -DNO_OPEN_SSL
endif

mstconfig_SOURCES =  mlxcfg_ui.h mlxcfg_parser.cpp mlxcfg_ui.cpp

# get mst device examples and tool name from makefile
AM_CXXFLAGS += -DMLXCFG_NAME=\"mstconfig\"
AM_CXXFLAGS += -DMST_DEV_EXAMPLE=\"04:00.0\" -DMST_DEV_EXAMPLE2=\"05:00.0\"
