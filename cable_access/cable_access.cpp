#include <string>
#include <cstring>
#include <cstdint>
#include <vector>
#include <sstream>

#include "cable_access.h"
#include "mtcr_cables.h"
#include "mtcr_ul/mtcr_ul_com.h"
#include "tools_layouts/reg_access_switch_layouts.h"
#include "tools_layouts/reg_access_hca_layouts.h"
#include "reg_access/reg_access.h"
#include "common/tools_time.h"

dm_dev_id_t mcables_get_connected_device_type(mfile* mf)
{
    dm_dev_id_t devid = DeviceUnknown;
    u_int32_t hwid = 0;
    u_int32_t revid = 0;
    cable_ctx* ctx = (cable_ctx*)(mf->cable_ctx);
    if (!ctx)
    {
        return devid;
    }
    MType tmp_tp = mf->tp;
    mf->tp = ctx->src_tp;
    switch_access_funcs(mf);
    if (dm_get_device_id(mf, &devid, &hwid, &revid))
    {
        devid = DeviceUnknown;
    }
    mf->tp = tmp_tp;
    switch_access_funcs(mf);
    return devid;
}

int send_paos(mfile* mf, int state, int local_ports[], int num_ports, bool verbose)
{
    int i = 0;
    MCABLES_ERROR ret = MCABLES_OK;
    cable_ctx* ctx = (cable_ctx*)(mf->cable_ctx);
    if (!ctx)
    {
        return MCABLES_ACCESS_ERROR;
    }
    MType tmp_tp = mf->tp;
    mf->tp = ctx->src_tp;
    switch_access_funcs(mf);
    if (verbose)
    {
        printf("-I- Changing %d local port/s state to %s\n", num_ports, state == 1 ? "UP" : "DOWN");
    }
    for (i = 0; i < num_ports; i++)
    {
        struct reg_access_hca_paos_reg_ext paos;
        memset(&paos, 0, sizeof(paos));
        paos.ase = 1;
        paos.admin_status = state;
        paos.local_port = local_ports[i];
        if (reg_access_paos(mf, REG_ACCESS_METHOD_SET, &paos))
        {
            printf("-E- Failed to change the state of the local port: %d\n", local_ports[i]);
            ret = MCABLES_REG_FAILED;
        }
    }
    mf->tp = tmp_tp;
    switch_access_funcs(mf);
    return ret;
}

int send_pmaos(mfile* mf, int state, bool verbose)
{
    MCABLES_ERROR ret = MCABLES_OK;

    cable_ctx* ctx = (cable_ctx*)(mf->cable_ctx);
    if (!ctx)
    {
        return MCABLES_ACCESS_ERROR;
    }
    MType tmp_tp = mf->tp;
    mf->tp = ctx->src_tp;
    switch_access_funcs(mf);
    struct reg_access_switch_pmaos_reg_ext pmaos;
    memset(&pmaos, 0, sizeof(pmaos));
    pmaos.ase = 1;

    pmaos.admin_status = state;
    pmaos.module = ctx->port;
    if (verbose)
    {
        printf("-I- Changing module state to %s\n", state == 1 ? "UP" : "DOWN");
    }
    if (reg_access_pmaos(mf, REG_ACCESS_METHOD_SET, &pmaos))
    {
        printf("-E- Failed to change the module state\n");
        ret = MCABLES_REG_FAILED;
    }
    mf->tp = tmp_tp;
    switch_access_funcs(mf);
    return ret;
}

void get_all_local_ports(mfile* mf, dm_dev_id_t dm, int module, int local_ports[MAX_LOCALS], int* num_ports, bool verbose)
{
    if (dm_dev_is_hca(dm))
    {
        local_ports[0] = 1;
        *num_ports = 1;
        return;
    }
    int max_num_local_ports = dm_get_hw_ports_num(dm) * MAX_LOCALS;
    ;
    int i = 0;
    *num_ports = 0;
    cable_ctx* ctx = (cable_ctx*)(mf->cable_ctx);
    if (!ctx)
    {
        return;
    }
    MType tmp_tp = mf->tp;
    mf->tp = ctx->src_tp;
    switch_access_funcs(mf);
    if (verbose)
    {
        printf("-I- Locating local ports ...\n");
    }
    for (i = 1; i <= max_num_local_ports && *num_ports < MAX_LOCALS; i++)
    {
        struct reg_access_hca_pmlp_reg_ext pmlp;
        memset(&pmlp, 0, sizeof(pmlp));
        pmlp.local_port = i;
        if (!reg_access_pmlp(mf, REG_ACCESS_METHOD_GET, &pmlp))
        {
            if (pmlp.width && pmlp.lane_module_mapping[0].module == module)
            {
                local_ports[*num_ports] = i;
                (*num_ports)++;
            }
        }
    }
    mf->tp = tmp_tp;
    switch_access_funcs(mf);
}

