/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 * pldm_buff.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: Samer Deeb
 */
 
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <cstring>

#include "pldm_buff.h"
#include "pldm_dev_id_record.h"
#include "pldm_component_image.h"
#include "pldm_pkg.h"
#include "pldm_utils/pldm_utils.h"

PldmPkg::PldmPkg() : deviceIDRecordCount(0), componentImageCount(0), packageHeaderChecksum(0) {}

PldmPkg::~PldmPkg()
{
    reset();
}

void PldmPkg::reset()
{
    while (!deviceIDRecords.empty())
    {
        delete deviceIDRecords.back();
        deviceIDRecords.pop_back();
    }
    while (!componentImages.empty())
    {
        delete componentImages.back();
        componentImages.pop_back();
    }
    psidRecordMap.clear();
    deviceIDRecordCount = 0;
    componentImageCount = 0;
    packageHeader.reset();
}

bool PldmPkg::unpack(PldmBuffer& buff)
{
    reset();
    if (!packageHeader.unpack(buff))
    {
        return false;
    }
    buff.read(deviceIDRecordCount);
    u_int8_t componentBitmapBitLength = packageHeader.getComponentBitmapBitLength();
    for (u_int8_t i = 0; i < deviceIDRecordCount; i++)
    {
        PldmDevIdRecord* deviceIDRecord = new PldmDevIdRecord(componentBitmapBitLength);
        if (!deviceIDRecord->unpack(buff))
        {
            delete deviceIDRecord;
            reset();
            return false;
        }
        deviceIDRecords.push_back(deviceIDRecord);
        std::string psid = deviceIDRecord->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID);
        psidRecordMap[psid] = deviceIDRecord;
    }
    // downstream device record support is added in revision 3 and above
    if (packageHeader.getPackageHeaderFormatRevision() >= FIRST_REVISION_SUPPORTED_DOWNSTREAM_DEVICES)
    {
        buff.read(downstreamDeviceRecordCount);
    }
    buff.read(componentImageCount);
    for (u_int8_t i = 0; i < componentImageCount; i++)
    {
        PldmComponenetImage* componentImage = new PldmComponenetImage();
        componentImage->unpack(buff);
        componentImages.push_back(componentImage);
    }
    buff.read(packageHeaderChecksum);
    return true;
}

bool PldmPkg::isComponentInPackage(const std::string& psid, const std::string& componentName) const
{
    PldmDevIdRecord* rec = findRecordByPsid(psid);
    if (rec == NULL)
    {
        return false;
    }
    std::vector<u_int8_t> componentsIndexes = rec->getComponentsIndexes();

    ComponentIdentifier componentIdentifier;
    StringToComponentIdentifier(componentName, componentIdentifier);

    for (u_int8_t i = 0; i < componentsIndexes.size(); i++)
    {
        if (componentsIndexes[i] == 0)
        {
            continue;
        }
        PldmComponenetImage* ComponentImage = getComponentByIndex(i);
        ComponentIdentifier currentComponentIdentifier =
        static_cast<ComponentIdentifier>(ComponentImage->getComponentIdentifier());
        std::string currentComponentName;
        ComponentIdentifierToStringValue(currentComponentIdentifier, ComponentField::Name, currentComponentName);
        if (currentComponentName == componentName ||
            (isNicFwComponent(currentComponentIdentifier) &&
            isNicFwComponent(componentIdentifier))) // 2 components for nic image FW, NIC_FW
        {
            return true;
        }
    }
    return false;
}

const PldmComponenetImage* PldmPkg::getImageByPsid(const std::string& psid) const
{
    PldmDevIdRecord* rec = findRecordByPsid(psid);
    if (rec == NULL)
    {
        return NULL;
    }
    int location = rec->getComponentImageIndex();
    if (location == -1 || location >= componentImageCount)
    {
        return NULL;
    }
    return componentImages[location];
}

