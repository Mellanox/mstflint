#ifndef RESET_FLOW_EXECUTOR_H
#define RESET_FLOW_EXECUTOR_H

#include <string>
#include <vector>
#include <map>
#include "ResetParameterDefs.h"
#include "ResetPlatformInterface.h"
#include "NVFWresetParams.h"
#include "mtcr.h"

class ResetFlowExecutor
{
public:
    ResetFlowExecutor(mfile* mf,
                      const ResetFlowParameters& resetParams,
                      const std::vector<std::string>& asicDBDFTargets);
    void RunResetFlow(const NVFWresetParams& params) const;

private:
    mfile* _mf;
    const ResetFlowParameters& _resetParams;
    ResetPlatformInterface* _resetPlatform;

    std::map<ResetKey, std::vector<ResetFlowStep>> BuildResetFlow(const std::vector<unsigned int>& resetFlowSteps) const;
    std::vector<ResetFlowStep> FindFlowSteps(std::map<ResetKey, std::vector<ResetFlowStep>>& resetFlowMap) const;
    void ExecuteResetSteps(std::vector<ResetFlowStep>& flowSteps,
                           const std::vector<std::string>& driverIgnoreList) const;
};

#endif // RESET_FLOW_EXECUTOR_H