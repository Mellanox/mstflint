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

#include "ResetParameterChooser.h"
#include "ResetParameterDefs.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "dev_mgt/tools_dev_types.h"

using namespace mft_core;

ResetFlowParameters ResetParameterChooser::getResetFlowParameters(const mfile* mf,
                                                                  std::vector<std::string>& asicDBDFTargets) const
{
    if (!DeviceTypeDetector::IsPCIESwitchDevice(mf))
    {
        throw MftGeneralException("This tool supports only PCIe switch devices, exiting...");
    }

    if ((mf->dinfo->pci.dev_id == DeviceBlueField2_HwId || mf->dinfo->pci.dev_id == DeviceBlueField3_HwId) &&
        DeviceTypeDetector::IsInInternalHost())
    {
        throw MftGeneralException("This tool supports only PCIe switch devices in host mode, exiting...");
    }

    DeviceTypeDetector::AddSocketDirectDevices(mf, asicDBDFTargets);

    return PrepareResetFlowParameters();
}

ResetFlowParameters ResetParameterChooser::PrepareResetFlowParameters() const
{
    const ResetDeviceParam& resetDeviceParam = _resetDeviceCapabilities.getResetDeviceParam();

    // Check if sync 2 is supported
    if (resetDeviceParam.syncSupported.find(ResetSync::FW_FLOW) == resetDeviceParam.syncSupported.end())
    {
        throw MftGeneralException("Sync 2 is not supported, which is required for PCIe switch devices");
    }
    ResetSync requiredSync = ResetSync::FW_FLOW;

    // Check if the method is supported.
    if (resetDeviceParam.methodSupported.find(ResetMethod::HOT_RESET) == resetDeviceParam.methodSupported.end())
    {
        throw MftGeneralException("Hot reset is not supported, which is required for PCIe switch devices");
    }
    ResetMethod requiredMethod = ResetMethod::HOT_RESET;

    // Check if the reset level is supported.
    if (resetDeviceParam.levelSupported.find(ResetLevel::PCI_RESET) == resetDeviceParam.levelSupported.end())
    {
        throw MftGeneralException("PCI reset is not supported, which is required for PCIe switch devices");
    }
    ResetLevel requiredLevel = ResetLevel::PCI_RESET;

    // FULL Chip reset type is the MROQ register index value 0.
    ResetType requiredType = ResetType::FULL_CHIP;

    return ResetFlowParameters{requiredLevel, requiredType, requiredSync, requiredMethod};
}
