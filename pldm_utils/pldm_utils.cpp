/*
 * SPDX-FileCopyrightText: Copyright (c) 2013-2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
 * SPDX-License-Identifier: LicenseRef-NvidiaProprietary
 *
 * NVIDIA CORPORATION, its affiliates and licensors retain all intellectual
 * property and proprietary rights in and to this material, related
 * documentation and any modifications thereto. Any use, reproduction,
 * disclosure or distribution of this material and related documentation
 * without an express license agreement from NVIDIA CORPORATION or
 * its affiliates is strictly prohibited.
 */

#include <sys/time.h>
#include <unistd.h>
#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>

#include "pldm_utils.h"

using namespace std;
// If a new component is added, update the Confluence page as well:
// https://nvidia.atlassian.net/wiki/spaces/SW/pages/3064486398/PLDM+fwpkg+Generation
vector<string> components_names = {"FW",      "NIC_FW", "ARM_Capsule",  "BF3BMC_PLDM",  "BFB", "BF3BMC_CEC_PLDM",
                                   "FW_SPC6", "VMOD",   "OEM_NVCONFIG", "MLNX_NVCONFIG"};

struct ComponentInfo
{
    string name;
    ComponentIdentifier identifier;
    ComponentClassification classification;
    u_int16_t activationMethod;
    u_int16_t options;
};

const std::vector<ComponentInfo> components_list = {
  {"FW", ComponentIdentifier::Identifier_FW_Comp, ComponentClassification::SwBundle,
   REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT, COMPONENT_OPTIONS_VALUE_FW},
  {"NIC_FW", ComponentIdentifier::Identifier_NIC_FW_Comp, ComponentClassification::Firmware,
   REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT, COMPONENT_OPTIONS_VALUE_DEFAULT},
  {"ARM_Capsule", ComponentIdentifier::Identifier_ARM_Capsule_Comp, ComponentClassification::SwBundle,
   REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT, COMPONENT_OPTIONS_VALUE_DEFAULT},
  {"BF3BMC_PLDM", ComponentIdentifier::Identifier_BF3BMC_PLDM_Comp, ComponentClassification::Firmware,
   REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT, COMPONENT_OPTIONS_VALUE_DEFAULT},
  {"BFB", ComponentIdentifier::Identifier_BFB_Comp, ComponentClassification::SwBundle,
   REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT, COMPONENT_OPTIONS_VALUE_DEFAULT},
  {"BF3BMC_CEC_PLDM", ComponentIdentifier::Identifier_BF3BMC_CEC_PLDM_Comp, ComponentClassification::Firmware,
   REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT, COMPONENT_OPTIONS_VALUE_DEFAULT},
  {"FW_SPC6", ComponentIdentifier::Identifier_FW_SPC6_Comp, ComponentClassification::Firmware,
   REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT, COMPONENT_OPTIONS_VALUE_DEFAULT},
  {"VMOD", ComponentIdentifier::Identifier_VMOD_Comp, ComponentClassification::Firmware,
   REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT, COMPONENT_OPTIONS_VALUE_DEFAULT},
  {"OEM_NVCONFIG", ComponentIdentifier::Identifier_OEM_NVCONFIG_Comp, ComponentClassification::Configuration,
   REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT, COMPONENT_OPTIONS_VALUE_DEFAULT},
  {"MLNX_NVCONFIG", ComponentIdentifier::Identifier_MLNX_NVCONFIG_Comp, ComponentClassification::Configuration,
   REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT, COMPONENT_OPTIONS_VALUE_DEFAULT}};

string NumToStr(u_int32_t num)
{
    stringstream ss;
    ss << num;
    return ss.str();
}

int ToInt(ComponentIdentifier value)
{
    return static_cast<int>(value);
}

bool ValidSizeAndFormat(const string& number, const u_int8_t size)
{
    string hexNumber = number;
    if (hexNumber.size() >= 2 && (hexNumber[0] == '0') && (tolower(hexNumber[1]) == 'x'))
    {
        hexNumber = hexNumber.substr(2);
    }
    if (hexNumber.size() % 2 != 0 && hexNumber != "0")
    {
        throw PLDMException("Invalid %s hexadecimal format.\n", hexNumber.c_str());
    }
    return hexNumber.size() / 2 <= size &&
           std::all_of(hexNumber.begin(), hexNumber.end(), [](unsigned char cha) { return std::isxdigit(cha); });
}

void strToArry(const string& number, const string& fieldName, vector<u_int8_t>& value, u_int32_t maxSize)
{
    string hexNumber = number;

    // Remove "0x" or "0X" prefix if present
    if (hexNumber.size() >= 2 && (hexNumber[0] == '0') && (tolower(hexNumber[1]) == 'x'))
    {
        hexNumber = hexNumber.substr(2);
    }

    for (size_t i = 0; i < hexNumber.length(); i += 2)
    {
        u_int8_t byte;
        try
        {
            byte = static_cast<u_int8_t>(stoi(hexNumber.substr(i, 2), nullptr, 16));
        }
        catch (...)
        {
            throw PLDMException("Invalid value for %s. It must to be hex format.\n", fieldName.c_str());
        }
        value.push_back(byte);
    }

    if (value.size() > maxSize)
    {
        throw PLDMException("%s must be %d bytes at most.", fieldName.c_str(), maxSize);
    }
    int paddingSize = maxSize - value.size();
    value.insert(value.begin(), paddingSize, 0x00);
}

bool WriteToFile(const string& fname, const string& content)
{
    FILE* file = fopen(fname.c_str(), "wb");
    if (!file)
    {
        return false;
    }
    fprintf(file, "%s", content.c_str());
    fclose(file);
    return true;
}

