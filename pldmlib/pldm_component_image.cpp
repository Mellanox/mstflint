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
