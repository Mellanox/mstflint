#ifndef NVFWRESET_PARAMS_H
#define NVFWRESET_PARAMS_H

#include <string>
#include <vector>
#include "ResetParameterDefs.h"

class NVFWresetParams
{
public:
    NVFWresetParams();
    ~NVFWresetParams(){};

    ResetCommandType cmdType;
    std::string device;
    ResetLevel resetLevel;
    ResetType resetType;
    ResetMethod method;
    ResetSync resetSync;
    bool answerYes;
    bool skipDriver;
    std::vector<unsigned int> resetFlowSteps;
    std::vector<std::string> driverIgnoreList;
    bool skipMstRestart;
    std::string logLevel;
};

#endif // NVFWRESET_PARAMS_H
