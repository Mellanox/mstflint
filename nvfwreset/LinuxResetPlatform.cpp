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

#include <vector>
#include <sstream>
#include <map>
#include <fstream>
#include <algorithm>
#include <utility>
#include <string.h>
#include "LinuxResetPlatform.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "mft_core/mft_core_utils/logger/Logger.h"
#include "ResetParameterDefs.h"
#include "mft_core/mft_core_utils/operating_system_api/FactoryOperatingSystemAPI.h"
#include "DeviceTypeDetector.h"
#include "common/tools_filesystem.h"
#include "common/tools_time.h"

namespace Filesystem = mstflint::common::filesystem;
using namespace mft_core;
const std::string PCI_DRIVERS_PATH = "/sys/bus/pci/drivers";
// Mellanox drivers that are allowed to be unbound/bound as part of the reset flow
static const std::vector<std::string> MLNX_DRIVERS = {"mlx5_core", "rshim_pcie", "nvme"};
// White-listed non-Mellanox drivers (e.g. PCIe port driver on parent bridges)
static const std::vector<std::string> WHITE_LIST_DRIVERS = {"pcieport"};

LinuxResetPlatform::LinuxResetPlatform(mfile* mf,
                                       const ResetFlowParameters& resetParams,
                                       const std::vector<std::string>& asicDBDFTargets) :
    CommonResetPlatform(mf, resetParams, asicDBDFTargets),
    _hotResetManager(mf, asicDBDFTargets, DeviceTypeDetector::IsPCIESwitchDevice(mf))
{
    _operatingSystemAPI = FactoryOperatingSystemAPI::GetInstance();
}

LinuxResetPlatform::~LinuxResetPlatform() {}

bool LinuxResetPlatform::IsNicDriverBound(const std::string& dbdf)
{
    std::string driverLink = std::string("/sys/bus/pci/devices/") + dbdf + "/driver";

    return Filesystem::exists(Filesystem::path(driverLink));
}

// Scan /sys/bus/pci/drivers/<driver_name>/ for every entry whose filename shares the
// DBD (domain:bus:device) prefix with one of the asic DBDF targets. This mirrors the
// python logic in MlnxDriverLinux (mlxfwreset_mlnxdriver.py) that iterates over all
// PCI functions currently bound to any driver (not only the target function). Every
// matched (dbdf, driver_name) pair will later need to be unbound before the reset and
// re-bound afterwards.
std::vector<std::pair<std::string, std::string>> LinuxResetPlatform::DiscoverBoundDrivers()
{
    std::vector<std::pair<std::string, std::string>> driversDbdf;

    Filesystem::path driversDir(PCI_DRIVERS_PATH);
    if (!Filesystem::exists(driversDir))
    {
        throw MftGeneralException("path " + PCI_DRIVERS_PATH + " doesn't exist!");
    }

    // Build the list of DBD prefixes (dbdf without the function number) from the asic targets
    std::vector<std::string> dbdPrefixes;
    dbdPrefixes.reserve(_asicDBDFTargets.size());
    for (const auto& asicDBDFTarget : _asicDBDFTargets)
    {
        const auto dotPos = asicDBDFTarget.find('.');
        dbdPrefixes.push_back(dotPos == std::string::npos ? asicDBDFTarget : asicDBDFTarget.substr(0, dotPos));
    }

    for (const auto& driverEntry : Filesystem::directory_iterator(driversDir))
    {
        if (!Filesystem::is_directory(driverEntry.path()))
        {
            continue;
        }

        const std::string driverName = driverEntry.path().filename().string();

        for (const auto& deviceEntry : Filesystem::directory_iterator(driverEntry.path()))
        {
            const std::string dbdf = deviceEntry.path().filename().string();

            bool matches = false;
            for (const auto& dbd : dbdPrefixes)
            {
                if (!dbd.empty() && dbdf.compare(0, dbd.size(), dbd) == 0)
                {
                    matches = true;
                    break;
                }
            }
            if (!matches)
            {
                continue;
            }

            const bool isMlnx = std::find(MLNX_DRIVERS.begin(), MLNX_DRIVERS.end(), driverName) != MLNX_DRIVERS.end();
            const bool isWhiteListed =
                std::find(WHITE_LIST_DRIVERS.begin(), WHITE_LIST_DRIVERS.end(), driverName) != WHITE_LIST_DRIVERS.end();
            if (!isMlnx && !isWhiteListed)
            {
                std::ostringstream errMsg;
                errMsg << "nvfwreset doesn't support 3rd party driver (" << driverName
                       << ") bound to " << dbdf
                       << "! Please stop the driver manually and resume operation with --skip_driver";
                throw MftGeneralException(errMsg.str());
            }

            LOG.Info("Discovered bound driver '" + driverName + "' on " + dbdf);
            driversDbdf.emplace_back(dbdf, driverName);
        }
    }

    std::sort(driversDbdf.begin(), driversDbdf.end());
    return driversDbdf;
}

