#--
# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#--

# Makefile.am -- Process this file with automake to produce Makefile.in

# MST HTTP server (Crow).
#
# C++17 REQUIREMENT: Crow does not compile below C++17, so this directory is
# only descended into when configure's HAVE_CXX17 probe succeeded and the
# target is built with $(CXX17_STD) (-std=c++17). There is no lower-standard
# variant: compiled with an older standard the sources simply do not build,
# which is why the decision is made in configure rather than in the code.
#
# Crow and Asio are header-only. -w keeps their headers from tripping the
# tree's warning flags; -UVERSION avoids the autotools VERSION macro colliding
# with Crow's `constexpr char VERSION[]` in crow/version.h.
#
# CROW_ENABLE_SSL changes the layout of crow::Crow (it gains the SSL server and
# context members), so every translation unit that includes crow.h must agree on
# it: a mix would be an ODR violation that links cleanly and misbehaves at run
# time. Only this target includes Crow, so setting it here is enough.
# The tree is pinned to C++14 by configure (see the CXX_STD note there) and
# automake emits $(CXXFLAGS) after every per-target _CXXFLAGS, so a -std in
# those would lose. Appending here is what actually makes C++17 win, and it is
# scoped to this directory - the only place allowed to use it until mstflint
# takes C++17 as its baseline.
CXXFLAGS += $(CXX17_STD)

bin_PROGRAMS = mstserver

mstserver_SOURCES = \
    MstHttpServer.cpp \
    MstHttpRoutes.cpp \
    MstServerTool.cpp \
    MstServerHttpUtil.cpp \
    MstServerServiceImpl.cpp \
    MstServerTls.cpp \
    MstHttpRoutes.h \
    MstServerTool.h \
    MstServerHttpUtil.h \
    MstServerService.h \
    MstServerServiceImpl.h \
    MstServerTls.h \
    MstTlsFingerprint.h

mstserver_CXXFLAGS = \
    $(AM_CXXFLAGS) $(COMPILER_FPIC) $(CXX17_STD) \
    -I$(top_srcdir) \
    -I$(top_srcdir)/include/mtcr_ul \
    -I$(top_srcdir)/mtcr_ul \
    -I$(top_srcdir)/ext_libs/crow/include \
    -I$(top_srcdir)/ext_libs/asio/include \
    $(openssl_CFLAGS) \
    -DASIO_STANDALONE -DCROW_ENABLE_SSL -DMST_UL -UVERSION -w

mstserver_DEPENDENCIES = \
    $(top_builddir)/cmdparser/libcmdparser.a \
    $(top_builddir)/${MTCR_CONF_DIR}/libmtcr_ul.la

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

mstserver_LDADD = $(mstserver_DEPENDENCIES) $(openssl_LIBS) $(mst_remote_curl_LIBS) $(FILESYSTEM_LIBS) ${LDL} -lpthread -lstdc++ $(MST_JSON_LIBS)
# -static: absorb libmtcr_ul rather than linking it dynamically, matching every
# other tool in the tree. mtcr_ul's install-exec-hook deletes
# $(pkglibdir)/libmtcr_ul.so* after install and ships only the static archive,
# so a dynamically linked consumer would fail at run time with
# "libmtcr_ul.so.0: cannot open shared object file".
mstserver_LDFLAGS = -static
