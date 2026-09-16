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

# MST HTTP client (libcurl transport over TLS).
#
# C++17 REQUIREMENT: this directory is only descended into when configure's
# HAVE_CXX17 probe succeeded, and every target below is compiled with
# $(CXX17_STD) (-std=c++17). Anything that links libmst_http_client.la and
# includes its headers must be built as C++17 or newer too.
#
# -UVERSION avoids the autotools VERSION macro colliding with third-party
# identifiers of the same name.
#
# OpenSSL is not optional here: the client pins the server key fingerprint and
# computes it with openssl. configure refuses --enable-remote when openssl is
# disabled for exactly this reason.
MST_SERVER_CXXFLAGS = \
    $(AM_CXXFLAGS) $(COMPILER_FPIC) $(CXX17_STD) \
    -I$(top_srcdir) $(JSON_CFLAGS) $(openssl_CFLAGS) $(mst_remote_curl_CFLAGS) \
    -UVERSION

# jsoncpp is NOT added to LIBADD below. libmst_http_client.la is a convenience
# archive, so LIBADD'ing libjson.la would absorb json_writer.o into it - and
# libmtcr_ul already links libnvtoolslogger.la, which absorbs the same objects
# through libmft_log_config.la. Two archives carrying them makes the final link
# fail with "multiple definition of Json::...". The headers still come in via
# $(JSON_CFLAGS); the symbols resolve from the logger's copy.
noinst_LTLIBRARIES = libmst_http_client.la

libmst_http_client_la_SOURCES = \
    MstHttpClient.cpp \
    MstKnownHosts.cpp \
    mst_http_client_c_api.cpp \
    MstCurlClient.h \
    MstHttpClient.h \
    MstKnownHosts.h \
    mst_http_client_c_api.h
libmst_http_client_la_CXXFLAGS = $(MST_SERVER_CXXFLAGS)
libmst_http_client_la_LIBADD = \
    $(openssl_LIBS) $(mst_remote_curl_LIBS) $(FILESYSTEM_LIBS) -lpthread -lstdc++
