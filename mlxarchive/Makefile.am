#                  - Mellanox Confidential and Proprietary -
#
#  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
#
#  Except as specifically permitted herein, no portion of the information,
#  including but not limited to object code and source code, may be reproduced,
#  modified, distributed, republished or otherwise exploited in any form or by
#  any means for any purpose without the prior written permission of Mellanox
#  Technologies Ltd. Use of software subject to the terms and conditions
#  detailed in the file "LICENSE.txt".

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
