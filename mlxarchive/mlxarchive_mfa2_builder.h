/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 * mlxarchive_mfa2_builder.h
 *
 *  Created on: March 26, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXARCHIVE_MFA2_BUILDER_H_
#define MLXARCHIVE_MFA2_BUILDER_H_

#include <string>
#include <vector>
#include <map>

#include <json/writer.h>
#include <json/reader.h>
#include <json/value.h>
#include <compatibility.h>

#include "mlxarchive_mfa2_descriptor.h"
#include "mlxarchive_mfa2_extension.h"
#include "mlxarchive_mfa2_component.h"

using namespace std;

namespace mfa2 {

class MFA2Builder {

public:
    MFA2Builder()   {};
    
    virtual PackageDescriptor           getPackageDescriptor()  const = 0;
    virtual vector<DeviceDescriptor>    getDeviceDescriptors()  const = 0;
    virtual vector<Component>           getComponents()         const = 0;

    virtual ~MFA2Builder()  {};
};


class MFA2JSONBuilder : MFA2Builder {

private:
    Json::Value _root;
    Json::Value _componentsJSON;
    Json::Value _deviceDescriptorsJSON;

public:
    explicit MFA2JSONBuilder(const string& jsonContent);

    PackageDescriptor           getPackageDescriptor()  const;
    vector<DeviceDescriptor>    getDeviceDescriptors()  const;
    vector<Component>           getComponents()         const;
};

class FWDirectoryBuilder : MFA2Builder {
private:
    VersionExtension            _version;
    string                      _directory;
    vector<string>              _files;
    //vector<FwOperations*>   _imgsFwOps;
    vector<DeviceDescriptor>    _deviceDescriptors;
    vector<Component>           _components;
    /*struct FWInfo {
        string      psid;
        u_int16_t   version[3];
        u_int16_t   date[3];
    };
    map<string, FwOperations*> _imgsFwOps;*/
public:
    FWDirectoryBuilder(const string& version, const string& time,
            string directory);
    PackageDescriptor           getPackageDescriptor()  const;
    vector<DeviceDescriptor>    getDeviceDescriptors()  const;
    vector<Component>           getComponents()         const;
};

}
#endif
