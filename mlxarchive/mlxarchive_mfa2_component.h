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
 * mlxarchive_mfa2_component.h
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXARCHIVE_MFA2_COMPONENT_H_
#define MLXARCHIVE_MFA2_COMPONENT_H_

#include <string>
#include <vector>

#include <compatibility.h>

#include "mlxarchive_mfa2_descriptor.h"

using namespace std;

namespace mfa2 {

class Component {

private:
    FingerPrint         _fingerPrint;
    ComponentDescriptor _descriptor;

public:

    explicit Component(ComponentDescriptor descriptor) :
        _fingerPrint("#BIN.COMPONENT!#"),
        _descriptor(descriptor) {};

    void packDescriptor(vector<u_int8_t>& buff) const { _descriptor.pack(buff); };
    void packData(vector<u_int8_t>& buff) {
        _fingerPrint.pack(buff);
        _descriptor.packData(buff);
    };
    u_int32_t getComponentBinarySize() const;
    void setComponentBinaryOffset(u_int64_t offset);
};

inline u_int32_t Component::getComponentBinarySize() const {
    return _fingerPrint.getSize() + _descriptor.getBinarySize();
}

inline void Component::setComponentBinaryOffset(u_int64_t offset) {
    _descriptor.setComponentBinaryOffset(offset);
}

}
#endif
