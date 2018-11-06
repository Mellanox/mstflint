/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 * mlxarchive_mfa2.cpp
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#include <xz_utils/xz_utils.h>
#include <mlxsign_lib/mlxsign_lib.h>
#include "mlxarchive_mfa2.h"
#include "mlxarchive_mfa2_utils.h"

using namespace mfa2;

/*void MFA2::updateSHA256()
{
    vector<u_int8_t> digest;
    MlxSignSHA256 mlxSignSHA256;

    //compute descriptors SHA256
    vector<u_int8_t> descriptorsBuff;
    packDescriptors(descriptorsBuff);
    mlxSignSHA256 << descriptorsBuff;
    mlxSignSHA256.getDigest(digest);
    _packageDescriptor.setDescriptorsSHA256(digest);

    //append the zipped components block
    packBytesArray(zippedComponentBlockBuff.data(), zippedComponentBlockBuff.size(), buff);

    //compute SHA256
    mlxSignSHA256 << zippedComponentBlockBuff;
    mlxSignSHA256.getDigest(digest);
}*/

void MFA2::packDescriptors(vector<u_int8_t>& buff) const
{
    _fingerPrint.pack(buff);
    _packageDescriptor.pack(buff);
    CONST_VECTOR_ITERATOR(DeviceDescriptor, _deviceDescriptors, it) {
        (*it).pack(buff);
    }
    CONST_VECTOR_ITERATOR(Component, _components, it) {
        (*it).packDescriptor(buff);
    }
}

void MFA2::pack(vector<u_int8_t>& buff)
{
    //find size of components block:
    u_int64_t componentsBlockSize = 0;
    CONST_VECTOR_ITERATOR(Component, _components, it) {
        componentsBlockSize += (*it).getComponentBinarySize();
    }
    _packageDescriptor.setComponentsBlockSize(componentsBlockSize);

    _fingerPrint.pack(buff);

    _packageDescriptor.pack(buff);

    CONST_VECTOR_ITERATOR(DeviceDescriptor, _deviceDescriptors, it) {
        (*it).pack(buff);
    }

    CONST_VECTOR_ITERATOR(Component, _components, it) {
        (*it).packDescriptor(buff);
    }

    _packageDescriptor.setComponentsBlockOffset(buff.size());

    //compress components block
    vector<u_int8_t> componentsBlockBuff;
    VECTOR_ITERATOR(Component, _components, it) {
        (*it).setComponentBinaryOffset(componentsBlockBuff.size());
        (*it).packData(componentsBlockBuff);
    }
    u_int32_t zippedSize = componentsBlockBuff.size();
    zippedSize = xz_compress_crc32(8, componentsBlockBuff.data(),
            componentsBlockBuff.size(), NULL, 0);
    if (zippedSize <= 0)
    {
        //TODO throw exception
        printf("-E- Error while compressing\n");
        exit(1);
    }
    _packageDescriptor.setComponentsBlockArchiveSize(zippedSize);
    vector<u_int8_t> zippedComponentBlockBuff(zippedSize);
    xz_compress_crc32(9, componentsBlockBuff.data(), componentsBlockBuff.size(),
            zippedComponentBlockBuff.data(), zippedSize);

    //compute descriptors SHA256
    vector<u_int8_t> descriptorsBuff;
    packDescriptors(descriptorsBuff);
    vector<u_int8_t> digest;
    MlxSignSHA256 mlxSignSHA256;
    mlxSignSHA256 << descriptorsBuff;
    mlxSignSHA256.getDigest(digest);
    _packageDescriptor.setDescriptorsSHA256(digest);

    //append the zipped components block
    packBytesArray(zippedComponentBlockBuff.data(), zippedComponentBlockBuff.size(), buff);

    //compute SHA256
    mlxSignSHA256 << zippedComponentBlockBuff;
    mlxSignSHA256.getDigest(digest);
    _packageDescriptor.setSHA256(digest);

}

/*void MFA2::update(vector<u_int8_t>& buff)
{
    //update components descriptors with information about components blocks
    u_int64_t offset = 0x0;

    VECTOR_ITERATOR(_components, );
}*/

void MFA2::generateBinary(vector<u_int8_t>& buff)
{
    vector<u_int8_t> tmpBuff;

    //do first pass
    pack(tmpBuff);

    //do second pass
    pack(buff);

    //compute SHA256

}
