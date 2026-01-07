#include "NVFWresetParams.h"
#include "ResetParameterDefs.h"

NVFWresetParams::NVFWresetParams() :
    cmdType(ResetCommandType::UNKNOWN),
    device(""),
    resetLevel(ResetLevel::UNKNOWN),
    resetType(ResetType::UNKNOWN),
    method(ResetMethod::UNKNOWN),
    resetSync(ResetSync::UNKNOWN),
    answerYes(false),
    skipDriver(false),
    resetFlowSteps({}),
    driverIgnoreList({}),
    skipMstRestart(false),
    logLevel("")
{
}
