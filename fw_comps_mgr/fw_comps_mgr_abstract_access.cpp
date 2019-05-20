#include "fw_comps_mgr_abstract_access.h"
#include "fw_comps_mgr_direct_access.h"
#include "fw_comps_mgr_dma_access.h"

AbstractComponentAccess* ComponentAccessFactory::createDataAccessObject(FwCompsMgr* Manager, mfile *Mf, bool isMDCCRegisterPresent)
{
#ifndef UEFI_BUILD
    if (getenv("DISABLE_DMA_ACCESS") != NULL) {
        return new DirectComponentAccess(Manager, Mf);
    }
#endif
    if (!isMDCCRegisterPresent) {
        return new DirectComponentAccess(Manager, Mf);
    }
    else {
#ifndef UEFI_BUILD
        DMAComponentAccess* obj = new DMAComponentAccess(Manager, Mf);
        if (obj->allocateMemory()) {
            return obj;
        }
        else {
            delete obj;
            return new DirectComponentAccess(Manager, Mf);
        }
#else
    return new DirectComponentAccess(Manager, Mf);
#endif
    }
}
