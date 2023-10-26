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
USER_DIR = $(top_srcdir)
RESOURCE_DUMP_SRC_DIR = $(USER_DIR)/resourcetools/resourcedump_lib/src
RD_COMMON_DIR = $(RESOURCE_DUMP_SRC_DIR)/common
SEGMENTS_DIR = $(RESOURCE_DUMP_SRC_DIR)/segments
FETCHERS_DIR = $(RESOURCE_DUMP_SRC_DIR)/fetchers
MTCR_DIR = $(USER_DIR)/${MTCR_CONF_DIR}
MTCR_INC_DIR = $(top_srcdir)/include/mtcr_ul

AM_CPPFLAGS = -I$(USER_DIR) -I$(RD_COMMON_DIR) -I$(SEGMENTS_DIR) -I$(FETCHERS_DIR) -I$(MTCR_DIR) -I$(MTCR_INC_DIR)

lib_LTLIBRARIES = libresource_dump_commands.la

libresource_dump_commands_la_SOURCES =  resource_dump_command.h \
                                        resource_dump_command.cpp \
                                        dump_command.h \
                                        dump_command.cpp \
                                        query_command.h \
                                        query_command.cpp

libresource_dump_commands_la_CFLAGS = $(AM_CFLAGS) $(COMPILER_FPIC)
libresource_dump_commands_la_CXXFLAGS = $(AM_CXXFLAGS) $(COMPILER_FPIC)
