
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
 * mlxarchive_mfa2.cpp
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#include <xz_utils/xz_utils.h>
#include <mlxsign_lib/mlxsign_lib.h>
#include "mlxarchive_mfa2.h"
#include "mlxarchive_mfa2_utils.h"

using namespace mfa2;

/*void MFA2::updateSHA256()
{
    vector<u_int8_t> digest;
    MlxSignSHA256 mlxSignSHA256;

    //compute descriptors SHA256
    vector<u_int8_t> descriptorsBuff;
    packDescriptors(descriptorsBuff);
    mlxSignSHA256 << descriptorsBuff;
    mlxSignSHA256.getDigest(digest);
    _packageDescriptor.setDescriptorsSHA256(digest);

    //append the zipped components block
    packBytesArray(zippedComponentBlockBuff.data(), zippedComponentBlockBuff.size(), buff);

    //compute SHA256
    mlxSignSHA256 << zippedComponentBlockBuff;
    mlxSignSHA256.getDigest(digest);
}*/

void MFA2::packDescriptors(vector<u_int8_t>& buff) const
{
    _fingerPrint.pack(buff);
    _packageDescriptor.pack(buff);
    CONST_VECTOR_ITERATOR(DeviceDescriptor, _deviceDescriptors, it) {
        (*it).pack(buff);
    }
    CONST_VECTOR_ITERATOR(Component, _components, it) {
        (*it).packDescriptor(buff);
    }
}

void MFA2::pack(vector<u_int8_t>& buff)
{
    //find size of components block:
    u_int64_t componentsBlockSize = 0;
    CONST_VECTOR_ITERATOR(Component, _components, it) {
        componentsBlockSize += (*it).getComponentBinarySize();
    }
    _packageDescriptor.setComponentsBlockSize(componentsBlockSize);

    _fingerPrint.pack(buff);

    _packageDescriptor.pack(buff);

    CONST_VECTOR_ITERATOR(DeviceDescriptor, _deviceDescriptors, it) {
        (*it).pack(buff);
    }

    CONST_VECTOR_ITERATOR(Component, _components, it) {
        (*it).packDescriptor(buff);
    }

    _packageDescriptor.setComponentsBlockOffset(buff.size());

    //compress components block
    vector<u_int8_t> componentsBlockBuff;
    VECTOR_ITERATOR(Component, _components, it) {
        (*it).setComponentBinaryOffset(componentsBlockBuff.size());
        (*it).packData(componentsBlockBuff);
    }
    u_int32_t zippedSize = componentsBlockBuff.size();
    zippedSize = xz_compress_crc32(8, componentsBlockBuff.data(),
            componentsBlockBuff.size(), NULL, 0);
    if (zippedSize <= 0)
    {
        //TODO throw exception
        printf("-E- Error while compressing\n");
        exit(1);
    }
    _packageDescriptor.setComponentsBlockArchiveSize(zippedSize);
    vector<u_int8_t> zippedComponentBlockBuff(zippedSize);
    xz_compress_crc32(9, componentsBlockBuff.data(), componentsBlockBuff.size(),
            zippedComponentBlockBuff.data(), zippedSize);

    //compute descriptors SHA256
    vector<u_int8_t> descriptorsBuff;
    packDescriptors(descriptorsBuff);
    vector<u_int8_t> digest;
    MlxSignSHA256 mlxSignSHA256;
    mlxSignSHA256 << descriptorsBuff;
    mlxSignSHA256.getDigest(digest);
    _packageDescriptor.setDescriptorsSHA256(digest);

    //append the zipped components block
    packBytesArray(zippedComponentBlockBuff.data(), zippedComponentBlockBuff.size(), buff);

    //compute SHA256
    mlxSignSHA256 << zippedComponentBlockBuff;
    mlxSignSHA256.getDigest(digest);
    _packageDescriptor.setSHA256(digest);

}

/*void MFA2::update(vector<u_int8_t>& buff)
{
    //update components descriptors with information about components blocks
    u_int64_t offset = 0x0;

    VECTOR_ITERATOR(_components, );
}*/

void MFA2::generateBinary(vector<u_int8_t>& buff)
{
    vector<u_int8_t> tmpBuff;

    //do first pass
    pack(tmpBuff);

    //do second pass
    pack(buff);

    //compute SHA256

}

