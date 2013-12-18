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
#        disclaimer in the documentation and/or othint2_oem.er materials
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
COMMON_DIR = $(USER_DIR)/common
LAYOUTS_DIR = $(USER_DIR)/tools_layouts
LAYOUTS_LIB = $(LAYOUTS_DIR)/libtools_layouts.la



INCLUDES = -I. -I.. -I$(MTCR_DIR) -I../mflash -I$(COMMON_DIR) \
           -I $(LAYOUTS_DIR) $(ZLIB_INC) -I$(MFT_EXT_LIBS_INC_DIR)/zlib

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe 
bin_PROGRAMS = mstflint

mstflint_SOURCES = flint.cpp flint.h subcommands.cpp subcommands.h\
					flint_params.cpp flint_params.h cmd_line_parser.cpp err_msgs.h

mstflint_LDADD =  ../mlxfwops/lib/libmlxfwops.la  ../cmdparser/libcmdparser.la ../mflash/libmflash.la $(MTCR_DIR)/libmtcr_ul.a $(ZLIB_LIB) $(LAYOUTS_LIB) $(LIBSTD_CPP) -ldl

mstflintinclude_HEADERS = $(top_srcdir)/include/mtcr_ul/mtcr.h
mstflintincludedir = @includedir@/mtcr_ul
