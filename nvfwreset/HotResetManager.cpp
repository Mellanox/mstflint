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

#include "HotResetManager.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "ResetParameterDefs.h"
#include "reg_access/reg_access.h"
#include "reg_access/reg_ids.h"
#include "reg_access/mcam_capabilities.h"
#include "common/PCILibrary.h"
#include "mft_core/mft_core_utils/logger/Logger.h"
#include "kernel/mst.h"
#include "common/tools_algorithm.h"
#include <sys/ioctl.h>
#include <glob.h>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include "common/tools_time.h"

namespace Filesystem = mstflint::common::algorithm;

HotResetManager::HotResetManager(mfile* mf, std::vector<std::string> asicDBDFTargets, bool isPcieSwitch) :
    _mf(mf), _asicDBDFTargets(asicDBDFTargets), _hot_reset_flow(HotResetFlow::UNKNOWN), _isPcieSwitch(isPcieSwitch)
{
    _operatingSystemAPI = FactoryOperatingSystemAPI::GetInstance();
    CheckPCIRegistersSupported();
}

void HotResetManager::CheckPCIRegistersSupported()
{
    bool mpir_supported = false;
    reg_access_status_t rc = ME_OK;
    std::string dbdf = std::to_string(_mf->dinfo->pci.domain) + ":" + std::to_string(_mf->dinfo->pci.bus) + ":" +
                       std::to_string(_mf->dinfo->pci.dev) + "." + std::to_string(_mf->dinfo->pci.func);
    rc = isRegisterValidAccordingToMcamReg(_mf, REG_ID_MPIR, &mpir_supported);
    if (rc != ME_OK)
    {
        LOG_AND_THROW_MFT_ERROR(std::string("Failed to check if MPIR register is supported for dbdf: ") + dbdf);
    }
    if (!mpir_supported)
    {
        LOG_AND_THROW_MFT_ERROR(std::string("MPIR register is not supported for dbdf: ") + dbdf);
    }
}

void HotResetManager::PrepareHotResetFlow(const std::vector<std::string>& driverIgnoreList)
{
    uint8_t requesterPcieIndex;
    SendMPQD(&requesterPcieIndex);
    SetHotResetFlow(requesterPcieIndex);
    CheckBindedDrivers(driverIgnoreList);
}

void HotResetManager::CheckBindedDrivers(const std::vector<std::string>& driverIgnoreList)
{
    std::map<std::string, std::string> forbiddenDrivers = CheckForbiddenDriversOnDiscoveredDevices();
    for (const std::string& driverToIgnore : driverIgnoreList)
    {
        std::string trimmedDriver = driverToIgnore;
        Filesystem::trim(trimmedDriver);
        for (const auto& forbiddenDriver : forbiddenDrivers)
        {
            if (forbiddenDriver.second == trimmedDriver)
            {
                LOG.Info("HotResetManager::CheckBindedDrivers: erasing driver: " + trimmedDriver);
                forbiddenDrivers[forbiddenDriver.first] = "IGNORED";
            }
        }
    }

    bool hasForbiddenDrivers = false;
    for (const auto& forbiddenDriver : forbiddenDrivers)
    {
        if (forbiddenDriver.second != "IGNORED")
        {
            if (!hasForbiddenDrivers)
            {
                LOG.Info("HotResetManager::CheckBindedDrivers: forbiddenDrivers: " + forbiddenDrivers.size());
                std::cout << std::endl;
                std::cout << "ERROR: The following drivers are currently bound to PCI devices on the switch:"
                          << std::endl;
                std::cout << "==============================================================================="
                          << std::endl;
                std::cout << "PCI           | Driver\n";
                std::cout << "--------------|----------\n";
            }
            hasForbiddenDrivers = true;

            std::cout << forbiddenDriver.first << "  | " << forbiddenDriver.second << std::endl;
        }
    }

    if (hasForbiddenDrivers)
    {
        throw mft_core::MftGeneralException(
          "\n"
          "Please unbind the drivers or add them to the ignore list.\n"
          "Driver that is resilient to device reset can be added to ignore list, for example:\n"
          "--ignore_list \"driver_1, driver_2, driver_3\n"
          "Exiting...\n");
    }
}

