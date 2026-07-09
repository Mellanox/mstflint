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

mtcr_pylibdir = $(libdir)/mstflint/python_tools/

mtcr_pylib_DATA = cmtcr.so
dist_mtcr_pylib_DATA = mtcr.py

# With --enable-vfio, libmtcr_ul.a absorbs vfio_driver_access -> libcommon
# (tools_json.cpp), which references jsoncpp symbols (Json::parseFromStream,
# Json::Value::asString, ...). cmtcr.so must therefore also link jsoncpp,
# otherwise it fails to dlopen at runtime with "undefined symbol: _ZN4Json...".
if ENABLE_VFIO
if USE_LOCAL_JSON
CMTCR_JSON_LIBS = $(top_builddir)/ext_libs/json/.libs/libjson.a
else
CMTCR_JSON_LIBS = -ljsoncpp
endif
else
CMTCR_JSON_LIBS =
endif

cmtcr.so:
	$(CC) -g -Wall -pthread -shared ${CFLAGS} ${LDFLAGS} -o cmtcr.so -Wl,--whole-archive $(top_builddir)/${MTCR_CONF_DIR}/.libs/libmtcr_ul.a -Wl,--no-whole-archive $(CMTCR_JSON_LIBS) -lstdc++

CLEANFILES = cmtcr.so
