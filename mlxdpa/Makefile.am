#
# Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
USER_DIR = ..
COMMON_DIR = $(USER_DIR)/common
UTILS_DIR = $(USER_DIR)/mft_utils
MTCR_DIR = $(USER_DIR)/${MTCR_CONFIG_DIR}
MLXSIGN_DIR = $(USER_DIR)/mlxsign_lib
X509_PARSER_DIR = $(USER_DIR)/x509_parser

INCLUDE_PATH = -I. -I.. -I$(USER_DIR) -I$(COMMON_DIR) -I$(UTILS_DIR) -I$(MLXSIGN_DIR) -I$(MTCR_DIR) -isystem $(MFT_EXT_LIBS_INC_DIR)

XML_FLAGS = -DUSE_XML -DLIBXML_STATIC

AM_CXXFLAGS = $(INCLUDE_PATH) -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC) $(XML_FLAGS)

bin_PROGRAMS = mstdpa

mstdpa_CXXFLAGS = $(AM_CXXFLAGS)
mstdpa_SOURCES  = mlxdpa_utils.h mlxdpa_utils.cpp cryptodata.h cryptodata.cpp hostelf.h hostelf.cpp mlxdpa.h mlxdpa.cpp \
                    certcontainerbase.h certcontainerbase.cpp certcontainerimp.h certcontainerimp.cpp
mstdpa_LDADD    = $(USER_DIR)/cmdparser/libcmdparser.a $(MLXSIGN_DIR)/libmlxsign.a $(UTILS_DIR)/libmftutils.a


if ARM64_BUILD
mstdpa_LDADD    += dpa_elf/arm64/libdpa_elf.a
endif
if X86_64_BUILD
mstdpa_LDADD    += dpa_elf/x86_64/libdpa_elf.a
endif

if ENABLE_OPENSSL
mstdpa_LDADD    +=  -lcrypto -lssl
else
mstdpa_CXXFLAGS += -DNO_OPEN_SSL
endif