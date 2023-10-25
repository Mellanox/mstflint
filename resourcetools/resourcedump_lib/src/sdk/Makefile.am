#
# Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software product is a proprietary product of Nvidia Corporation and its affiliates
# (the "Company") and all right, title, and interest in and to the software
# product, including all associated intellectual property rights, are and
# shall remain exclusively with the Company.
#
# This software product is governed by the End User License Agreement
# provided with the software product.
#

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

lib_LTLIBRARIES = libresource_dump_sdk.a

libresource_dump_sdk_a_SOURCES = resource_dump_sdk.h resource_dump_sdk.cpp
libresource_dump_sdk_a_CFLAGS = $(AM_CFLAGS) $(COMPILER_FPIC)
libresource_dump_sdk_a_CXXFLAGS = $(AM_CXXFLAGS) $(COMPILER_FPIC)

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

resource_dump_sdk_so_DEPS = -L$(COMMANDS_DIR)/ -lresource_dump_commands \
	-L$(FETCHERS_DIR)/ -lreg_access_resource_dump_fetcher \
	-L$(FILTERS_DIR)/ -lresource_dump_filters \
	-L$(RD_COMMON_DIR)/ -lresource_dump_common \
	-L$(REG_ACCESS_DIR)/ -lreg_access \
	-L$(TOOLS_LAYOUT_DIR)/ -ltools_layouts \
	$(MTCR_LIB) \
	$(OFED_LIBS) \
	-lstdc++

# if !WIN_BUILD
libresource_dump_sdk.so: libresource_dump_sdk.a
	$(CC) -Wall -pthread -shared ${CFLAGS} $(COMPILER_FPIC) libresource_dump_sdk_a-resource_dump_sdk.o \
	-o libresource_dump_sdk.so ${AM_LDFLAGS} $(resource_dump_sdk_so_DEPS)
# else
# libresource_dump_sdk.dll: libresource_dump_sdk.la
# 	$(CC) -Wall -pthread -shared -Wl,--no-undefined,--enable-runtime-pseudo-reloc ${CFLAGS} $(COMPILER_FPIC) libresource_dump_sdk_la-resource_dump_sdk.o \
# 	-o libresource_dump_sdk.dll ${AM_LDFLAGS} $(resource_dump_sdk_so_DEPS) -lws2_32
# endif

CLEANFILES = $(resource_dump_sdk_so_DATA)
