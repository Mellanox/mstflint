/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#define VERSION_STRING_TYPE_ASCII 0x1

#define COMPONENT_NAME 0
#define COMPONENT_IDENTIFIER 1
#define COMPONENT_CLASSIFICATION 2
#define COMPONENT_ACTIVATION_METHOD 3
#define COMPONENT_OPTIONS 4

#define COMPONENT_CLASSIFICATION_VALUE_SW_BUNDLE 0xD
#define COMPONENT_CLASSIFICATION_VALUE_FW 0XA

#define COMPONENT_COMPARISON_STAMP_VALUE 0xffffffff

#define COMPONENT_OPTIONS_VALUE_FW 0x1
#define COMPONENT_OPTIONS_VALUE_DEFAULT 0x0000

#define REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT 0x0038
#define DEV_ID_TYPE 0x100

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
    Identifier_NIC_FW_Comp = 0x3001,
    Identifier_BF3BMC_PLDM_Comp = 0x3010,
    Identifier_BF3BMC_CEC_PLDM_Comp = 0x3018,
    Identifier_ARM_Capsule_Comp = 0x3020,
    Identifier_BFB_Comp = 0x3030,
    Identifier_General = 0xffff
};

std::string NumToStr(u_int32_t num);
int ToInt(ComponentIdentifier value);
void StringToComponentIdentifier(std::string componentIdentifierStr, ComponentIdentifier& componentIdentifier);
void ComponentIdentifierToStringValue(ComponentIdentifier componentIdentifier, u_int16_t field, std::string& value);
void ComponentIdentifierToValue(ComponentIdentifier componentIdentifier, u_int16_t field, u_int16_t& value);
bool isNicFwComponent(ComponentIdentifier componentIdentifier);
bool isValidComponent(ComponentIdentifier componentIdentifier);
const u_int8_t expectedHeaderIdentifier[16] = {0xf0, 0x18, 0x87, 0x8c, 0xcb, 0x7d, 0x49, 0x43,
                                               0x98, 0x00, 0xa0, 0x2f, 0x05, 0x9a, 0xca, 0x02};

class PLDMException
{
public:
    std::string _err;
    PLDMException(const char* fmt, ...);
    ~PLDMException(){};
};
#endif /* PLDM_UTILS_H_ */
