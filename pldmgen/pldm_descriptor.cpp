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

 #include <cstring>
 #include <iomanip>
 #include <algorithm>
 
 #include "pldm_descriptor.h"
 #include "pldm_utils/pldm_utils.h"
 
 using namespace std;
 
 #define UUID_BYTES_LEN 16
 #define APSKU_BYTES_LEN 4
 
 void PLDMDescriptor::ParseType(const string& type)
 {
     for (const auto& entry : DESCRIPTOR_TYPE_LIST)
     {
         if (entry.first == type)
         {
             _type = static_cast<u_int16_t>(entry.second);
             return;
         }
     }
     throw PLDMException("Invalid descriptor type: %s", type.c_str());
 }
 
 PLDMDescriptor::PLDMDescriptor(const string& type, const string& value)
 {
     ParseType(type);
 
     if (type == PSID_STR || type == RECOVERY_STR)
     {
         AddVendoreDefinedMetaDataDescriptor(type);
         dumpString(_value, value);
         if (type == PSID_STR)
         {
             const size_t psidLength = 0x16;
             while (_value.size() < psidLength)
             {
                 _value.push_back(0x0);
             }
         }
     }
     else if (type == UUID_STR)
     {
         strToArry(value, "UUID", _value, UUID_BYTES_LEN);
     }
     else
     {
         u_int32_t num = 0;
         if (!mft_utils::strToNum(value, num))
         {
             throw PLDMException("Invalid value %s given for %s", value.c_str(), type.c_str());
         }
         if (num >= (1 << 16) && type != APSKU_STR)
         {
             throw PLDMException("value %s is larger than max allowed value for "
                                 "descriptor of type %s",
                                 value.c_str(),
                                 type.c_str());
         }
         if (type == IANA_ENTERPRISE_ID_STR)
         {
             dumpUInt32(_value, num);
         }
         else if (type == APSKU_STR)
         {
             if (!ValidSizeAndFormat(value, APSKU_BYTES_LEN))
             {
                 throw PLDMException(
                   "Invalid value for APSKU. It must be in hexadecimal format and no more than %d bytes in length.\n",
                   APSKU_BYTES_LEN);
             }
             AddVendoreDefinedMetaDataDescriptor(type);
             dumpUInt32(_value, num);
         }
         else
         {
             dumpUInt16(_value, num);
         }
     }
 }
 
 void PLDMDescriptor::AddVendoreDefinedMetaDataDescriptor(string type)
 {
     // VendorDefinedDescriptorTitleStringType
     dumpUInt8(_value, VERSION_STRING_TYPE_ASCII);
     // VendorDefinedDescriptorTitleStringLength
     dumpUInt8(_value, type.length());
     // VendorDefinedDescriptorTitleString
     dumpString(_value, type);
 }
 
 void PLDMDescriptor::Pack(vector<u_int8_t>& buff)
 {
     // Type
     dumpUInt16(buff, _type);
 
     // Length
     dumpUInt16(buff, _value.size());
 
     // Value
     dumpBytesArray(buff, _value.data(), _value.size());
 
     return;
 }
 
 bool PLDMDescriptor::IsDefaultValue(const string& descriptorName)
 {
     return DEFAULT_VALUES_MAP.find(descriptorName) != DEFAULT_VALUES_MAP.end();
 }
 
 string PLDMDescriptor::GetDefaultValue(const string& descriptorName)
 {
     const auto it = DEFAULT_VALUES_MAP.find(descriptorName);
     if (it == DEFAULT_VALUES_MAP.end())
     {
         throw PLDMException("No default value defined for descriptor '%s'", descriptorName.c_str());
     }
     return it->second;
 }
 
 string PLDMDescriptor::ValidAndNormalizeValue(const string& value)
 {
     for (const auto& it : DESCRIPTOR_TYPE_LIST)
     {
         if (ToLower(it.first) == ToLower(value))
         {
             return it.first;
         }
     }
    throw PLDMException("Invalid Descriptor value %s given", value.c_str());
 }
 