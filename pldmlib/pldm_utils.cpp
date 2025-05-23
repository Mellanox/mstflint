/*
 * SPDX-FileCopyrightText: Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <string>

#include "pldm_utils.h"

#define VECTOR_POS_FW 0
#define VECTOR_POS_NIC_FW 1
#define VECTOR_POS_ARM_Capsule 2
#define VECTOR_POS_BF3BMC_PLDM 3
#define VECTOR_POS_BFB 4
#define VECTOR_POS_BF3BMC_CEC_PLDM 5

using namespace std;

const std::vector<std::tuple<std::string, ComponentIdentifier, uint16_t, uint16_t, uint16_t>> components_list = {
  {make_tuple("FW",
              ComponentIdentifier::Identifier_FW_Comp,
              COMPONENT_CLASSIFICATION_VALUE_SW_BUNDLE,
              REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT,
              COMPONENT_OPTIONS_VALUE_FW)},
  {make_tuple("NIC_FW",
              ComponentIdentifier::Identifier_NIC_FW_Comp,
              COMPONENT_CLASSIFICATION_VALUE_FW,
              REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT,
              COMPONENT_OPTIONS_VALUE_DEFAULT)},
  {make_tuple("ARM_Capsule",
              ComponentIdentifier::Identifier_ARM_Capsule_Comp,
              COMPONENT_CLASSIFICATION_VALUE_SW_BUNDLE,
              REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT,
              COMPONENT_OPTIONS_VALUE_DEFAULT)},
  {make_tuple("BF3BMC_PLDM",
              ComponentIdentifier::Identifier_BF3BMC_PLDM_Comp,
              COMPONENT_CLASSIFICATION_VALUE_FW,
              REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT,
              COMPONENT_OPTIONS_VALUE_DEFAULT)},
  {make_tuple("BFB",
              ComponentIdentifier::Identifier_BFB_Comp,
              COMPONENT_CLASSIFICATION_VALUE_SW_BUNDLE,
              REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT,
              COMPONENT_OPTIONS_VALUE_DEFAULT)},
  {make_tuple("BF3BMC_CEC_PLDM",
              ComponentIdentifier::Identifier_BF3BMC_CEC_PLDM_Comp,
              COMPONENT_CLASSIFICATION_VALUE_FW,
              REQUESTED_COMPONENT_ACTIVATION_MODE_VALUE_DEFAULT,
              COMPONENT_OPTIONS_VALUE_DEFAULT)}};

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

void StringToComponentIdentifier(string componentIdentifierStr, ComponentIdentifier& componentIdentifier)
{
    for (const auto& component : components_list)
    {
        if (get<COMPONENT_NAME>(component) == componentIdentifierStr)
        {
            componentIdentifier = get<COMPONENT_IDENTIFIER>(component);
            return;
        }
    }
    throw PLDMException("Component type \"%s\" is not valid.\n", componentIdentifierStr.c_str());
}

void ComponentIdentifierToStringValue(ComponentIdentifier componentIdentifier, u_int16_t field, string& value)
{
    for (const auto& component : components_list)
    {
        if (get<COMPONENT_IDENTIFIER>(component) == componentIdentifier)
        {
            switch (field)
            {
                case COMPONENT_NAME:
                    value = get<COMPONENT_NAME>(component);
                    break;
                default:
                    throw PLDMException("Component field \"%d\" is not valid.\n", field);
            }
            break;
        }
    }
}

void ComponentIdentifierToValue(ComponentIdentifier componentIdentifier, u_int16_t field, u_int16_t& value)
{
    for (const auto& component : components_list)
    {
        if (get<COMPONENT_IDENTIFIER>(component) == componentIdentifier)
        {
            switch (field)
            {
                case COMPONENT_IDENTIFIER:
                    value = ToInt(get<COMPONENT_IDENTIFIER>(component));
                    break;
                case COMPONENT_CLASSIFICATION:
                    value = get<COMPONENT_CLASSIFICATION>(component);
                    break;
                case COMPONENT_ACTIVATION_METHOD:
                    value = get<COMPONENT_ACTIVATION_METHOD>(component);
                    break;
                case COMPONENT_OPTIONS:
                    value = get<COMPONENT_OPTIONS>(component);
                    break;
                default:
                    throw PLDMException("Component field \"%d\" is not valid.\n", field);
            }
            break;
        }
    }
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
