#include <map>

#include "signature_manager.h"
#include "tools_utils.h"
#include "fs4_ops.h"
#include "fs3_ops.h"
using namespace std;


bool ConnectX6FwOperationsSignatureManager::AddSignature(mfile* mf, Fs3Operations* imageOps, Flash *f, u_int32_t imageOffset)
{
(void)mf;
#if !defined(UEFI_BUILD) && !defined(NO_OPEN_SSL)
    int signature_size = 3 * HMAC_SIGNATURE_LENGTH;
    uint8_t signature_data[3 * HMAC_SIGNATURE_LENGTH] = { 0 };
    //FOR BOOT, CRITICAL, NON-CRITICAL
    imageOps->GetImageCache().get(signature_data, imageOffset, signature_size);
    if (!f->write(imageOffset, signature_data, signature_size)) {
        return errmsg(MLXFW_FLASH_WRITE_ERR, "Failed to burn HMAC digest: %s", f->err());
    }
#else  
    (void)imageOps;
    (void)f;
    (void)imageOffset;
#endif
    return true;
};
