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
# USER_DIR = $(top_srcdir)
# COMMON_DIR = $(USER_DIR)/common
# MTCR_DIR = $(USER_DIR)/${MTCR_CONFIG_DIR}
# UTILS_DIR = $(USER_DIR)/mft_utils

# AM_CFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"
# AM_CXXFLAGS = -Wall -W -MP -MD -pipe -Werror $(COMPILER_FPIC)

noinst_LTLIBRARIES = libresource_dump_common.la

libresource_dump_common_la_SOURCES =    resource_dump_error_handling.h \
                                        resource_dump_error_handling.cpp resource_dump_constants.h
libresource_dump_common_la_CFLAGS = $(AM_CFLAGS) $(COMPILER_FPIC) -I$(top_srcdir)/include/mtcr_ul
libresource_dump_common_la_CXXFLAGS = $(AM_CXXFLAGS) $(COMPILER_FPIC) -I$(top_srcdir)/include/mtcr_ul


libresource_dump_common_la_DEPENDENCIES = $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la
libresource_dump_common_la_LIBADD = $(libresource_dump_common_la_DEPENDENCIES)