MFA2 * MFA2::LoadMFA2Package(const string & file_name) {
    Mfa2Buffer mfa2buff;
    if(!mfa2buff.loadFile(file_name)) {
        fprintf(stderr, "Failed to load mfa2 package: %s\n", file_name.c_str());
        return NULL;
    }
    FingerPrint finger_print("");
    VersionExtension version("");
    PackageDescriptor        packageDescriptor(0, 0, version);
    vector<DeviceDescriptor> deviceDescriptors;
    vector<Component>        components;
    MFA2 * mfa2pkg = new MFA2(packageDescriptor, deviceDescriptors, components);
    if(!mfa2pkg->unpack(mfa2buff)) {
        delete mfa2pkg;
        mfa2pkg =  NULL;
        return NULL;
    }
    mfa2pkg->setBufferAndZipOffset(mfa2buff.getBuffer(), mfa2buff.getSize(), mfa2buff.tell());
    return mfa2pkg;
}

bool MFA2::unpack(Mfa2Buffer & buff) {
    if (!_fingerPrint.unpack(buff)) {
        return false;
    }
    _packageDescriptor.unpack(buff);
    u_int16_t devCount = _packageDescriptor.getDeviceDescriptorsCount();
    u_int16_t compCount = _packageDescriptor.getComponentsCount();

    for(u_int16_t devIdx=0; devIdx<devCount; devIdx++) {
        vector<ComponentPointerExtension> componentPointers;
        PSIDExtension psidExt("");
        DeviceDescriptor devDescriptor(componentPointers, psidExt);
        devDescriptor.unpack(buff);
        _deviceDescriptors.push_back(devDescriptor);
    }

    for(u_int16_t compIdx=0; compIdx<compCount; compIdx++) {
        VersionExtension version("");
        ComponentDescriptor compDescriptor(version, "");
        compDescriptor.unpack(buff);
        Component comp(compDescriptor);
        _components.push_back(comp);
    }

    return true;
}

void MFA2::minidump() {
    printf("Package Version : %s\n", _packageDescriptor.getVersionExtension().getVersion(false).c_str());
}

void MFA2::dump() {
    //printf("Finger print    : %s\n", _fingerPrint.toString().c_str());
    u_int16_t devCount = _packageDescriptor.getDeviceDescriptorsCount();
    //u_int16_t compCount = _packageDescriptor.getComponentsCount();
    printf("Package Version : %s\n", _packageDescriptor.getVersionExtension().getVersion(false).c_str());
    printf("Creation Time   : %s\n", _packageDescriptor.getVersionExtension().getDateAndTime().c_str());
    //printf("Extensions      : %u\n", _packageDescriptor.getExtensionsCount());
    printf("Devices         : %u\n", devCount);
    for(u_int16_t index=0; index < devCount; index++) {
        DeviceDescriptor & devDescriptor = _deviceDescriptors[index];
        string psid = devDescriptor.getPSIDExtension().getString();
        u_int8_t compPtrCount = devDescriptor.getComponentPointerExtensionsCount();
        printf("    PSID       : %s\n", psid.c_str());
        printf("    Num of Images : %u\n", compPtrCount);
        for(u_int8_t comp=0; comp < compPtrCount; comp++) {
            const ComponentPointerExtension & compPtr = devDescriptor.getComponentPointerExtension(comp);
            u_int16_t compIndex = compPtr.getComponentIndex();
            Component compObj = _components[compIndex];
            const ComponentDescriptor & compDescr = compObj.getComponentDescriptor();
            printf("        Index   : %u\n", compIndex);
            printf("        Version : %s\n", compDescr.getVersionExtension().getVersion(true).c_str());
            char buffer[32] = { 0 };
            compDescr.getVersionExtension().getDateAndTime(buffer);
            printf("        Date    : %s\n", buffer);
        }

    }
}

bool MFA2::extractComponent(Component* requiredComponent, vector<u_int8_t>& fwBinaryData)
{
    PackageDescriptor packageDescriptor = getPackageDescriptor();
    u_int64_t totalSize = packageDescriptor.getComponentsBlockSize();
    u_int32_t zipOffset = packageDescriptor.getComponentsBlockOffset();

    vector<u_int8_t> unzippedBlockBuff;
    unzippedBlockBuff.resize(totalSize);
    vector<u_int8_t> zippedBuff = getBuffer();
    u_int8_t* zippedData = (u_int8_t*)zippedBuff.data() + zipOffset;
    int32_t retVal = xz_decompress_crc32(zippedData, zippedBuff.size() - zipOffset, unzippedBlockBuff.data(), totalSize);
    if (retVal != (int32_t)totalSize) {
        printf("Decompress error occurred %s\n", xz_get_error(retVal));
        return false;
    }
    u_int32_t requiredOffset = requiredComponent->getBinaryComponentOffset();
    u_int32_t componentBinarySize = requiredComponent->getComponentBinarySize() - strlen(FINGERPRINT_MFA2);
    fwBinaryData.resize(componentBinarySize);
    for (unsigned int index = 0; index < componentBinarySize; index++) {
        fwBinaryData[index] = unzippedBlockBuff[requiredOffset + index + strlen(FINGERPRINT_MFA2)];//skip 16 bytes from decompressed file !
    }
    return true;
}

