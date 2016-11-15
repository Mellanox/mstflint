#--
# Copyright (c) 2004-2010 Mellanox Technologies LTD. All rights reserved.
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
USER_DIR = $(top_srcdir)
MTCR_DIR = $(top_srcdir)/mtcr_ul
COMMON_DIR = $(top_srcdir)/common
LAYOUTS_DIR = $(top_srcdir)/tools_layouts
UTILS_DIR = $(top_srcdir)/mft_utils
DEV_MGT_DIR = $(top_srcdir)/dev_mgt
LAYOUTS_LIB = $(LAYOUTS_DIR)/libtools_layouts.a
UTILS_LIB = $(USER_DIR)/mft_utils/libmftutils.a
CMDIF_DIR = $(USER_DIR)/cmdif
EXT_LIB_DIR = $(USER_DIR)/ext_libs

SUBDIRS = mlxconfig_dbs

AM_CPPFLAGS = -I. -I$(USER_DIR) -I$(top_srcdir)/include/mtcr_ul -I$(MTCR_DIR) -I$(COMMON_DIR) $(WIN64_INC)\
           -I $(LAYOUTS_DIR) -I $(UTILS_DIR) -I$(DEV_MGT_DIR) -I$(CMDIF_DIR)


AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe  -Wno-deprecated-declarations -DDATA_PATH=\"$(pkgdatadir)\"
bin_PROGRAMS = mstconfig

mstconfig_LDADD = $(UTILS_LIB) $(EXT_LIB_DIR)/sqlite/libsqlite3.a $(EXT_LIB_DIR)/muparser/libmuparser.a\
								$(CMDIF_DIR)/libcmdif.a ../reg_access/libreg_access.a $(LAYOUTS_LIB) $(MTCR_DIR)/libmtcr_ul.a\
								$(DEV_MGT_DIR)/libdev_mgt.a $(MLNXOS_PPC_LIBS) $(LIBSTD_CPP) -ldl

if DISABLE_XML2
AM_CXXFLAGS += -DDISABLE_XML2
else
AM_CPPFLAGS += -I$(XML2_INC_DIR)
mstconfig_LDADD += -lxml2
endif

mstconfig_SOURCES =  mlxcfg_ui.h mlxcfg_parser.cpp mlxcfg_ui.cpp\
			mlxcfg_status.h mlxcfg_utils.h mlxcfg_utils.cpp mlxcfg_view.h\
			 mlxcfg_db_manager.h mlxcfg_db_manager.cpp mlxcfg_param.h mlxcfg_param.cpp mlxcfg_tlv.h mlxcfg_tlv.cpp\
			 mlxcfg_commander.h mlxcfg_commander.cpp mlxcfg_generic_commander.h mlxcfg_generic_commander.cpp\
			 mlxcfg_param_lib.h mlxcfg_param_lib.cpp mlxcfg_4thgen_commander.h mlxcfg_4thgen_commander.cpp

#get mst device examples and tool name from makefile
AM_CXXFLAGS += -DMLXCFG_NAME=\"mstconfig\"
AM_CXXFLAGS += -DMST_DEV_EXAMPLE=\"04:00.0\" -DMST_DEV_EXAMPLE2=\"05:00.0\"

