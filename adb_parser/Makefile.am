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

DIST_SUBDIRS = .

USER_DIR = ..
INCLUDES = -I$(USER_DIR) -I$(USER_DIR)/common
AM_CXXFLAGS = -Wall -W -g -MP -MD -Werror -pipe $(COMPILER_FPIC)

lib_LTLIBRARIES = libadb_parser.a
libadb_parser_a_SOURCES = adb_parser.h adb_parser.cpp buf_ops.h buf_ops.cpp expr.h expr.cpp adb_expr.h adb_expr.cpp adb_db.h adb_db.cpp
libadb_parser_a_LIBADD = -lexpat -lboost_regex -lboost_filesystem -lboost_system 
