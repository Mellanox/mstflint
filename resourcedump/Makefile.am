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