bool MFA2::unzipLatestVersionComponent(map_string_to_component& matchingComponentsMap, vector<u_int8_t>& fwBinaryData)
{
    map_string_to_component::iterator itAtKey = matchingComponentsMap.find(_latestComponentKey);
    if (itAtKey == matchingComponentsMap.end()) {
        return false;
    }
    Component* requiredComponent = &itAtKey->second;
    return extractComponent(requiredComponent, fwBinaryData);
}

bool MFA2::unzipComponent(map_string_to_component& matchingComponentsMap, u_int32_t choice, vector<u_int8_t>& fwBinaryData)
{
    if (choice >= matchingComponentsMap.size()) {
        return false;
    }
    map_string_to_component::iterator itAtOffset = matchingComponentsMap.begin();
    std::advance(itAtOffset, choice);
    Component* requiredComponent = &itAtOffset->second;
    return extractComponent(requiredComponent, fwBinaryData);
}

bool MFA2::getLatestComponent(vector<u_int8_t>& fwBinaryData, u_int16_t fw_ver[3])
{
    map_string_to_component matchingComponentsMap = getMatchingComponents(NULL, fw_ver);
    map_string_to_component::iterator itAtKey = matchingComponentsMap.find(_latestComponentKey);
    if (itAtKey == matchingComponentsMap.end()) {
        return false;
    }
    Component* requiredComponent = &itAtKey->second;
    return extractComponent(requiredComponent, fwBinaryData);
}


map_string_to_component MFA2::getMatchingComponents(char* device_psid, u_int16_t fw_ver[3])
{
    map_string_to_component matchingComponentsMap;
    PackageDescriptor packageDescriptor = getPackageDescriptor();
    u_int16_t devCount = packageDescriptor.getDeviceDescriptorsCount();
    Version currentLatestVersion;
    u_int8_t deviceMajorVer = (u_int8_t)fw_ver[0];
    u_int8_t deviceMinorVer = (u_int8_t)fw_ver[1];
    u_int16_t deviceSubMinorVer = fw_ver[2];
    for (u_int16_t index = 0; index < devCount; index++) {
        DeviceDescriptor devDescriptor = getDeviceDescriptor(index);
        string psid = devDescriptor.getPSIDExtension().getString();
        if (device_psid != NULL) {
            if (strcmp((char*)psid.c_str(), device_psid)) {
                continue;
            }
        }
        u_int8_t compPtrCount = devDescriptor.getComponentPointerExtensionsCount();
        for (u_int8_t comp = 0; comp < compPtrCount; comp++) {
            const ComponentPointerExtension& compPtr = devDescriptor.getComponentPointerExtension(comp);
            u_int16_t compIndex = compPtr.getComponentIndex();
            Component compObj = getComponentObject(compIndex);
            const ComponentDescriptor & compDescr = compObj.getComponentDescriptor();
            u_int8_t majorVer = compDescr.getVersionExtension().getMajor();
            u_int8_t minorVer = compDescr.getVersionExtension().getMinor();
            u_int16_t subMinorVer = compDescr.getVersionExtension().getSubMinor();
            if (deviceMajorVer != 0xff) {
                if (deviceMajorVer != majorVer) {
                    continue;
                }
            }
            if (deviceMinorVer != 0xff) {
                if (minorVer != deviceMinorVer) {
                    continue;
                }
            }
            if (deviceSubMinorVer != 0xffff) {
                if (subMinorVer != deviceSubMinorVer) {
                    continue;
                }
            }
            char dateTimeBuffer[32] = { 0 };
            compDescr.getVersionExtension().getDateAndTime(dateTimeBuffer);
            VersionExtension currentVersion = compDescr.getVersionExtension();
            string currentVersionString = currentVersion.getVersion(true);
            string mapKey = currentVersionString + "  " + dateTimeBuffer;
            matchingComponentsMap.insert(std::pair<string, Component>(mapKey, compObj));
            Version version(currentVersionString);
            //find the latest matching FW version
            if (version > currentLatestVersion) {
                currentLatestVersion = version;
                _latestComponentKey = mapKey;
            }
        }
    }
    return matchingComponentsMap;
}

