/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include <vector>
#include "pldm_record_descriptor.h"

// Base record — Firmware Device ID Record layout (DSP0267 Table 4).
// unpack() is a template-method that defers the byte position between the
// VersionString and the Descriptors to a virtual hook so the downstream variant
// (Table 5) can plug in the MinVersionComparisonStamp without re-implementing
// the skeleton.
class PldmDevIdRecord
{
public:
    PldmDevIdRecord(u_int16_t componentBitmapBitLength = 0);
    virtual ~PldmDevIdRecord();
    bool unpack(PldmBuffer& buff);
    int getComponentImageIndex() const;
    std::vector<u_int8_t> getComponentsIndexes() const;
    std::vector<PldmRecordDescriptor*> getRecordDescriptors() const { return recordDescriptors; };
    std::string GetVendorDefinedValue(PldmRecordDescriptor::VendorDefinedType type) const;
    PldmRecordDescriptor* findVendorDefinedDescriptor(PldmRecordDescriptor::VendorDefinedType type) const;
    std::string getComponentImageSetVersionString() const { return componentImageSetVersionString; };
    u_int32_t getDeviceUpdateOptionFlags() const { return deviceUpdateOptionFlags; };
    bool getDescriptor(u_int16_t type, u_int16_t& descriptor) const;

    void reset();

protected:
    // downstream records read the MinVersionComparisonStamp when UpdateOptionFlags bit 0 is set.
    virtual bool unpackPostVersionString(PldmBuffer& /*buff*/) { return true; }

    u_int16_t componentBitmapBitLength;

    u_int16_t recordLength;
    u_int8_t descriptorCount;
    u_int32_t deviceUpdateOptionFlags;
    u_int8_t componentImageSetVersionStringType;
    u_int8_t componentImageSetVersionStringLength;
    u_int16_t firmwareDevicePackageDataLength;
    std::vector<u_int8_t> applicableComponents;
    std::string componentImageSetVersionString;
    std::vector<PldmRecordDescriptor*> recordDescriptors;
    std::vector<u_int8_t> firmwareDevicePackageData;
};

class PldmDownstreamDeviceRecord : public PldmDevIdRecord
{
public:
    PldmDownstreamDeviceRecord(u_int16_t componentBitmapBitLength = 0);
    u_int32_t getSelfContainedActivationMinVersionComparisonStamp() const
    {
        return selfContainedActivationMinVersionComparisonStamp;
    };

protected:
    bool unpackPostVersionString(PldmBuffer& buff) override;

private:
    u_int32_t selfContainedActivationMinVersionComparisonStamp;
};

#endif /* _PLDM_DEV_ID_RECORD_HDR_ */
