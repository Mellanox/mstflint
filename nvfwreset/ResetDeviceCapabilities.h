#ifndef RESET_DEVICE_CAPABILITIES_H
#define RESET_DEVICE_CAPABILITIES_H

#include <set>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "NVFWresetParams.h"
#include "ResetParameterDefs.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "reg_access/reg_access.h"
#include "tools_layouts/reg_access_hca_layouts.h"

class ResetDeviceCapabilities
{
public:
    ResetDeviceCapabilities(mfile* mf, NVFWresetParams& params);
    const ResetDeviceParam& getResetDeviceParam() const { return _resetDeviceParam; }

private:
    struct ResetDeviceParam _resetDeviceParam;
    reg_access_hca_mroq_ext sendMroqCommand(mfile* mf, NVFWresetParams& params);
    bool isMroqSupported(mfile* mf);
    void parseResetLevels(reg_access_hca_mroq_ext& mroq);
    void parseResetSyncTypes(reg_access_hca_mroq_ext& mroq);
    void parseResetTypes(reg_access_hca_mroq_ext& mroq);
    void parseResetMethods(reg_access_hca_mroq_ext& mroq);
};

#endif // RESET_DEVICE_CAPABILITIES_H