#include <vector>
#include <sstream>
#include <map>
#include <fstream>
#include <string.h>
#include "LinuxResetPlatform.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "mft_core/mft_core_utils/logger/Logger.h"
#include "ResetParameterDefs.h"
#include "mft_core/mft_core_utils/operating_system_api/FactoryOperatingSystemAPI.h"
#include "DeviceTypeDetector.h"
#include "common/tools_filesystem.h"

namespace Filesystem = mstflint::common::filesystem;
using namespace mft_core;
const std::string PCI_DRIVERS_PATH = "/sys/bus/pci/drivers/mlx5_core";

LinuxResetPlatform::LinuxResetPlatform(mfile* mf,
                                       const ResetFlowParameters& resetParams,
                                       const std::vector<std::string>& asicDBDFTargets) :
    CommonResetPlatform(mf, resetParams, asicDBDFTargets),
    _hotResetManager(mf, asicDBDFTargets, DeviceTypeDetector::IsPCIESwitchDevice(mf))
{
    _operatingSystemAPI = FactoryOperatingSystemAPI::GetInstance();
}

LinuxResetPlatform::~LinuxResetPlatform() {}

bool LinuxResetPlatform::IsNicDriverBound(const std::string& asicDBDFTarget)
{
    std::string driverLink = std::string("/sys/bus/pci/devices/") + asicDBDFTarget + "/driver";

    return Filesystem::exists(Filesystem::path(driverLink));
}

void LinuxResetPlatform::ToggleNicDriver(const std::string& asicDBDFTarget, bool unbind)
{
    const std::string sysfsPath = std::string(PCI_DRIVERS_PATH) + (unbind ? "/unbind" : "/bind");

    LOG.Info("Writing '" + asicDBDFTarget + "' to " + sysfsPath);

    std::ofstream outFile(sysfsPath);
    if (!outFile.is_open())
    {
        std::ostringstream errMsg;
        errMsg << "Failed to open " << sysfsPath << " for " << (unbind ? "unbinding" : "binding")
               << " Asic DBDF target driver. errno=" << errno << " (" << strerror(errno) << ")";
        throw MftGeneralException(errMsg.str());
    }

    outFile << asicDBDFTarget;
    if (!outFile.good())
    {
        std::ostringstream errMsg;
        errMsg << "Failed to write Asic DBDF target '" << asicDBDFTarget << "' to " << sysfsPath << ". errno=" << errno
               << " (" << strerror(errno) << ")";
        throw MftGeneralException(errMsg.str());
    }

    outFile.close();

    LOG.Info("LinuxResetPlatform::ToggleNicDriver: Asic DBDF target driver " +
             std::string(unbind ? "unbound" : "bound") + " successfully");
}

void LinuxResetPlatform::StopNicDriver()
{
    PrintStartResetFlowMessage(ResetFlowStep::StopNicDriver);
    LOG.Debug("LinuxResetPlatform::StopNicDriver");
    bool unbind = true;
    for (const auto& asicDBDFTarget : _asicDBDFTargets)
    {
        // Check if the driver path exists
        if (IsNicDriverBound(asicDBDFTarget))
        {
            LOG.Info("Asic DBDF target driver is bound: " + asicDBDFTarget);
            _nicDriverState[asicDBDFTarget] = NicDriverState::WAS_BOUND;
            ToggleNicDriver(asicDBDFTarget, unbind);
        }
        else
        {
            LOG.Info("Asic DBDF target driver is unbound: " + asicDBDFTarget);
            _nicDriverState[asicDBDFTarget] = NicDriverState::WAS_UNBOUND;
        }
    }
    PrintEndResetFlowMessage();
}

void LinuxResetPlatform::StartNicDriver()
{
    PrintStartResetFlowMessage(ResetFlowStep::StartNicDriver);
    LOG.Debug("LinuxResetPlatform::StartNicDriver");
    for (const auto& asicDBDFTarget : _asicDBDFTargets)
    {
        if (_nicDriverState[asicDBDFTarget] == NicDriverState::WAS_BOUND)
        {
            bool unbind = false;
            ToggleNicDriver(asicDBDFTarget, unbind);
        }
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

void LinuxResetPlatform::WaitForReady()
{
    PrintStartResetFlowMessage(ResetFlowStep::WaitForReady);
    LOG.Debug("LinuxResetPlatform::WaitForReady");
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