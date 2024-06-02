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

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/include/mtcr_ul -I$(top_srcdir)/common -I$(top_srcdir)/dev_mgt

pkglib_LTLIBRARIES = libmtcr_ul.la

libmtcr_ul_la_SOURCES = mtcr_ul.c mtcr_ib.h  mtcr_int_defs.h\
			mtcr_ib_res_mgt.h mtcr_ib_res_mgt.c\
			mtcr_tools_cif.c mtcr_tools_cif.h\
			mtcr_ul_icmd_cif.c mtcr_icmd_cif.h\
			mtcr_mem_ops.c mtcr_mem_ops.h\
			mtcr_ul_com_defs.h mtcr_mf.h\
			mtcr_ul_com.h mtcr_ul_com.c\
			packets_common.c packets_common.h\
			packets_layout.c packets_layout.h \
			fwctrl.c fwctrl.h fwctrl_ioctl.h
libmtcr_ul_la_CFLAGS = -W -Wall -g -MP -MD -fPIC -DMTCR_API="" -DMST_UL

if ENABLE_INBAND
libmtcr_ul_la_SOURCES += mtcr_ib_ofed.c
endif

libraryincludedir=$(includedir)/mstflint
libraryinclude_HEADERS = $(top_srcdir)/include/mtcr_ul/mtcr.h  $(top_srcdir)/include/mtcr_ul/mtcr_com_defs.h  $(top_srcdir)/include/mtcr_ul/mtcr_mf.h
