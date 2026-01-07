#ifndef LINUX_RESET_PLATFORM_H
#define LINUX_RESET_PLATFORM_H

#include <map>
#include "ResetPlatformInterface.h"
#include "CommonResetPlatform.h"
#include "HotResetManager.h"
#include "mft_core/mft_core_utils/operating_system_api/FactoryOperatingSystemAPI.h"

class LinuxResetPlatform : public CommonResetPlatform
{
public:
    LinuxResetPlatform(mfile* mf,
                       const ResetFlowParameters& resetParams,
                       const std::vector<std::string>& asicDBDFTargets);
    virtual ~LinuxResetPlatform() override;
    virtual void StopNicDriver() override;
    virtual void StartNicDriver() override;
    virtual void DisableLinks() override;
    virtual void HotReset() override;
    virtual void LinkDisableReset() override;
    virtual void PciReset() override;
    virtual void WaitForReady() override;
    virtual void MSTRestart() override;
    virtual void PreConditionForHotReset(const std::vector<std::string>& ignoreList) override;

private:
    HotResetManager _hotResetManager;
    std::unique_ptr<OperatingSystemAPI> _operatingSystemAPI;
    void ToggleNicDriver(const std::string& asicDBDFTarget, bool unbind);
    bool IsNicDriverBound(const std::string& asicDBDFTarget);
};

#endif // LINUX_RESET_PLATFORM_H