#ifndef COMMON_RESET_PLATFORM_H
#define COMMON_RESET_PLATFORM_H

#include <memory>
#include <map>
#include "ResetPlatformInterface.h"
#include "mft_core/mft_core_utils/operating_system_api/FactoryOperatingSystemAPI.h"
#include "ResetParameterDefs.h"

class CommonResetPlatform : public ResetPlatformInterface
{
public:
    CommonResetPlatform(mfile* mf,
                        const ResetFlowParameters& resetParams,
                        const std::vector<std::string>& asicDBDFTargets);
    virtual void SendMFRL() override;
    virtual void SaveUptimeBeforeReset() override;
    virtual void CheckUptimeAfterReset() override;

protected:
    std::map<std::string, NicDriverState> _nicDriverState;
    std::unique_ptr<OperatingSystemAPI> _operatingSystemAPI;
};

#endif // COMMON_RESET_PLATFORM_H