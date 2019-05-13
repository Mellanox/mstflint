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

#ifndef _PLDM_DEV_ID_RECORD_HDR_
#define _PLDM_DEV_ID_RECORD_HDR_

class PldmRecordDescriptor;

class PldmDevIdRecord {
public:
    PldmDevIdRecord(u_int8_t componentBitmapBitLength=0);
    virtual ~PldmDevIdRecord();

    bool unpack(PldmBuffer & buff);
    void print(FILE * fp);

    int getComponentImageIndex() const;
    std::string getDevicePsid() const;
    std::string getDescription() const;
    u_int16_t get() const {
        return recordLength;
    }
    u_int8_t getDescriptorCount() const { return descriptorCount; }
    u_int32_t getDeviceUpdateOptionFlags() const {
        return deviceUpdateOptionFlags;
    }
    u_int8_t getComponentImageSetVersionStringType() const {
        return componentImageSetVersionStringType;
    }
    u_int8_t getComponentImageSetVersionStringLength() const {
        return componentImageSetVersionStringLength;
    }
    u_int16_t getFirmwareDevicePackageDataLength() const {
        return firmwareDevicePackageDataLength;
    }
    const std::string & getComponentImageSetVersionString() const {
        return componentImageSetVersionString;
    }
    const PldmRecordDescriptor * getRecordDescriptor(int index) const {
        return recordDescriptors[index];
    }
    const u_int8_t * getFirmwareDevicePackageData() const {
        return firmwareDevicePackageData;
    }

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

