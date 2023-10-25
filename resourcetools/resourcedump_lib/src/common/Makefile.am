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
# USER_DIR = $(top_srcdir)
# COMMON_DIR = $(USER_DIR)/common
# MTCR_DIR = $(USER_DIR)/${MTCR_CONFIG_DIR}
# UTILS_DIR = $(USER_DIR)/mft_utils

# AM_CFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"
# AM_CXXFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC)

lib_LTLIBRARIES =                       libresource_dump_common.a

libresource_dump_common_a_SOURCES =    resource_dump_error_handling.h \
                                        resource_dump_error_handling.cpp resource_dump_constants.h
libresource_dump_common_a_CFLAGS = $(AM_CFLAGS) $(COMPILER_FPIC)
libresource_dump_common_a_CXXFLAGS = $(AM_CXXFLAGS) $(COMPILER_FPIC)


