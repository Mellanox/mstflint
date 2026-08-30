# Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mft_core/mft_core_utils \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxlink \
    -I$(top_srcdir)/mlxreg

AM_CPPFLAGS += $(JSON_CFLAGS)

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

EXTRA_DIST = README.md

# Optional, flag-gated dependencies. The SDK source gates its use of these
# subsystems on the same ENABLE_* macros, so the library is self-consistent
# whether or not the features are configured in.
if ENABLE_VFIO
VFIO_LIBADD = $(top_builddir)/vfio_driver_access/libvfio_access_driver.la
endif

if ENABLE_NVML
NVML_LIBADD = \
    $(top_builddir)/mft_core/device/nvml/libnvml_discovery.la \
    $(top_builddir)/mft_core/mft_core_utils/load_shared_library/libload_shared_library.la
endif

# Self-contained SDK shared object: mstflint's counterpart of libmft_sdk.so.
sdklibdir = $(libdir)/mstflint/sdk
sdklib_LTLIBRARIES = libmstflint_sdk.la

libmstflint_sdk_la_SOURCES = \
    mft_sdk_class.cpp \
    mft_sdk_cr_space_access.cpp \
    mft_sdk_discovery.cpp \
    mft_sdk_errors.cpp \
    mft_sdk_hca_caps.cpp \
    mft_sdk_i2c_access.cpp \
    mft_sdk_reg_access.cpp \
    mft_sdk_telemetry.cpp \
    mft_sdk.h \
    mft_sdk_class.hpp \
    mft_sdk_cr_space_access.h \
    mft_sdk_discovery.h \
    mft_sdk_errors.h \
    mft_sdk_hca_caps.h \
    mft_sdk_i2c_access.h \
    mft_sdk_query.h \
    mft_sdk_reg_access.h \
    mft_sdk_telemetry.h \
    mft_sdk_telemetry_types.h \
    mft_sdk_types.h

libmstflint_sdk_la_CXXFLAGS = $(AM_CXXFLAGS) $(COMPILER_FPIC)
libmstflint_sdk_la_LDFLAGS = -shared -avoid-version -Wl,-soname,libmstflint_sdk.so -Wl,--allow-multiple-definition

libmstflint_sdk_la_LIBADD = \
    $(top_builddir)/hca_capabilities/libhca_capabilities.la \
    $(top_builddir)/mlxreg/mlxreg_sdk/libmlxreg_sdk.la \
    $(top_builddir)/mlxlink/modules/libmodules_lib.la \
    $(MSTREG_SDK_WHOLE_ARCHIVE) \
    $(top_builddir)/mft_utils/libmftutils.la \
    $(MTCR_SDK_WHOLE_ARCHIVE) \
    $(top_builddir)/adb_parser/libadb_parser.la \
    $(top_builddir)/cmdif/libcmdif.la \
    $(top_builddir)/dev_mgt/libdev_mgt.la \
    $(top_builddir)/tools_layouts/libtools_layouts.la \
    $(top_builddir)/xz_utils/libxz_utils.la \
    $(top_builddir)/ext_libs/minixz/libminixz.la \
    $(top_builddir)/common/libcommon.la \
    $(top_builddir)/pci_library/libpci_library.la \
    $(top_builddir)/reg_access/libreg_access.la \
    $(top_builddir)/mft_core/mft_core_utils/operating_system_api/lib_os_api.la \
    $(top_builddir)/mft_core/mft_core_utils/logger/liblogger.la \
    $(top_builddir)/mft_core/mft_core_utils/mft_exceptions/libmftexceptions.la \
    $(top_builddir)/cmdparser/libcmdparser.a \
    $(VFIO_LIBADD) \
    $(NVML_LIBADD) \
    $(liblzma_LIBS) \
    $(expat_LIBS) \
    $(LDL)

# Public SDK headers. Kept under the mstflint include tree (to avoid clashing
# with an MFT-provided $(includedir)/mft_sdk), but inside an mft_sdk/ subdir so
# consumers use `#include <mft_sdk/...>` (with -I$(includedir)/mstflint/sdk) --
# consistent with MFT and with the headers' own internal <mft_sdk/...> includes.
sdkincludedir = $(includedir)/mstflint/sdk/mft_sdk
sdkinclude_HEADERS = \
    mft_sdk.h \
    mft_sdk_cr_space_access.h \
    mft_sdk_discovery.h \
    mft_sdk_errors.h \
    mft_sdk_hca_caps.h \
    mft_sdk_i2c_access.h \
    mft_sdk_query.h \
    mft_sdk_reg_access.h \
    mft_sdk_telemetry.h \
    mft_sdk_telemetry_types.h \
    mft_sdk_types.h

# pkg-config metadata so consumers can build against the SDK with
# `pkg-config --cflags --libs mstflint_sdk`. Installed to the conventional
# $(libdir)/pkgconfig, generated from mstflint_sdk.pc.in by configure.
pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = mstflint_sdk.pc

# The SDK ships as a redistributable binary: strip the installed shared object
# and drop the libtool .la (nothing links against it, and .la files are not
# wanted in a distribution).
install-data-hook:
	$(STRIP) --strip-unneeded $(DESTDIR)$(sdklibdir)/libmstflint_sdk.so
	rm -f $(DESTDIR)$(sdklibdir)/libmstflint_sdk.la
