# Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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
#
# Makefile.am -- Process this file with automake to produce Makefile.in

USER_DIR=$(top_srcdir)
COM_DIR = $(USER_DIR)/common
UTILS_DIR = $(USER_DIR)/mft_utils
MTCR_DIR = $(USER_DIR)/${MTCR_CONF_DIR}
RES_MGMT_DIR = $(USER_DIR)/tools_res_mgmt
DEV_MGT_DIR = $(USER_DIR)/dev_mgt
TOOLS_CRYPTO_DIR = $(USER_DIR)/tools_crypto
CMDIF_DIR = $(USER_DIR)/cmdif

CURL_LIBS = -lcurl  -lssl -lcrypto -lrt

INCLUDES = $(JSON_CFLAGS) -I. \
           -I$(USER_DIR) -I$(USER_DIR)/libmfa \
           -I$(MTCR_DIR) -I$(USER_DIR)/include/mtcr_ul \
           -I$(USER_DIR)/mflash -I$(USER_DIR)/common \
           -I$(UTILS_DIR) -I$(USER_DIR)/mlxfwops/lib \
           -I$(USER_DIR)/dev_mgt -I$(USER_DIR)/tools_layouts

lib_LTLIBRARIES = libmstarchive.a

libmstarchive_a_SOURCES = \
              mlxarchive_mfa2_utils.h mlxarchive_mfa2_utils.cpp\
              mlxarchive_mfa2_common_header.h mlxarchive_mfa2_common_header.cpp\
              mlxarchive_mfa2_element.h mlxarchive_mfa2_element.cpp\
              mlxarchive_mfa2_extension.h mlxarchive_mfa2_extension.cpp\
              mlxarchive_mfa2_descriptor.h mlxarchive_mfa2_descriptor.cpp\
              mlxarchive_mfa2_component.h\
              mlxarchive_mfa2.h mlxarchive_mfa2.cpp\
              mlxarchive_mfa2_builder.h mlxarchive_mfa2_builder.cpp\
              mlxarchive_mfa2_package_gen.h mlxarchive_mfa2_package_gen.cpp\
              mfa2_buff.h mfa2_buff.cpp

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(INCLUDES) $(COMPILER_FPIC)
bin_PROGRAMS = mstarchive

mstarchive_SOURCES = mlxarchive.cpp mlxarchive.h
mstarchive_LDADD = libmstarchive.a\
                   $(USER_DIR)/mlxfwops/lib/libmlxfwops.a\
                   $(USER_DIR)/libmfa/libmfa.a\
                   $(USER_DIR)/fw_comps_mgr/libfw_comps_mgr.a\
                   $(MTCR_DIR)/libmtcr_ul.a\
                   $(USER_DIR)/mflash/libmflash.a\
                   $(RES_MGMT_DIR)/libtools_res_mgmt.a\
                   $(DEV_MGT_DIR)/libdev_mgt.a\
                   $(CMDIF_DIR)/libcmdif.a\
                   $(UTILS_DIR)/libmftutils.a\
                   $(JSON_LIBS)\
                   $(USER_DIR)/cmdparser/libcmdparser.a\
                   $(USER_DIR)/reg_access/libreg_access.a\
                   $(USER_DIR)/tools_layouts/libtools_layouts.a\
                   $(USER_DIR)/xz_utils/libxz_utils.a\
                   $(USER_DIR)/ext_libs/minixz/libminixz.a\
		   $(USER_DIR)/xz_utils/libxz_utils.a \
                   $(CURL_LIBS)\
                   -lboost_regex -lboost_filesystem -lboost_system \
                   -llzma -lm $(LIBSTD_CPP) ${LDL}

if ENABLE_OPENSSL
mstarchive_LDADD += $(top_srcdir)/mlxsign_lib/libmlxsign.a -lcrypto
else
endif

if ENABLE_CS
mstarchive_LDADD += $(top_srcdir)/tools_crypto/libtools_crypto.a -lcrypto
else
endif

if ENABLE_INBAND
mstarchive_LDADD += $(top_srcdir)/mad_ifc/libmad_ifc.a
else
endif
