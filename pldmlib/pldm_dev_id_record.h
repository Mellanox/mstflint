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

#ifndef _PLDM_DEV_ID_RECORD_HDR_
#define _PLDM_DEV_ID_RECORD_HDR_

class PldmRecordDescriptor;

class PldmDevIdRecord {
public:
    PldmDevIdRecord(u_int8_t componentBitmapBitLength=0);
    virtual ~PldmDevIdRecord();
    bool unpack(PldmBuffer & buff);
    int getComponentImageIndex() const;
    std::string getDevicePsid() const;
    std::string getDescription() const;
    void print(FILE * fp);
private:
    u_int8_t componentBitmapBitLength;

    u_int16_t recordLength;
    u_int8_t descriptorCount;
    u_int32_t deviceUpdateOptionFlags;
    u_int8_t componentImageSetVersionStringType;
    u_int8_t componentImageSetVersionStringLength;
    u_int16_t firmwareDevicePackageDataLength;
    u_int8_t * applicableComponents;
    std::string componentImageSetVersionString;
    std::vector<PldmRecordDescriptor *> recordDescriptors;
    u_int8_t * firmwareDevicePackageData;
};

#endif /* _PLDM_DEV_ID_RECORD_HDR_ */

