#--
#                 - Mellanox Confidential and Proprietary -
# 
# Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
# 
# Except as specifically permitted herein, no portion of the information,
# including but not limited to object code and source code, may be reproduced,
# modified, distributed, republished or otherwise exploited in any form or by
# any means for any purpose without the prior written permission of Mellanox
# Technologies Ltd. Use of software subject to the terms and conditions
# detailed in the file "LICENSE.txt".
#--

# Makefile.am -- Process this file with automake to produce Makefile.in
USER_DIR = $(top_srcdir)
UTILS_DIR = $(top_srcdir)/mft_utils

MTCR_DIR    = $(top_srcdir)/${MTCR_CONF_DIR}
MTCR_INC_DIR = $(top_srcdir)/include/mtcr_ul
MFLASH_DIR  = $(top_srcdir)/mflash
COMMON_DIR  = $(top_srcdir)/common
LAYOUTS_DIR = $(top_srcdir)/tools_layouts
MFT_UTILS_DIR = $(top_srcdir)/mft_utils

INCLUDES = -I. -I$(USER_DIR) -I$(MTCR_DIR) -I$(MFT_EXT_LIBS_INC_DIR) -I$(UTILS_DIR)

AM_CXXFLAGS = -Wall -W -DMST_UL -g -MP -MD -pipe -Werror

lib_LTLIBRARIES = libmstreg_lib.a

libmstreg_lib_a_SOURCES = mlxreg_exception.h \
                           mlxreg_exception.cpp \
                           mlxreg_parser.h \
                           mlxreg_parser.cpp \
                           mlxreg_lib.h \
                           mlxreg_lib.cpp

mstreg_SOURCES = mlxreg_ui.cpp mlxreg_ui.h

bin_PROGRAMS = mstreg

mstreg_LDADD = libmstreg_lib.a \
                $(USER_DIR)/cmdparser/libcmdparser.a \
                $(MFT_UTILS_DIR)/libmftutils.a \
                $(MTCR_DIR)/libmtcr_ul.a \
                $(USER_DIR)/adb_parser/libadb_parser.a \
                $(USER_DIR)/cmdif/libcmdif.a \
                $(USER_DIR)/dev_mgt/libdev_mgt.a \
                $(USER_DIR)/reg_access/libreg_access.a \
                $(LAYOUTS_DIR)/libtools_layouts.a \
                $(USER_DIR)/tools_crypto/libtools_crypto.a \
                $(USER_DIR)/xz_utils/libxz_utils.a \
                $(USER_DIR)/ext_libs/minixz/libminixz.a \
                -lexpat -lboost_regex -lboost_filesystem -lboost_system \
                -llzma $(LIBSTD_CPP) ${LDL}
