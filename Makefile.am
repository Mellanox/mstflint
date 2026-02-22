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

SUBDIRS = $(NVML_DIR) mft_core ext_libs $(TOOLS_CRYPTO) tools_layouts common $(VFIO_DRIVER_DIR) ${MTCR_CONF_DIR} mtcr_py $(MAD_IFC) $(XZ_UTILS_DIR) reg_access cmdif dev_mgt pci_library mft_utils $(CABLE_ACCESS_DIR) tools_res_mgmt mvpd mflash fw_comps_mgr libmfa pldmlib cmdparser mlxconfig $(NVFWRESET_DIR) $(DPA) mlxfwops $(FW_MGR_TOOLS) mlxtokengenerator flint small_utils mst_utils mstdump ${ADABE_TOOLS} tracers resourcetools

DIST_SUBDIRS = tracers

man_MANS = man/mstflint.1 man/mstconfig.1 man/mstmcra.1 man/mstmread.1 man/mstmwrite.1 man/mstmtserver.1 man/mstregdump.1 man/mstvpd.1 man/mstprivhost.1 man/mstarchive.1 man/mstreg.1 man/mstfwtrace.1 man/mstlink.1 man/mstcongestion.1 man/mstfwmanager.1 man/mstfwreset.1 man/mstresourcedump.1

EXTRA_DIST = \
	mstflint.spec \
	tools_git_sha \
	debian \
	$(man_MANS)
