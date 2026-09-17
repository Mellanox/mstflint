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

AM_CPPFLAGS = -I$(top_srcdir) -I$(top_srcdir)/include/mtcr_ul -I$(top_srcdir)/common -I$(top_builddir)/common -I$(top_srcdir)/dev_mgt $(COMPILER_FPIC)

bin_PROGRAMS = \
    mstdevices_info

mstdevices_info_SOURCES = mdevices_info.c
mstdevices_info_DEPENDENCIES = $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
               			         $(top_builddir)/dev_mgt/libdev_mgt.la \
 	                             $(top_builddir)/reg_access/libreg_access.la
mstdevices_info_LDADD = $(mstdevices_info_DEPENDENCIES) ${LDL}
mstdevices_info_LDFLAGS = -static


# jsoncpp is resolved at the END of the link line. libmtcr_ul.a and
# libmst_http_client.a are mutually dependent (mtcr_remote.c calls the client;
# the client needs Json), and ld makes a single pass over each archive, so the
# Json objects carried inside libmtcr_ul are already behind it by the time the
# client's undefined Json symbols show up. Listing jsoncpp last closes that gap.
if USE_LOCAL_JSON
MST_JSON_LIBS = $(top_builddir)/ext_libs/json/libjson.la
else
MST_JSON_LIBS = -ljsoncpp
endif

# Registers/unregisters devices served by a remote mstserver. Only built
# with --enable-remote, since it drives the MST HTTP client directly and there
# is nothing to register without the mtcr remote path.
if ENABLE_MTCR_REMOTE
# mstremote belongs to the remote feature, which configure already refuses to
# enable without a C++17 compiler - so C++17 is always available here. Raised
# with the rest of the feature rather than held at the tree standard.
#
# It has to be CXXFLAGS: automake emits $(CXXFLAGS) after every per-target
# _CXXFLAGS, so a -std in mstremote_CXXFLAGS would lose to the tree's C++14.
# The append is inside this conditional so a build without --enable-remote
# leaves the directory at the tree standard.
CXXFLAGS += $(CXX17_STD)

bin_PROGRAMS += mstremote

mstremote_SOURCES = mstremote.cpp
mstremote_CPPFLAGS = $(AM_CPPFLAGS) -I$(top_srcdir)/${MTCR_CONF_DIR}
mstremote_CXXFLAGS = $(AM_CXXFLAGS) $(COMPILER_FPIC)
mstremote_DEPENDENCIES = $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
                         $(top_builddir)/mst_server/client/libmst_http_client.la \
                         $(top_builddir)/cmdparser/libcmdparser.a
# openssl and libcurl come in through libmst_http_client, which speaks TLS.
# mstremote itself no longer computes anything: the passphrase goes to the
# server over the encrypted channel and is checked there against a salted
# verifier.
mstremote_LDADD = $(mstremote_DEPENDENCIES) $(openssl_LIBS) $(mst_remote_curl_LIBS) $(FILESYSTEM_LIBS) ${LDL} -lstdc++ $(MST_JSON_LIBS)
mstremote_LDFLAGS = -static
endif

if ENABLE_CABLES
bin_PROGRAMS += mstcable_discovery
mstcable_discovery_SOURCES = cable_discovery.cpp
mstcable_discovery_DEPENDENCIES = $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la \
               			         $(top_builddir)/dev_mgt/libdev_mgt.la \
								 $(top_builddir)/reg_access/libreg_access.la \
								 $(top_builddir)/mft_utils/libmftutils.la
    mstcable_discovery_LDADD = $(mstcable_discovery_DEPENDENCIES) ${LDL}
    mstcable_discovery_LDFLAGS = -static
endif