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

# Makefile.am -- Process this file with automake to produce Makefile.in
USER_DIR = $(top_srcdir)
#MTCR_DIR = $(USER_DIR)/${MTCR_CONFIG_DIR}
RESOURCE_DUMP_SRC_DIR = $(USER_DIR)/resourcetools/resourcedump_lib/src
RD_COMMON_DIR = $(RESOURCE_DUMP_SRC_DIR)/common
COMMANDS_DIR = $(RESOURCE_DUMP_SRC_DIR)/commands
FETCHERS_DIR = $(RESOURCE_DUMP_SRC_DIR)/fetchers
SEGMENTS_DIR = $(RESOURCE_DUMP_SRC_DIR)/segments
#REG_ACCESS_DIR = $(USER_DIR)/reg_access
#TOOLS_LAYOUT_DIR = $(USER_DIR)/tools_layout

AM_CPPFLAGS = -I$(USER_DIR) -I$(COMMANDS_DIR) -I$(FETCHERS_DIR) -I$(RD_COMMON_DIR) -I$(SEGMENTS_DIR)

# AM_CFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"
# AM_CXXFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC)

lib_LTLIBRARIES = libresource_dump_filters.a

libresource_dump_filters_a_SOURCES =   filter.h \
                                        filter.cpp \
                                        include_exclude_segments_filter.h \
                                        include_exclude_segments_filter.cpp \
                                        strip_control_segments_filter.h \
                                        strip_control_segments_filter.cpp

libresource_dump_filters_a_CFLAGS = $(AM_CFLAGS) $(COMPILER_FPIC)
libresource_dump_filters_a_CXXFLAGS = $(AM_CXXFLAGS) $(COMPILER_FPIC)
