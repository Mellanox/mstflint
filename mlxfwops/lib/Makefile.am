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
MTCR_DIR = $(top_srcdir)/mtcr_ul
MTCR_INC_DIR = $(top_srcdir)/include/mtcr_ul
MFLASH_DIR = $(top_srcdir)/mflash
MINIXZ_DIR = $(top_srcdir)/ext_libs/minixz
COMMON_DIR = $(top_srcdir)/common
LAYOUTS_DIR = $(top_srcdir)/tools_layouts
UTILS_LIB = $(top_srcdir)/mft_utils

INCLUDES = -I$(srcdir) -I$(MTCR_INC_DIR) -I$(MFLASH_DIR) -I$(top_srcdir)/ext_libs/json -I$(MINIXZ_DIR)\
           -I$(COMMON_DIR) -I$(MFT_EXT_LIBS_INC_DIR)/zlib -I $(LAYOUTS_DIR) -I$(top_srcdir)/common -I$(UTILS_LIB)

MLXFWOPS_VERSION = 1

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe -DNO_MFA_SUPPORT

noinst_LIBRARIES = libmlxfwops.a

libmlxfwops_a_SOURCES = flint_base.cpp \
               flint_io.cpp \
               fw_ops.cpp \
               fs2_ops.cpp fs2_ops.h \
               fs3_ops.cpp fs3_ops.h \
               mlxfwops.cpp mlxfwops.h \
               mlxfwops_com.h mlxfwops.h fw_ops.h flint_base.h flint_io.h

