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

#include <fstream>
#include <algorithm>
#include <cstdint>
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "reg_access/reg_access.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "tools_layouts/reg_access_hca_layouts.h"
#include "ResetParameterDefs.h"
#include "DeviceTypeDetectorDefs.h"
#include "DeviceTypeDetector.h"
#include "dev_mgt/tools_dev_types.h"
#include "mtcr.h"
#include "mtcr_ul/mtcr_icmd_cif.h"

const std::vector<std::uint32_t> socketDirectSupportedDevID = {0x226, 0x224, 0x21e, 0x218, 0x216, 0x212, 0x20f,
                                                               0x20d, 0x209, 0x20b, 0x21c, 0x222, 0x223};

bool DeviceTypeDetector::IsPCIESwitchDevice(const mfile* mf)
{
    bool isPCIESwitch = false;
    if (mf == nullptr || mf->dinfo == nullptr)
    {
        throw mft_core::MftGeneralException("Device is not open");
    }

    int pcieIndex = PCI_INDEX_0;
    isPCIESwitch = IsUpstreamPortType(mf, pcieIndex);
    if (!isPCIESwitch)
    {
        pcieIndex = PCI_INDEX_1;
        try
        {
            if (IsUpstreamPortType(mf, pcieIndex))
            {
                isPCIESwitch = true;
            }
        }
        catch (const std::exception& e)
        {
            LOG.Error("DeviceTypeDetector::IsPCIESwitchDevice: Failed to check if device is a PCI Switch with: " +
                      std::string(e.what()));
        }
    }
    LOG.Info("DeviceTypeDetector::IsPCIESwitchDevice: device is" + std::string(isPCIESwitch ? " a" : " not a") +
             " PCI Switch with PCIe index " + std::to_string(pcieIndex));
    return isPCIESwitch;
}

bool DeviceTypeDetector::IsUpstreamPortType(const mfile* mf, int pcieIndex)
{
    bool isUpstreamPort = false;
    reg_access_hca_mpein_reg_ext mpein;
    memset(&mpein, 0, sizeof(reg_access_hca_mpein_reg_ext));
    mpein.pcie_index = pcieIndex;
    reg_access_status_t status = reg_access_mpein(const_cast<mfile*>(mf), REG_ACCESS_METHOD_GET, &mpein);
    if (status != ME_REG_ACCESS_OK)
    {
        throw mft_core::MftGeneralException("Failed to send MPEIN: " + std::string(reg_access_err2str(status)));
    }
    if (mpein.port_type == PCI_EXPRESS_UPSTREAM_PORT)
    {
        isUpstreamPort = true;
    }
    return isUpstreamPort;
}

bool DeviceTypeDetector::IsInInternalHost()
{
    bool isInInternalHost = false;
    std::ifstream file(std::string("/sys/bus/pci/devices/") + std::string(MELLANOX_INTERNAL_HOST_PCI_ADDRESS) +
                       "/vendor");
    if (file.is_open())
    {
        std::string line;
        std::getline(file, line);
        line.erase(0, line.find_first_not_of(" \t\n\r"));
        isInInternalHost = (line == std::to_string(MELLANOX_VENDOR_ID));
    }

    return isInInternalHost;
}

std::string DeviceTypeDetector::GetMacAddress(const mfile* mf)
{
    reg_access_hca_mgir_ext mgir;
    memset(&mgir, 0, sizeof(reg_access_hca_mgir_ext));
    reg_access_status_t status = reg_access_mgir(const_cast<mfile*>(mf), REG_ACCESS_METHOD_GET, &mgir);
    if (status != ME_REG_ACCESS_OK)
    {
        throw mft_core::MftGeneralException("Failed to send MGIR: " + std::string(reg_access_err2str(status)));
    }
    return std::to_string(mgir.hw_info.manufacturing_base_mac_31_0) +
           std::to_string(mgir.hw_info.manufacturing_base_mac_47_32);
}

void DeviceTypeDetector::AddSocketDirectDevices(const mfile* mf, std::vector<std::string>& asicDBDFTargets)
{
    if (std::find(socketDirectSupportedDevID.begin(), socketDirectSupportedDevID.end(), mf->dinfo->pci.dev_id) !=
        socketDirectSupportedDevID.end())
    {
        return;
    }

    std::string macAddress = GetMacAddress(mf);
    if (macAddress.empty())
    {
        LOG_AND_THROW_MFT_ERROR(std::string("Failed to get MAC address for device: ") +
                                std::to_string(mf->dinfo->pci.domain) + ":" + std::to_string(mf->dinfo->pci.bus) + ":" +
                                std::to_string(mf->dinfo->pci.dev) + ":" + std::to_string(mf->dinfo->pci.func));
    }

    int numDevices = 0;
    mfile* currentMF = nullptr;
    dev_info* pciDevices = mdevices_info(MDEVS_TAVOR_CR, &numDevices);
    if (!pciDevices)
    {
        LOG_AND_THROW_MFT_ERROR(std::string("Failed to get devices info. numDevices: ") + std::to_string(numDevices));
    }
    for (int count = 0; count < numDevices; count++)
    {
        mclose(currentMF);
        currentMF = mopen(pciDevices[count].dev_name);
        if (!currentMF)
        {
            LOG.Error(std::string("Failed to open device: ") + pciDevices[count].dev_name);
            continue;
        }

        // Skip if the current device is the same as the user's device
        if (currentMF->dinfo->pci.domain == mf->dinfo->pci.domain && currentMF->dinfo->pci.bus == mf->dinfo->pci.bus &&
            currentMF->dinfo->pci.dev == mf->dinfo->pci.dev && currentMF->dinfo->pci.func == mf->dinfo->pci.func)
        {
            continue;
        }

        // Skip if the current device is not the same device type as the user's device
        if (currentMF->dinfo->pci.dev_id != mf->dinfo->pci.dev_id)
        {
            continue;
        }

        // Check only function 0 (skip otherwise)
        if (currentMF->dinfo->pci.func != 0)
        {
            continue;
        }

        // Skip if device in livefish mode
        if (is_livefish_device(currentMF))
        {
            continue;
        }

        try
        {
            std::string currentMacAddress = GetMacAddress(currentMF);
            if (macAddress.compare(currentMacAddress) != 0)
            {
                continue;
            }
        }
        catch (const std::exception& e)
        {
            continue;
        }

        char dbdf[32] = {0};
        snprintf(dbdf,
                 sizeof(dbdf),
                 "%04x:%02x:%02x.%x",
                 currentMF->dinfo->pci.domain,
                 currentMF->dinfo->pci.bus,
                 currentMF->dinfo->pci.dev,
                 currentMF->dinfo->pci.func);
        asicDBDFTargets.push_back(dbdf);

        // No need to continue searching for socket direct devices, only one with the same MAC address is allowed.
        break;
    }
    mdevices_info_destroy(pciDevices, numDevices);
}