#
# Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
#
# This software product is a proprietary product of Nvidia Corporation and its affiliates
# (the "Company") and all right, title, and interest in and to the software
# product, including all associated intellectual property rights, are and
# shall remain exclusively with the Company.
#
# This software product is governed by the End User License Agreement
# provided with the software product.
#

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
