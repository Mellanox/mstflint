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

#ifndef _PLDM_RECORD_DESCRIPTOR_HDR_
#define _PLDM_RECORD_DESCRIPTOR_HDR_

class PldmRecordDescriptor {
public:
    PldmRecordDescriptor();
    virtual ~PldmRecordDescriptor();

    bool unpack(PldmBuffer & buff);
    void print(FILE * fp);

    const std::string & getPsid() const { return psid; }
    u_int16_t getDescriptorLength() const { return descriptorLength; }
    const u_int8_t * getDescriptorData() const { return descriptorData; }
    std::string getDescription() const;

private:
    u_int16_t descriptorType;
    u_int16_t descriptorLength;
    u_int8_t * descriptorData;

    std::string psid;

    void extractPsid();
    enum {
        PCI_Vendor_ID = 0x0000,
        IANA_Enterprise_ID = 0x0001,
        FD_UUID = 0x0002,
        PnP_Vendor_ID = 0x0003,
        ACPI_Vendor_ID = 0x0004,
        PCI_Device_ID = 0x0100,
        PCI_Subsystem_Vendor_ID = 0x0101,
        PCI_Subsystem_ID = 0x0102,
        PCI_Revision_ID = 0x0103,
        PnP_Product_ID = 0x0104,
        ACPI_Product_ID = 0x0105,
        Vendor_Defined = 0xFFFF
    };
};

#endif /* _PLDM_RECORD_DESCRIPTOR_HDR_ */

