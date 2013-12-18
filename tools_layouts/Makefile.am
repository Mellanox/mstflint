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
USER_DIR = ..
MTCR_DIR = $(USER_DIR)/mtcr_ul
INCLUDES = -I$(USER_DIR) -I$(MTCR_DIR) -I$(USER_DIR)/common #-I$(MFT_EXT_LIBS_INC_DIR)
AM_CFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) 
lib_LTLIBRARIES = libtools_layouts.la

libraryincludedir=$(includedir)/mstmft/tools_layouts/

libraryinclude_HEADERS = adb_to_c_utils.h cibfw_layouts.h

libtools_layouts_la_SOURCES = cibfw_layouts.c adb_to_c_utils.c
#libtools_layouts_la_DEPENDENCIES = $(USER_DIR)/xz_utils/libxz_utils.la $(USER_DIR)/tools_crypto/libtools_crypto.la
#libtools_layouts_la_LIBADD = $(USER_DIR)/xz_utils/libxz_utils.la $(USER_DIR)/tools_crypto/libtools_crypto.la $(WS2_LIB)

