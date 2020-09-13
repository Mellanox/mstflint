#--
# Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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

USER_DIR = $(top_srcdir)
bin_SCRIPTS=mstresourceparse

PYTHON_WRAPPER=mstresourceparse
PYTHON_WRAPPER_SCRIPT=$(USER_DIR)/common/python_wrapper
${PYTHON_WRAPPER}: $(PYTHON_WRAPPER_SCRIPT)
	cp $(PYTHON_WRAPPER_SCRIPT) $@
pythonlibdir=$(libdir)/mstflint/python_tools/mstresourceparse
dist_pythonlib_SCRIPTS = mstresourceparse.py
dist_pythonlib_DATA = __init__.py
parserspythonlibdir=$(libdir)/mstflint/python_tools/mstresourceparse/parsers
dist_parserspythonlib_DATA = parsers/*.py
utilspythonlibdir=$(libdir)/mstflint/python_tools/mstresourceparse/utils
dist_utilspythonlib_DATA = utils/*.py
segmentspythonlibdir=$(libdir)/mstflint/python_tools/mstresourceparse/segments
dist_segmentspythonlib_DATA = segments/*.py
resourcepythonlibdir=$(libdir)/mstflint/python_tools/mstresourceparse/resource_data
dist_resourcepythonlib_DATA = resource_data/*.py

CLEANFILES=${PYTHON_WRAPPER}
