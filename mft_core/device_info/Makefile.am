# Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

DEVICE_INFO_GENERATOR = $(srcdir)/generate_device_properties.py
DEVICE_INFO_JSON_INPUT = $(srcdir)/json
DEVICE_INFO_GEN_DIR = generated
DEVICE_INFO_GEN_H = $(DEVICE_INFO_GEN_DIR)/device_properties_data.h
DEVICE_INFO_GEN_PY = $(DEVICE_INFO_GEN_DIR)/device_properties_data.py
DEVICE_INFO_GEN_STAMP = $(DEVICE_INFO_GEN_DIR)/.device_properties_data.stamp

BUILT_SOURCES = $(DEVICE_INFO_GEN_H) $(DEVICE_INFO_GEN_PY)
CLEANFILES = $(DEVICE_INFO_GEN_H) $(DEVICE_INFO_GEN_PY) $(DEVICE_INFO_GEN_STAMP)

EXTRA_DIST = $(DEVICE_INFO_GENERATOR) \
             $(wildcard $(DEVICE_INFO_JSON_INPUT)/*.json)

# A single generator invocation produces both files. Drive it through one
# stamp target so the recipe runs exactly once even under `make -j`, avoiding
# the double-run/race a multi-target rule would cause. The recovery rules
# regenerate if an output is removed while the stamp is still present; the
# .py recovery depends on the .h so that, under `make -j`, only one sub-make
# can run the generator when both outputs are missing.
$(DEVICE_INFO_GEN_H): $(DEVICE_INFO_GEN_STAMP)
	@if test -f $@; then :; else \
	  rm -f $(DEVICE_INFO_GEN_STAMP); \
	  $(MAKE) $(AM_MAKEFLAGS) $(DEVICE_INFO_GEN_STAMP); \
	fi

$(DEVICE_INFO_GEN_PY): $(DEVICE_INFO_GEN_H)
	@if test -f $@; then :; else \
	  rm -f $(DEVICE_INFO_GEN_STAMP); \
	  $(MAKE) $(AM_MAKEFLAGS) $(DEVICE_INFO_GEN_STAMP); \
	fi

$(DEVICE_INFO_GEN_STAMP): $(DEVICE_INFO_GENERATOR) $(wildcard $(DEVICE_INFO_JSON_INPUT)/*.json)
	$(MKDIR_P) $(DEVICE_INFO_GEN_DIR)
	$(PYTHON3) $(DEVICE_INFO_GENERATOR) $(DEVICE_INFO_JSON_INPUT) $(DEVICE_INFO_GEN_DIR)
	@touch $(DEVICE_INFO_GEN_H) $(DEVICE_INFO_GEN_PY)
	@touch $@

AM_CPPFLAGS = -I$(top_srcdir) -I$(builddir)/$(DEVICE_INFO_GEN_DIR) -I$(srcdir)

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe -Werror $(COMPILER_FPIC)

noinst_LTLIBRARIES = libdeviceproperties.la

libdeviceproperties_la_SOURCES = \
	device_hw_ids.h \
	device_properties_api.h \
	device_properties_constants.h \
	device_properties_api.cpp

libdeviceproperties_la_DEPENDENCIES = \
	../mft_core_utils/mft_exceptions/libmftexceptions.la \
	../mft_core_utils/logger/liblogger.la

libdeviceproperties_la_LIBADD = $(libdeviceproperties_la_DEPENDENCIES) -lm
