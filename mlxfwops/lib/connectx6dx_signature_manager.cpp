#include "signature_manager.h"
#include "flint_io.h"
#include "flint_base.h"
#include "fw_ops.h"
#include "tools_utils.h"

using namespace std;


bool ConnectX6DXFwOperationsSignatureManager::AddSignature(mfile* mf, Fs3Operations* imageOps, Flash *f, u_int32_t imageOffset)
{
    (void)mf;
    (void)imageOps;
    (void)f;
    (void)imageOffset;
    return true;
}

bool ConnectX6DXFwOperationsSignatureManager::GetSecureBootInfo()
{
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    return true;
#else
    return false;
#endif
}
