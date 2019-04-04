#--
#                 - Mellanox Confidential and Proprietary -
# 
# Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
# 
# Except as specifically permitted herein, no portion of the information,
# including but not limited to object code and source code, may be reproduced,
# modified, distributed, republished or otherwise exploited in any form or by
# any means for any purpose without the prior written permission of Mellanox
# Technologies Ltd. Use of software subject to the terms and conditions
# detailed in the file "LICENSE.txt".
#--

# Makefile.am -- Process this file with automake to produce Makefile.in

bin_SCRIPTS=mstfwtrace

PYTHON_WRAPPER=mstfwtrace
PYTHON_WRAPPER_SCRIPT=../../common/python_wrapper
${PYTHON_WRAPPER}: $(PYTHON_WRAPPER_SCRIPT)
	cp $(PYTHON_WRAPPER_SCRIPT) $@
CLEANFILES=${PYTHON_WRAPPER}
pythonlibdir=$(libdir)/mstflint/python_tools/$(PYTHON_WRAPPER)
pythonlib_DATA = mstfwtrace.py fw_trace_utilities.py secure_fw_trace.py
EXTRA_DIST = $(PYTHON_WRAPPER).py

clean: myclean
myclean:
	rm -rf $(bin_SCRIPTS) dist build *.spec