bool HotResetManager::IsBridgeDevice(const std::string& dbdf)
{
    std::string cmd = "lspci -s " + dbdf + " -n";
    LOG.Debug("Running command: " + cmd);
    auto rc_out = _operatingSystemAPI->execCommand(cmd);
    if (rc_out.first != 0)
    {
        throw mft_core::MftGeneralException("Failed to run: " + cmd);
    }
    std::string output = rc_out.second;
    if (output.empty())
    {
        throw mft_core::MftGeneralException("Empty output from lspci command for device " + dbdf);
    }

    std::istringstream iss(output);
    std::string bdf, classCode;
    iss >> bdf >> classCode;

    bool isUpstreamPort = (classCode.rfind("0604", 0) == 0); // 0604 is the class code for upstream ports

    return isUpstreamPort;
}


// Get the PCIe Device/Port Type for a given DBDF.
// Returns the PCIeDeviceType value (bits [7:4] of CAP_EXP+0x02).

PCIeDeviceType HotResetManager::GetPcieDeviceType(const std::string& dbdf)
{
    std::string cmd = "setpci -s " + dbdf + " CAP_EXP+0x02.w";
    LOG.Debug("Running command: " + cmd);
    auto rc_out = _operatingSystemAPI->execCommand(cmd);
    int rc = rc_out.first;
    std::string output = rc_out.second;

    if (rc != 0)
    {
        throw mft_core::MftGeneralException("Failed to run: " + cmd + ". Error: " + output);
    }

    // Strip whitespaces
    output.erase(remove_if(output.begin(), output.end(), ::isspace), output.end());

    // Check if output is a valid 4-hex-digit string
    if (output.size() != 4 ||
        output.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
    {
        throw mft_core::MftGeneralException("Invalid PCIe device type: " + output);
    }

    int value = std::stoi(output, nullptr, 16);
    PCIeDeviceType deviceType = static_cast<PCIeDeviceType>((value >> 4) & 0xf);

    return deviceType;
}

bool HotResetManager::IsUpstreamPortType(const std::string& dbdf)
{
    return GetPcieDeviceType(dbdf) == PCIeDeviceType::UPSTREAM_PORT;
}

bool HotResetManager::IsDownstreamPortType(const std::string& dbdf)
{
    return GetPcieDeviceType(dbdf) == PCIeDeviceType::DOWNSTREAM_PORT;
}

bool HotResetManager::IsLeafSwitchUnderneath(const std::string& downstream_dbdf)
{
    // Get the domain from the downstream port DBDF (format: domain:bus:device.function)
    size_t first_colon = downstream_dbdf.find(':');
    if (first_colon == std::string::npos)
        return false;
    std::string domain = downstream_dbdf.substr(0, first_colon);

    // Get SECONDARY_BUS from the downstream port
    std::string cmd = "setpci -s " + downstream_dbdf + " SECONDARY_BUS";
    LOG.Debug("Running command: " + cmd);
    auto rc_out = _operatingSystemAPI->execCommand(cmd);
    int rc = rc_out.first;
    std::string output = rc_out.second;

    if (rc != 0)
    {
        return false;
    }

    // Clean whitespace
    output.erase(remove_if(output.begin(), output.end(), ::isspace), output.end());

    // Check if output is valid (should be 2-hex-digits)
    if (output.size() != 2 ||
        output.find_first_not_of("0123456789abcdefABCDEF") != std::string::npos)
    {
        return false;
    }

    std::string secondary_bus = output;
    // Construct the potential upstream port DBDF (domain:secondary_bus:00.0)
    std::string potential_upstream_dbdf = domain + ":" + secondary_bus + ":00.0";
    LOG.Debug("Potential upstream DBDF: " + potential_upstream_dbdf);

    try
    {
        if (IsUpstreamPortType(potential_upstream_dbdf))
        {
            LOG.Debug("Potential upstream DBDF is an upstream port");
            return true;
        }
        else
        {
            LOG.Debug("Potential upstream DBDF is not an upstream port");
            return false;
        }
    }
    catch (const std::exception& e)
    {
        LOG.Debug(std::string("Failed to get the PCIe device type for potential upstream DBDF: ") +
                  potential_upstream_dbdf + ". Error: " + e.what());
        return false;
    }
}

std::map<std::string, std::string> HotResetManager::CheckForbiddenDriversOnDiscoveredDevices()
{
    std::map<std::string, std::string> forbiddenDrivers;
    for (const auto& dbdf : _asicDBDFTargets)
    {
        std::string upstream_dbdf;
        std::string domain = dbdf.substr(0, 4);
        std::string device = dbdf.substr(8, 2);
        if (IsBridgeDevice(dbdf))
        {
            upstream_dbdf = dbdf;
        }
        else
        {
            uint8_t requesterPcieIndex;
            uint8_t bus;
            uint8_t device;
            SendMPQD(&requesterPcieIndex);
            SendMPIR(requesterPcieIndex, &bus, &device);
            std::ostringstream oss;
            oss << domain << ":" << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(bus) << ":"
                << std::setw(2) << static_cast<int>(device) << ".0";

            upstream_dbdf = oss.str();
        }
        LOG.Info("HotResetManager::CheckForbiddenDriversOnDiscoveredDevices: new upstream_dbdf: " + upstream_dbdf);
        _upstream_dbdfs.push_back(upstream_dbdf);

        if (_isPcieSwitch)
        {
            {
                std::map<std::string, std::string> drivers = GetForbiddenDriversFromUpstreamPort(upstream_dbdf, dbdf);
                if (!drivers.empty())
                {
                    forbiddenDrivers.insert(drivers.begin(), drivers.end());
                }
            }
        }
    }
    LOG.Info("HotResetManager::CheckForbiddenDriversOnDiscoveredDevices: upstream_dbdfs: " + _upstream_dbdfs.size());

    return forbiddenDrivers;
}

void HotResetManager::GetSecondaryAndSubordinateBuses(const std::string& upstream_dbdf,
                                                      uint8_t* secondaryBus,
                                                      uint8_t* subordinateBus)
{
    std::string cmdSecondaryBus = "setpci -s " + upstream_dbdf + " SECONDARY_BUS";
    std::string cmdSubordinateBus = "setpci -s " + upstream_dbdf + " SUBORDINATE_BUS";
    auto rc_outSecondaryBus = _operatingSystemAPI->execCommand(cmdSecondaryBus);
    auto rc_outSubordinateBus = _operatingSystemAPI->execCommand(cmdSubordinateBus);
    if (rc_outSecondaryBus.first != 0 || rc_outSubordinateBus.first != 0)
    {
        throw mft_core::MftGeneralException("Failed to run: " + cmdSecondaryBus + " or " + cmdSubordinateBus);
    }
    std::string outputSecondaryBus = rc_outSecondaryBus.second;
    std::string outputSubordinateBus = rc_outSubordinateBus.second;
    *secondaryBus = static_cast<uint8_t>(std::stoi(outputSecondaryBus, nullptr, 16));
    *subordinateBus = static_cast<uint8_t>(std::stoi(outputSubordinateBus, nullptr, 16));
    if (*secondaryBus == 0 && *subordinateBus == 0)
    {
        LOG.Info(
          "HotResetManager::GetForbiddenDriversFromUpstreamPort: secondary and subordinate bus are 0, meaning there are no downstream devices. Skipping scan.");
        return;
    }
    LOG.Info("HotResetManager::GetSecondaryAndSubordinateBuses: secondaryBus: " + std::to_string(*secondaryBus));
    LOG.Info("HotResetManager::GetSecondaryAndSubordinateBuses: subordinateBus: " + std::to_string(*subordinateBus));
}

std::map<std::string, std::string>
  HotResetManager::GetForbiddenDriversFromUpstreamPort(const std::string& upstream_dbdf, const std::string& dbdf)
{
    std::map<std::string, std::string> forbiddenDrivers;
    uint8_t secondaryBus, subordinateBus;
    LOG.Info("HotResetManager::GetForbiddenDriversFromUpstreamPort: upstream_dbdf: " + upstream_dbdf);
    GetSecondaryAndSubordinateBuses(upstream_dbdf, &secondaryBus, &subordinateBus);

    std::string domain = upstream_dbdf.substr(0, 4);
    std::string dbd = dbdf.substr(0, 10);
    for (uint8_t bus = secondaryBus; bus <= subordinateBus; bus++)
    {
        std::map<std::string, std::string> pci_devices = GetAllPciDevicesForDomainBus(domain, bus);
        for (const std::pair<std::string, std::string>& pci_device : pci_devices)
        {
            LOG.Info("HotResetManager::GetForbiddenDriversFromUpstreamPort: pci_device: " + pci_device.first);
            if (pci_device.first.rfind(dbd, 0) == 0)
            {
                continue;
            }

            if (IsUpstreamPortType(pci_device.first))
            {
                LOG.Info("HotResetManager::GetForbiddenDriversFromUpstreamPort: pci_device is an upstream port. Skipping scan.");
                continue;
            }
            if (IsDownstreamPortType(pci_device.first) && (!IsLeafSwitchUnderneath(pci_device.first)))
            {
                LOG.Info("HotResetManager::GetForbiddenDriversFromUpstreamPort: pci_device is a downstream port and a leaf switch underneath. Skipping scan.");
                continue;
            }

            auto rc_out = _operatingSystemAPI->execCommand("lspci -k -s " + pci_device.first);
            if (rc_out.first != 0)
            {
                throw mft_core::MftGeneralException("Failed to run: lspci -k -s " + pci_device.first);
            }
            std::string output = rc_out.second;
            LOG.Info("HotResetManager::GetForbiddenDriversFromUpstreamPort: output: " + output);
            std::istringstream output_stream(output);
            std::string line;
            while (std::getline(output_stream, line))
            {
                if (line.find("Kernel driver in use:") != std::string::npos)
                {
                    std::string tag = "Kernel driver in use:";
                    std::string driver = line.substr(line.find(tag) + std::string(tag).size());
                    Filesystem::trim(driver);
                    LOG.Info("HotResetManager::GetForbiddenDriversFromUpstreamPort: driver: " + driver);
                    forbiddenDrivers[pci_device.first] = driver;
                }
            }
        }
    }
    return forbiddenDrivers;
}

std::map<std::string, std::string> HotResetManager::GetAllPciDevicesForDomainBus(const std::string& domain, uint8_t bus)
{
    std::map<std::string, std::string> devices;
    char pattern[128];
    snprintf(pattern, sizeof(pattern), "/sys/bus/pci/devices/%s:%02x:*", domain.c_str(), bus);

    glob_t globResult;
    memset(&globResult, 0, sizeof(glob_t));
    if (glob(pattern, GLOB_NOSORT, nullptr, &globResult) == 0)
    {
        for (size_t i = 0; i < globResult.gl_pathc; ++i)
        {
            std::string path = globResult.gl_pathv[i];
            std::string dbdf = path.substr(path.find_last_of('/') + 1);
            devices[dbdf] = path;
        }
    }
    globfree(&globResult);

    return devices;
}

void HotResetManager::SendMPQD(uint8_t* requesterPcieIndex)
{
    struct reg_access_hca_mpqd_reg_ext mpqd;
    memset(&mpqd, 0, sizeof(struct reg_access_hca_mpqd_reg_ext));
    mpqd.DPNv = 1;
    reg_access_status_t status = reg_access_mpqd(_mf, REG_ACCESS_METHOD_GET, &mpqd);
    if (status)
    {
        throw mft_core::MftGeneralException("Failed to send MPQD");
    }

    LOG.Info("HotResetManager::SendMPQD: requester_pcie_index: " + std::to_string(mpqd.requester_pcie_index));
    *requesterPcieIndex = mpqd.requester_pcie_index;
}

void HotResetManager::SendMPIR(uint8_t pcie_index, uint8_t* bus, uint8_t* device)
{
    struct reg_access_hca_mpir_ext mpir;
    memset(&mpir, 0, sizeof(struct reg_access_hca_mpir_ext));
    mpir.pcie_index = pcie_index;
    reg_access_status_t status = reg_access_mpir(_mf, REG_ACCESS_METHOD_GET, &mpir);
    if (status)
    {
        throw mft_core::MftGeneralException("Failed to send MPIR");
    }
    LOG.Info("HotResetManager::SendMPIR: sdm: " + std::to_string(mpir.sdm));
    *bus = mpir.bus;
    *device = mpir.device;
}

bool HotResetManager::CheckIfDirectNic(uint8_t requesterPcieIndex)
{
    int numDevices = 0;
    dev_info* pciDevices = mdevices_info(MDEVS_TAVOR_CR, &numDevices);
    if (!pciDevices)
    {
        LOG_AND_THROW_MFT_ERROR(std::string("Failed to get devices info. numDevices: ") + std::to_string(numDevices));
    }
    std::map<std::string, std::uint32_t> directNicDevice;
    PCILibrary::FindDirectNicDevice(directNicDevice);
    LOG.Debug("Number of found direct nic devices: " + std::to_string(directNicDevice.size()));
    if (!directNicDevice.empty())
    {
        std::string v3 = PCILibrary::GetV3FieldFromVPD(_asicDBDFTargets[0]);
        if (directNicDevice.find(v3) != directNicDevice.end())
        {
            struct reg_access_hca_mpir_ext mpir;
            int directNicIndex = 0;
            if (requesterPcieIndex == 0)
            {
                directNicIndex = 1;
            }
            else
            {
                directNicIndex = 0;
            }
            SendMPIR(directNicIndex, &mpir);
            char dbdf[32] = {0};
            snprintf(dbdf, sizeof(dbdf), "%04x:%02x:%02x.0", directNicDevice[v3], mpir.bus, mpir.device);
            _asicDBDFTargets.push_back(dbdf);
            LOG.Info("HotResetManager::CheckIfDirectNic: direct nic device found: " + std::string(dbdf));
            return true;
        }
    }
    LOG.Info("HotResetManager::CheckIfDirectNic: direct nic device not found");
    return false;
}

void HotResetManager::SendMPIR(uint8_t requesterPcieIndex, struct reg_access_hca_mpir_ext* mpir)
{
    memset(mpir, 0, sizeof(struct reg_access_hca_mpir_ext));
    mpir->pcie_index = requesterPcieIndex;
    reg_access_status_t status = reg_access_mpir(_mf, REG_ACCESS_METHOD_GET, mpir);
    if (status)
    {
        throw mft_core::MftGeneralException("Failed to send MPIR");
    }
}

void HotResetManager::SetHotResetFlow(uint8_t requesterPcieIndex)
{
    struct reg_access_hca_mpir_ext mpir;
    SendMPIR(requesterPcieIndex, &mpir);

    bool isDirectNic = CheckIfDirectNic(requesterPcieIndex);
    if (isDirectNic)
    {
        _hot_reset_flow = HotResetFlow::DIRECT_NIC;
    }

    if (mpir.sdm == 1 && _hot_reset_flow == HotResetFlow::UNKNOWN)
    {
        if (_asicDBDFTargets.size() < 2)
        {
            throw mft_core::MftGeneralException(
              "Socket direct device not found by the tool but FW reported this device is socket direct. Exiting...");
        }
        _hot_reset_flow = HotResetFlow::SOCKET_DIRECT;
    }

    if (_hot_reset_flow == HotResetFlow::UNKNOWN)
    {
        _hot_reset_flow = HotResetFlow::SINGLE_DEVICE;
    }

    LOG.Info("HotResetManager::SetHotResetFlow: hot reset flow set successfully");
}

void HotResetManager::ExecuteHotResetFlow()
{
    struct hot_reset_pcie_switch info;
    info.in_parallel = false;

    LOG.Info("HotResetManager::ExecuteHotResetFlow: asicDBDFTarget 1: " + _asicDBDFTargets[0]);
    if (_asicDBDFTargets.size() > 1)
    {
        if (_asicDBDFTargets.size() != 2)
        {
            throw mft_core::MftGeneralException("HotResetManager::ExecuteHotResetFlow: There is more than two devices to reset. Exiting...");
        }
        LOG.Info("HotResetManager::ExecuteHotResetFlow: asicDBDFTarget 2: " + _asicDBDFTargets[1]);
        info.in_parallel = true;
    }

    if (info.in_parallel)
    {
        info.device_2.domain = std::stoi(_asicDBDFTargets[1].substr(0, 4), nullptr, 16);
        info.device_2.bus = std::stoi(_asicDBDFTargets[1].substr(5, 2), nullptr, 16);
        info.device_2.device = std::stoi(_asicDBDFTargets[1].substr(8, 2), nullptr, 16);
        info.device_2.function = 0;
        std::ostringstream device2_os;
        device2_os << "HotResetManager::ExecuteHotResetFlow: device_2: "
                   << std::setfill('0') << std::setw(4) << std::hex << info.device_2.domain << ":"
                   << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(info.device_2.bus) << ":"
                   << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(info.device_2.device) << "."
                   << std::dec << static_cast<int>(info.device_2.function);
        LOG.Info(device2_os.str());
    }

    info.device_1.domain = std::stoi(_asicDBDFTargets[0].substr(0, 4), nullptr, 16);
    info.device_1.bus = std::stoi(_asicDBDFTargets[0].substr(5, 2), nullptr, 16);
    info.device_1.device = std::stoi(_asicDBDFTargets[0].substr(8, 2), nullptr, 16);
    info.device_1.function = std::stoi(_asicDBDFTargets[0].substr(11, 1), nullptr, 16);
    std::ostringstream device1_os;
    device1_os << "HotResetManager::ExecuteHotResetFlow: device_1: "
                << std::setfill('0') << std::setw(4) << std::hex << info.device_1.domain << ":"
                << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(info.device_1.bus) << ":"
                << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(info.device_1.device) << "."
                << std::dec << static_cast<int>(info.device_1.function);
    LOG.Info(device1_os.str());
    int status = ioctl(_mf->fd, PCICONF_HOT_RESET, &info);
    if (status != 0)
    {
        throw mft_core::MftGeneralException(std::string("Failed to send Hot Reset, check dmesg for more details."));
    }

    // Sleep for 2 seconds after sending hot reset
    nbu::mft::common::mft_msleep(2000);

    LOG.Info("HotResetManager::ExecuteHotResetFlow: Hot reset sent successfully");
}