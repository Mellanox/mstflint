#--
# Copyright (c) 2004-2010 Mellanox Technologies LTD. All rights reserved.
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

USER_DIR = ..
INCLUDES = -I.
AM_CPPFLAGS = -DXZ_DEC_ANY_CHECK -W  -g -MP -MD ${COMPILER_FPIC}
noinst_LTLIBRARIES = libminixz.a
libminixz_a_SOURCES = xz_crc32.c  xz_dec_bcj.c  xz_dec_lzma2.c  xz_dec_stream.c xz_config.h   xz.h xz_lzma2.h    xz_private.h  xz_stream.h

libminixz_a_DEPENDENCIES =  xz_crc32.c  xz_dec_bcj.c  xz_dec_lzma2.c  xz_dec_stream.c xz_config.h   xz.h xz_lzma2.h    xz_private.h  xz_stream.h
libminixz_a_LIBADD =


