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

AM_CPPFLAGS = \
    -I$(srcdir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONFIG_DIR} \
    -I$(top_srcdir)/common -I$(top_builddir)/common \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxsign_lib

XML_FLAGS = -DUSE_XML -DLIBXML_STATIC

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) $(XML_FLAGS)

noinst_LIBRARIES = libmstdpa.a

libmstdpa_a_SOURCES = \
    certcontainerbase.cpp \
    certcontainerbase.h \
    certcontainerimp.cpp \
    certcontainerimp.h

libmstdpa_a_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) $(XML_FLAGS)

libmstdpa_a_DEPENDENCIES = $(top_builddir)/mft_utils/libmftutils.la

libmstdpa_a_LIBADD = $(libmstdpa_a_DEPENDENCIES)

bin_PROGRAMS = mstdpa

mstdpa_SOURCES = \
    certcontainerbase.cpp \
    certcontainerbase.h \
    certcontainerimp.cpp \
    certcontainerimp.h \
    cryptodata.cpp \
    cryptodata.h \
    hostelf.cpp \
    hostelf.h \
    mlxdpa.cpp \
    mlxdpa.h \
    mlxdpa_utils.cpp \
    mlxdpa_utils.h

mstdpa_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) $(XML_FLAGS)

mstdpa_LDADD = \
    $(top_builddir)/cmdparser/libcmdparser.a \
    $(top_builddir)/mlxsign_lib/libmlxsign.la \
    $(top_builddir)/mft_utils/libmftutils.la

# these are precompiled
if ARM64_BUILD
mstdpa_LDADD += $(srcdir)/dpa_elf/arm64/libdpa_elf
endif
if X86_64_BUILD
mstdpa_LDADD += $(srcdir)/dpa_elf/x86_64/libdpa_elf
endif

if ENABLE_OPENSSL
mstdpa_LDADD += -lcrypto -lssl
else
mstdpa_CXXFLAGS += -DNO_OPEN_SSL
endif
