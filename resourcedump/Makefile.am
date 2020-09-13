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
bin_SCRIPTS=mstresourcedump

PYTHON_WRAPPER=mstresourcedump
PYTHON_WRAPPER_SCRIPT=$(USER_DIR)/common/python_wrapper
${PYTHON_WRAPPER}: $(PYTHON_WRAPPER_SCRIPT)
	cp $(PYTHON_WRAPPER_SCRIPT) $@
pythonlibdir=$(libdir)/mstflint/python_tools/mstresourcedump
dist_pythonlib_SCRIPTS = mstresourcedump.py
dist_pythonlib_DATA = __init__.py
validationpythonlibdir=$(libdir)/mstflint/python_tools/mstresourcedump/validation
dist_validationpythonlib_DATA = validation/*.py
utilspythonlibdir=$(libdir)/mstflint/python_tools/mstresourcedump/utils
dist_utilspythonlib_DATA = utils/*.py
segmentspythonlibdir=$(libdir)/mstflint/python_tools/mstresourcedump/segments
dist_segmentspythonlib_DATA = segments/*.py
resourcepythonlibdir=$(libdir)/mstflint/python_tools/mstresourcedump/resource_data
dist_resourcepythonlib_DATA = resource_data/*.py
filterspythonlibdir=$(libdir)/mstflint/python_tools/mstresourcedump/filters
dist_filterspythonlib_DATA = filters/*.py 
fetcherspythonlibdir=$(libdir)/mstflint/python_tools/mstresourcedump/fetchers
dist_fetcherspythonlib_DATA = fetchers/*.py
commandspythonlibdir=$(libdir)/mstflint/python_tools/mstresourcedump/commands
dist_commandspythonlib_DATA = commands/*.py

CLEANFILES=${PYTHON_WRAPPER}
