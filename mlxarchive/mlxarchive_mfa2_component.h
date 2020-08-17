
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
#define FINGERPRINT_MFA2 "#BIN.COMPONENT!#"

namespace mfa2 {

class Component {

private:
    FingerPrint         _fingerPrint;
    ComponentDescriptor _descriptor;

public:

    explicit Component(ComponentDescriptor descriptor) :
        _fingerPrint(FINGERPRINT_MFA2),
        _descriptor(descriptor) {};

    void packDescriptor(vector<u_int8_t>& buff) const { _descriptor.pack(buff); };
    void packData(vector<u_int8_t>& buff) {
        _fingerPrint.pack(buff);
        _descriptor.packData(buff);
    };
    void unpackData(vector<u_int8_t>& buff) {
        _descriptor.unpackData(buff);
    };
    u_int32_t getComponentBinarySize() const;
    u_int64_t getBinaryComponentOffset();
    void setComponentBinaryOffset(u_int64_t offset);
    const ComponentDescriptor & getComponentDescriptor() const { return _descriptor;}
};

inline u_int32_t Component::getComponentBinarySize() const {
    return _fingerPrint.getSize() + _descriptor.getBinarySize();
}

inline void Component::setComponentBinaryOffset(u_int64_t offset) {
    _descriptor.setComponentBinaryOffset(offset);
}

inline u_int64_t Component::getBinaryComponentOffset() {
    return _descriptor.getComponentBinaryOffset();
}
}
#endif
