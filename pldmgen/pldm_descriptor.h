/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

 #ifndef PLDM_DEVICEDESCRIPTOR_H_
 #define PLDM_DEVICEDESCRIPTOR_H_
 
 #include <string>
 #include <vector>
 #include <map>
 
 #include "common/compatibility.h"
 #include "pldm_utils/pldm_utils.h"
 #include "mft_utils/mft_utils.h"
 
 #define PCI_VENDOR_ID_STR "PCI Vendor ID"
 #define APSKU_STR "APSKU"
 #define PSID_STR "PSID"
 #define UUID_STR "UUID"
 #define IANA_ENTERPRISE_ID_STR "IANA Enterprise ID"
 #define PCI_REVISION_ID_STR "PCI Revision ID"
 #define PCI_DEVICE_ID_STR "PCI Device ID"
 #define PCI_SUBSYSTEM_ID_STR "PCI Subsystem ID"
 #define PCI_SUBSYSTEM_VENDOR_ID_STR "PCI Subsystem Vendor ID"
 #define RECOVERY_STR "recovery"
 
 using DescriptorTypeEntry = std::pair<std::string, DescriptorType>;
 // If a new descriptor is added, update the Confluence page as well:
 // https://nvidia.atlassian.net/wiki/spaces/SW/pages/3064486398/PLDM+fwpkg+Generation
 // Order is important, it is used for the fwpkg descriptor order
 static const std::vector<DescriptorTypeEntry> DESCRIPTOR_TYPE_LIST = {
   {PCI_VENDOR_ID_STR, DescriptorType::TYPE_PCI_VENDOR_ID},
   {IANA_ENTERPRISE_ID_STR, DescriptorType::TYPE_IANA_ENTERPRISE_ID},
   {UUID_STR, DescriptorType::TYPE_UUID},
   // Vendor defined descriptors
   {APSKU_STR, DescriptorType::TYPE_VENDOR_DEFINED},
   {PSID_STR, DescriptorType::TYPE_VENDOR_DEFINED},
   {RECOVERY_STR, DescriptorType::TYPE_VENDOR_DEFINED},
   /****************************/
   {PCI_DEVICE_ID_STR, DescriptorType::TYPE_PCI_DEVICE_ID},
   {PCI_SUBSYSTEM_VENDOR_ID_STR, DescriptorType::TYPE_PCI_SUBSYSTEM_VENDOR_ID},
   {PCI_SUBSYSTEM_ID_STR, DescriptorType::TYPE_PCI_SUBSYSTEM_ID},
   {PCI_REVISION_ID_STR, DescriptorType::TYPE_PCI_REVISION_ID}};
 
 const std::map<std::string, std::string> DEFAULT_VALUES_MAP = {{IANA_ENTERPRISE_ID_STR, "0x00001647"},
                                                                {RECOVERY_STR, "recovery"},
                                                                {PCI_VENDOR_ID_STR, "0x15b3"}};
 
 class PLDMDescriptor
 {
 public:
     u_int16_t _type;
     std::vector<u_int8_t> _value;
 
     PLDMDescriptor(const std::string& type, const std::string& value);
     void Pack(std::vector<u_int8_t>& buff);
     static bool IsDefaultValue(const std::string& descriptorName);
     static std::string GetDefaultValue(const std::string& descriptorName);
     static std::string ValidAndNormalizeValue(const std::string& value);

 private:
     void ParseType(const std::string& type);
     void AddVendoreDefinedMetaDataDescriptor(std::string type);
 };
 
 #endif
 