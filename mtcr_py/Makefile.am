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
MTCR_CONFIG_DIR = mtcr_ul
mtcr_pylibdir = $(libdir)/mstflint/python_tools/
USER_DIR = ..
MTCR_DIR = $(USER_DIR)/${MTCR_CONFIG_DIR}

mtcr_pylib_DATA = cmtcr.so mtcr.py
dist_mtcr_pylib_DATA = mtcr.py
cmtcr.so:
	$(CC) -g -Wall -pthread -shared ${CFLAGS} $(MTCR_DIR)/*.o -o cmtcr.so

CLEANFILES = cmtcr.so

