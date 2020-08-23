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
#include <map>

#include "pldm_buff.h"
#include "pldm_pkg_hdr.h"
#include "pldm_record_descriptor.h"
#include "pldm_dev_id_record.h"
#include "pldm_component_image.h"
#include "pldm_pkg.h"

const u_int8_t PldmPkg::UUID[] = {0xF0, 0x18, 0x87, 0x8C, 0xCB, 0x7D, 0x49,
            0x43, 0x98, 0x00, 0xA0, 0x2F, 0x05, 0x9A, 0xCA, 0x02};

PldmPkg::PldmPkg(): deviceIDRecordCount(0) {
}

PldmPkg::~PldmPkg() {
    while(!deviceIDRecords.empty()) {
        delete deviceIDRecords.back();
        deviceIDRecords.pop_back();
    }
    while(!componentImages.empty()) {
        delete componentImages.back();
        componentImages.pop_back();
    }
}

bool PldmPkg::unpack(PldmBuffer & buff) {
    if(!packageHeader.unpack(buff)) {
        return false;
    }
    buff.read(deviceIDRecordCount);
    u_int8_t componentBitmapBitLength = \
            packageHeader.getComponentBitmapBitLength();
    u_int8_t i;
    for(i=0; i< deviceIDRecordCount; i++) {
        PldmDevIdRecord * deviceIDRecord = new PldmDevIdRecord(componentBitmapBitLength);
        deviceIDRecord->unpack(buff);
        deviceIDRecords.push_back(deviceIDRecord);
        psidImageMap[deviceIDRecord->getDevicePsid()] = deviceIDRecord->getComponentImageIndex();
    }
    buff.read(componentImageCount);
    for(i=0; i< componentImageCount; i++) {
        PldmComponenetImage * componentImage = new PldmComponenetImage();
        componentImage->unpack(buff);
        componentImages.push_back(componentImage);
    }
    buff.read(packageHeaderChecksum);
    return true;
}


void PldmPkg::print(FILE * fp) {
    fprintf(fp, "packageHeader:\n");
    packageHeader.print(fp);
    fprintf(fp, "deviceIDRecordCount: 0x%X\n", deviceIDRecordCount);
    u_int8_t i;
    for(i=0; i< deviceIDRecordCount; i++) {
        fprintf(fp, "deviceIDRecords[%d]:\n", i);
        deviceIDRecords[i]->print(fp);
    }
    fprintf(fp, "componentImageCount: 0x%X\n", componentImageCount);
    for(i=0; i< componentImageCount; i++) {
        fprintf(fp, "componentImages[%d]:\n", i);
        componentImages[i]->print(fp);
    }
    fprintf(fp, "packageHeaderChecksum: 0x%X\n", packageHeaderChecksum);
}

const PldmComponenetImage * PldmPkg::getImageByPsid(const std::string & psid) const {
    PsidImageMap::const_iterator it = psidImageMap.find(psid);
    if (it == psidImageMap.end())
        return NULL;
    int location = it->second;
    if(location == -1 || location >= componentImageCount)
        return NULL;
    return componentImages[location];
}
