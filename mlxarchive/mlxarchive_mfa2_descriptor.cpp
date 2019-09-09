
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
 * mlxarchive_mfa2_descriptor.cpp
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */


#include "mlxarchive_mfa2_descriptor.h"

using namespace mfa2;

/* Class Descriptor */
MFA2Type Descriptor::descriptorTypeToMFA2Type(DescriptorType type)
{
    switch (type) {
        case PackageDescriptorType:
            return MFA2Type_PACKAGE_DESCRIPTOR;
        case DeviceDescriptorType:
            return MFA2Type_DEVICE_DESCRIPTOR;
        case ComponentDescriptorType:
            return MFA2Type_COMPONENT_DESCRIPTOR;
        default:
            //TODO throw exception
            return MFA2Type_COMPONENT_DESCRIPTOR;
    }
}

Descriptor::Descriptor(u_int8_t version, DescriptorType type, u_int32_t length)
    : Element(version, descriptorTypeToMFA2Type(type), length)
{
}

void Descriptor::packMultiPart(u_int8_t extensionsCount, u_int16_t totalLength,
        vector<u_int8_t>& buff) const
{
    struct tools_open_multi_part multiPart;
    vector<u_int8_t> tmpBuff(tools_open_multi_part_size(), 0x0);

    CommonHeader commonHeader(0x0, MFA2Type_MULTI_PART,
            tools_open_multi_part_size());
    commonHeader.pack(buff);

    memset(&multiPart, 0x0, sizeof(multiPart));

    multiPart.number_of_extensions = extensionsCount;
    multiPart.total_length = totalLength +
            ((extensionsCount + 1) * tools_open_common_header_size());

    tools_open_multi_part_pack(&multiPart, tmpBuff.data());

    packBytesArray(tmpBuff.data(), tmpBuff.size(), buff);
}

bool Descriptor::unpackMultiPart(u_int8_t &extensionsCount, u_int16_t &totalLength, Mfa2Buffer & buff) {
    CommonHeader commonHeader(0x0, MFA2Type_MULTI_PART, 0x0);
    commonHeader.unpack(buff);
    struct tools_open_multi_part multiPart;
    int arr_size = tools_open_multi_part_size();
    u_int8_t * arr = new u_int8_t[arr_size];
    buff.read(arr, arr_size);
    memset(&multiPart, 0x0, arr_size);
    tools_open_multi_part_unpack(&multiPart, arr);
    delete[] arr;
    arr = NULL;
    extensionsCount = multiPart.number_of_extensions;
    totalLength = multiPart.total_length - ((extensionsCount + 1) * tools_open_common_header_size());
    return true;
}

Descriptor::~Descriptor()
{
    VECTOR_ITERATOR(Extension*, _extensions, it) {
        delete (*it);
    }
};

/* Class PackageDescriptor */
PackageDescriptor::PackageDescriptor(u_int16_t deviceDescriptorsCount,
                      u_int16_t componentsCount,
                      VersionExtension version) :
                          Descriptor(ELEMENT_VERSION,
                                  Descriptor::PackageDescriptorType,
                                  LENGTH),
                          _deviceDescriptorsCount(deviceDescriptorsCount),
                          _componentsCount(componentsCount),
                          _version(version),
                          _componentsBlockArchiveSize(0x0),
                          _componentsBlockSize(0x0),
                          _SHA256Extension(SHA256Extension::SHA256Scope_All),
                          _descriptorsSHA256Extension(
                                  SHA256Extension::SHA256Scope_Descriptors)
{
}

