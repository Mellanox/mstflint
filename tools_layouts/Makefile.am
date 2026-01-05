#--
# Copyright (c) 2004-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#--

# Makefile.am -- Process this file with automake to produce Makefile.in
AM_CPPFLAGS = -I$(top_srcdir)/${MTCR_CONFIG_DIR} -I$(top_srcdir)/common
AM_CFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)
AM_CXXFLAGS =  -DDATA_PATH=\"$(pkgdatadir)\"

SUBDIRS = ${ADABE_DBS}

noinst_LTLIBRARIES = libadb_utils.la libtools_layouts.la libmlxarchive_layouts.la libcables_layouts.la

toolslayoutsincludedir = $(includedir)/mstflint/tools_layouts/

toolslayoutsinclude_HEADERS = icmd_layouts.h icmd_hca_layouts.h adb_to_c_utils.h
libadb_utils_la_SOURCES = adb_to_c_utils.c

libtools_layouts_la_SOURCES = prm_adb_db.cpp prm_adb_db.h \
				adb_to_c_utils.c adb_to_c_utils.h\
				cibfw_layouts.c cibfw_layouts.h \
				register_access_open_layouts.h register_access_open_layouts.c \
				tools_open_layouts.c tools_open_layouts.h\
				register_access_sib_layouts.h register_access_sib_layouts.c \
				cx4fw_layouts.c cx4fw_layouts.h \
				image_layout_layouts.c image_layout_layouts.h\
				cx6fw_layouts.c cx6fw_layouts.h\
				icmd_layouts.c icmd_layouts.h \
				icmd_hca_layouts.c icmd_hca_layouts.h \
				reg_access_hca_layouts.c reg_access_hca_layouts.h\
				image_info_layouts.c image_info_layouts.h \
				reg_access_switch_layouts.c reg_access_switch_layouts.h \
				fs5_image_layout_layouts.h fs5_image_layout_layouts.c \
				tokens_layout_layouts.c tokens_layout_layouts.h

libtools_layouts_la_DEPENDENCIES = libadb_utils.la
libmlxarchive_layouts_la_DEPENDENCIES = $(libtools_layouts_la_DEPENDENCIES)
libmlxarchive_layouts_la_LIBADD = $(libtools_layouts_la_LIBADD)
libmlxarchive_layouts_la_SOURCES = mlxarchive_layouts.h mlxarchive_layouts.c

libcables_layouts_la_SOURCES = cables_layouts.h cables_layouts.c
libcables_layouts_la_DEPENDENCIES = $(libtools_layouts_la_DEPENDENCIES)
libcables_layouts_la_LIBADD = $(libtools_layouts_la_DEPENDENCIES)

EXTRA_DIST = ${ADABE_DBS_EXTRA_DIST}
