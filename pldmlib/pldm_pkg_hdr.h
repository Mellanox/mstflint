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
 * pldm_utils.h
 *
 *  Created on: Feb 27, 2019
 *      Author: Samer Deeb
 */

#ifndef _PLDM_PKG_HDR_
#define _PLDM_PKG_HDR_

class PldmPkgHdr {
public:
    PldmPkgHdr();
    virtual ~PldmPkgHdr();

    bool unpack(PldmBuffer & buff);
    void print(FILE * fp);

    const u_int32_t * getPackageHeaderIdentifier() const {
        return packageHeaderIdentifier;
    }
    u_int8_t getPackageHeaderFormatRevision() const {
        return packageHeaderFormatRevision;
    }
    u_int16_t getPackageHeaderSize() const {
        return packageHeaderSize;
    }
    const u_int8_t * getPackageReleaseDateTime() const {
        return packageReleaseDateTime;
    }
    u_int16_t getComponentBitmapBitLength() const {
        return componentBitmapBitLength;
    }
    u_int8_t getPackageVersionStringType() const {
        return packageVersionStringType;
    }
    u_int8_t getPackageVersionStringLength() const {
        return packageVersionStringLength;
    }
    const std::string & getPackageVersionString() const {
        return packageVersionString;
    }

private:
    static const int ID_COUNT = 4;
    static const int TIMESTAMP_SIZE = 13;
    u_int32_t packageHeaderIdentifier[ID_COUNT];
    u_int8_t packageHeaderFormatRevision;
    u_int16_t packageHeaderSize;
    u_int8_t packageReleaseDateTime[TIMESTAMP_SIZE];
    u_int16_t componentBitmapBitLength;
    u_int8_t packageVersionStringType;
    u_int8_t packageVersionStringLength;
    std::string packageVersionString;
};

#endif /* _PLDM_PKG_HDR_ */

