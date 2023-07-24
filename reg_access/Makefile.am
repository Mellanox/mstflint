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
MTCR_DIR = $(top_srcdir)/${MTCR_CONF_DIR}
COMMON_DIR = $(top_srcdir)/common
LAYOUTS_DIR = $(top_srcdir)/tools_layouts
USER_DIR = $(top_srcdir)

AM_CPPFLAGS = -I. -I$(USER_DIR) -I$(srcdir) -I$(LAYOUTS_DIR) -I$(USER_DIR)/include/mtcr_ul

AM_CFLAGS = -W -Wall -g -MP -MD $(COMPILER_FPIC)

lib_LTLIBRARIES = libreg_access.a libmlxconfig_4th_gen_regsiters.a

libreg_access_a_SOURCES = reg_access.c reg_access.h reg_access_common.h reg_access_macros.h
libreg_access_a_DEPENDENCIES = $(USER_DIR)/tools_layouts/libtools_layouts.a
libreg_access_a_LIBADD = $(libreg_access_a_DEPENDENCIES)

libmlxconfig_4th_gen_regsiters_a_SOURCES = mlxconfig_4th_gen_registers.c mlxconfig_4th_gen_registers.h
libmlxconfig_4th_gen_regsiters_a_DEPENDENCIES = $(USER_DIR)/tools_layouts/libmlxconfig_4th_gen_layouts.a
libmlxconfig_4th_gen_regsiters_a_LIBADD = $(libmlxconfig_4th_gen_regsiters_la_DEPENDENCIES)
RREG_ACCESS_SO = rreg_access.so
reg_access_pylibdir = $(libdir)/mstflint/python_tools/

reg_access_pylib_DATA = ${RREG_ACCESS_SO} regaccess.py regaccess_structs.py
dist_reg_access_pylib_DATA = regaccess.py regaccess_structs.py

${RREG_ACCESS_SO}: libreg_access.a
	$(CC) -g -Wall -pthread -shared ${CFLAGS} *.o -o ${RREG_ACCESS_SO} \
	-L$(USER_DIR)/tools_layouts -ltools_layouts -lmlxconfig_4th_gen_layouts -L$(MTCR_DIR) -lmtcr_ul

CLEANFILES = ${RREG_ACCESS_SO}
