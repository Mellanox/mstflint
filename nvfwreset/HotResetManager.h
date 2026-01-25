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

#ifndef _HOT_RESET_MANAGER_H
#define _HOT_RESET_MANAGER_H

#include <vector>
#include <string>
#include <memory>
#include <map>
#include "mtcr.h"
#include "ResetParameterDefs.h"
#include "mft_core/mft_core_utils/operating_system_api/FactoryOperatingSystemAPI.h"

class HotResetManager
{
public:
    HotResetManager(mfile* mf, std::vector<std::string> asicDBDFTargets, bool isPcieSwitch);
    void PrepareHotResetFlow(const std::vector<std::string>& driverIgnoreList);
    void ExecuteHotResetFlow();

private:
    mfile* _mf;
    std::vector<std::string> _asicDBDFTargets;
    std::vector<std::string> _upstream_dbdfs;
    HotResetFlow _hot_reset_flow;
    std::unique_ptr<OperatingSystemAPI> _operatingSystemAPI;
    bool _isPcieSwitch;
    PCIeDeviceType GetPcieDeviceType(const std::string& dbdf);
    bool IsUpstreamPortType(const std::string& dbdf);
    bool IsDownstreamPortType(const std::string& dbdf);
    bool IsLeafSwitchUnderneath(const std::string& downstream_dbdf);
    void SetHotResetFlow(uint8_t requesterPcieIndex);
    void SendMPQD(uint8_t* requesterPcieIndex);
    void SendMPIR(uint8_t pcie_index, uint8_t* bus, uint8_t* device);
    bool IsBridgeDevice(const std::string& dbdf);
    std::map<std::string, std::string> CheckForbiddenDriversOnDiscoveredDevices();
    std::map<std::string, std::string> GetForbiddenDriversFromUpstreamPort(const std::string& upstream_dbdf,
                                                                           const std::string& dbdf);
    std::map<std::string, std::string> GetAllPciDevicesForDomainBus(const std::string& domain, uint8_t bus);
    void CheckBindedDrivers(const std::vector<std::string>& driverIgnoreList);
    void CheckPCIRegistersSupported();
    bool CheckIfDirectNic();
    void
      GetSecondaryAndSubordinateBuses(const std::string& upstream_dbdf, uint8_t* secondaryBus, uint8_t* subordinateBus);
};

#endif // _HOT_RESET_MANAGER_H