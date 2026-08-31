# Copyright (c) 2023-2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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

SUBDIRS = $(NVML_DIR) ext_libs mft_core $(TOOLS_CRYPTO) tools_layouts common $(VFIO_DRIVER_DIR) ${MTCR_CONF_DIR} mtcr_py $(MAD_IFC) $(XZ_UTILS_DIR) reg_access cmdif dev_mgt pci_library mft_utils $(CABLE_ACCESS_DIR) tools_res_mgmt mvpd mflash fw_comps_mgr libmfa pldm_utils pldmlib cmdparser $(DPA) mlxfwops mlxconfig $(NVFWRESET_DIR) $(FW_MGR_TOOLS) $(PLDM_PKG_GEN) mlxtokengenerator flint small_utils mst_utils mstdump efuse ${ADABE_TOOLS} $(HCA_CAP_DIR) $(MSTFLINT_SDK_DIR) tracers resourcetools $(IBDUMP_DIR)

DIST_SUBDIRS = tracers

man_MANS = man/mstflint.1 man/mstconfig.1 man/mstmcra.1 man/mstmread.1 man/mstmwrite.1 man/mstmtserver.1 man/mstregdump.1 man/mstvpd.1 man/mstprivhost.1 man/mstarchive.1 man/mstreg.1 man/mstfwtrace.1 man/mstlink.1 man/mstcongestion.1 man/mstfwmanager.1 man/mstfwreset.1 man/mstresourcedump.1

EXTRA_DIST = \
	mstflint.spec \
	mstflint-sdk.spec \
	tools_git_sha \
	debian \
	$(man_MANS)

# ---------------------------------------------------------------------------
# Standalone mstflint SDK build
#
# Builds and installs only libmstflint_sdk.so and the subdirectories it links
# against, skipping the rest of the tool suite (flint, mlxconfig, mstdump, ...).
# Requires configuring with --enable-mstflint-sdk (which itself requires
# --enable-adb-generic-tools).
#
#   make sdk           # build the SDK and its dependencies only
#   make install-sdk   # install the SDK library, headers and PRM databases
#
# mtcr is absorbed statically into the .so (mft_sdk/Makefile.am), so the only
# installed runtime artifacts are the SDK library, its headers and the PRM
# databases the SDK opens at runtime (prm_dbs/{hca,gpu,switch}/ext).
# ---------------------------------------------------------------------------
if ENABLE_MSTFLINT_SDK

# Dependency subdirs in the same relative order as the top-level SUBDIRS, so
# the proven build order is preserved. Building the mlxreg/mlxlink parents also
# builds the convenience libs the SDK links (libmstreg_lib, libmlxreg_sdk,
# libmodules_lib); mft_core builds the mft_core_utils and NVML libs.
SDK_BUILD_SUBDIRS = \
	ext_libs \
	mft_core \
	tools_layouts \
	common \
	$(VFIO_DRIVER_DIR) \
	${MTCR_CONF_DIR} \
	$(XZ_UTILS_DIR) \
	reg_access \
	cmdif \
	dev_mgt \
	pci_library \
	mft_utils \
	cmdparser \
	$(ADABE_TOOLS) \
	$(HCA_CAP_DIR) \
	$(MSTFLINT_SDK_DIR)

# Subdirs that install SDK runtime artifacts: the .so and headers (mft_sdk) and
# the PRM databases getDefaultDBName() opens under $(pkgdatadir)/prm_dbs.
SDK_INSTALL_SUBDIRS = \
	$(MSTFLINT_SDK_DIR) \
	tools_layouts/adb/prm/hca/ext \
	tools_layouts/adb/prm/gpu/ext \
	tools_layouts/adb/prm/switch/ext

sdk:
	@for dir in $(SDK_BUILD_SUBDIRS); do \
		echo "  SDK-BUILD    $$dir"; \
		$(MAKE) $(AM_MAKEFLAGS) -C $$dir all || exit 1; \
	done

install-sdk: sdk
	@for dir in $(SDK_INSTALL_SUBDIRS); do \
		echo "  SDK-INSTALL  $$dir"; \
		$(MAKE) $(AM_MAKEFLAGS) -C $$dir install || exit 1; \
	done

else

sdk install-sdk:
	@echo "error: the standalone SDK targets require ./configure --enable-mstflint-sdk" >&2; \
	exit 1

endif

.PHONY: sdk install-sdk
