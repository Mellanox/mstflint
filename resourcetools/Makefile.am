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


SUBDIRS = resourcedump_lib

USER_DIR = $(top_srcdir)
bin_SCRIPTS = mstresourcedump mstresourceparse

PYTHON_WRAPPER=mstresourcedump
PYTHON_WRAPPER_SCRIPT=$(USER_DIR)/common/python_wrapper
${PYTHON_WRAPPER}: $(PYTHON_WRAPPER_SCRIPT)
	cp $(PYTHON_WRAPPER_SCRIPT) $@

PYTHON_WRAPPER2=mstresourceparse
${PYTHON_WRAPPER2}: $(PYTHON_WRAPPER_SCRIPT)
	cp $(PYTHON_WRAPPER_SCRIPT) $@

pythonlibdir=$(libdir)/mstflint/python_tools/resourcetools
dist_pythonlib_SCRIPTS = mstresourcedump.py mstresourceparse.py

segmentspythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/segments
dist_segmentspythonlib_DATA = segments/*.py

maindumppythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib
dist_maindumppythonlib_DATA = resourcedump_lib/*.py
validationpythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/validation
dist_validationpythonlib_DATA = resourcedump_lib/validation/*.py
utilspythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/utils
dist_utilspythonlib_DATA = resourcedump_lib/utils/*.py
filterspythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/filters
dist_filterspythonlib_DATA = resourcedump_lib/filters/*.py
fetcherspythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/fetchers
dist_fetcherspythonlib_DATA = resourcedump_lib/fetchers/*.py
commandspythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/commands
dist_commandspythonlib_DATA = resourcedump_lib/commands/*.py
cresourcedumppythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourcedump_lib/cresourcedump
dist_cresourcedumppythonlib_DATA = resourcedump_lib/cresourcedump/*.py

mainparsepythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourceparse_lib
dist_mainparsepythonlib_DATA = resourceparse_lib/*.py
parsersparsepythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourceparse_lib/parsers
dist_parsersparsepythonlib_DATA = resourceparse_lib/parsers/*.py
parseutilspythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourceparse_lib/utils
dist_parseutilspythonlib_DATA = resourceparse_lib/utils/*.py
parsedatapythonlibdir=$(libdir)/mstflint/python_tools/resourcetools/resourceparse_lib/resource_data
dist_parsedatapythonlib_DATA = resourceparse_lib/resource_data/*.py

CLEANFILES = ${PYTHON_WRAPPER} ${PYTHON_WRAPPER2}
