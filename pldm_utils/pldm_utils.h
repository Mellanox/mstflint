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

#ifndef PLDM_UTILS_H_
#define PLDM_UTILS_H_

#include <memory>
#include <string>
#include <vector>

#include <json/value.h>
#include "common/compatibility.h"

#define VERSION_STRING_TYPE_ASCII 0x1

constexpr const char* UNRECOGNIZE_COMPONENT_IDENTIFIER_STR = "Unrecognize component identifier";
constexpr u_int8_t FIRST_REVISION_SUPPORTED_DOWNSTREAM_DEVICES = 0x02;
constexpr int ALL_COMPONENTS = 4;
constexpr int FIRST_COMPONENT_IN_ARGV = 4;
constexpr u_int32_t COMPONENT_COMPARISON_STAMP_VALUE = 0xffffffff;
constexpr u_int16_t COMPONENT_OPTIONS_VALUE_FW = 0x0001;
constexpr u_int16_t COMPONENT_OPTIONS_VALUE_DEFAULT = 0x0000;
constexpr u_int16_t REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT = 0x0038;
constexpr u_int16_t DEV_ID_TYPE = 0x0100;

enum class ComponentField : u_int16_t
{
    Name = 0,
    Identifier = 1,
    Classification = 2,
    ActivationMethod = 3,
    Options = 4
};

enum class ComponentClassification : u_int16_t
{
    SwBundle = 0x000D,
    Firmware = 0x000A,
    Configuration = 0x0003,
    DownstreamDevice = 0xFFFF
};

enum class DescriptorType : uint16_t
{
    TYPE_PCI_VENDOR_ID = 0x0,
    TYPE_IANA_ENTERPRISE_ID = 0x1,
    TYPE_UUID = 0x02,
    TYPE_PCI_DEVICE_ID = 0x100,
    TYPE_PCI_SUBSYSTEM_VENDOR_ID = 0x101,
    TYPE_PCI_SUBSYSTEM_ID = 0x102,
    TYPE_PCI_REVISION_ID = 0x103,
    TYPE_VENDOR_DEFINED = 0xffff
};

enum class ComponentIdentifier
{
    Identifier_Not_Valid = 0x0000,
    Identifier_FW_Comp = 0x0001,
    Identifier_OEM_NVCONFIG_Comp = 0x0003,
    Identifier_MLNX_NVCONFIG_Comp = 0x0004,
    Identifier_FW_SPC6_Comp = 0x2001,
    Identifier_NIC_FW_Comp = 0x3001,
    Identifier_BF3BMC_PLDM_Comp = 0x3010,
    Identifier_BF3BMC_CEC_PLDM_Comp = 0x3018,
    Identifier_ARM_Capsule_Comp = 0x3020,
    Identifier_BFB_Comp = 0x3030,
    Identifier_VMOD_Comp = 0xE005,
    Identifier_General = 0xffff
};

const std::vector<u_int8_t> headerFormatRevision1 = {0xf0, 0x18, 0x87, 0x8c, 0xcb, 0x7d, 0x49, 0x43,
                                                     0x98, 0x00, 0xa0, 0x2f, 0x05, 0x9a, 0xca, 0x02};
// multi component is supported only in revision 3
const std::vector<u_int8_t> headerFormatRevision3 = {0x31, 0x19, 0xCE, 0x2F, 0xE8, 0x0A, 0x4A, 0x99,
                                                     0xAF, 0x6D, 0x46, 0xF8, 0xB1, 0x21, 0xF6, 0xBF};

const std::map<std::uint8_t, std::vector<u_int8_t>> PACKAGE_HEADER_FORMAT_REVISION_MAP = {
  {0x1, headerFormatRevision1},
  {0x3, headerFormatRevision3},
};

std::string NumToStr(u_int32_t num);
int ToInt(ComponentIdentifier value);
bool ValidSizeAndFormat(const std::string& number, const u_int8_t size);
bool readFromFile(const std::string& fname, std::string& content);
bool WriteToFile(const std::string& fname, const std::string& content);
bool WriteToFile(const std::string& fname, const std::vector<u_int8_t>& buff);

void dumpUInt8(std::vector<u_int8_t>& buff, u_int8_t val);
void dumpUInt16(std::vector<u_int8_t>& buff, u_int16_t val);
void dumpUInt32(std::vector<u_int8_t>& buff, u_int32_t val);
void dumpString(std::vector<u_int8_t>& buff, const std::string& str);
void dumpBytesArray(std::vector<u_int8_t>& buff, const u_int8_t* arr, unsigned int len);
std::string GetComponentNames();
void strToArry(const std::string& number,
               const std::string& fieldName,
               std::vector<u_int8_t>& value,
               u_int32_t maxSize = 0);
std::string createTempFile();
std::string GetStringFromJson(const Json::Value& root, const char* key, const char* defaultValue = nullptr);
void StringToComponentIdentifier(const std::string& componentIdentifierStr, ComponentIdentifier& componentIdentifier);
void ComponentIdentifierToStringValue(ComponentIdentifier componentIdentifier, ComponentField field, std::string& value);
void ComponentIdentifierToValue(ComponentIdentifier componentIdentifier, ComponentField field, u_int16_t& value);
bool isNicFwComponent(ComponentIdentifier componentIdentifier);
bool isValidComponent(ComponentIdentifier componentIdentifier);
std::string ToLower(const std::string& str);
std::string ValidAndNormalizeComponentIdentifier(const std::string& identifier);

class PLDMException
{
public:
    std::string _err;
    PLDMException(const char* fmt, ...);
    ~PLDMException(){};
};
#endif /* PLDM_UTILS_H_ */
