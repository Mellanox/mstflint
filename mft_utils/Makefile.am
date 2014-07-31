#--
#                 - Mellanox Confidential and Proprietary -
# 
# Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
# 
# Except as specifically permitted herein, no portion of the information,
# including but not limited to object code and source code, may be reproduced,
# modified, distributed, republished or otherwise exploited in any form or by
# any means for any purpose without the prior written permission of Mellanox
# Technologies Ltd. Use of software subject to the terms and conditions
# detailed in the file "LICENSE.txt".
#--

# Makefile.am -- Process this file with automake to produce Makefile.in
USER_DIR = $(top_srcdir)
INCLUDES = -I. -I$(USER_DIR)/common

AM_CFLAGS = -MD -pipe -Wall -W -Werror

noinst_HEADERS = mft_sig_handler.h errmsg.h

noinst_LIBRARIES = libmftutils.a

libmftutils_a_SOURCES =  mft_sig_handler.c errmsg.cpp

