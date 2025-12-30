#
# Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
MFT_CORE_DIR = $(USER_DIR)/mft_core
OS_DIR = $(MFT_CORE_DIR)/mft_core_utils/operating_system_api
LOG_DIR = $(MFT_CORE_DIR)/mft_core_utils/logger
AM_CPPFLAGS = -I. -I$(OS_DIR) -I$(LOG_DIR)

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe -Werror $(COMPILER_FPIC)

noinst_LTLIBRARIES = libmftexceptions.la

libmftexceptions_la_SOURCES = MftGeneralException.h MftGeneralException.cpp

libmftexceptions_la_DEPENDENCIES = $(OS_DIR)/lib_os_api.la
libmftexceptions_la_LIBADD = $(LIBSTD_CPP_SO) $(libmftexceptions_la_DEPENDENCIES)
