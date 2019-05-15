#ifndef USER_MLXFWOPS_LIB_FW_ABSTRACT_COMP_ACCESS_H_
#define USER_MLXFWOPS_LIB_FW_ABSTRACT_COMP_ACCESS_H_

#include "fw_comps_mgr.h"

class AbstractComponentAccess
{
public:
    virtual bool accessComponent(u_int32_t updateHandle, u_int32_t offset,
        u_int32_t size,
        u_int32_t data[],
        access_type_t access,
        const char* currComponentStr,
        ProgressCallBackAdvSt *progressFuncAdv) = 0;

    virtual fw_comps_error_t  getLastFirmwareError() = 0;
    virtual reg_access_status_t  getLastRegisterAccessStatus() = 0;

    AbstractComponentAccess(FwCompsMgr* Manager, mfile *Mf)
    {
        _mf = Mf;
        _manager = Manager;
        _lastFwError = FWCOMPS_SUCCESS;
    }
    virtual ~AbstractComponentAccess() {}

protected:
    mfile *_mf;
    FwCompsMgr* _manager;
    fw_comps_error_t _lastFwError;
    reg_access_status_t _lastRegisterAccessStatus;
};

class ComponentAccessFactory
{
public:
    AbstractComponentAccess* createDataAccessObject(FwCompsMgr* manager, mfile *Mf, bool IsMDCCRegisterPresent);
    static ComponentAccessFactory* GetInstance() {
        static ComponentAccessFactory myObj;
        return &myObj;
    }
};


#endif
