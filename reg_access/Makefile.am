#--
#                 - Mellanox Confidential and Proprietary -
# 
# Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
# 
# Except as specifically permitted herein, no portion of the information,
# including but not limited to object code and source code, may be reproduced,
# modified, distributed, republished or otherwise exploited in any form or by
# any means for any purpose without the prior written permission of Mellanox
# Technologies Ltd. Use of software subject to the terms and conditions
# detailed in the file "LICENSE.txt".
#--

# Makefile.am -- Process this file with automake to produce Makefile.in
MTCR_DIR = $(top_srcdir)/mtcr_ul
COMMON_DIR = $(top_srcdir)/common
LAYOUTS_DIR = $(top_srcdir)/tools_layouts
USER_DIR = $(top_srcdir)

INCLUDES = -I. -I$(USER_DIR) -I$(srcdir) -I$(LAYOUTS_DIR) -I$(USER_DIR)/include/mtcr_ul

AM_CFLAGS = -W -Wall -Werror -g -MP -MD $(COMPILER_FPIC)

noinst_LIBRARIES = libreg_access.a

libreg_access_a_SOURCES = reg_access.c
libreg_access_a_DEPENDENCIES = $(USER_DIR)/tools_layouts/libtools_layouts.a
libreg_access_a_LIBADD = $(libreg_access_a_DEPENDENCIES)

