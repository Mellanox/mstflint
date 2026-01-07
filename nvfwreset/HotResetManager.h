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
    void SetHotResetFlow(uint8_t requesterPcieIndex);
    void SendMPQD(uint8_t* requesterPcieIndex);
    void SendMPIR(uint8_t pcie_index, uint8_t* bus, uint8_t* device);
    bool IsUpstreamPort(const std::string& dbdf);
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