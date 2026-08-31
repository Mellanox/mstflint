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

AM_CPPFLAGS = -I$(srcdir) -I$(top_srcdir) -I$(builddir)/generated $(JSON_CFLAGS)

AM_CXXFLAGS = -Wall -W -g -MP -MD -pipe $(COMPILER_FPIC)

noinst_LTLIBRARIES = libdevice_info.la

libdevice_info_la_SOURCES = device_properties_api.cpp

noinst_HEADERS = \
    device_properties_api.h \
    device_hw_ids.h \
    device_properties_constants.h

# device_properties_data.h is generated in $(builddir)/generated; depending on
# it here forces automake to run the generator before compiling the .cpp.
nodist_libdevice_info_la_SOURCES = generated/device_properties_data.h

libdevice_info_la_LIBADD = \
    $(top_builddir)/mft_core/mft_core_utils/logger/liblogger.la \
    $(top_builddir)/mft_core/mft_core_utils/mft_exceptions/libmftexceptions.la

noinst_PROGRAMS = generate_device_properties
generate_device_properties_CPPFLAGS = $(JSON_CFLAGS)
generate_device_properties_SOURCES = generate_device_properties.cpp
generate_device_properties_LDADD = $(JSON_LIBS)
generate_device_properties_DEPENDENCIES = $(JSON_LIBS)

# Build libjson.la on demand, so `make -C mft_core` works before ext_libs is built.
$(top_builddir)/ext_libs/json/libjson.la:
	cd $(top_builddir)/ext_libs/json && $(MAKE) $(AM_MAKEFLAGS) libjson.la

DEVICE_PROPS_GENERATOR = generate_device_properties$(EXEEXT)
DEVICE_PROPS_JSON_DIR = $(srcdir)/json
DEVICE_PROPS_GEN_DIR = generated
DEVICE_PROPS_GEN_H = $(DEVICE_PROPS_GEN_DIR)/device_properties_data.h
DEVICE_PROPS_GEN_PY = $(DEVICE_PROPS_GEN_DIR)/device_properties_data.py
DEVICE_PROPS_GEN_STAMP = $(DEVICE_PROPS_GEN_DIR)/.device_properties_data.stamp

BUILT_SOURCES = $(DEVICE_PROPS_GEN_H) $(DEVICE_PROPS_GEN_PY)
CLEANFILES = $(DEVICE_PROPS_GEN_H) $(DEVICE_PROPS_GEN_PY) $(DEVICE_PROPS_GEN_STAMP)

# A single generator invocation produces both files. Drive it through one
# stamp target so the recipe runs exactly once even under `make -j`, avoiding
# the double-run/race a multi-target rule would cause. The recovery rules
# regenerate if an output is removed while the stamp is still present; the
# .py recovery depends on the .h so that, under `make -j`, only one sub-make
# can run the generator when both outputs are missing.
$(DEVICE_PROPS_GEN_H): $(DEVICE_PROPS_GEN_STAMP)
	@if test -f $@; then :; else \
	  rm -f $(DEVICE_PROPS_GEN_STAMP); \
	  $(MAKE) $(AM_MAKEFLAGS) $(DEVICE_PROPS_GEN_STAMP); \
	fi

$(DEVICE_PROPS_GEN_PY): $(DEVICE_PROPS_GEN_H)
	@if test -f $@; then :; else \
	  rm -f $(DEVICE_PROPS_GEN_STAMP); \
	  $(MAKE) $(AM_MAKEFLAGS) $(DEVICE_PROPS_GEN_STAMP); \
	fi

$(DEVICE_PROPS_GEN_STAMP): $(DEVICE_PROPS_GENERATOR) $(wildcard $(DEVICE_PROPS_JSON_DIR)/*.json)
	$(MKDIR_P) $(DEVICE_PROPS_GEN_DIR)
	@touch $@
	./$(DEVICE_PROPS_GENERATOR) $(DEVICE_PROPS_JSON_DIR) $(DEVICE_PROPS_GEN_DIR)
	@touch $(DEVICE_PROPS_GEN_H) $(DEVICE_PROPS_GEN_PY)

EXTRA_DIST = \
    device_properties_api.py \
    device_properties_constants.py \
    unit_test/test_device_id_constants.py \
    unit_test/test_device_properties_constants.py \
    unit_test/test_device_properties_api.py

# 'make dist' bundles the per-device JSON files without enumerating them here
# (the whole point of option 7 is that the JSON list lives only on disk).
dist-hook:
	cp -R $(srcdir)/json $(distdir)/

# Python unit tests. `make check` runs them; the drift-guard tests need the
# raw sources, and test_device_properties_api.py imports the module, which in
# turn imports the build-generated device_properties_data module.
TESTS = \
    unit_test/test_device_id_constants.py \
    unit_test/test_device_properties_constants.py \
    unit_test/test_device_properties_api.py

TEST_EXTENSIONS = .py
PY_LOG_COMPILER = $(PYTHON)
AM_TESTS_ENVIRONMENT = \
    PYTHONPATH="$(srcdir):$(builddir)/generated:$$PYTHONPATH"; export PYTHONPATH;

# Distribute the Python API alongside other mstflint python tools. The generated
# device_properties_data.py is co-installed so device_properties_api.py can import it.
device_info_pylibdir = $(libdir)/mstflint/python_tools/
dist_device_info_pylib_DATA = device_properties_api.py device_properties_constants.py
device_info_pylib_DATA = generated/device_properties_data.py
