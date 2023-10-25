#
# Copyright © 2013-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

if LINUX_BUILD
USER_DIR = $(top_srcdir)
COMMON_DIR = $(top_srcdir)/common
MTCR_DIR = $(top_srcdir)/${MTCR_CONF_DIR}
MTCR_INC_DIR = $(top_srcdir)/include/mtcr_ul
UTILS_DIR = $(top_srcdir)/mft_utils
LAYOUTS_DIR = $(top_srcdir)/tools_layouts
LAYOUTS_LIB = $(LAYOUTS_DIR)/libtools_layouts.la
REG_ACCESS_DIR = $(top_srcdir)/reg_access
RES_MGMT_DIR = $(top_srcdir)/tools_res_mgmt
DEV_MGT_DIR = $(top_srcdir)/dev_mgt
TOOLS_CRYPTO_DIR = $(top_srcdir)/tools_crypto
RES_DUMP_DIR= $(top_srcdir)/resourcedump/resourcedump_lib
INFINIBAND_INCLUDE = -isystem /usr
AM_CPPFLAGS = -I$(top_srcdir) -I$(COMMON_DIR) -I$(REG_ACCESS_DIR) -I$(LAYOUTS_DIR) -I$(MTCR_DIR) $(INFINIBAND_INCLUDE) -I$(MTCR_INC_DIR)

AM_CXXFLAGS = -Wall -W -MP -H -MD -pipe -DMST_UL -g -std=c++11 $(COMPILER_FPIC)
AM_CPPFLAGS += $(AM_CXXFLAGS)
CRESOURCEDUMP_SO = cresourcedump.so
lib_LTLIBRARIES = libresourcedump.la


libresourcedump_la_SOURCES = resource_dump.c resource_dump.h
libresourcedump_la_LIBADD = $(MTCR_DIR)/libmtcr_ul.a $(USER_DIR)/reg_access/libreg_access.la \
                            $(DEV_MGT_DIR)/libdev_mgt.la -L$(USER_DIR)/tools_layouts/.libs -ltools_layouts


resourcedump_pylibdir = $(libdir)/mstflint/python_tools/mstresourcedump/resourcedump_lib/
dist_resourcedump_pylib_DATA = cresourcedump.so

${CRESOURCEDUMP_SO}: libresourcedump.la
	$(CC) -Wall -pthread -fpic -shared ${CFLAGS} resource_dump.o -o ${CRESOURCEDUMP_SO} $(MFT_CORE_LIB_LINK) \
	-L$(USER_DIR)/reg_access/.libs -lreg_access -L$(DEV_MGT_DIR)  -ldev_mgt \
    -L$(MTCR_DIR) -L$(USER_DIR)/tools_layouts/.libs -ltools_layouts \
    $(MFT_CORE_LIB_LINK)

endif
