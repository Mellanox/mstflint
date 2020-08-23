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
#include <errno.h>
#include <string>


#include "pldm_buff.h"
#include "pldm_component_image.h"


PldmComponenetImage::PldmComponenetImage(): componentClassification(0),
    componentIdentifier(0), componentComparisonStamp(0), componentOptions(0),
    requestedComponentActivationMethod(0), componentLocationOffset(0),
    componentSize(0), componentVersionStringType(0),
    componentVersionStringLength(0), componentData(NULL) {
}

PldmComponenetImage::~PldmComponenetImage() {
    if(componentData) {
        delete [] componentData;
    }
}

bool PldmComponenetImage::unpack(PldmBuffer & buff) {

    buff.read(componentClassification);
    buff.read(componentIdentifier);
    buff.read(componentComparisonStamp);
    buff.read(componentOptions);
    buff.read(requestedComponentActivationMethod);
    buff.read(componentLocationOffset);
    buff.read(componentSize);
    buff.read(componentVersionStringType);
    buff.read(componentVersionStringLength);
    buff.read(componentVersionString, componentVersionStringLength);

    return readComponentData(buff);
}

bool PldmComponenetImage::readComponentData(PldmBuffer & buff) {
    componentData = new u_int8_t[componentSize];
    // restore previous position
    long pos = buff.tell();
    buff.seek(componentLocationOffset, SEEK_SET);
    buff.read(componentData, componentSize);
    // restore previous position
    buff.seek(pos, SEEK_SET);
    return true;
}

void PldmComponenetImage::print(FILE * fp) {
    fprintf(fp, "componentClassification: 0x%X\n", componentClassification);
    fprintf(fp, "componentIdentifier: 0x%X\n", componentIdentifier);
    fprintf(fp, "componentComparisonStamp: 0x%X\n", componentComparisonStamp);
    fprintf(fp, "componentOptions: 0x%X\n", componentOptions);
    fprintf(fp, "requestedComponentActivationMethod: 0x%X\n", requestedComponentActivationMethod);
    fprintf(fp, "componentLocationOffset: 0x%X\n", componentLocationOffset);
    fprintf(fp, "componentSize: 0x%X\n", componentSize);
    fprintf(fp, "componentVersionStringType: 0x%X\n", componentVersionStringType);
    fprintf(fp, "componentVersionStringLength: 0x%X\n", componentVersionStringLength);
    fprintf(fp, "componentVersionString: %s\n", componentVersionString.c_str());
}
