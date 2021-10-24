#
# Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software product is a proprietary product of Nvidia Corporation and its affiliates
# (the "Company") and all right, title, and interest in and to the software
# product, including all associated intellectual property rights, are and
# shall remain exclusively with the Company.
#
# This software product is governed by the End User License Agreement
# provided with the software product.
#

# Makefile.am -- Process this file with automake to produce Makefile.in

DIST_SUBDIRS = .

USER_DIR = ..
INCLUDES = -I$(USER_DIR) -I$(USER_DIR)/common
AM_CXXFLAGS = -Wall -W -g -MP -MD -Werror -pipe $(COMPILER_FPIC)

lib_LTLIBRARIES = libadb_parser.a
libadb_parser_a_SOURCES = buf_ops.cpp expr.cpp adb_expr.cpp adb_parser.cpp adb_db.cpp adb_config.cpp adb_exceptionHolder.cpp adb_field.cpp adb_instance.cpp adb_logfile.cpp adb_node.cpp adb_xmlCreator.cpp
