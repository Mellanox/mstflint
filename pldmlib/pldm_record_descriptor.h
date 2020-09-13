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

