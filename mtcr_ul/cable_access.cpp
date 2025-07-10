#include <string>
#include <cstring>
#include <cstdint>
#include <vector>

#include "cable_access.h"
#include "mtcr_cables.h"

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
    if (_fwUpPageOpened)
    {
        closeFwUpgradePage();
    }
    if (_GwNode)
    {
        delete _GwNode;
    }
    if (_PageNode)
    {
        delete _PageNode;
    }
    if (_adb)
    {
        delete _adb;
    }
    if (_cableCrspaceAdb)
    {
        delete _cableCrspaceAdb;
    }
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
        ss << "Cable access R/W failed status: " << rc << ". ";
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