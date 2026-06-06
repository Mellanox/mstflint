/*
 * Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 *
 * This software product is a proprietary product of Nvidia Corporation and its affiliates
 * (the "Company") and all right, title, and interest in and to the software
 * product, including all associated intellectual property rights, are and
 * shall remain exclusively with the Company.
 *
 * This software product is governed by the End User License Agreement
 * provided with the software product.
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
 