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
 * mlxarchive_mfa2.h
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXARCHIVE_MFA2_H_
#define MLXARCHIVE_MFA2_H_

#include <string>
#include <vector>

#include <compatibility.h>

#include "mlxarchive_mfa2_utils.h"
#include "mlxarchive_mfa2_descriptor.h"
#include "mlxarchive_mfa2_component.h"

using namespace std;

namespace mfa2 {

class MFA2 {
private:

    FingerPrint              _fingerPrint;
    PackageDescriptor        _packageDescriptor;
    vector<DeviceDescriptor> _deviceDescriptors;
    vector<Component>        _components;

    //void updateSHA256();
    void pack(vector<u_int8_t>& buff);
    void packDescriptors(vector<u_int8_t>& buff) const;
public:
    MFA2(PackageDescriptor packageDescriptor,
         vector<DeviceDescriptor> deviceDescriptors,
         vector<Component> components) : 
             _fingerPrint("MLNX.MFA2.XZ.00!"),
             _packageDescriptor(packageDescriptor),
             _deviceDescriptors(deviceDescriptors),
             _components(components) {};

    void generateBinary(vector<u_int8_t>& buff);
};

}

#endif