bool PldmPkg::getPldmDescriptorByPsid(std::string psid, u_int16_t type, u_int16_t& descriptor) const
{
    bool found = false;
    for (auto devIdRec : deviceIDRecords)
    {
        // if psid is empty, we will return the descriptor for the first device record
        std::string devIdPsid = devIdRec->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID);
        if (devIdPsid == psid || psid.empty())
        {
            found = devIdRec->getDescriptor(type, descriptor);
            break;
        }
    }
    return found;
}

std::string PldmPkg::getPldmVendorDefinedDescriptorByPsid(std::string psid,
                                                        PldmRecordDescriptor::VendorDefinedType type) const
{
    std::string descriptor = "";
    for (auto devIdRec : deviceIDRecords)
    {
        std::string devIdPsid = devIdRec->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID);
        if (devIdPsid == psid || psid.empty())
        {
            descriptor = devIdRec->GetVendorDefinedValue(type);
            break;
        }
    }
    return descriptor;
}
bool PldmPkg::isPsidInPldm(std::string psid) const
{
    if (psid.empty())
    {
        return true;
    }
    bool found = false;
    for (auto devIdRec : deviceIDRecords)
    {
        if (devIdRec->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID) == psid)
        {
            return true;
        }
    }
    return found;
}

bool PldmPkg::getComponentDataByPsid(ComponentIdentifier compIdentifier,
                                    std::string psid,
                                    u_int8_t** buff,
                                    u_int32_t& buffSize)
{
    bool found = false;
    for (auto devIdRec : deviceIDRecords)
    {
        std::string devIdPsid = devIdRec->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID);
        if (devIdPsid == psid || psid.empty())
        {
            u_int16_t comps_count = getComponentImageCount();
            std::vector<u_int8_t> appliedComponents = devIdRec->getComponentsIndexes();
            for (u_int16_t i = 0; i < comps_count; i++)
            {
                // the current DeviceRecord doesn't contain this component.
                if (appliedComponents[i] == 0)
                {
                    continue;
                }

                PldmComponenetImage* ComponentImage = getComponentByIndex(i);
                ComponentIdentifier identifier =
                static_cast<ComponentIdentifier>(ComponentImage->getComponentIdentifier());
                if (identifier == compIdentifier ||
                    (isNicFwComponent(compIdentifier) && isNicFwComponent(identifier))) // 2 components for nic image
                                                                                        // FW, NIC_FW
                {
                    buffSize = ComponentImage->getComponentSize();
                    *buff = new u_int8_t[buffSize];
                    if (buff == nullptr)
                    {
                        return false;
                    }
                    memcpy(*buff, ComponentImage->getComponentData(), buffSize);
                    found = true;
                    break;
                }
            }
        }
        if (found)
        {
            break;
        }
    }
    return found;
}

PldmDevIdRecord* PldmPkg::findRecordByPsid(const std::string& psid) const
{
    if (deviceIDRecords.empty())
    {
        return NULL;
    }
    if (psid.empty())
    {
        return deviceIDRecords[0];
    }
    PsidRecordMap::const_iterator it = psidRecordMap.find(psid);
    return (it == psidRecordMap.end()) ? NULL : it->second;
}

bool PldmPkg::recomputeHeaderChecksum(PldmBuffer& buff) const
{
    u_int16_t headerSize = packageHeader.getPackageHeaderSize();
    if (headerSize < sizeof(u_int32_t))
    {
        return false;
    }
    size_t bufSize = buff.size();
    if ((size_t)headerSize > bufSize)
    {
        return false;
    }
    // CRC is the last dword of the header; packageHeaderSize includes it.
    size_t checksumOffset = (size_t)headerSize - sizeof(u_int32_t);
    if (checksumOffset > bufSize)
    {
        return false;
    }
    u_int32_t newCrc = pldm_crc32(buff.data(), checksumOffset);
    u_int32_t le = __cpu_to_le32(newCrc);
    return buff.writeAt(checksumOffset, (const u_int8_t*)&le, sizeof(le));
}