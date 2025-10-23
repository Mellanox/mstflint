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
    -I$(srcdir)/components \
    -I$(top_srcdir) \
    -I$(top_srcdir)/common -I$(top_builddir)/common \
    -I$(top_srcdir)/dev_mgt \
    -I$(top_srcdir)/ext_libs/minixz \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mflash \
    -I$(top_srcdir)/mft_utils \
    -I$(top_srcdir)/mlxfwops/uefi_c \
    -I$(top_srcdir)/mtcr_ul \
    -I$(top_srcdir)/tools_layouts

AM_CPPFLAGS += $(JSON_CFLAGS)

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) -Wno-implicit-fallthrough

if ENABLE_FWMGR
AM_CPPFLAGS += -I$(top_srcdir)/libmfa
else
AM_CXXFLAGS += -DNO_MFA_SUPPORT
endif

if ENABLE_OPENSSL
else
AM_CXXFLAGS += -DNO_OPEN_SSL
endif

if ENABLE_CS
else
AM_CXXFLAGS += -DNO_CS_CMD
endif

noinst_LIBRARIES = libmlxfwops.a

libmlxfwops_a_SOURCES = \
    aux_tlv_ops.cpp \
    aux_tlv_ops.h \
    bluefiled_signature_manager.cpp \
    connectx6_signature_manager.cpp \
    flint_base.cpp \
    flint_base.h \
    flint_io.cpp \
    flint_io.h \
    fs_checks.cpp \
    fs_checks.h \
    fs2_ops.cpp \
    fs2_ops.h \
    fs3_ops.cpp \
    fs3_ops.h \
    fs4_ops.cpp \
    fs4_ops.h \
    fs5_ops.cpp \
    fs5_ops.h \
    fsctrl_ops.cpp \
    fsctrl_ops.h \
    fs_pldm.cpp \
    fs_pldm.h \
    fw_ops.cpp \
    fw_ops.h\
    fw_version.cpp \
    mlxfwops_com.h \
    mlxfwops.cpp \
    mlxfwops.h \
    security_version_gw.cpp \
    security_version_gw.h \
    signature_manager_factory.h \
    signature_manager.h \
    components/fs_cert_ops.cpp \
    components/fs_cert_ops.h \
    components/fs_comps_factory.h \
    components/fs_comps_ops.cpp \
    components/fs_comps_ops.h \
    components/fs_synce_ops.cpp \
    components/fs_synce_ops.h

if ENABLE_DPA
AM_CXXFLAGS += -DENABLE_DPA
libmlxfwops_a_SOURCES += \
    components/fs_dpa_app_ops.cpp \
    components/fs_dpa_app_ops.h
libmlxfwops_a_DEPENDENCIES = $(top_builddir)/mlxdpa/libmstdpa.a
endif
