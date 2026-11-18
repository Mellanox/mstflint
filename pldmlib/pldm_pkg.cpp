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
#include <new>

#include "pldm_buff.h"
#include "pldm_dev_id_record.h"
#include "pldm_component_image.h"
#include "pldm_pkg.h"
#include "pldm_utils/pldm_utils.h"
#include "common/tools_endianness.h"

// component are ordered by priority
const std::vector<std::string> PldmPkg::PARSEABLE_PRIORITY_COMPONENTS = {"FW", "NIC_FW", "FW_SPC6", "VMOD"};

PldmPkg::PldmPkg() :
    deviceIDRecordCount(0), componentImageCount(0), downstreamDeviceRecordCount(0), packageHeaderChecksum(0)
{
}

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
    while (!downstreamDeviceRecords.empty())
    {
        delete downstreamDeviceRecords.back();
        downstreamDeviceRecords.pop_back();
    }
    while (!componentImages.empty())
    {
        delete componentImages.back();
        componentImages.pop_back();
    }
    psidRecordMap.clear();
    deviceIDRecordCount = 0;
    downstreamDeviceRecordCount = 0;
    componentImageCount = 0;
    packageHeader.reset();
}

bool PldmPkg::unpackRecords(PldmBuffer& buff,
                            std::vector<PldmDevIdRecord*>& records,
                            u_int8_t count,
                            u_int16_t componentBitmapBitLength,
                            bool isDownstream)
{
    for (u_int8_t i = 0; i < count; i++)
    {
        PldmDevIdRecord* record =
          isDownstream ? static_cast<PldmDevIdRecord*>(new PldmDownstreamDeviceRecord(componentBitmapBitLength)) :
                         new PldmDevIdRecord(componentBitmapBitLength);
        if (!record->unpack(buff))
        {
            delete record;
            reset();
            return false;
        }
        // Downstream devices have no PSID descriptor
        records.push_back(record);
        std::string psid = record->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID);
        if (!psid.empty())
        {
            psidRecordMap[psid] = record;
        }
    }
    return true;
}

// WA: ComponentOpaqueDataLength only matters at revision >= 2, and every
// known spc6 fwpkg carries exactly one device ID record. Only deviceIDRecords[0] is inspected;
// if a package ever legitimately carries multiple device records with different device
// identities, a single package-wide flag is the wrong model and this must be revisited.
bool PldmPkg::isSpc6Device(u_int8_t pldmRevision) const
{
    if (pldmRevision < FIRST_REVISION_SUPPORTED_DOWNSTREAM_DEVICES)
    {
        return false;
    }
    u_int16_t pciDeviceId;
    if (!deviceIDRecords.empty() &&
        deviceIDRecords[0]->getDescriptor(static_cast<u_int16_t>(DescriptorType::TYPE_PCI_DEVICE_ID), pciDeviceId))
    {
        return IsSpc6PciDeviceId(pciDeviceId);
    }
    return false;
}

bool PldmPkg::unpack(PldmBuffer& buff)
{
    reset();
    if (!packageHeader.unpack(buff))
    {
        return false;
    }
    u_int8_t pldmRevision = packageHeader.getPackageHeaderFormatRevision();

    u_int16_t componentBitmapBitLength = packageHeader.getComponentBitmapBitLength();
    buff.read(deviceIDRecordCount);

    if (!unpackRecords(buff, deviceIDRecords, deviceIDRecordCount, componentBitmapBitLength, /*isDownstream=*/false))
    {
        return false;
    }

    const bool spc6Device = isSpc6Device(pldmRevision);

    // downstream device record support is added in revision 3 and above
    if (packageHeader.getPackageHeaderFormatRevision() >= FIRST_REVISION_SUPPORTED_DOWNSTREAM_DEVICES)
    {
        buff.read(downstreamDeviceRecordCount);
        if (!unpackRecords(buff,
                           downstreamDeviceRecords,
                           downstreamDeviceRecordCount,
                           componentBitmapBitLength,
                           /*isDownstream=*/true))
        {
            return false;
        }
    }

    buff.read(componentImageCount);
    for (u_int8_t i = 0; i < componentImageCount; i++)
    {
        PldmComponenetImage* componentImage = new PldmComponenetImage();
        if (!componentImage->unpack(buff, pldmRevision, spc6Device))
        {
            delete componentImage;
            reset();
            return false;
        }
        componentImages.push_back(componentImage);
    }
    buff.read(packageHeaderChecksum);
    return !buff.overflowed();
}

bool PldmPkg::getMainComponentNameByPsid(const std::string& psid, std::string& component) const
{
    std::string validPsid = psid;
    std::vector<std::string> componentNames;
    if (validPsid.empty())
    {
        if (psidRecordMap.empty())
        {
            return false;
        }
        validPsid = psidRecordMap.begin()->first;
    }
    if (!getComponentsNamesByPsid(validPsid, componentNames))
    {
        return false;
    }
    for (const std::string& mainComponentName : PARSEABLE_PRIORITY_COMPONENTS)
    {
        if (std::find(componentNames.begin(), componentNames.end(), mainComponentName) != componentNames.end())
        {
            component = mainComponentName;
            return true;
        }
    }
    return false;
}

bool PldmPkg::getParsedSupportedComponentsByPsid(const std::string& psid,
                                                 std::vector<std::string>& parsedComponentNames) const
{
    std::vector<std::string> allComponentNames;
    if (!getComponentsNamesByPsid(psid, allComponentNames))
    {
        return false;
    }

    std::copy_if(
      PARSEABLE_PRIORITY_COMPONENTS.begin(), PARSEABLE_PRIORITY_COMPONENTS.end(),
      std::back_inserter(parsedComponentNames),
      [&allComponentNames](const std::string& name)
      { return std::find(allComponentNames.begin(), allComponentNames.end(), name) != allComponentNames.end(); });
    return true;
}

