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