void LinuxResetPlatform::ToggleNicDriver(const std::string& dbdf, const std::string& driverName, bool unbind)
{
    const std::string sysfsPath = PCI_DRIVERS_PATH + "/" + driverName + (unbind ? "/unbind" : "/bind");

    LOG.Info("Writing '" + dbdf + "' to " + sysfsPath);

    std::ofstream outFile(sysfsPath);
    if (!outFile.is_open())
    {
        std::ostringstream errMsg;
        errMsg << "Failed to open " << sysfsPath << " for " << (unbind ? "unbinding" : "binding") << " driver '"
               << driverName << "' on " << dbdf << ". errno=" << errno << " (" << strerror(errno) << ")";
        throw MftGeneralException(errMsg.str());
    }

    outFile << dbdf;
    if (!outFile.good())
    {
        std::ostringstream errMsg;
        errMsg << "Failed to write DBDF '" << dbdf << "' to " << sysfsPath << ". errno=" << errno << " ("
               << strerror(errno) << ")";
        throw MftGeneralException(errMsg.str());
    }

    outFile.close();

    LOG.Info("LinuxResetPlatform::ToggleNicDriver: driver '" + driverName + "' on " + dbdf + " " +
             std::string(unbind ? "unbound" : "bound") + " successfully");
}

void LinuxResetPlatform::StopNicDriver()
{
    PrintStartResetFlowMessage(ResetFlowStep::StopNicDriver);
    LOG.Debug("LinuxResetPlatform::StopNicDriver");

    // Discover every (dbdf, driver_name) currently bound for the target DBDs.
    // Validation of 3rd-party drivers happens inside DiscoverBoundDrivers so that
    // we fail fast before unbinding anything.
    _driversDbdfToRebind = DiscoverBoundDrivers();

    if (_driversDbdfToRebind.empty())
    {
        LOG.Info("No bound drivers found for asic DBDF targets, nothing to unbind");
    }

    const bool unbind = true;
    for (const auto& dbdfDriver : _driversDbdfToRebind)
    {
        const std::string& dbdf = dbdfDriver.first;
        const std::string& driverName = dbdfDriver.second;
        if (IsNicDriverBound(dbdf))
        {
            ToggleNicDriver(dbdf, driverName, unbind);
        }
        else
        {
            LOG.Info("Driver '" + driverName + "' on " + dbdf + " is already unbound, skipping");
        }
    }

    PrintEndResetFlowMessage();
}

void LinuxResetPlatform::StartNicDriver()
{
    PrintStartResetFlowMessage(ResetFlowStep::StartNicDriver);
    LOG.Debug("LinuxResetPlatform::StartNicDriver");

    const bool unbind = false;
    for (const auto& dbdfDriver : _driversDbdfToRebind)
    {
        const std::string& dbdf = dbdfDriver.first;
        const std::string& driverName = dbdfDriver.second;
        if (IsNicDriverBound(dbdf))
        {
            LOG.Info("Driver '" + driverName + "' on " + dbdf + " is already bound, skipping");
            continue;
        }
        ToggleNicDriver(dbdf, driverName, unbind);
    }

    PrintEndResetFlowMessage();
}

void LinuxResetPlatform::DisableLinks()
{
    PrintStartResetFlowMessage(ResetFlowStep::DisableLinks);
    LOG.Debug("LinuxResetPlatform::DisableLinks");
    PrintEndResetFlowMessage();
}

void LinuxResetPlatform::HotReset()
{
    PrintStartResetFlowMessage(ResetFlowStep::HotReset);
    LOG.Info("LinuxResetPlatform::HotReset");
    _hotResetManager.ExecuteHotResetFlow();
    PrintEndResetFlowMessage();
}

void LinuxResetPlatform::LinkDisableReset()
{
    PrintStartResetFlowMessage(ResetFlowStep::LinkDisableReset);
    LOG.Debug("LinuxResetPlatform::LinkDisableReset");
    PrintEndResetFlowMessage();
}

void LinuxResetPlatform::PciReset()
{
    PrintStartResetFlowMessage(ResetFlowStep::PciReset);
    LOG.Debug("LinuxResetPlatform::PciReset");
    PrintEndResetFlowMessage();
}

void LinuxResetPlatform::WaitForFWReady()
{
    PrintStartResetFlowMessage(ResetFlowStep::WaitForFWReady);
    LOG.Debug("LinuxResetPlatform::WaitForFWReady");
    msleep(2000);
    LOG.Debug("LinuxResetPlatform::WaitForFWReady: FW is ready");
    PrintEndResetFlowMessage();
}

void LinuxResetPlatform::MSTRestart()
{
    LOG.Debug("LinuxResetPlatform::MSTRestart");
    PrintStartResetFlowMessage(ResetFlowStep::MSTRestart);
    mclose(_mf);
    // Restart the mst service
    std::string restartMstCmd = "mst restart";
    LOG.Info("Restarting mst service: " + restartMstCmd);
    std::ofstream outFile(restartMstCmd);
    if (!outFile.is_open())
    {
        std::ostringstream errMsg;
        errMsg << "Failed to open " << restartMstCmd << " for restarting mst service. errno=" << errno << " ("
               << strerror(errno) << ")";
        throw MftGeneralException(errMsg.str());
    }
    outFile << restartMstCmd;
    if (!outFile.good())
    {
        std::ostringstream errMsg;
        errMsg << "Failed to write " << restartMstCmd;
        throw MftGeneralException(errMsg.str());
    }
    outFile.close();

    LOG.Info("LinuxResetPlatform::MSTRestart: MST restarted successfully");
    PrintEndResetFlowMessage();
}

void LinuxResetPlatform::PreConditionForHotReset(const std::vector<std::string>& driverIgnoreList)
{
    LOG.Debug("LinuxResetPlatform::PreConditionForHotReset");
    _hotResetManager.PrepareHotResetFlow(driverIgnoreList);
    PrintStartResetFlowMessage(ResetFlowStep::PreConditionForHotReset);
    PrintEndResetFlowMessage();
}