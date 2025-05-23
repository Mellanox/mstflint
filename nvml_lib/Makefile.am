# Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

AM_CPPFLAGS = \
    -I$(srcdir) \
    -I$(top_srcdir)

AM_CXXFLAGS = -Wall -W -g -MP -MD  -pipe $(COMPILER_FPIC)
AM_CFLAGS = -Wall -W -g -MP -MD  -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES = libnvml_device.la

libnvml_device_la_SOURCES = \
    nvml_device.cpp \
    nvml_exception.cpp \
    nvml_lib_wrapper.cpp \
    nvml_c_wrapper.cpp \
    $(top_builddir)/tools_layouts/reg_access_gpu_layouts.c \
    $(top_builddir)/tools_layouts/reg_access_hca_layouts.c

libnvml_device_la_DEPENDENCIES = $(top_builddir)/tools_layouts/libadb_utils.la
libnvml_device_la_LIBADD = $(libnvml_device_la_DEPENDENCIES)
libnvml_device_la_LDFLAGS = -static