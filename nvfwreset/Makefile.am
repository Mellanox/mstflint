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

AM_CPPFLAGS = \
    -I$(srcdir) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/${MTCR_CONF_DIR} \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/common \
    -I$(top_builddir)/common \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/cmdparser \
    -I$(top_srcdir)/tools_layouts \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/reg_access \
    -I$(top_srcdir)/pci_library

AM_CXXFLAGS = -Wall -W -DMST_UL -g -MP -MD -pipe

bin_PROGRAMS = nvfwreset

nvfwreset_SOURCES = \
    CommonResetPlatform.cpp \
    CommonResetPlatform.h \
    DeviceTypeDetector.cpp \
    DeviceTypeDetector.h \
    DeviceTypeDetectorDefs.h \
    HotResetManager.cpp \
    HotResetManager.h \
    LinuxResetPlatform.cpp \
    LinuxResetPlatform.h \
    NVFWresetMain.cpp \
    NVFWresetParams.cpp \
    NVFWresetParams.h \
    NVFWresetParser.cpp \
    NVFWresetParser.h \
    ResetDeviceCapabilities.cpp \
    ResetDeviceCapabilities.h \
    ResetFlowExecutor.cpp \
    ResetFlowExecutor.h \
    ResetParameterChooser.cpp \
    ResetParameterChooser.h \
    ResetParameterDefs.h \
    ResetPlatformInterface.cpp \
    ResetPlatformInterface.h

nvfwreset_DEPENDENCIES = \
    $(top_builddir)/cmdparser/libcmdparser.a \
    $(top_builddir)/mft_utils/libmftutils.la \
    $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
    $(top_builddir)/dev_mgt/libdev_mgt.la \
    $(top_builddir)/pci_library/libpci_library.la \
    $(top_builddir)/reg_access/libreg_access.la \
    $(top_builddir)/common/libcommon.la \
    $(top_builddir)/mft_core/mft_core_utils/logger/liblogger.la \
    $(top_builddir)/mft_core/mft_core_utils/mft_exceptions/libmftexceptions.la \
    $(top_builddir)/mft_core/mft_core_utils/operating_system_api/lib_os_api.la

nvfwreset_LDADD = $(nvfwreset_DEPENDENCIES) ${LDL}

nvfwreset_LDFLAGS = -static