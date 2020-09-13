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
