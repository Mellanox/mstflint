#--
#                 - Mellanox Confidential and Proprietary -
# 
# Copyright (C) Jan 2019, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
# 
# Except as specifically permitted herein, no portion of the information,
# including but not limited to object code and source code, may be reproduced,
# modified, distributed, republished or otherwise exploited in any form or by
# any means for any purpose without the prior written permission of Mellanox
# Technologies Ltd. Use of software subject to the terms and conditions
# detailed in the file "LICENSE.txt".
#--

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
