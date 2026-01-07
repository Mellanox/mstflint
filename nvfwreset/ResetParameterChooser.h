#ifndef PARAMETER_CHOOSER_H
#define PARAMETER_CHOOSER_H

#include <vector>
#include <string>
#include "ResetParameterDefs.h"
#include "NVFWresetParams.h"
#include "ResetDeviceCapabilities.h"
#include "DeviceTypeDetector.h"
#include "mtcr.h"

class ResetParameterChooser
{
public:
    ResetParameterChooser(const mfile* mf, NVFWresetParams& params) :
        _resetDeviceCapabilities(const_cast<mfile*>(mf), params)
    {
    }

    ResetFlowParameters getResetFlowParameters(const mfile* mf, std::vector<std::string>& asicDBDFTargets) const;

private:
    ResetFlowParameters PrepareResetFlowParameters() const;
    ResetDeviceCapabilities _resetDeviceCapabilities;
};

#endif // PARAMETER_CHOOSER_H