int mcables_reset_module(mfile* mf, bool verbose)
{
    int local_ports[MAX_LOCALS] = {-1};
    int num_ports = 1;
    dm_dev_id_t dm = mcables_get_connected_device_type(mf);
    cable_ctx* ctx = (cable_ctx*)(mf->cable_ctx);
    u_int32_t mtype = 0;
    mget_mdevs_type(mf, &mtype);
    if (mtype == (int)MST_IB)
    {
        printf("-E- Operation is not supported via inband device.");
        return MCABLES_NOT_SUPPORTED;
    }
    get_all_local_ports(mf, dm, ctx->port, local_ports, &num_ports, verbose);
    int rc = send_paos(mf, PAOS_DOWN, local_ports, num_ports, verbose);
    rc += send_pmaos(mf, PMAOS_DOWN, verbose);
    if (verbose)
    {
        printf("-I- Sleeping %.02f seconds...\n", PAOS_SLEEP / 1000.0);
    }
    msleep(PAOS_SLEEP);
    rc += send_pmaos(mf, PMAOS_UP, verbose);
    rc += send_paos(mf, PAOS_UP, local_ports, num_ports, verbose);
    if (verbose)
    {
        printf("-I- Sleeping another %.02f seconds...\n", PAOS_SLEEP / 1000.0);
    }
    msleep(PAOS_SLEEP);
    if (rc)
    {
        return MCABLES_REG_FAILED;
    }
    return MCABLES_OK;
}

cableAccess::cableAccess(const char* mstDevName, mfile* mf)
{
    _mstDevName = mstDevName;
    _errMsg = "";
    _mf = mf;
    _mfCreatedInClass = false;
    _lidNumber = 0;
    _isLegacyGw = true;
    _fwUpPageOpened = false;
    memset(&_attr, 0, sizeof(_attr));
    memset(&_cblIds, 0, sizeof(_cblIds));
    _deviceOpened = false;
    _cable_type = DeviceUnknown;
    _supportFwUp = false;
}

bool cableAccess::init()
{
    if (_mstDevName.empty())
    {
        _errMsg += "Invalid device name";
        return false;
    }

    _mf = mopen_adv(_mstDevName.c_str(), (MType)(MST_DEFAULT | MST_CABLE));

    if (!_mf)
    {
        _errMsg += "Failed to detect connected cable";
        return false;
    }
    _mfCreatedInClass = true;

    u_int32_t dev_type = 0;
    mget_mdevs_type(_mf, &dev_type);

    if (dev_type != MST_CABLE)
    {
        if (dev_type == MST_REMOTE)
        {
            _deviceOpened = true;
            return true;
        }
        _errMsg = "This is not a cable device!";
        return false;
    }

    _cable_type = mcables_get_dm(_mf);
    _deviceOpened = true;
    return true;
}

cableAccess::~cableAccess()
{
    if (_mf && _mfCreatedInClass)
    {
        mclose(_mf);
    }
}

string cableAccess::getLastErrMsg()
{
    return _errMsg;
}

bool cableAccess::rw(u_int32_t addr, u_int32_t len, u_int8_t* data, int _rw)
{
    int rc = 0;
    if (_rw)
    {
        rc = mcables_write_bytes(_mf, addr, data, len);
    }
    else
    {
        rc = mcables_read_bytes(_mf, addr, data, len);
    }
    // printf("-D- RW RC[%d]\n", rc);
    //    printf("-D- RW: %d, addr: %#x, len: %#x, bytes[0]: %02x\n", _rw, addr, len, data[0]);
    if (rc)
    {
        ostringstream ss;
        if (((cable_ctx*)(_mf->cable_ctx))->internal_error_msg[0] != '\0')
        {
            ss << ((cable_ctx*)(_mf->cable_ctx))->internal_error_msg;
        }
        else
        {
            ss << "Cable access R/W failed status: " << rc << ". ";
        }
        _errMsg += ss.str();
        return false;
    }
    return true;
}

bool cableAccess::read(u_int32_t addr, u_int32_t len, u_int8_t* data)
{
    return rw(addr, len, data, 0);
}

bool cableAccess::write(u_int32_t addr, u_int32_t len, u_int8_t* data)
{
    return rw(addr, len, data, 1);
}

void cableAccess::setBurnFlow(bool isBurnFlow)
{
    mcables_set_burn_flow(isBurnFlow);
}

bool cableAccess::isBurnSupported()
{
    if (_mf->hw_dev_id == DeviceConnectX3_HwId || _mf->hw_dev_id == DeviceConnectX3Pro_HwId)
    {
        return false;
    }
    return true;
}

bool cableAccess::isResetSupported()
{
    MType tp = mcables_get_tp(_mf);
    if (tp != MST_PCICONF)
    {
        return false;
    }
    return true;
}

bool cableAccess::resetCableModule(bool verbose)
{
    if (!isBurnSupported() || !isResetSupported())
    {
        _errMsg = "Reset module is not supported in this device!";
        return false;
    }
    if (mcables_reset_module(_mf, verbose))
    {
        _errMsg = "Failed to reset the cable!";
        return false;
    }
    return true;
}

bool cableAccess::resetCable()
{
    MType tp = mcables_get_tp(_mf);
    if (tp != MST_IB)
    {
        return resetCableModule(false);
    }
    return false;
}

