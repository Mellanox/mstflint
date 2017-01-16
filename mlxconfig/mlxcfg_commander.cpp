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

Commander* Commander::create(std::string device, std::string dbName) {
    mfile* mf;
    mf = mopen(device.c_str());
    if (mf == NULL) {
        throw MlxcfgException("Failed to open the device");
    }
    Commander* cmdr = create(mf, device, dbName);
    cmdr->setExtResourceType(false);
    return cmdr;
}

Commander* Commander::create(mfile* mf, std::string device, std::string dbName) {

    bool isFifthGen;
    dm_dev_id_t deviceId;
    u_int32_t hwDevId, hwRevId;
    Commander* commander = NULL;
    if( dm_get_device_id(mf, &deviceId, &hwDevId, &hwRevId) ) {
        throw MlxcfgException("Failed to identify the device");
    }

    // check if device is supported:
    switch(deviceId) {
        case DeviceConnectX3:
        case DeviceConnectX3Pro:
            isFifthGen = false;
            break;
        case DeviceConnectIB:
        case DeviceConnectX4:
        case DeviceConnectX4LX:
        case DeviceConnectX5:
            isFifthGen = true;
            break;
        default:
            throw MlxcfgException("Unsupported device");
    }

    if(dm_is_livefish_mode(mf)) {
        throw MlxcfgException("Device in Livefish mode is not supported");
    }

    if(isFifthGen) {
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
