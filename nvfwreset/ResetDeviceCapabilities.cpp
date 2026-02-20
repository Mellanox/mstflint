/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 */

#include "ResetDeviceCapabilities.h"
#include "ResetParameterDefs.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "reg_access/reg_access.h"
#include "reg_access/reg_ids.h"
#include "reg_access/mcam_capabilities.h"
#include "tools_layouts/reg_access_hca_layouts.h"

using namespace mft_core;

ResetDeviceCapabilities::ResetDeviceCapabilities(mfile* mf, NVFWresetParams& params)
{
    try
    {
        if (!isMroqSupported(mf))
        {
            throw MftGeneralException("MROQ is not supported on this device.");
        }

        reg_access_hca_mroq_ext mroq = sendMroqCommand(mf, params);
        parseResetLevels(mroq);
        parseResetSyncTypes(mroq);
        parseResetMethods(mroq);
    }
    catch (const std::exception& e)
    {
        throw MftGeneralException(e.what());
    }
}

reg_access_hca_mroq_ext ResetDeviceCapabilities::sendMroqCommand(mfile* mf, NVFWresetParams& params)
{
    reg_access_hca_mroq_ext mroq;
    memset(&mroq, 0, sizeof(mroq));
    ResetType resetType = params.resetType == ResetType::UNKNOWN ? ResetType::FULL_CHIP : params.resetType;
    mroq.reset_type = static_cast<u_int8_t>(resetType);
    reg_access_status_t status = reg_access_mroq(mf, REG_ACCESS_METHOD_GET, &mroq);
    if (status != ME_REG_ACCESS_OK)
    {
        throw MftGeneralException("Failed to send MROQ command: " + std::string(reg_access_err2str(status)));
    }
    LOG.Info("ResetDeviceCapabilities::sendMroqCommand: reset_type: " + std::to_string(mroq.reset_type) +
             ", pci_sync_for_fw_update_start: " + std::to_string(mroq.pci_sync_for_fw_update_start) +
             ", pci_reset_req_method: " + std::to_string(mroq.pci_reset_req_method));
    return mroq;
}

bool ResetDeviceCapabilities::isMroqSupported(mfile* mf)
{
    bool mroqSupported = false;
    reg_access_status_t rc = ME_OK;
    char dbdf[20];
    snprintf(dbdf, sizeof(dbdf), "%04x:%02x:%02x.%x", mf->dinfo->pci.domain, mf->dinfo->pci.bus, mf->dinfo->pci.dev, mf->dinfo->pci.func);
    rc = isRegisterValidAccordingToMcamReg(mf, REG_ID_MROQ, &mroqSupported);
    if (rc != ME_OK)
    {
        LOG_AND_THROW_MFT_ERROR(std::string("Failed to check if MROQ register is supported for dbdf: ") + dbdf);
    }
    if (!mroqSupported)
    {
        LOG_AND_THROW_MFT_ERROR(std::string("MROQ register is not supported for dbdf: ") + dbdf);
    }
    return mroqSupported;
}

void ResetDeviceCapabilities::parseResetLevels(reg_access_hca_mroq_ext& mroq)
{
    // reset_trigger contains the supported reset triggers/levels as a bitmask
    // Bit 0: LIVE_PATCH
    // Bit 1: IMMEDIATE_RESET
    // Bit 4: PCI_RESET
    // Bit 6: WARM_REBOOT
    if (mroq.reset_trigger & static_cast<u_int8_t>(ResetLevelBitmask::LIVE_PATCH))
        _resetDeviceParam.levelSupported.insert(ResetLevel::LIVE_PATCH);
    if (mroq.reset_trigger & static_cast<u_int8_t>(ResetLevelBitmask::IMMEDIATE_RESET))
        _resetDeviceParam.levelSupported.insert(ResetLevel::IMMEDIATE_RESET);
    if (mroq.reset_trigger & static_cast<u_int8_t>(ResetLevelBitmask::PCI_RESET))
        _resetDeviceParam.levelSupported.insert(ResetLevel::PCI_RESET);
    if (mroq.reset_trigger & static_cast<u_int8_t>(ResetLevelBitmask::WARM_REBOOT))
        _resetDeviceParam.levelSupported.insert(ResetLevel::WARM_REBOOT);
}

void ResetDeviceCapabilities::parseResetMethods(reg_access_hca_mroq_ext& mroq)
{
    // pci_reset_req_method contains the supported reset methods as a bitmask
    // Bit 0: Link_Disable
    // Bit 1: Hot_Reset (SBR)
    if (mroq.pci_reset_req_method & static_cast<u_int8_t>(ResetMethodBitmask::LINK_DISABLE))
        _resetDeviceParam.methodSupported.insert(ResetMethod::LINK_DISABLE);
    if (mroq.pci_reset_req_method & static_cast<u_int8_t>(ResetMethodBitmask::HOT_RESET))
        _resetDeviceParam.methodSupported.insert(ResetMethod::HOT_RESET);
}

void ResetDeviceCapabilities::parseResetSyncTypes(reg_access_hca_mroq_ext& mroq)
{
    // pci_sync_for_fw_update_start contains the supported sync types as a bitmask
    // Bit 0: TOOL_FLOW
    // Bit 1: DRIVER_FLOW
    // Bit 2: FW_FLOW
    if (mroq.pci_sync_for_fw_update_start & static_cast<u_int8_t>(ResetSyncBitmask::TOOL_FLOW))
        _resetDeviceParam.syncSupported.insert(ResetSync::TOOL_FLOW);
    if (mroq.pci_sync_for_fw_update_start & static_cast<u_int8_t>(ResetSyncBitmask::DRIVER_FLOW))
        _resetDeviceParam.syncSupported.insert(ResetSync::DRIVER_FLOW);
    if (mroq.pci_sync_for_fw_update_start & static_cast<u_int8_t>(ResetSyncBitmask::FW_FLOW))
        _resetDeviceParam.syncSupported.insert(ResetSync::FW_FLOW);
}