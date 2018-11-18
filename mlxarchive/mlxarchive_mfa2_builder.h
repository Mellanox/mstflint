
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
 */

/*
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
    FWDirectoryBuilder(const string& version, string directory);
    PackageDescriptor           getPackageDescriptor()  const;
    vector<DeviceDescriptor>    getDeviceDescriptors()  const;
    vector<Component>           getComponents()         const;
};

}
#endif
