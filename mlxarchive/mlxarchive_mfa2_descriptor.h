
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
 * mlxarchive_mfa2_desc.h
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXARCHIVE_MFA2_DESCRIPTOR_H_
#define MLXARCHIVE_MFA2_DESCRIPTOR_H_

#include <string>
#include <vector>

#include <compatibility.h>
#include <tools_layouts/tools_open_layouts.h>

#include "mlxarchive_mfa2_element.h"
#include "mlxarchive_mfa2_extension.h"
#include "mlxarchive_mfa2_utils.h"
#include "mfa2_buff.h"

using namespace std;

namespace mfa2 {

class Descriptor : protected Element {
protected:
    enum DescriptorType {
        PackageDescriptorType,
        DeviceDescriptorType,
        ComponentDescriptorType
    };
    MFA2Type descriptorTypeToMFA2Type(DescriptorType type);

    /*class MultiPart : private Element {
    private:
        u_int8_t    _numberOfExtensions;
        u_int16_t   _length;

        const static u_int8_t  ELEMENT_VERSION = 0x0;
        const static u_int32_t LENGTH  = TOOLS_OPEN_MULTI_PART_SIZE;
    public:
        MultiPart()
        void pack(vector<u_int8_t>& buff);
    };

    MultiPart           _multiPart;*/
    vector<Extension*>  _extensions;
public:
    Descriptor(u_int8_t vesrion, DescriptorType type, u_int32_t length);
    virtual ~Descriptor();
    void addExtension(Extension* extension);
    void packMultiPart(u_int8_t extensionsCount, u_int16_t totalLength,
            vector<u_int8_t>& buff) const;
    bool unpackMultiPart(u_int8_t &extensionsCount, u_int16_t &totalLength, Mfa2Buffer & buff);
    virtual void pack(vector<u_int8_t>& buff) const = 0;
    virtual bool unpack(Mfa2Buffer & buff) = 0;
    u_int16_t getExtensionsCount() const { return _extensions.size(); }
    Extension * getExtension(int index) { return _extensions[index];}
};

inline void Descriptor::addExtension(Extension* extension)
{
    _extensions.push_back(extension);
}

class PackageDescriptor : public Descriptor {
private:
    u_int16_t                   _deviceDescriptorsCount;
    u_int16_t                   _componentsCount;
    VersionExtension            _version;
    u_int32_t                   _componentsBlockOffset;
    u_int32_t                   _componentsBlockArchiveSize;
    u_int64_t                   _componentsBlockSize;
    //u_int8_t                  _componentBlockCompression;
    SHA256Extension             _SHA256Extension;
    SHA256Extension             _descriptorsSHA256Extension;

    u_int32_t                   _packageDescriptorStructOffset;
    u_int32_t                   _SHA256ExtensionOffset;
    u_int32_t                   _descriptorsSHA256ExtensionOffset;
public:
    const static u_int8_t  ELEMENT_VERSION = 0x0;
    const static u_int32_t LENGTH  = TOOLS_OPEN_PACKAGE_DESCRIPTOR_SIZE;

    PackageDescriptor(u_int16_t deviceDescriptorsCount,
                      u_int16_t componentsCount,
                      VersionExtension version);

    void setComponentsBlockOffset(u_int64_t offset);
    void setComponentsBlockArchiveSize(u_int32_t size);
    void setComponentsBlockSize(u_int64_t size);
    void setDescriptorsSHA256(const vector<u_int8_t>& digest);
    void setSHA256(const vector<u_int8_t>& digest);
    void pack(vector<u_int8_t>& buff) const;
    virtual bool unpack(Mfa2Buffer & buff);
    u_int16_t getDeviceDescriptorsCount() const { return _deviceDescriptorsCount;}
    u_int16_t getComponentsCount() const { return _componentsCount;}
    const VersionExtension & getVersionExtension() const {return _version;}
    u_int64_t getComponentsBlockSize  ();
    u_int32_t getComponentsBlockOffset  ();
};

inline void PackageDescriptor::setComponentsBlockOffset(u_int64_t offset)
{
    _componentsBlockOffset = offset;
}

inline u_int32_t PackageDescriptor::getComponentsBlockOffset()
{
    return _componentsBlockOffset;
}

inline void PackageDescriptor::setComponentsBlockArchiveSize(u_int32_t size)
{
    _componentsBlockArchiveSize = size;
}

inline void PackageDescriptor::setComponentsBlockSize(u_int64_t size)
{
    _componentsBlockSize = size;
}
inline u_int64_t PackageDescriptor::getComponentsBlockSize() 
{
    return _componentsBlockSize;
}

class DeviceDescriptor : public Descriptor {
private:
    vector<ComponentPointerExtension>   _componentPointers;
    PSIDExtension                       _PSID;
public:
    const static u_int8_t  ELEMENT_VERSION = 0x0;
    const static u_int32_t LENGTH  = 0x0;

    DeviceDescriptor(vector<ComponentPointerExtension> componentPointers,
            PSIDExtension PSID);
    void pack(vector<u_int8_t>& buff) const;
    virtual bool unpack(Mfa2Buffer & buff);

    const PSIDExtension & getPSIDExtension() const { return _PSID;}
    u_int8_t getComponentPointerExtensionsCount() const { return _componentPointers.size(); }
    const ComponentPointerExtension & getComponentPointerExtension(int index) { return _componentPointers[index]; }
};


class ComponentDescriptor : public Descriptor {
private:
    VersionExtension    _version;
    //string              _source;
    u_int64_t           _componentBlockOffset;
    u_int64_t           _binarySize;
    vector<u_int8_t>    _data;
public:
    const static u_int8_t  ELEMENT_VERSION = 0x0;
    const static u_int32_t LENGTH  = TOOLS_OPEN_COMPONENT_DESCIPTOR_SIZE;
    ComponentDescriptor(VersionExtension version, string source);
    ComponentDescriptor(VersionExtension version, vector<u_int8_t> data);

    virtual bool unpack(Mfa2Buffer & buff);
    const VersionExtension & getVersionExtension() const {return _version;}

    //string      getSource               ()                          const;
    void        setComponentBinaryOffset(u_int64_t offset);
    u_int64_t   getComponentBinaryOffset() const; 
    void        pack                    (vector<u_int8_t>& buff)    const;
    u_int32_t   getBinarySize           ()                          const;
    void        packData                (vector<u_int8_t>& buff)    const;
    void        unpackData(vector<u_int8_t>& buff);
};

/*inline string ComponentDescriptor::getSource() const
{
    return _source;
};*/
inline u_int64_t ComponentDescriptor::getComponentBinaryOffset() const{
    return _componentBlockOffset;
}

inline void ComponentDescriptor::setComponentBinaryOffset(u_int64_t offset)
{
    _componentBlockOffset = offset;
}

inline u_int32_t ComponentDescriptor::getBinarySize() const
{
    return _binarySize;
};

inline void ComponentDescriptor::unpackData(vector<u_int8_t>& buff)
{
    unpackBytesArray(_data.data(), _data.size(), buff);
}
inline void ComponentDescriptor::packData(vector<u_int8_t>& buff) const
{
    packBytesArray(_data.data(), _data.size(), buff);
}

}
#endif
