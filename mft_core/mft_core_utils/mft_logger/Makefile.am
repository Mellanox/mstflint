# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

# The MFT logger. Three convenience libraries plus the mstlogger_config CLI:
#
#   libmft_log_config.la     the JSON config file (reader + writer), shared by
#                            the runtime and the CLI so the two cannot drift
#   libmft_logger.la         the MftLogger singleton and the C ABI (spdlog)
#   libmft_log_config_ui.la  the mstlogger_config command line
#
# Sources include each other as "mft_logger/<file>.h" - the same spelling every
# consumer elsewhere in the tree uses - hence the -I on mft_core/mft_core_utils.
# $(top_builddir) is needed for common/tools_version.h, which common/ generates.

AM_CPPFLAGS = \
    -I$(top_srcdir) \
    -I$(top_builddir) \
    -I$(top_srcdir)/mft_core/mft_core_utils \
    $(JSON_CFLAGS)

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe -Werror $(COMPILER_FPIC)

# spdlog is header-only and third party: -isystem keeps -Werror from tripping
# over its headers. It is only needed by mft_logger.cpp.
SPDLOG_CXXFLAGS = -isystem $(top_srcdir)/ext_libs/spdlog/include -DSPDLOG_NO_THREAD_ID

# The bundled jsoncpp is a libtool convenience library, so its objects are
# already folded into .libs/libmft_logger.a and must not be linked twice into
# the .so. A system jsoncpp is a real shared library and still has to be named.
if USE_LOCAL_JSON
MFT_LOGGER_JSON_LIBS = $(top_builddir)/ext_libs/json/libjson.la
MFT_LOGGER_JSON_SO_LIBS =
else
MFT_LOGGER_JSON_LIBS = -ljsoncpp
MFT_LOGGER_JSON_SO_LIBS = -ljsoncpp
endif

OS_API_LA = $(top_builddir)/mft_core/mft_core_utils/operating_system_api/lib_os_api.la

noinst_LTLIBRARIES = libmft_log_config.la libmft_logger.la libmft_log_config_ui.la

libmft_log_config_la_SOURCES = \
    log_config.cpp \
    log_config.h \
    log_config_defs.h \
    layers.h
libmft_log_config_la_LIBADD = $(MFT_LOGGER_JSON_LIBS) -lstdc++

libmft_logger_la_SOURCES = \
    mft_logger.cpp \
    mft_logger.h \
    mft_logger_c.h
libmft_logger_la_CXXFLAGS = $(AM_CXXFLAGS) $(SPDLOG_CXXFLAGS)
libmft_logger_la_LDFLAGS = -pthread
libmft_logger_la_DEPENDENCIES = libmft_log_config.la $(OS_API_LA)
libmft_logger_la_LIBADD = libmft_log_config.la $(OS_API_LA) -lstdc++

libmft_log_config_ui_la_SOURCES = \
    log_config_ui.cpp \
    log_config_ui.h
libmft_log_config_ui_la_LIBADD = libmft_log_config.la -lstdc++

bin_PROGRAMS = mstlogger_config

mstlogger_config_SOURCES = main.cpp
mstlogger_config_DEPENDENCIES = \
    libmft_log_config_ui.la \
    libmft_log_config.la \
    $(top_builddir)/cmdparser/libcmdparser.a
mstlogger_config_LDADD = $(mstlogger_config_DEPENDENCIES) $(MFT_LOGGER_JSON_LIBS) -lstdc++
mstlogger_config_LDFLAGS = -static

# ---------------------------------------------------------------------------
# libmft_logger.so - the same logger exposed as a plain shared object so the
# Python facade can bind the mft_log C ABI through ctypes. Hand-rolled rather
# than a libtool lib_LTLIBRARIES, matching cmtcr.so / ccmdif.so / rreg_access.so
# elsewhere in the tree: one unversioned .so installed next to the module that
# loads it. --whole-archive is required because nothing in the .so references
# mft_log() - the ctypes caller does, at runtime. libtool has already folded
# log_config, lib_os_api and the bundled jsoncpp into .libs/libmft_logger.a,
# so that single archive is the whole logger.
MFT_LOGGER_SO = libmft_logger.so

$(MFT_LOGGER_SO): libmft_logger.la
	$(CXX) -shared -pthread $(CXXFLAGS) $(LDFLAGS) $(COMPILER_FPIC) -o $@ \
	  -Wl,--whole-archive .libs/libmft_logger.a -Wl,--no-whole-archive \
	  $(MFT_LOGGER_JSON_SO_LIBS) -lstdc++

all-local: $(MFT_LOGGER_SO)

CLEANFILES = $(MFT_LOGGER_SO)

mft_logger_pylibdir = $(libdir)/mstflint/python_tools/
mft_logger_pylib_DATA = $(MFT_LOGGER_SO)
dist_mft_logger_pylib_DATA = mft_logger_api.py