void PackageDescriptor::pack(vector<u_int8_t>& buff) const
{
    vector<u_int8_t> tmpBuff;
    struct tools_open_package_descriptor packageDescriptor;

    //TODO: pack the multipart, it comes before the desc' itself
    packMultiPart(_extensions.size() + 3,
            LENGTH + VersionExtension::LENGTH + 2 * SHA256Extension::LENGTH,
            buff);

    //pack common header
    _commonHeader.pack(buff);

    //pack the packageDescriptor struct
    memset(&packageDescriptor, 0x0, sizeof(packageDescriptor));

    packageDescriptor.num_of_devices = _deviceDescriptorsCount;
    packageDescriptor.num_of_components = _componentsCount;
    packageDescriptor.cb_offset = _componentsBlockOffset;
    packageDescriptor.cb_archive_size = _componentsBlockArchiveSize;
    packageDescriptor.cb_size_l = (u_int32_t) _componentsBlockSize;
    packageDescriptor.cb_size_h = _componentsBlockSize >> 32;
    //printf("cb_size_l=0x%x cb_size_h=0x%x\n",
    //        packageDescriptor.cb_size_l, packageDescriptor.cb_size_h);
    packageDescriptor.cb_compression = 0x1; //TODO use enums
    packageDescriptor.user_data_offset = 0x0; //TODO

    tmpBuff.resize(tools_open_package_descriptor_size(), 0x0);
    tools_open_package_descriptor_pack(&packageDescriptor, tmpBuff.data());

    //_packageDescriptorStructOffset = buff.size();
    packBytesArray(tmpBuff.data(), tmpBuff.size(), buff);

    //pack Version Extension
    _version.pack(buff);

    //pack SHA256 Extension
    //_SHA256ExtensionOffset = buff.size();
    _SHA256Extension.pack(buff);

    //pack DescriptorSHA256 Extension
    //_descriptorsSHA256ExtensionOffset = buff.size();
    _descriptorsSHA256Extension.pack(buff);

    //pack optional extensions
    CONST_VECTOR_ITERATOR(Extension*, _extensions, it) {
        (*it)->pack(buff);
    }

}

bool PackageDescriptor::unpack(Mfa2Buffer & buff) {
    u_int8_t extensionsCount;
    u_int16_t totalLength;
    unpackMultiPart(extensionsCount, totalLength, buff);

    //pack common header
    _commonHeader.unpack(buff);

    //unpack descriptor
    struct tools_open_package_descriptor packageDescriptor;
    int arr_size = tools_open_package_descriptor_size();
    u_int8_t * arr = new u_int8_t[arr_size];
    buff.read(arr, arr_size);
    memset(&packageDescriptor, 0x0, arr_size);
    tools_open_package_descriptor_unpack(&packageDescriptor, arr);
    delete[] arr;
    arr = NULL;

    _deviceDescriptorsCount = packageDescriptor.num_of_devices;
    _componentsCount = packageDescriptor.num_of_components;
    _componentsBlockOffset = packageDescriptor.cb_offset;
    _componentsBlockArchiveSize = packageDescriptor.cb_archive_size;
    _componentsBlockSize = (u_int64_t)(
            packageDescriptor.cb_size_l | (u_int64_t)packageDescriptor.cb_size_h << 32);

    u_int8_t extIdx = 0;
    //pack Version Extension
    _version.unpack(buff);
    extIdx++;

    //pack SHA256 Extension
    //_SHA256ExtensionOffset = buff.size();
    _SHA256Extension.unpack(buff);
    extIdx++;

    //pack DescriptorSHA256 Extension
    _descriptorsSHA256Extension.unpack(buff);
    extIdx++;;

    //pack optional extensions
    for(; extIdx < extensionsCount; extIdx++) {
        CommentExtension* extension = new CommentExtension("");
        extension->unpack(buff);
        addExtension(extension);
        //_extensions.push_back(extension);
    }
    return true;
}

void PackageDescriptor::setDescriptorsSHA256(const vector<u_int8_t>& digest)
{
    _descriptorsSHA256Extension.setDigest(digest);
}

void PackageDescriptor::setSHA256(const vector<u_int8_t>& digest)
{
    _SHA256Extension.setDigest(digest);
}

/* Class DeviceDescriptor */
DeviceDescriptor::DeviceDescriptor(
        vector<ComponentPointerExtension> componentPointers, PSIDExtension PSID)
    : Descriptor(ELEMENT_VERSION, Descriptor::DeviceDescriptorType, LENGTH),
      _componentPointers(componentPointers), _PSID(PSID)
{
};

