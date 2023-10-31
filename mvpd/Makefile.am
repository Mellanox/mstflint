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

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/tools_layouts -I$(top_srcdir)/include/mtcr_ul -I$(top_srcdir)/dev_mgt

AM_CFLAGS = -W -Wall -g -MP -MD $(COMPILER_FPIC)

noinst_LTLIBRARIES = libmvpd.la

libmvpd_la_SOURCES =  mvpd.c mvpd.h

libmvpd_la_DEPENDENCIES = $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la
libmvpd_la_LIBADD = $(libmvpd_la_DEPENDENCIES)

RMVPD_SO = rmvpd.so

noinst_HEADERS = mvpd.h

${RMVPD_SO}: libmvpd.la
	$(CC) -g -Wall -pthread -shared ${CFLAGS} *.o -o ${RMVPD_SO} \
	 $(top_builddir)/${MTCR_CONF_DIR}/.libs/libmtcr_ul.a

CLEANFILES = ${RMVPD_SO}
