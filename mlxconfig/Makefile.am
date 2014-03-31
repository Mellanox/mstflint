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


INCLUDES = -I. -I$(USER_DIR) -I$(top_srcdir)/include/mtcr_ul -I$(MTCR_DIR) -I$(COMMON_DIR) $(WIN64_INC)\
           -I$(MFT_EXT_LIBS_INC_DIR) -I $(LAYOUTS_DIR) -I$(MFT_EXT_LIBS_INC_DIR)/zlib -I $(UTILS_DIR) -I$(DEV_MGT_DIR)

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe
bin_PROGRAMS = mstconfig

mstconfig_LDADD =  ../reg_access/libreg_access.a $(LAYOUTS_LIB)  $(MTCR_DIR)/libmtcr_ul.a  $(MLNXOS_PPC_LIBS) $(LIBSTD_CPP) $(UTILS_LIB) $(DEV_MGT_DIR)/libdev_mgt.a -ldl

mstconfig_SOURCES = mlxcfg_ui.h mlxcfg_ui.cpp\
			 mlxcfg_parser.cpp\
			 mlxcfg_lib.h mlxcfg_lib.cpp

#get mst device examples and tool name from makefile
AM_CXXFLAGS += -DMLXCFG_NAME=\"mstconfig\"
AM_CXXFLAGS += -DMST_DEV_EXAMPLE=\"/sys/bus/pci/devices/0000:04:00.0/config\"

