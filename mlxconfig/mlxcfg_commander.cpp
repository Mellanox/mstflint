/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the main directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary forms, with or
 *     without modification, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary form must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the documentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *
 * mlxcfg_commander.cpp
 *
 *  Created on: Jun 22, 2016
 *      Author: ahmads
 */


#include <set>
#include <mtcr.h>
#include "mlxcfg_4thgen_commander.h"
#include "mlxcfg_generic_commander.h"
#include "mlxcfg_param_lib.h"
#include "mlxcfg_utils.h"

using namespace std;


Commander* Commander::create(std::string device, std::string dbName)
{
    mfile *mf;
    int rc;
    u_int32_t type = 0;

    mf = mopen(device.c_str());
    if (mf == NULL) {
        throw MlxcfgException("Failed to open the device");
    }
    rc = mget_mdevs_type(mf, &type);
    if (rc) {
        throw MlxcfgException("Failed to get device type");
    }
    if (type & (MST_USB | MST_USB_DIMAX)) {
        throw MlxcfgException("MTUSB device is not supported.");
    }

    Commander *cmdr = NULL;
    try {
        cmdr = create(mf, device, dbName);
    } catch (MlxcfgException& exp) {
        mclose(mf);
        throw exp;
    }
    cmdr->setExtResourceType(false);
    return cmdr;
}

Commander* Commander::create(mfile *mf, std::string device, std::string dbName)
{

    bool isFifthGen, _isSwitch = false;
    dm_dev_id_t deviceId = DeviceUnknown;
    u_int32_t hwDevId, hwRevId;
    Commander *commander = NULL;
    if (dm_get_device_id(mf, &deviceId, &hwDevId, &hwRevId) ) {
        throw MlxcfgException("Failed to identify the device");
    }

    // check if device is supported:
    switch (deviceId) {
    case DeviceConnectX3:
    case DeviceConnectX3Pro:
        isFifthGen = false;
        break;

    case DeviceConnectIB:
    case DeviceConnectX4:
    case DeviceConnectX4LX:
    case DeviceConnectX5:
    case DeviceBlueField:
    case DeviceBlueField2:
    case DeviceConnectX6:
    case DeviceConnectX6DX:
    case DeviceConnectX6LX:
        isFifthGen = true;
        break;

    case DeviceSwitchIB:
    case DeviceSpectrum:
    case DeviceSwitchIB2:
    case DeviceQuantum:
    case DeviceSpectrum2:
    case DeviceSpectrum3:
        _isSwitch = true;
        isFifthGen = true;
        break;

    default:
        throw MlxcfgException("Unsupported device");
    }

    if (dm_is_livefish_mode(mf)) {
        throw MlxcfgException("Device in Livefish mode is not supported");
    }

    if (isFifthGen) {
        if (dbName.empty()) {//take internal db file
            dbName = getDefaultDBName(_isSwitch);
        }
        commander = new GenericCommander(mf, dbName);
    } else {
        commander = new FourthGenCommander(mf, device);
    }
    return commander;
}

Commander::~Commander()
{
    if (!_extResource && _mf) {
        mclose(_mf);
    }
}

string Commander::getDefaultDBName(bool isSwitch)
{
    const string dbDirName = "mlxconfig_dbs";
    const string hostDBName = "mlxconfig_host.db";
    const string switchDBName = "mlxconfig_switch.db";
    const string dbFileName = isSwitch ? switchDBName : hostDBName;
    string dbPathName = "";
#ifdef __WIN__
    char execFilePathCStr[1024] = {0x0};
    GetModuleFileName(GetModuleHandle("libmtcr-1.dll"), execFilePathCStr, 1024);
    dbPathName = execFilePathCStr;
    dbPathName = dbPathName.substr(0, dbPathName.rfind("\\") + 1);
    dbPathName += dbDirName + "\\" + dbFileName;
#elif defined MST_UL
    dbPathName = DATA_PATH "/" + dbDirName + "/" + dbFileName;
#else
    char line[1024] = {0};
    string confFile = string(ROOT_PATH) + string("etc/mft/mft.conf");
    FILE *fd = fopen(confFile.c_str(), "r");
    if (!fd) {
        throw MlxcfgException("Failed to open conf file : %s\n", confFile.c_str());
    }
    string prefix = "", dataPath = "";
    while ((fgets(line, 1024, fd))) {
        string l = line;
        if (l.find(dbDirName) != string::npos) {
            size_t eqPos = l.find("=");
            if (eqPos != string::npos) {
                dataPath = l.substr(eqPos + 1);
                dataPath = mlxcfg_trim(dataPath);
            }
        } else if (l.find("mft_prefix_location") != string::npos) {
            size_t eqPos = l.find("=");
            if (eqPos != string::npos) {
                prefix = l.substr(eqPos + 1);
                prefix = mlxcfg_trim(prefix);
            }
        }
    }
    if (!prefix.empty() && !dataPath.empty()) {
        dbPathName = prefix + dataPath + "/" + dbFileName;
    }
    fclose(fd);
#endif
    return dbPathName;
}