void DeviceDescriptor::pack(vector<u_int8_t>& buff) const
{
    //TODO: pack the multipart, it comes before the desc' itself
    packMultiPart(_extensions.size() + 2,
            DeviceDescriptor::LENGTH + _PSID.length() +
            ComponentPointerExtension::LENGTH,
            buff);

    //pack common header
    _commonHeader.pack(buff);

    //pack PSID
    _PSID.pack(buff);

    //pack component pointers
    CONST_VECTOR_ITERATOR(ComponentPointerExtension, _componentPointers, it) {
        (*it).pack(buff);
    }
}

bool DeviceDescriptor::unpack(Mfa2Buffer & buff) {
    //unpack extensions
    u_int8_t extensionsCount;
    u_int16_t totalLength;
    unpackMultiPart(extensionsCount, totalLength, buff);
    _commonHeader.unpack(buff);

    //pack PSID
    _PSID.unpack(buff);

    ComponentPointerExtension compExt(0);
    compExt.unpack(buff);
    _componentPointers.push_back(compExt);
    return true;
}

/* Class ComponentDescriptor */
ComponentDescriptor::ComponentDescriptor(VersionExtension version, string source) :
      Descriptor(ELEMENT_VERSION, Descriptor::ComponentDescriptorType, LENGTH),
      _version(version)/*, _source(source)*/,
      _componentBlockOffset(0x0), _binarySize(getFileSize(source))
{
    packBinFile(source, _data);
};

ComponentDescriptor::ComponentDescriptor(VersionExtension version,
        vector<u_int8_t> data) :
      Descriptor(ELEMENT_VERSION, Descriptor::ComponentDescriptorType, LENGTH),
      _version(version), _componentBlockOffset(0x0), _binarySize(data.size()),
      _data(data)
{
    //printf("_data.size()=%d\n", (int)_data.size());
};

void ComponentDescriptor::pack(vector<u_int8_t>& buff) const
{
    //TODO: pack the multipart, it comes before the desc' itself
    /*memset(&multi_part, 0x0, sizeof(multi_part));
    multi_part.number_of_extensions = _extensions.size() +*/
    packMultiPart(_extensions.size() + 1,
            ComponentDescriptor::LENGTH + VersionExtension::LENGTH,
            buff);

    vector<u_int8_t> tmpBuff;
    struct tools_open_component_desciptor componentDescriptor;

    //pack common header
    _commonHeader.pack(buff);

    //pack the packageDescriptor struct
    memset(&componentDescriptor, 0x0, sizeof(componentDescriptor));
    componentDescriptor.identifier = 0x0; //TODO
    componentDescriptor.pldm_classification = 0x0; //TODO
    componentDescriptor.cb_offset_h = _componentBlockOffset >> 32;
    componentDescriptor.cb_offset_l = (u_int32_t)_componentBlockOffset;
    componentDescriptor.size = _binarySize;

    tmpBuff.resize(tools_open_component_desciptor_size());
    tools_open_component_desciptor_pack(&componentDescriptor, tmpBuff.data());
    packBytesArray(tmpBuff.data(), tmpBuff.size(), buff);

    _version.pack(buff);

}

bool ComponentDescriptor::unpack(Mfa2Buffer & buff) {
    //unpack extensions
    u_int8_t extensionsCount;
    u_int16_t totalLength;
    unpackMultiPart(extensionsCount, totalLength, buff);

    //unpack common header
    _commonHeader.unpack(buff);

    //unpack descriptor
    struct tools_open_component_desciptor componentDescriptor;
    int arr_size = tools_open_component_desciptor_size();
    u_int8_t * arr = new u_int8_t[arr_size];
    buff.read(arr, arr_size);
    memset(&componentDescriptor, 0x0, arr_size);
    tools_open_component_desciptor_unpack(&componentDescriptor, arr);
    delete[] arr;
    arr = NULL;
    _binarySize = componentDescriptor.size;
    _componentBlockOffset = (u_int64_t)(
            componentDescriptor.cb_offset_l | (u_int64_t)componentDescriptor.cb_offset_h << 32);

    //unpack version
    _version.unpack(buff);

    return true;
}
