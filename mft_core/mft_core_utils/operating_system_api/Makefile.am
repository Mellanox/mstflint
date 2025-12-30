#
# Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

USER_DIR = $(top_srcdir)
AM_CPPFLAGS = -I. -I$(USER_DIR)/common

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe -Werror $(COMPILER_FPIC)

noinst_LTLIBRARIES = lib_os_api.la

lib_os_api_la_SOURCES = OperatingSystemAPI.h OperatingSystemAPIDefs.h FactoryOperatingSystemAPI.cpp FactoryOperatingSystemAPI.h
lib_os_api_la_SOURCES += Linux.cpp Linux.h

lib_os_api_la_DEPENDENCIES =
lib_os_api_la_LIBADD = $(LIBSTD_CPP_SO) -lstdc++
