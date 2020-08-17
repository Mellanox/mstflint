/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) 2019, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 * pldm_buff.cpp
 *
 *  Created on: Feb 27, 2019
 *      Author: Samer Deeb
 */

#include <stdlib.h>
#include <stdio.h>
#include <string>


#include "pldm_buff.h"
#include "pldm_record_descriptor.h"


PldmRecordDescriptor::PldmRecordDescriptor(): descriptorType(0),
    descriptorLength(0), descriptorData(NULL){
}

PldmRecordDescriptor::~PldmRecordDescriptor() {
    if(descriptorData) {
        delete [] descriptorData;
    }
}

bool PldmRecordDescriptor::unpack(PldmBuffer & buff) {
    buff.read(descriptorType);
    buff.read(descriptorLength);
    if(descriptorLength) {
        descriptorData = new u_int8_t[descriptorLength];
        buff.read(descriptorData, descriptorLength);
        extractPsid();
    }
    return true;
}

void PldmRecordDescriptor::extractPsid() {
    if (descriptorType == Vendor_Defined) {
        u_int8_t * psidptr = descriptorData;
        psidptr++;
        u_int8_t prefixlen = *psidptr;
        psidptr++;
        psidptr += prefixlen;
        psid = std::string(reinterpret_cast<const char *>(psidptr));
    }
}

void PldmRecordDescriptor::print(FILE * fp) {
    fprintf(fp, "descriptorType: 0x%X ", descriptorType);
    fprintf(fp, "descriptorLength: 0x%X ", descriptorLength);
    fprintf(fp, "data: %s\n", getDescription().c_str());
}

std::string PldmRecordDescriptor::getDescription() const {
    char description[256] = {'\0'};
    switch(descriptorType) {
    case PCI_Vendor_ID:
        sprintf(description, "PCI Vendor ID: 0x%02x%02x",
                descriptorData[1], descriptorData[0]);
        break;
    case PCI_Device_ID:
            sprintf(description, "PCI Device ID: 0x%02x%02x",
                    descriptorData[1], descriptorData[0]);
            break;
    case PCI_Subsystem_Vendor_ID:
            sprintf(description, "PCI Subsystem Vendor ID: 0x%02x%02x",
                    descriptorData[1], descriptorData[0]);
            break;
    case PCI_Subsystem_ID:
            sprintf(description, "PCI Subsystem ID: 0x%02x%02x",
                    descriptorData[1], descriptorData[0]);
            break;
    case Vendor_Defined:
        sprintf(description, "PSID: %s", psid.c_str());
        break;

    }
    return description;
}
