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

SUBDIRS = printutil
USER_DIR = $(top_srcdir)
COMMON_DIR = $(top_srcdir)/common
MTCR_DIR = $(top_srcdir)/${MTCR_CONF_DIR}
MTCR_INC_DIR = $(top_srcdir)/include/mtcr_ul
UTILS_DIR = $(top_srcdir)/mft_utils
MLXREG_DIR = $(top_srcdir)/mlxreg
MLXLINK_MODULES_DIR = $(top_srcdir)/mlxlink

AM_CPPFLAGS = \
    -I$(srcdir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxlink \
    -I$(top_srcdir)/mlxreg

AM_CPPFLAGS += $(JSON_CFLAGS)

AM_CFLAGS = -Wall -W -g -MP -MD -pipe  $(COMPILER_FPIC) -DDATA_PATH=\"$(pkgdatadir)\"
AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe #$(COMPILER_FPIC)

noinst_LTLIBRARIES = libmodules_lib.la

libmodules_lib_la_SOURCES = \
    amber_field.cpp \
    amber_field.h \
    mlxlink_amBER_collector.cpp \
    mlxlink_amBER_collector.h \
    mlxlink_cables_commander.cpp \
    mlxlink_cables_commander.h \
    mlxlink_commander.cpp \
    mlxlink_commander.h \
    mlxlink_enums.h \
    mlxlink_err_inj_commander.cpp \
    mlxlink_err_inj_commander.h \
    mlxlink_eye_opener.cpp \
    mlxlink_eye_opener.h \
    mlxlink_maps.cpp \
    mlxlink_maps.h \
    mlxlink_port_info.cpp \
    mlxlink_port_info.h \
    mlxlink_reg_parser.cpp \
    mlxlink_reg_parser.h \
    mlxlink_ui.cpp \
    mlxlink_ui.h \
    mlxlink_user_input.cpp \
    mlxlink_user_input.h \
    mlxlink_utils.cpp \
    mlxlink_utils.h

libmodules_lib_la_LIBADD = \
    $(top_builddir)/mlxlink/modules/printutil/libprint_util_lib.la \
    $(JSON_LIBS)
