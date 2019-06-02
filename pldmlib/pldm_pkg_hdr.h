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

