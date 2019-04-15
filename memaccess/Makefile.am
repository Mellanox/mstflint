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
USER_DIR = ..
MTCR_CONFIG_DIR=include/mtcr_ul/
INCLUDES = -I. -I$(USER_DIR) -I../common -I../${MTCR_CONFIG_DIR}

AM_CPPFLAGS = -W  -g -MP -MD -Werror $(COMPILER_FPIC)

lib_LTLIBRARIES = libmemaccess.a

libmemaccess_a_SOURCES = qpcaccess.c

libraryincludedir=$(includedir)/mstflint/memaccess/

libraryinclude_HEADERS = qpcaccess.h

