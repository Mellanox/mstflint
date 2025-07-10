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