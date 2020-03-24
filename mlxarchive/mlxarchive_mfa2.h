
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
 * mlxarchive_mfa2.h
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXARCHIVE_MFA2_H_
#define MLXARCHIVE_MFA2_H_

#include <string>
#include <vector>
#include <map>
#include <compatibility.h>

#include "mlxarchive_mfa2_utils.h"
#include "mlxarchive_mfa2_descriptor.h"
#include "mlxarchive_mfa2_component.h"
#include "mfa2_buff.h"

using namespace std;


namespace mfa2 {
    typedef map <string, Component> map_string_to_component;
class MFA2 {
private:

    FingerPrint              _fingerPrint;
    PackageDescriptor        _packageDescriptor;
    vector<DeviceDescriptor> _deviceDescriptors;
    vector<Component>        _components;
        string                   _latestComponentKey;
        long _zipOffset;
    //void updateSHA256();
        vector<u_int8_t> mfa2Buffer;
    void pack(vector<u_int8_t>& buff);
    void packDescriptors(vector<u_int8_t>& buff) const;
    bool unpack(Mfa2Buffer & buff);
        bool extractComponent(Component* requiredComponent, vector<u_int8_t>& fwBinaryData);
public:
    MFA2(PackageDescriptor packageDescriptor,
         vector<DeviceDescriptor> deviceDescriptors,
         vector<Component> components) : 
             _fingerPrint(MFA2_FINGER_PRINT),
             _packageDescriptor(packageDescriptor),
             _deviceDescriptors(deviceDescriptors),
            _components(components), _zipOffset(0){};

    virtual ~MFA2() {}
    static MFA2 * LoadMFA2Package(const string & file_name);
    void generateBinary(vector<u_int8_t>& buff);
    void dump();
        void minidump();
        PackageDescriptor getPackageDescriptor() const {
            return _packageDescriptor;
        }

        long getZipOffset() {
            return _zipOffset;
        }

        u_int16_t getDeviceCount() const {
            return _packageDescriptor.getDeviceDescriptorsCount();
        }
        DeviceDescriptor getDeviceDescriptor(int index) const {
            return _deviceDescriptors[index];
        }

        Component getComponentObject(int compIndex) const {
            return _components[compIndex];
        }

        void setBufferAndZipOffset(u_int8_t* buffer, long length, long zipOffset)
        {
            mfa2Buffer.resize(length);
            for (int i = 0; i < length; i++) {
                mfa2Buffer[i] = buffer[i];
            }
            _zipOffset = zipOffset;
        }

        vector<u_int8_t> getBuffer() {
            return mfa2Buffer;
        }
        map_string_to_component getMatchingComponents(char* psid, int majorVer);
        bool unzipComponent(map_string_to_component& matchingComponentsMap, u_int32_t choice, vector<u_int8_t>& fwBinaryData);
        bool unzipLatestVersionComponent(map_string_to_component& matchingComponentsMap, vector<u_int8_t>& fwBinaryData);
};

}

#endif
