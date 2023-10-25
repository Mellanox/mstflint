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
RESOURCE_DUMP_SRC_DIR = $(USER_DIR)/resourcetools/resourcedump_lib/src
RD_COMMON_DIR = $(RESOURCE_DUMP_SRC_DIR)/common
SEGMENTS_DIR = $(RESOURCE_DUMP_SRC_DIR)/segments
FETCHERS_DIR = $(RESOURCE_DUMP_SRC_DIR)/fetchers
MTCR_DIR = $(USER_DIR)/${MTCR_CONF_DIR}


AM_CPPFLAGS = -I$(USER_DIR) -I$(RD_COMMON_DIR) -I$(SEGMENTS_DIR) -I$(FETCHERS_DIR) -I$(MTCR_DIR)

lib_LTLIBRARIES = libresource_dump_commands.a

libresource_dump_commands_a_SOURCES =  resource_dump_command.h \
                                        resource_dump_command.cpp \
                                        dump_command.h \
                                        dump_command.cpp \
                                        query_command.h \
                                        query_command.cpp

libresource_dump_commands_a_CFLAGS = $(AM_CFLAGS) $(COMPILER_FPIC)
libresource_dump_commands_a_CXXFLAGS = $(AM_CXXFLAGS) $(COMPILER_FPIC)