bool PldmPkg::getComponentsNamesByPsid(const std::string& psid, std::vector<std::string>& componentNames) const
{
    PldmDevIdRecord* rec = findRecordByPsid(psid);
    if (rec == NULL)
    {
        return false;
    }
    std::vector<u_int8_t> componentsIndexes = rec->getComponentsIndexes();

    for (size_t i = 0; i < componentsIndexes.size() && i < componentImageCount; i++)
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
        componentNames.push_back(currentComponentName);
    }
    return true;
}

bool PldmPkg::isComponentInPackage(const std::string& psid, const std::string& componentName) const
{
    std::vector<std::string> componentNames;
    if (!getComponentsNamesByPsid(psid, componentNames))
    {
        return false;
    }

    ComponentIdentifier componentIdentifier;
    StringToComponentIdentifier(componentName, componentIdentifier);

    // if the component is firmware, we need to check if it contains FW or NIC_FW - both are valid for firmware
    // components
    if (isNicFwComponent(componentIdentifier))
    {
        std::vector<std::string> targets = {"FW", "NIC_FW"};
        return std::find_first_of(componentNames.begin(), componentNames.end(), targets.begin(), targets.end()) !=
               componentNames.end();
    }
    return std::find(componentNames.begin(), componentNames.end(), componentName) != componentNames.end();
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

bool PldmPkg::getPldmDescriptorByPsid(const std::string& psid, u_int16_t type, u_int16_t& descriptor) const
{
    std::string mainComponentName;
    if (!getMainComponentNameByPsid(psid, mainComponentName))
    {
        return false;
    }
    // special case for VMOD component , his device id represent the device and nt the component
    if (mainComponentName == "VMOD" && type == DEV_ID_TYPE)
    {
        descriptor = 0;
        return true;
    }

    auto getDescriptorFromRecords = [&](const std::vector<PldmDevIdRecord*>& records)
    {
        for (auto devIdRec : records)
        {
            // if psid is empty, we will return the descriptor for the first matching device record
            std::string devIdPsid = devIdRec->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID);
            if (devIdPsid == psid || psid.empty())
            {
                return devIdRec->getDescriptor(type, descriptor);
            }
        }
        return false;
    };

    if (getDescriptorFromRecords(deviceIDRecords))
    {
        return true;
    }
    return getDescriptorFromRecords(downstreamDeviceRecords);
}

std::string PldmPkg::getPldmVendorDefinedDescriptorByPsid(const std::string& psid,
                                                          PldmRecordDescriptor::VendorDefinedType type) const
{
    auto getVendorDefinedFromRecords = [&](const std::vector<PldmDevIdRecord*>& records) -> std::string
    {
        for (auto devIdRec : records)
        {
            std::string devIdPsid = devIdRec->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID);
            if (devIdPsid == psid || psid.empty())
            {
                return devIdRec->GetVendorDefinedValue(type);
            }
        }
        return std::string();
    };

    std::string descriptor = getVendorDefinedFromRecords(deviceIDRecords);
    if (!descriptor.empty())
    {
        return descriptor;
    }
    return getVendorDefinedFromRecords(downstreamDeviceRecords);
}
bool PldmPkg::isPsidInPldm(const std::string& psid) const
{
    if (psid.empty())
    {
        return true;
    }
    auto psidExistsInRecords = [&](const std::vector<PldmDevIdRecord*>& records)
    {
        for (auto devIdRec : records)
        {
            if (devIdRec->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID) == psid)
            {
                return true;
            }
        }
        return false;
    };
    return psidExistsInRecords(deviceIDRecords) || psidExistsInRecords(downstreamDeviceRecords);
}

bool PldmPkg::extractComponentDataFromRecords(const std::vector<PldmDevIdRecord*>& records,
                                              ComponentIdentifier compIdentifier,
                                              const std::string& psid,
                                              u_int8_t** buff,
                                              u_int32_t& buffSize)
{
    bool found = false;
    for (auto devIdRec : records)
    {
        std::string devIdPsid = devIdRec->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID);
        if (devIdPsid == psid || psid.empty())
        {
            u_int16_t comps_count = getComponentImageCount();
            std::vector<u_int8_t> appliedComponents = devIdRec->getComponentsIndexes();
            for (u_int16_t i = 0; i < comps_count; i++)
            {
                if (i >= appliedComponents.size())
                {
                    break;
                }
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
                    *buff = new (std::nothrow) u_int8_t[buffSize];
                    if (*buff == nullptr)
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
    if (psid.empty())
    {
        if (!deviceIDRecords.empty())
        {
            return deviceIDRecords[0];
        }
        return downstreamDeviceRecords.empty() ? NULL : downstreamDeviceRecords[0];
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
    u_int32_t le = mft_cpu_to_le32(newCrc);
    return buff.writeAt(checksumOffset, (const u_int8_t*)&le, sizeof(le));
}

bool PldmPkg::getComponentDataByPsid(ComponentIdentifier compIdentifier,
                                     const std::string& psid,
                                     u_int8_t** buff,
                                     u_int32_t& buffSize)
{
    if (extractComponentDataFromRecords(deviceIDRecords, compIdentifier, psid, buff, buffSize))
    {
        return true;
    }
    return extractComponentDataFromRecords(downstreamDeviceRecords, compIdentifier, psid, buff, buffSize);
}