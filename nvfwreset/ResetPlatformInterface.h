#ifndef RESET_PLATFORM_INTERFACE_H
#define RESET_PLATFORM_INTERFACE_H

#include "mtcr.h"
#include "ResetParameterDefs.h"
#include <vector>
#include <string>

class ResetPlatformInterface
{
public:
    ResetPlatformInterface(mfile* mf,
                           const ResetFlowParameters& resetParams,
                           const std::vector<std::string>& asicDBDFTargets) :
        _mf(mf), _resetParams(resetParams), _asicDBDFTargets(asicDBDFTargets)
    {
    }
    virtual ~ResetPlatformInterface() {}
    static std::string ShowResetFlowSteps();
    virtual void StopNicDriver() = 0;
    virtual void DisableLinks() = 0;
    virtual void SendMFRL() = 0;
    virtual void HotReset() = 0;
    virtual void LinkDisableReset() = 0;
    virtual void PciReset() = 0;
    virtual void StartNicDriver() = 0;
    virtual void WaitForReady() = 0;
    virtual void MSTRestart() = 0;
    virtual void SaveUptimeBeforeReset() = 0;
    virtual void CheckUptimeAfterReset() = 0;
    virtual void PreConditionForHotReset(const std::vector<std::string>& ignoreList) = 0;

protected:
    mfile* _mf;
    unsigned long long _uptimeBeforeReset;
    const ResetFlowParameters _resetParams;
    const std::vector<std::string> _asicDBDFTargets;
    void PrintStartResetFlowMessage(ResetFlowStep step);
    void PrintEndResetFlowMessage();
};

#endif // RESET_PLATFORM_INTERFACE_H