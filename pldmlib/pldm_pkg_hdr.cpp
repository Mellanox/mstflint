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
#include "pldm_pkg_hdr.h"


PldmPkgHdr::PldmPkgHdr(): packageHeaderFormatRevision(0), packageHeaderSize(0),
        componentBitmapBitLength(0), packageVersionStringType(0),
        packageVersionStringLength(0)
{
    int i = 0;
    for(i=0; i<ID_COUNT; i++) {
        packageHeaderIdentifier[i] = 0;
    }

    for(i=0; i<TIMESTAMP_SIZE; i++) {
        packageReleaseDateTime[i] = 0;
    }

}

PldmPkgHdr::~PldmPkgHdr() {
}

bool PldmPkgHdr::unpack(PldmBuffer & buff) {
    for(int i=0; i<ID_COUNT; i++) {
        buff.read(packageHeaderIdentifier[i]);
    }
    buff.read(packageHeaderFormatRevision);
    buff.read(packageHeaderSize);
    buff.read(packageReleaseDateTime, TIMESTAMP_SIZE);
    buff.read(componentBitmapBitLength);
    buff.read(packageVersionStringType);
    buff.read(packageVersionStringLength);
    buff.read(packageVersionString, packageVersionStringLength);
    return true;
}

void PldmPkgHdr::print(FILE * fp) {

    for(int i=0; i<ID_COUNT; i++) {
        fprintf(fp, "packageHeaderIdentifier[%d]: 0x%X\n", i,
                packageHeaderIdentifier[i]);
    }
    fprintf(fp, "packageHeaderFormatRevision: 0x%X\n", packageHeaderFormatRevision);
    fprintf(fp, "packageHeaderSize: 0x%X\n", packageHeaderSize);
    fprintf(fp, "componentBitmapBitLength: 0x%X\n", componentBitmapBitLength);
    fprintf(fp, "packageVersionStringType: 0x%X\n", packageVersionStringType);
    fprintf(fp, "packageVersionStringLength: 0x%X\n", packageVersionStringLength);
    fprintf(fp, "packageVersionString: %s\n", packageVersionString.c_str());
}
