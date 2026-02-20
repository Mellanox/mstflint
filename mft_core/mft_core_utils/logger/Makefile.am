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

AM_CPPFLAGS = -I$(top_srcdir)

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe -Werror $(COMPILER_FPIC)

noinst_LTLIBRARIES = liblogger.la

liblogger_la_SOURCES = Logger.cpp Logger.h LoggerDefs.h

liblogger_la_DEPENDENCIES = ../operating_system_api/lib_os_api.la
liblogger_la_LIBADD = $(LIBSTD_CPP_SO) $(liblogger_la_DEPENDENCIES) -lstdc++