bool WriteToFile(const string& fname, const vector<u_int8_t>& data)
{
    FILE* fh;

    if ((fh = fopen(fname.c_str(), "wb")) == NULL)
    {
        return false;
    }

    // Write output
    if (fwrite(data.data(), 1, data.size(), fh) != data.size())
    {
        fclose(fh);
        return false;
    }

    fclose(fh);

    return true;
}

bool readFromFile(const string& fname, string& content)
{
    std::ifstream ifs(fname.c_str());
    if (!ifs.good())
    {
        throw PLDMException("The provided cookbook file cannot be accessed.");
    }
    for (std::string line; std::getline(ifs, line);)
    {
        content += line;
    }
    ifs.close();
    return true;
}

void dumpUInt8(vector<u_int8_t>& buff, u_int8_t val)
{
    buff.push_back(val);
}

void dumpUInt16(vector<u_int8_t>& buff, u_int16_t val)
{
    val = __cpu_to_le16(val);
    buff.push_back(((u_int8_t*)&val)[0]);
    buff.push_back(((u_int8_t*)&val)[1]);
}

void dumpUInt32(vector<u_int8_t>& buff, u_int32_t val)
{
    val = __cpu_to_le32(val);
    buff.push_back(((u_int8_t*)&val)[0]);
    buff.push_back(((u_int8_t*)&val)[1]);
    buff.push_back(((u_int8_t*)&val)[2]);
    buff.push_back(((u_int8_t*)&val)[3]);
}

void dumpString(vector<u_int8_t>& buff, const string& str)
{
    for (unsigned int i = 0; i < str.length(); i++)
    {
        buff.push_back(str[i]);
    }
}

void dumpBytesArray(vector<u_int8_t>& buff, const u_int8_t* arr, unsigned int len)
{
    for (unsigned int i = 0; i < len; i++)
    {
        buff.push_back(arr[i]);
    }
}

string createTempFile()
{
    char templateStr[] = "/tmp/tmpfileXXXXXX";
    int fd = mkstemp(templateStr);
    if (fd == -1)
    {
        throw PLDMException("Failed generating tmp file name.");
    }
    close(fd);
    return string(templateStr);
}

string GetStringFromJson(const Json::Value& root, const char* key, const char* defaultValue)
{
    if (!root.isObject())
    {
        throw PLDMException("Expected JSON object format.");
    }

    Json::Value value = root[key];
    if (value.isNull())
    {
        if (defaultValue != nullptr)
        {
            return defaultValue;
        }
        throw PLDMException("The key \"%s\" is not found in the JSON.", key);
    }
    return value.asString();
}

void StringToComponentIdentifier(const string& componentIdentifierStr, ComponentIdentifier& componentIdentifier)
{
    for (const auto& component : components_list)
    {
        if (component.name == componentIdentifierStr)
        {
            componentIdentifier = component.identifier;
            return;
        }
    }
    throw PLDMException("Component type \"%s\" is not valid.\n", componentIdentifierStr.c_str());
}

void ComponentIdentifierToStringValue(ComponentIdentifier componentIdentifier, ComponentField field, string& value)
{
    for (const auto& component : components_list)
    {
        if (component.identifier == componentIdentifier)
        {
            switch (field)
            {
                case ComponentField::Name:
                    value = component.name;
                    break;
                default:
                    throw PLDMException("Component field \"%d\" is not valid.\n", static_cast<int>(field));
            }
            break;
        }
    }
}

void ComponentIdentifierToValue(ComponentIdentifier componentIdentifier, ComponentField field, u_int16_t& value)
{
    for (const auto& component : components_list)
    {
        if (component.identifier == componentIdentifier)
        {
            switch (field)
            {
                case ComponentField::Identifier:
                    value = static_cast<u_int16_t>(component.identifier);
                    break;
                case ComponentField::Classification:
                    value = static_cast<u_int16_t>(component.classification);
                    break;
                case ComponentField::ActivationMethod:
                    value = component.activationMethod;
                    break;
                case ComponentField::Options:
                    value = component.options;
                    break;
                default:
                    throw PLDMException("Component field \"%d\" is not valid.\n", static_cast<int>(field));
            }
            break;
        }
    }
}

string GetComponentNames()
{
    // Skip the first element (FW) - it is legacy component
    size_t componentPos = 1;
    string components = components_list[componentPos++].name;
    for (; componentPos < components_list.size(); componentPos++)
    {
        components += "," + components_list[componentPos].name;
    }
    return components;
}

bool isNicFwComponent(ComponentIdentifier componentIdentifier)
{
    return ((componentIdentifier == ComponentIdentifier::Identifier_FW_Comp ||
             componentIdentifier == ComponentIdentifier::Identifier_NIC_FW_Comp));
}

bool isValidComponent(ComponentIdentifier componentIdentifier)
{
    return componentIdentifier != ComponentIdentifier::Identifier_Not_Valid;
}

PLDMException::PLDMException(const char* fmt, ...)
{
    char tmp[1024];
    va_list args;

    va_start(args, fmt);
    vsprintf(tmp, fmt, args);
    va_end(args);
    _err = tmp;
}

// ********************************************************
// functions for new Parser
// ********************************************************

std::string ValidAndNormalizeComponentIdentifier(const string& identifier)
{
    for (const auto& component : components_names)
    {
        if (ToLower(component) == ToLower(identifier))
        {
            return component;
        }
    }
    throw PLDMException("Invalid component: %s", identifier.c_str());
}

std::string ToLower(const std::string& str)
{
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

u_int32_t pldm_crc32(const u_int8_t* data, size_t len)
{
    u_int32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (int j = 0; j < 8; j++)
        {
            u_int32_t mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
        }
    }
    return ~crc;
}
