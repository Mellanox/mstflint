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

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>
#include <cstring>

#include "pldm_buff.h"
#include "pldm_pkg_hdr.h"
#include "pldm_dev_id_record.h"
#include "pldm_component_image.h"
#include "pldm_pkg.h"

const u_int8_t PldmPkg::UUID[] = {0xF0, 0x18, 0x87, 0x8C, 0xCB, 0x7D, 0x49, 0x43,
                                  0x98, 0x00, 0xA0, 0x2F, 0x05, 0x9A, 0xCA, 0x02};

PldmPkg::PldmPkg() : deviceIDRecordCount(0), componentImageCount(0) {}

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
    deviceIDRecordCount = 0;
    componentImageCount = 0;
    packageHeader.reset();
}

bool PldmPkg::unpack(PldmBuffer& buff)
{
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
        psidImageMap[deviceIDRecord->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID)] =
          deviceIDRecord->getComponentImageIndex();
        psidComponentsMap[deviceIDRecord->GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType::PSID)] =
          deviceIDRecord->getComponentsIndexes();
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

void PldmPkg::print(FILE* fp)
{
    fprintf(fp, "packageHeader:\n");
    packageHeader.print(fp);
    fprintf(fp, "deviceIDRecordCount: 0x%X\n", deviceIDRecordCount);
    u_int8_t i;
    for (i = 0; i < deviceIDRecordCount; i++)
    {
        fprintf(fp, "deviceIDRecords[%d]:\n", i);
        deviceIDRecords[i]->print(fp);
    }
    fprintf(fp, "componentImageCount: 0x%X\n", componentImageCount);
    for (i = 0; i < componentImageCount; i++)
    {
        fprintf(fp, "componentImages[%d]:\n", i);
        componentImages[i]->print(fp);
    }
    fprintf(fp, "packageHeaderChecksum: 0x%X\n", packageHeaderChecksum);
}

const PldmComponenetImage* PldmPkg::getImageByPsid(const std::string& psid) const
{
    PsidImageMap::const_iterator it = psidImageMap.find(psid);
    if (it == psidImageMap.end())
        return NULL;
    int location = it->second;
    if (location == -1 || location >= componentImageCount)
        return NULL;
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
