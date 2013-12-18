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
USER_DIR = ../..
MTCR_DIR = $(USER_DIR)/mtcr_ul
MFLASH_DIR = $(USER_DIR)/mflash
MINIXZ_DIR = $(USER_DIR)/ext_libs/minixz
LIBMFA_DIR = $(USER_DIR)/libmfa
COMMON_DIR = $(USER_DIR)/common
LAYOUTS_DIR = $(USER_DIR)/tools_layouts


INCLUDES = -I. -I.. -I$(MTCR_DIR) -I$(MFLASH_DIR) -I$(LIBMFA_DIR) -I$(USER_DIR)/ext_libs/json -I$(MINIXZ_DIR)\
           -I$(COMMON_DIR) -I$(MFT_EXT_LIBS_INC_DIR)/zlib -I $(LAYOUTS_DIR) -I$(top_srcdir)/common

 
MLXFWOPS_VERSION = 1

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe -DNO_MFA_SUPPORT

lib_LTLIBRARIES = libmlxfwops.la

libmlxfwops_la_SOURCES = flint_base.cpp \
               flint_io.cpp \
               fw_ops.cpp \
               fs2_ops.cpp fs2_ops.h\
               fs3_ops.cpp fs3_ops.h\
               mlxfwops.cpp mlxfwops.h

mlxfwopsincludedir=$(includedir)/mft/mlxfwops
mlxfwopsinclude_HEADERS = mlxfwops_com.h mlxfwops.h fw_ops.h flint_base.h flint_io.h

