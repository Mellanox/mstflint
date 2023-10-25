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
MTCR_DIR = $(USER_DIR)/${MTCR_CONF_DIR}
RESOURCE_DUMP_SRC_DIR = $(USER_DIR)/resourcetools/resourcedump_lib/src
RD_COMMON_DIR = $(RESOURCE_DUMP_SRC_DIR)/common
SEGMENTS_DIR = $(RESOURCE_DUMP_SRC_DIR)/segments
REG_ACCESS_DIR = $(USER_DIR)/reg_access
TOOLS_LAYOUT_DIR = $(USER_DIR)/tools_layouts

AM_CPPFLAGS = -I$(USER_DIR) -I$(MTCR_DIR) -I$(TOOLS_LAYOUT_DIR) -I$(REG_ACCESS_DIR) -I$(RD_COMMON_DIR) -I$(SEGMENTS_DIR)

# AM_CFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"
# AM_CXXFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC)

lib_LTLIBRARIES = libreg_access_resource_dump_fetcher.a

libreg_access_resource_dump_fetcher_a_SOURCES = \
    fetcher.h fetcher_factory.h fetcher_factory.cpp\
    reg_access_resource_dump_fetcher.h reg_access_resource_dump_fetcher.cpp
if ENABLE_RDMEM
libreg_access_resource_dump_fetcher_a_SOURCES += \
    reg_access_resource_dump_mkey_fetcher.h reg_access_resource_dump_mkey_fetcher.cpp
endif


libreg_access_resource_dump_fetcher_a_CFLAGS = $(AM_CFLAGS) $(COMPILER_FPIC)
libreg_access_resource_dump_fetcher_a_CXXFLAGS = $(AM_CXXFLAGS) $(COMPILER_FPIC)
