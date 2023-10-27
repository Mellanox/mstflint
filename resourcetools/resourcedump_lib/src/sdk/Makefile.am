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

USER_DIR = $(top_srcdir)
MTCR_DIR = $(USER_DIR)/${MTCR_CONF_DIR}
TOOLS_LAYOUT_DIR = $(USER_DIR)/tools_layouts
REG_ACCESS_DIR = $(USER_DIR)/reg_access
RESOURCE_DUMP_SRC_DIR = $(USER_DIR)/resourcetools/resourcedump_lib/src
RD_COMMON_DIR = $(RESOURCE_DUMP_SRC_DIR)/common
SEGMENTS_DIR = $(RESOURCE_DUMP_SRC_DIR)/segments
FILTERS_DIR = $(RESOURCE_DUMP_SRC_DIR)/filters
FETCHERS_DIR = $(RESOURCE_DUMP_SRC_DIR)/fetchers
COMMANDS_DIR = $(RESOURCE_DUMP_SRC_DIR)/commands
# COMMON_DIR = $(USER_DIR)/common

AM_CPPFLAGS = -I$(USER_DIR) -I$(RD_COMMON_DIR) -I$(SEGMENTS_DIR) -I$(FILTERS_DIR) -I$(FETCHERS_DIR) -I$(COMMANDS_DIR)

noinst_LTLIBRARIES = libresource_dump_sdk.la

libresource_dump_sdk_la_SOURCES = resource_dump_sdk.h resource_dump_sdk.cpp
libresource_dump_sdk_la_CFLAGS = $(AM_CFLAGS) $(COMPILER_FPIC)
libresource_dump_sdk_la_CXXFLAGS = $(AM_CXXFLAGS) $(COMPILER_FPIC)

resource_dump_sdk_sodir = $(libdir)/mstflint/sdk
# if !WIN_BUILD
resource_dump_sdk_so_DATA = libresource_dump_sdk.so
# else
# resource_dump_sdk_so_DATA = libresource_dump_sdk.dll
# endif

libraryincludedir=$(includedir)/mstflint/sdk/
libraryinclude_HEADERS = resource_dump_sdk.h $(SEGMENTS_DIR)/resource_dump_segments.h $(SEGMENTS_DIR)/resource_dump_segments_le.h $(SEGMENTS_DIR)/resource_dump_segments_be.h $(RD_COMMON_DIR)/resource_dump_types.h

# if WIN_BUILD
# MTCR_LIB = $(MTCR_DIR)/.libs/libmtcr.dll.a
# else
MTCR_LIB = -L$(MTCR_DIR)/ -lmtcr_ul
# endif

if ENABLE_RDMEM
OFED_LIBS = -libverbs -lmlx5
else
OFED_LIBS =
endif

resource_dump_sdk_so_DEPS = \
    $(COMMANDS_DIR)/.libs/libresource_dump_commands.a \
    $(FETCHERS_DIR)/.libs/libreg_access_resource_dump_fetcher.a \
    $(FILTERS_DIR)/.libs/libresource_dump_filters.a \
    $(RD_COMMON_DIR)/.libs/libresource_dump_common.a \
    $(REG_ACCESS_DIR)/.libs/libreg_access.a \
    $(TOOLS_LAYOUT_DIR)/.libs/libtools_layouts.a \
    $(MTCR_LIB) \
    $(OFED_LIBS) \
    -lstdc++

# if !WIN_BUILD
libresource_dump_sdk.so: libresource_dump_sdk.la
	$(CC) -Wall -pthread -shared ${CFLAGS} $(COMPILER_FPIC) libresource_dump_sdk_la-resource_dump_sdk.o \
	-o libresource_dump_sdk.so ${AM_LDFLAGS} $(resource_dump_sdk_so_DEPS)
# else
# libresource_dump_sdk.dll: libresource_dump_sdk.la
# 	$(CC) -Wall -pthread -shared -Wl,--no-undefined,--enable-runtime-pseudo-reloc ${CFLAGS} $(COMPILER_FPIC) libresource_dump_sdk_la-resource_dump_sdk.o \
# 	-o libresource_dump_sdk.dll ${AM_LDFLAGS} $(resource_dump_sdk_so_DEPS) -lws2_32
# endif

CLEANFILES = $(resource_dump_sdk_so_DATA)
