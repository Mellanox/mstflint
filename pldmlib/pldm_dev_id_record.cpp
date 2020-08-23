/*
 * Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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


#include "pldm_buff.h"
#include "pldm_record_descriptor.h"
#include "pldm_dev_id_record.h"



PldmDevIdRecord::PldmDevIdRecord(u_int8_t bitmapBitLength):
        componentBitmapBitLength(bitmapBitLength), recordLength(0),
        descriptorCount(0), deviceUpdateOptionFlags(0),
        componentImageSetVersionStringType(0),
        componentImageSetVersionStringLength(0),
        firmwareDevicePackageDataLength(0), applicableComponents(NULL),
        firmwareDevicePackageData(NULL) {
}

PldmDevIdRecord::~PldmDevIdRecord() {
    if(applicableComponents) {
        delete [] applicableComponents;
    }
    if(firmwareDevicePackageData) {
        delete [] firmwareDevicePackageData;
    }
    while(!recordDescriptors.empty()) {
        delete recordDescriptors.back();
        recordDescriptors.pop_back();
    }

}

bool PldmDevIdRecord::unpack(PldmBuffer & buff) {
    buff.read(recordLength);
    buff.read(descriptorCount);
    buff.read(deviceUpdateOptionFlags);
    buff.read(componentImageSetVersionStringType);
    buff.read(componentImageSetVersionStringLength);
    buff.read(firmwareDevicePackageDataLength);
    if(componentBitmapBitLength) {
        u_int8_t applicableComponentsLen = componentBitmapBitLength/8;
        applicableComponents = new u_int8_t[applicableComponentsLen];
        buff.read(applicableComponents, applicableComponentsLen);
    }
    buff.read(componentImageSetVersionString,
            componentImageSetVersionStringLength);
    for(u_int8_t i=0; i<descriptorCount; i++) {
        PldmRecordDescriptor * descriptor = new PldmRecordDescriptor();
        descriptor->unpack(buff);
        recordDescriptors.push_back(descriptor);
    }
    if(firmwareDevicePackageDataLength) {
        buff.read(firmwareDevicePackageData, firmwareDevicePackageDataLength);
    }
    return true;
}

void PldmDevIdRecord::print(FILE * fp) {
    fprintf(fp, "recordLength: 0x%X\n", recordLength);
    fprintf(fp, "descriptorCount: 0x%X\n", descriptorCount);
    fprintf(fp, "deviceUpdateOptionFlags: 0x%X\n", deviceUpdateOptionFlags);
    fprintf(fp, "componentImageSetVersionStringType: 0x%X\n", componentImageSetVersionStringType);
    fprintf(fp, "componentImageSetVersionStringLength: 0x%X\n", componentImageSetVersionStringLength);
    fprintf(fp, "firmwareDevicePackageDataLength: 0x%X\n", firmwareDevicePackageDataLength);
    if(componentBitmapBitLength) {
        u_int8_t applicableComponentsLen = componentBitmapBitLength/8;
        for(u_int8_t i=0; i<applicableComponentsLen; i++) {
            fprintf(fp, "applicableComponents[%d]: 0x%X\n", i, applicableComponents[i]);
        }
    }
    fprintf(fp, "componentImageSetVersionString: %s\n", componentImageSetVersionString.c_str());
    for(u_int8_t i=0; i<descriptorCount; i++) {
        fprintf(fp, "recordDescriptors[%d]:\n", i);
        recordDescriptors[i]->print(fp);
    }

}

int PldmDevIdRecord::getComponentImageIndex() const {
    u_int8_t applicableComponentsLen = componentBitmapBitLength/8;
    int index = -1;
    static const u_int8_t index_map[] = {0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80};
    for(u_int8_t i=0; i<applicableComponentsLen; i++) {
        u_int8_t flags = applicableComponents[i];
        for(u_int8_t j=0; j<8; j++) {
            if (flags & index_map[j]) {
                index = i * 8 + j;
                break;
            }
        }
        if(index != -1)
            break;
    }
    return index;
}

std::string PldmDevIdRecord::getDevicePsid() const {
    std::string psid;
    for(u_int8_t i=0; i<descriptorCount; i++) {
        psid = recordDescriptors[i]->getPsid();
        if(psid != "")
            break;
    }
    return psid;
}

std::string PldmDevIdRecord::getDescription() const {

    std::string description;
    for(u_int8_t i=0; i<descriptorCount - 1; i++) {
        description += (recordDescriptors[i]->getDescription() + ", ");
    }
    if(descriptorCount > 0) {
        description += recordDescriptors[descriptorCount-1]->getDescription();
    }
    return description;
}
