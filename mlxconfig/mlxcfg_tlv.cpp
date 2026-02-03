/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *
 * mlxcfg_tlv.cpp
 *
 *  Created on: May 24, 2016
 *      Author: ahmads
 */

#include <sstream>
#include <signal.h>
#include <stdio.h>
#include <iomanip>
#include <algorithm>

#include <compatibility.h>
#include <mlxcfg_db_manager.h>
#include <tools_layouts/tools_open_layouts.h>
#include <tools_layouts/reg_access_hca_layouts.h>
#include <mft_utils.h>
#include "mlxcfg_tlv.h"

#include <muParser.h>

using namespace mu;
using namespace std;

#define TLV_NAME_HEADER "name"
#define TLV_ID_HEADER "id"
#define TLV_CAP_HEADER "cap"
#define TLV_TARGET_HEADER "target"
#define TLV_CLASS_HEADER "class"
#define TLV_VERSION_HEADER "version"
#define TLV_SIZE_HEADER "size"
#define TLV_DESCRIPTION_HEADER "description"
#define TLV_MLXCONFIG_NAME_HEADER "mlxconfig_name"
#define CHECK_IF_FIELD_FOUND(b, s)                                            \
    if (!b)                                                                   \
    {                                                                         \
        throw MlxcfgException("The TLVConf field %s was not initialized", s); \
    }

TLVConf::TLVConf(int columnsCount, char** dataRow, char** headerRow) :
    _isNameFound(false),
    _isIdFound(false),
    _isSizeFound(false),
    _isCapFound(false),
    _isTargetFound(false),
    _isClassFound(false),
    _isVersion(false),
    _isDescriptionFound(false),
    _isMlxconfigNameFound(false),
    _paramsDefaultQueried(false),
    _paramsCurrentQueried(false),
    _paramsNextQueried(false),
    _port(0),
    _module(-1),
    _hostId(0),
    _pfIndex(0),
    _isHostIdValid(false),
    _maxTlvVersionSuppByFw(0)
{
    for (int i = 0; i < columnsCount; i++)
    {
        if (strcmp(headerRow[i], TLV_NAME_HEADER) == 0)
        {
            _name = dataRow[i];
            _isNameFound = true;
        }
        else if (strcmp(headerRow[i], TLV_ID_HEADER) == 0)
        {
            _id = atoi(dataRow[i]);
            _isIdFound = true;
        }
        else if (strcmp(headerRow[i], TLV_CAP_HEADER) == 0)
        {
            if (dataRow[i] == NULL)
            {
                _cap = false;
            }
            else
            {
                _cap = atoi(dataRow[i]);
            }
            _isCapFound = true;
        }
        else if (strcmp(headerRow[i], TLV_TARGET_HEADER) == 0)
        {
            _target = str2TLVTarget(dataRow[i]);
            _isTargetFound = true;
        }
        else if (strcmp(headerRow[i], TLV_CLASS_HEADER) == 0)
        {
            _tlvClass = str2TLVClass(dataRow[i]);
            _isClassFound = true;
        }
        else if (strcmp(headerRow[i], TLV_VERSION_HEADER) == 0)
        {
            _version = atoi(dataRow[i]);
            _isVersion = true;
        }
        else if (strcmp(headerRow[i], TLV_SIZE_HEADER) == 0)
        {
            _size = atoi(dataRow[i]);
            _isSizeFound = true;
        }
        else if (strcmp(headerRow[i], TLV_DESCRIPTION_HEADER) == 0)
        {
            _description = dataRow[i] ? dataRow[i] : "";
            _isDescriptionFound = true;
        }
        else if (strcmp(headerRow[i], TLV_MLXCONFIG_NAME_HEADER) == 0)
        {
            _mlxconfigName = dataRow[i] ? dataRow[i] : "";
            _isMlxconfigNameFound = true;
        }
        else
        {
            printf("UNKNOWN - %s = %s\n", headerRow[i], dataRow[i] ? dataRow[i] : "NULL");
        }
    }

    CHECK_IF_FIELD_FOUND(_isNameFound, TLV_NAME_HEADER)
    CHECK_IF_FIELD_FOUND(_isIdFound, TLV_ID_HEADER)
    CHECK_IF_FIELD_FOUND(_isCapFound, TLV_CAP_HEADER)
    CHECK_IF_FIELD_FOUND(_isTargetFound, TLV_TARGET_HEADER)
    CHECK_IF_FIELD_FOUND(_isClassFound, TLV_CLASS_HEADER)
    CHECK_IF_FIELD_FOUND(_isVersion, TLV_VERSION_HEADER)
    CHECK_IF_FIELD_FOUND(_isSizeFound, TLV_SIZE_HEADER)
    CHECK_IF_FIELD_FOUND(_isDescriptionFound, TLV_DESCRIPTION_HEADER)
    CHECK_IF_FIELD_FOUND(_isMlxconfigNameFound, TLV_MLXCONFIG_NAME_HEADER)

    _alreadyQueried = false;
    if (_tlvClass == Physical_Port)
    {
        _attrs[PORT_ATTR] = "1";
    }
    if (_tlvClass == Module)
    {
        _attrs[MODULE_ATTR] = "0";
    }
    else if (_tlvClass == Per_Host_Per_Function)
    {
        _attrs[FUNC_ATTR] = "0";
        _attrs[HOST_ATTR] = "0";
    }
    _attrs[WRITER_ID_ATTR] = numToStr(WRITER_ID_UNSPECIFIED);
    _attrs[OVR_EN_ATTR] = "1";
    _attrs[RD_EN_ATTR] = "1";
    _attrs[PRIORITY_ATTR] = "MLNX";

    _buff.resize(_size, 0);

    _isReadOnly = false;
}

int TLVConf::getMaxPort(mfile* mf)
{
    static int maxPort = 0;
    if (maxPort == 0)
    {
        reg_access_status_t rc;
        struct reg_access_hca_mgir_ext mgir;
        memset(&mgir, 0, sizeof(mgir));
        rc = reg_access_mgir(mf, REG_ACCESS_METHOD_GET, &mgir);
        if (rc == ME_OK)
        {
            maxPort = mgir.hw_info.num_ports;
        }
        else
        {
            maxPort = 8;
        }
    }
    return maxPort;
}

int TLVConf::getMaxModule()
{
    /*TODO adding implementation of mst device class*/
    return 1;
}

TLVConf::~TLVConf() {}

std::shared_ptr<TLVConf> TLVConf::cloneDeep() const
{
    auto copy = std::make_shared<TLVConf>(*this);

    // Deep clone parameter vectors
    copy->_paramsDefault.clear();
    copy->_paramsCurrent.clear();
    copy->_paramsNext.clear();

    for (const auto& p : _paramsDefault)
    {
        if (p)
        {
            copy->_paramsDefault.push_back(p->cloneDeep());
        }
    }
    for (const auto& p : _paramsCurrent)
    {
        if (p)
        {
            copy->_paramsCurrent.push_back(p->cloneDeep());
        }
    }
    for (const auto& p : _paramsNext)
    {
        if (p)
        {
            copy->_paramsNext.push_back(p->cloneDeep());
        }
    }

    return copy;
}

void TLVConf::CheckModuleAndPortMatchClass(int32_t tlvModule, u_int32_t port, string mlxconfigName)
{
    if ((tlvModule != -1) && !this->isModuleTargetClass())
    {
        string error = mlxconfigName + " doesn't have a module";
        throw MlxcfgException(error.c_str());
    }
    else if ((tlvModule == -1) && this->isModuleTargetClass())
    {
        string error = mlxconfigName + " with no module does not exist";
        throw MlxcfgException(error.c_str());
    }

    if ((port != 0) && !this->isPortTargetClass())
    {
        string error = mlxconfigName + " doesn't have a physical port";
        throw MlxcfgException(error.c_str());
    }
    else if ((port == 0) && this->isPortTargetClass())
    {
        string error = mlxconfigName + " with no port does not exist";
        throw MlxcfgException(error.c_str());
    }
}

void TLVConf::getView(TLVConfView& tlvConfView, QueryType qt)
{
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);

    tlvConfView.name = _mlxconfigName;
    tlvConfView.description = _description;
    tlvConfView.tlvClass = _tlvClass;
    for (size_t j = 0; j < params->size(); j++)
    {
        if (!(*params)[j]->_mlxconfigName.empty())
        {
            ParamView paramView;
            (*params)[j]->getView(paramView);
            tlvConfView.params.push_back(paramView);
        }
    }
}

// This function checks if the mlxconfig tool should support this TLV
bool TLVConf::isMlxconfigSupported()
{
    for (size_t i = 0; i < _paramsNext.size(); i++)
    {
        if (_paramsNext[i]->_mlxconfigName.empty() == false)
        {
            return true;
        }
    }
    return false;
}

// This function checks if the FW knows the TLV.
bool TLVConf::isFWSupported(mfile* mf, bool isWriteOperation)
{
    bool suppRead = false, suppWrite = false;
    // printf("-D- tlv=%s\n", _name.c_str());

    if (nvqcCom5thGen(mf, getTlvTypeBe(), suppRead, suppWrite, _maxTlvVersionSuppByFw))
    {
        // Don't throw exception if we fail to run nvqc, maybe its an old fw
        return false;
    }
    // EXP_ROM TLVs are SW2SW TLVs always have support read/write and
    // FW only support to return EXP_ROM TLV version through NVQC register
    if (_target != EXP_ROM)
    {
        if (suppRead && !suppWrite)
        {
            _isReadOnly = true;
        }
        if (!suppRead)
        {
            return false;
        }

        if (isWriteOperation && !suppWrite)
        {
            return false;
        }
    }
    return true;
}

void TLVConf::unpack(u_int8_t* buff, QueryType qt)
{
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);
    for (vector<std::shared_ptr<Param>>::iterator p = params->begin(); p != params->end(); ++p)
    {
        (*p)->unpack(buff);
    }
}

void TLVConf::pack(u_int8_t* buff, QueryType qt)
{
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);
    for (vector<std::shared_ptr<Param>>::iterator p = params->begin(); p != params->end(); ++p)
    {
        (*p)->pack(buff);
    }
}

void TLVConf::invalidate(mfile* mf)
{
    MError mRc = nvdiCom5thGen(mf, getTlvTypeBe(), _isHostIdValid);
    if (mRc)
    {
        throw MlxcfgException("Failed to reset %s settings %s", _name.c_str(), m_err2str(mRc));
    }
}

u_int32_t TLVConf::getGlobalTypeBe()
{
    struct tools_open_global_type type;
    u_int32_t tlvType = 0;

    type.param_class = (u_int8_t)_tlvClass;
    type.param_idx = _id;
    tools_open_global_type_pack(&type, (u_int8_t*)&tlvType);

    return tlvType;
}

u_int32_t TLVConf::getPhysicalPortTypeBe()
{
    struct tools_open_per_port_type type;
    u_int32_t tlvType = 0;

    if (_attrs[PORT_ATTR] == ALL_ATTR_VAL)
    {
        type.param_class = Physical_Port_Common;
        type.port = 0; // port field is reserved
    }
    else
    {
        type.param_class = Physical_Port;
        type.port = _port;
    }
    type.param_idx = _id;

    tools_open_per_port_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

u_int32_t TLVConf::getModuleTypeBe()
{
    struct tools_open_configuration_item_type_class_module type;
    u_int32_t tlvType = 0;
    type.type_class = Module;
    type.module_index = _module;
    type.parameter_index = _id;
    tools_open_configuration_item_type_class_module_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

u_int32_t TLVConf::getPerHostTypeBe()
{
    u_int32_t tlvType = 0;
    struct tools_open_host_type type;

    memset(&type, 0x0, sizeof(type));
    type.param_class = (u_int8_t)_tlvClass;
    type.param_idx = _id;
    tools_open_host_type_pack(&type, (u_int8_t*)&tlvType);

    return tlvType;
}

u_int32_t TLVConf::getPerHostFunctionTypeBe()
{
    struct tools_open_per_host_type type;
    u_int32_t tlvType = 0, num = 0;
    string host = _attrs[HOST_ATTR], func = _attrs[FUNC_ATTR];

    memset(&type, 0, sizeof(struct tools_open_per_host_type));
    // user request specific host / pf
    if (_hostId != 0 || _pfIndex != 0)
    {
        type.param_class = Per_Host_Per_Function;
        type.host = _hostId;
        type.function = _pfIndex;
    }
    else
    {
        if ((host == ALL_ATTR_VAL) && (func == ALL_ATTR_VAL))
        {
            type.param_class = All_Hosts_All_Functions;
            type.function = 0;
            type.host = 0;
        }
        else if ((host == ALL_ATTR_VAL) && (func != ALL_ATTR_VAL))
        {
            type.param_class = All_Hosts_Per_Function;
            type.host = 0;
            if (!strToNum(_attrs[FUNC_ATTR], num))
            {
                throw MlxcfgException(FUNC_ATTR " attribute value %s is not valid", func.c_str());
            }
            type.function = num;
        }
        else if ((host != ALL_ATTR_VAL) && (func == ALL_ATTR_VAL))
        {
            type.param_class = Per_Host_All_Functions;
            type.function = 0;
            if (!strToNum(_attrs[HOST_ATTR], num))
            {
                throw MlxcfgException(HOST_ATTR " attribute value %s is not valid", host.c_str());
            }
            type.host = num;
        }
        else if ((host != ALL_ATTR_VAL) && (func != ALL_ATTR_VAL))
        {
            type.param_class = Per_Host_Per_Function;
            if (!strToNum(_attrs[HOST_ATTR], num))
            {
                throw MlxcfgException(HOST_ATTR " attribute value %s is not valid", host.c_str());
            }
            type.host = num;
            if (!strToNum(_attrs[FUNC_ATTR], num))
            {
                throw MlxcfgException(FUNC_ATTR " attribute value %s is not valid", func.c_str());
            }
            type.function = num;
        }
    }

    type.param_idx = _id;
    tools_open_per_host_type_pack(&type, (u_int8_t*)&tlvType);
    return tlvType;
}

u_int32_t TLVConf::getTlvTypeBe()
{
    switch (_tlvClass)
    {
        case Switch_Global:
        case NVFile:
        case Global:
            return getGlobalTypeBe();

        case Physical_Port_Common:
        case Physical_Port:
            return getPhysicalPortTypeBe();

        case All_Hosts_All_Functions:
        case All_Hosts_Per_Function:
        case Per_Host_All_Functions:
        case Per_Host_Per_Function:
            return getPerHostFunctionTypeBe();

        case Per_Host:
            return getPerHostTypeBe();

        case Module:
            return getModuleTypeBe();

        default:
            break;
    }
    throw MlxcfgException("The tlv %s has unknown class %d", _name.c_str(), _tlvClass);
}

std::shared_ptr<Param> TLVConf::getValidBitParam(string n, QueryType qt)
{
    std::shared_ptr<Param> vP = getParamByName(n, qt);
    if (!vP)
    {
        throw MlxcfgException("The valid bit %s in the tlv %s was not found\n", n.c_str(), _name.c_str());
    }
    if ((vP->_type != UNSIGNED) && (vP->_type != INTEGER) && (vP->_type != ENUM) && (vP->_type != BOOLEAN_TYPE))
    {
        throw MlxcfgException("The valid bit %s is of invalid type", n.c_str());
    }
    return vP;
}

bool TLVConf::checkParamValidBit(std::shared_ptr<Param> p, QueryType qt)
{
    if (!p->_validBit.empty())
    {
        std::shared_ptr<Param> vP = getValidBitParam(p->_validBit, qt);
        if (!vP->_value)
        {
            return false;
        }
    }
    return true;
}

bool TLVConf::mnvda(mfile* mf, u_int8_t* buff, u_int16_t len, u_int32_t type, reg_access_method_t method, QueryType qT)
{
    bool isSet = (method == REG_ACCESS_METHOD_SET);
    MError mRc = mnvaCom5thGen(mf, buff, len, type, method, qT, _isHostIdValid);
    if (mRc)
    {
        // Todo: ask for this check:
        if ((mRc != ME_REG_ACCESS_RES_NOT_AVLBL) || isSet)
        {
            throw MlxcfgException("Failed to %s %s settings %s (%d)", isSet ? "set" : "get", _name.c_str(),
                                  m_err2str(mRc), mRc);
        }
        return false;
    }
    return true;
}

void TLVConf::invalidateParamsQueried()
{
    _paramsDefaultQueried = false;
    _paramsCurrentQueried = false;
    _paramsNextQueried = false;
}

bool* TLVConf::getParamsQueried(QueryType qt)
{
    if (qt == QueryDefault)
    {
        return &_paramsDefaultQueried;
    }
    else if (qt == QueryCurrent)
    {
        return &_paramsCurrentQueried;
    }
    else if (qt == QueryNext)
    {
        return &_paramsNextQueried;
    }
    else
    {
        throw MlxcfgException("Invalid query type");
    }
}

std::vector<std::shared_ptr<Param>>* TLVConf::getParams(QueryType qt)
{
    if (qt == QueryDefault)
    {
        return &_paramsDefault;
    }
    else if (qt == QueryCurrent)
    {
        return &_paramsCurrent;
    }
    else if (qt == QueryNext)
    {
        return &_paramsNext;
    }
    else
    {
        throw MlxcfgException("Invalid query type");
    }
}

void TLVConf::parseParamValue(string paramMlxconfigName,
                              string valToParse,
                              u_int32_t& val,
                              string& strVal,
                              u_int32_t index,
                              QueryType qt)
{
    std::shared_ptr<Param> p = NULL;
    p = findParamByMlxconfigName(paramMlxconfigName, qt);

    // not sure we should reach below code
    if (!p)
    {
        p = findParamByMlxconfigName(getConfigNameWithSuffixByInterval(paramMlxconfigName, index), qt);
    }

    if (!p)
    {
        throw MlxcfgException("Unknown Parameter %s", paramMlxconfigName.c_str());
    }
    p->_value->parseValue(valToParse, val, strVal);
}

vector<pair<ParamView, string>> TLVConf::query(mfile* mf, QueryType qT)
{
    vector<pair<ParamView, string>> queryResult;
    vector<u_int8_t> defaultBuff(_size, 0);
    vector<u_int8_t> emptyBuff(_size, 0);
    bool* queryBefore = getParamsQueried(qT);
    std::vector<std::shared_ptr<Param>>* params = getParams(qT);

    if (!*queryBefore)
    {
        std::fill(_buff.begin(), _buff.end(), 0);
        bool success = mnvda(mf, _buff.data(), _size, getTlvTypeBe(), REG_ACCESS_METHOD_GET, qT);
        *queryBefore = true;
        if (success)
        {
            unpack(_buff.data(), qT);
        }
        else
        {
            if (mlxcfg_is_debug_enabled())
            {
                printf("mnvda GET failed for %s settings emptyBuff\n", _name.c_str());
            }
            unpack(emptyBuff.data(), qT); // in case mnvda failed , unpack default empty buff
        }
    }

    for (std::vector<std::shared_ptr<Param>>::iterator it = params->begin(); it != params->end(); ++it)
    {
        ParamView paramView;
        std::shared_ptr<Param> p = *(it);
        if (!_paramsDefaultQueried && !checkParamValidBit(p, qT))
        { // then take default value
            bool success = mnvda(mf, defaultBuff.data(), _size, getTlvTypeBe(), REG_ACCESS_METHOD_GET, QueryDefault);
            _paramsDefaultQueried = true;
            if (success)
            {
                unpack(defaultBuff.data(), QueryDefault);
            }
            else
            {
                unpack(emptyBuff.data(), qT); // in case mnvda failed , unpack default empty buff
            }
        }
        if (p->_mlxconfigName.empty() || (p->_supportedFromVersion > _maxTlvVersionSuppByFw))
        {
            continue;
        }
        p->getView(paramView);
        queryResult.push_back(make_pair(paramView, p->_dependency));
    }

    return queryResult;
}

void TLVConf::updateParamByMlxconfigName(string paramMlxconfigName, string val, mfile* mf, QueryType qt)
{
    std::shared_ptr<Param> p = findParamByMlxconfigNamePortModule(paramMlxconfigName, this->_port, this->_module, qt);
    if (!p)
    {
        auto ret = MlxcfgDBManager::getMlxconfigNamePortModule(paramMlxconfigName, mf);
        p = findParamByMlxconfigNamePortModule(get<0>(ret), get<1>(ret), get<2>(ret), qt);
        if (!p)
        {
            throw MlxcfgException("Unknown parameter: %s", paramMlxconfigName.c_str());
        }
    }
    p->setVal(val);
    // check if there is a valid bit
    if (!p->_validBit.empty())
    {
        (getValidBitParam(p->_validBit, qt))->_value->setVal(1);
    }
}

void TLVConf::updateParamByMlxconfigName(string paramMlxconfigName, string val, u_int32_t index, QueryType qt)
{
    std::shared_ptr<Param> p = findParamByMlxconfigName(paramMlxconfigName, qt);

    if (!p)
    {
        p = findParamByMlxconfigName(getConfigNameWithSuffixByInterval(paramMlxconfigName, index), qt);
    }

    if (!p)
    {
        throw MlxcfgException("Unknown parameter: %s", paramMlxconfigName.c_str());
    }
    p->setVal(val, index % MAX_ARRAY_SIZE);
}

void TLVConf::updateParamByName(string paramName, string val, QueryType qt)
{
    std::shared_ptr<Param> p = NULL;
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);
    for (std::vector<std::shared_ptr<Param>>::iterator it = params->begin(); it != params->end(); ++it)
    {
        if (paramName == (*it)->_name)
        {
            p = *it;
            break;
        }
    }
    if (!p)
    {
        throw MlxcfgException("Unknown parameter %s of the configuration %s", paramName.c_str(), _name.c_str());
    }
    p->setVal(val);
    // check if there is a valid bit
    if (!p->_validBit.empty())
    {
        (getValidBitParam(p->_validBit, qt))->_value->setVal(1);
    }
}

void TLVConf::updateParamByName(string paramName, vector<string> vals, QueryType qt)
{
    std::shared_ptr<Param> p = NULL;
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);
    for (std::vector<std::shared_ptr<Param>>::iterator it = params->begin(); it != params->end(); ++it)
    {
        if (paramName == (*it)->_name)
        {
            p = *it;
            break;
        }
    }

    if (!p)
    {
        throw MlxcfgException("Unknown parameter %s of the configuration %s", paramName.c_str(), _name.c_str());
    }

    p->setVal(vals);
}

bool TLVConf::isAStringParam(string paramName)
{
    std::shared_ptr<Param> param = getParamByName(paramName, QueryDefault);
    if (!param)
    {
        throw MlxcfgException("Unknown parameter %s of the configuration %s", paramName.c_str(), _name.c_str());
    }
    return (param->_type == STRING);
}

TLVTarget TLVConf::str2TLVTarget(char* s)
{
    if (strcmp(s, "NIC") == 0)
    {
        return NIC;
    }
    else if (strcmp(s, "EXP_ROM") == 0)
    {
        return EXP_ROM;
    }
    else if (strcmp(s, "NIC-internal") == 0)
    {
        return NIC_INTERNAL;
    }
    else if (strcmp(s, "SWITCH") == 0)
    {
        return SWITCH;
    }
    throw MlxcfgException("Unknown target '%s'", s);
}

TLVClass TLVConf::str2TLVClass(char* s)
{
    int i = atoi(s);
    switch (i)
    {
        case 0:
            return Global;

        case 1:
            return Physical_Port;

        case 2:
            return BMC;

        case 3:
            return Per_Host_Per_Function;

        case 6:
            return NVFile;

        case 7:
            return Per_Host;

        case 8:
            return Switch_Global;

        case 9:
            return Module;
    }
    throw MlxcfgException("Unknown TLV class %d", i);
}

std::shared_ptr<Param> TLVConf::getParamByName(string name, QueryType qt)
{
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);
    for (std::vector<std::shared_ptr<Param>>::iterator it = params->begin(); it != params->end(); ++it)
    {
        std::shared_ptr<Param> p = (*it);
        if (name == p->_name)
        {
            return p;
        }
    }
    return NULL;
}

std::shared_ptr<Param> TLVConf::findParamByMlxconfigName(string mlxconfigname, QueryType qt)
{
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);
    for (std::vector<std::shared_ptr<Param>>::iterator it = params->begin(); it != params->end(); ++it)
    {
        if (mlxconfigname == (*it)->_mlxconfigName)
        {
            return *it;
        }
    }
    return NULL;
}

std::shared_ptr<Param>
  TLVConf::findParamByMlxconfigNamePortModule(string mlxconfigname, u_int32_t port, int32_t tlvModule, QueryType qt)
{
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);
    for (std::vector<std::shared_ptr<Param>>::iterator it = params->begin(); it != params->end(); ++it)
    {
        if ((mlxconfigname == (*it)->_mlxconfigName) && (port == (*it)->_port) && (tlvModule == (*it)->_module))
        {
            return *it;
        }
    }
    return NULL;
}

std::shared_ptr<Param> TLVConf::findParamByName(string name, QueryType qt)
{
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);
    for (std::vector<std::shared_ptr<Param>>::iterator it = params->begin(); it != params->end(); ++it)
    {
        if (name == (*it)->_name)
        {
            return *it;
        }
    }
    return NULL;
}

u_int32_t TLVConf::getParamValueByName(string n, QueryType qt)
{
    std::shared_ptr<Param> p = getParamByName(n, qt);
    if (!p)
    {
        throw MlxcfgException("The parameter %s was not found", n.c_str());
    }
    return p->_value->getIntVal();
}

void evalExpr(string expr, string var, u_int32_t& varVal, u_int32_t& exprResult)
{
    double x = 0;
    mu::Parser p;

    try
    {
        if (!var.empty())
        {
            p.DefineVar(var, &x);
        }
        p.SetExpr(expr);
        exprResult = (u_int32_t)p.Eval();
        varVal = (u_int32_t)x;
    }
    catch (Parser::exception_type& /*e*/)
    {
        throw MlxcfgException("Error parsing mathematical expression");
    }
}

void TLVConf::getExprVarsValues(vector<string>& vars,
                                std::vector<std::shared_ptr<TLVConf>> ruleTLVs,
                                map<string, u_int32_t>& var2ValMap,
                                string expr,
                                QueryType qt)
{
    std::shared_ptr<Param> vP = NULL;
    // find value of all vars(w/o temp vars) in the tempVars string:
    VECTOR_ITERATOR(string, vars, i)
    {
        string var = *i;
        // TODO: make sure: assume temp var starts with '_'
        if ((var[0] != '_' /*&& !isTempVarsExpr*/) && (var2ValMap.find(var) == var2ValMap.end()))
        {
            size_t pos = var.find('.');
            if (pos == string::npos)
            {
                // the var is in the same tlv or it is a temp var
                vP = getParamByName(var, qt);
            }
            else
            {
                string tlvName = var.substr(0, pos);
                for (std::vector<std::shared_ptr<TLVConf>>::iterator k = ruleTLVs.begin(); k != ruleTLVs.end(); ++k)
                {
                    if ((*k)->_name == tlvName)
                    {
                        vP = (*k)->getParamByName(var.substr(pos + 1), qt);
                        // printf("tlvName=%s p=%s val=%d\n", tlvName.c_str(), vP->_name.c_str(), vP->_value);
                        break;
                    }
                }
            }
            if (vP == NULL)
            {
                throw MlxcfgException("The parameter %s in the rule %s was not found\n", var.c_str(), expr.c_str());
            }
            var2ValMap[var] = vP->_value->getIntVal();
        }
    }
}

void substituteVarsValues(string orgExpr,
                          string& expr,
                          map<string, u_int32_t>& var2ValMap,
                          bool isTempVars,
                          string& tempVar)
{
    string var = "";

    expr = "";
    tempVar = "";
    for (unsigned int j = 0; j < orgExpr.size(); j++)
    {
        if (orgExpr[j] == '$')
        {
            var = "";
            j++;
            while (j < orgExpr.size() &&
                   (orgExpr[j] == '_' || orgExpr[j] == '.' || ('a' <= orgExpr[j] && orgExpr[j] <= 'z') ||
                    ('A' <= orgExpr[j] && orgExpr[j] <= 'Z') || ('0' <= orgExpr[j] && orgExpr[j] <= '9')))
            {
                var += orgExpr[j];
                j++;
            }
            if ((var[0] == '_') && isTempVars)
            {
                tempVar = var.substr(1);
                expr += tempVar;
            }
            else
            {
                stringstream ss;
                ss << var2ValMap[var];
                expr += ss.str();
            }
            if (j < orgExpr.size())
            {
                expr += orgExpr[j];
            }
        }
        else
        {
            expr += orgExpr[j];
        }
    }
    // eval temp vars values and update the map:
}

void TLVConf::evalTempVars(std::shared_ptr<Param> p,
                           std::vector<std::shared_ptr<TLVConf>> ruleTLVs,
                           map<string, u_int32_t>& var2ValMap,
                           QueryType qt)
{
    vector<string> vars;

    p->extractVars(vars, p->_tempVars);
    getExprVarsValues(vars, ruleTLVs, var2ValMap, p->_tempVars, qt);

    // Substitute vars (w/o temp vars) with value:
    string expr = "";
    string orgExpr = p->_tempVars;
    string var = "";
    string tempVar = "";
    substituteVarsValues(orgExpr, expr, var2ValMap, true, tempVar);

    u_int32_t v, r;
    evalExpr(expr, tempVar, v, r);
    var2ValMap['_' + tempVar] = v;
}

u_int32_t TLVConf::evalRule(std::shared_ptr<Param> p,
                            string rule,
                            std::vector<std::shared_ptr<TLVConf>>& ruleTLVs,
                            map<string, u_int32_t>& var2ValMap,
                            QueryType qt)
{
    string expr = "";
    string orgExpr = rule;
    string var = "";
    string temp = "";
    vector<string> vars;

    p->extractVars(vars, rule);
    getExprVarsValues(vars, ruleTLVs, var2ValMap, rule, qt);

    substituteVarsValues(orgExpr, expr, var2ValMap, false, temp);
    u_int32_t v, r;
    evalExpr(expr, temp, v, r);
    return r;
}

void TLVConf::checkRules(std::vector<std::shared_ptr<TLVConf>> ruleTLVs, QueryType qt)
{
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);
    for (std::vector<std::shared_ptr<Param>>::iterator it = params->begin(); it != params->end(); ++it)
    {
        std::shared_ptr<Param> p = *it;
        map<string, u_int32_t> var2ValMap;

        if (p->_supportedFromVersion > _maxTlvVersionSuppByFw)
        {
            continue;
        }

        // first, find values of temp vars
        if (!p->_tempVars.empty())
        {
            evalTempVars(p, ruleTLVs, var2ValMap, qt);
        }

        if (!p->_maxVal.empty())
        {
            u_int32_t r = evalRule(p, p->_maxVal, ruleTLVs, var2ValMap, qt);
            if (p->_value->getIntVal() > r)
            {
                throw MlxcfgException("Parameter %s' value is larger than maximum allowed %d",
                                      p->_mlxconfigName.c_str(), r);
            }
        }

        if (!p->_minVal.empty())
        {
            u_int32_t r = evalRule(p, p->_minVal, ruleTLVs, var2ValMap, qt);
            if (p->_value->getIntVal() < r)
            {
                throw MlxcfgException("Parameter %s' value is smaller than minimum allowed %d",
                                      p->_mlxconfigName.c_str(), r);
            }
        }

        if (!p->_rule.empty())
        {
            if (evalRule(p, p->_rule, ruleTLVs, var2ValMap, qt) == 0)
            {
                string paramsList = "";
                vector<string> vars;
                p->extractVars(vars, p->_tempVars);
                p->extractVars(vars, p->_rule);
                VECTOR_ITERATOR(string, vars, it)
                {
                    if (((*it).find('_') == 0) || (paramsList.find(*it) != string::npos))
                    {
                        continue;
                    }
                    paramsList += (*it) + ", ";
                }
                throw MlxcfgException(
                  "The Parameter %s has Illegal constraint.\n"
                  "Note: The constraint of this parameter is affected by the following parameters:\n%s",
                  p->_mlxconfigName.c_str(),
                  (paramsList.size() <= 2) ? "" : (paramsList.substr(0, paramsList.size() - 2)).c_str());
            }
        }
    }
}

// mlxconfig always set the next value
void TLVConf::setOnDevice(mfile* mf)
{
    pack(_buff.data(), QueryNext);
    mnvda(mf, _buff.data(), _size, getTlvTypeBe(), REG_ACCESS_METHOD_SET, QueryNext);
}

void TLVConf::getRuleTLVs(std::set<string>& result)
{
    VECTOR_ITERATOR(std::shared_ptr<Param>, _paramsNext, p)
    {
        vector<string> rulesTLV;
        (*p)->getRulesTLV(rulesTLV);
        VECTOR_ITERATOR(string, rulesTLV, r)
        {
            result.insert(*r);
            // printf("-D- rule TLV: %s\n", r->c_str());
        }
    }
    return;
}

void TLVConf::genXMLTemplate(string& xmlTemplate, bool allAttrs, bool withVal, bool defaultAttrVal, bool confFormat)
{
    map<string, string> attrs;

    if (this->isPortTargetClass())
    {
        attrs[PORT_ATTR] = defaultAttrVal ? ALL_ATTR_VAL : _attrs[PORT_ATTR];
    }
    else if (this->isModuleTargetClass())
    {
        attrs[MODULE_ATTR] = defaultAttrVal ? ALL_ATTR_VAL : _attrs[MODULE_ATTR];
    }
    else if ((_tlvClass == Per_Host_Per_Function) && allAttrs)
    {
        attrs[HOST_ATTR] = defaultAttrVal ? ALL_ATTR_VAL : _attrs[HOST_ATTR];
        attrs[FUNC_ATTR] = defaultAttrVal ? ALL_ATTR_VAL : _attrs[FUNC_ATTR];
    }

    if (allAttrs)
    {
        attrs[OVR_EN_ATTR] = defaultAttrVal ? "1" : _attrs[OVR_EN_ATTR];
        attrs[RD_EN_ATTR] = defaultAttrVal ? "1" : _attrs[RD_EN_ATTR];
        attrs[PRIORITY_ATTR] = defaultAttrVal ? MLNX_PRIORITY_ATTR : _attrs[PRIORITY_ATTR];
        attrs[WRITER_ID_ATTR] = defaultAttrVal ? numToStr(WRITER_ID_UNSPECIFIED) : _attrs[WRITER_ID_ATTR];
    }

    xmlTemplate = "<" + _name;
    MAP_ITERATOR(string, string, attrs, it)
    {
        xmlTemplate += " " + it->first + "='" + it->second + "'";
    }
    xmlTemplate += ">\n\n";

    for (std::vector<std::shared_ptr<Param>>::iterator it = _paramsNext.begin(); it != _paramsNext.end(); ++it)
    {
        string paramXMLTemplate;
        (*it)->genXMLTemplate(paramXMLTemplate, withVal, confFormat);
        vector<string> lines = splitStr(paramXMLTemplate, '\n');
        VECTOR_ITERATOR(string, lines, line)
        {
            xmlTemplate += "\t" + *line + "\n";
        }
        xmlTemplate += "\n";
    }

    xmlTemplate += "</" + _name + ">";
}

bool TLVConf::isPortTargetClass()
{
    return this->_tlvClass == 1;
}

bool TLVConf::isModuleTargetClass()
{
    return this->_tlvClass == 9;
}

bool TLVConf::isHostTargetClass()
{
    return this->_tlvClass == 3 || this->_tlvClass == 7;
}

void TLVConf::unpackTLVType(TLVClass tlvClass, tools_open_tlv_type& type, u_int32_t& id)
{
    struct tools_open_global_type global;
    struct tools_open_host_type per_host;
    struct tools_open_per_port_type per_port;
    struct tools_open_configuration_item_type_class_module per_module;
    struct tools_open_per_host_type per_host_function;
    switch (tlvClass)
    {
        case Switch_Global:
        case NVFile:
        case Global:
            // printf("-D- global\n");
            tools_open_global_type_unpack(&global, (u_int8_t*)&(type.tlv_type_dw.tlv_type_dw));
            // printf("-D- id=%d\n", global.param_idx);
            id = global.param_idx;
            type.global = global;
            break;

        case Physical_Port_Common:
        case Physical_Port:
            tools_open_per_port_type_unpack(&per_port, (u_int8_t*)&(type.tlv_type_dw.tlv_type_dw));
            id = per_port.param_idx;
            type.per_port = per_port;
            break;

        case All_Hosts_All_Functions:
        case All_Hosts_Per_Function:
        case Per_Host_All_Functions:
        case Per_Host_Per_Function:
            tools_open_per_host_type_unpack(&per_host_function, (u_int8_t*)&(type.tlv_type_dw.tlv_type_dw));
            id = per_host_function.param_idx;
            type.per_host = per_host_function;
            break;

        case Module:
            tools_open_configuration_item_type_class_module_unpack(&per_module,
                                                                   (u_int8_t*)&(type.tlv_type_dw.tlv_type_dw));
            id = per_module.parameter_index;
            type.per_module = per_module;
            break;

        case Per_Host:
            tools_open_host_type_unpack(&per_host, (u_int8_t*)&(type.tlv_type_dw.tlv_type_dw));
            id = per_host.param_idx;
            type.host = per_host;
            break;

        default:
            throw MlxcfgException("Unknown TLV class %d", (u_int32_t)tlvClass);
    }
}

void TLVConf::setAttr(string attr, string val)
{
    if (_attrs.find(attr) == _attrs.end())
    {
        throw MlxcfgException("%s attribute does not apply to tlv %s", attr.c_str(), _name.c_str());
    }
    else
    {
        _attrs[attr] = val;
    }
}

void TLVConf::genRaw(string& raw)
{
    vector<u_int32_t> buff;
    ostringstream buffSS;

    genBin(buff);

    for (unsigned int i = 0; i < buff.size(); i++)
    {
        buff.data()[i] = __be32_to_cpu(buff.data()[i]);
        buffSS << "0x";
        buffSS << std::setfill('0') << std::setw(8) << std::hex;
        buffSS << buff.data()[i] << " ";
    }
    raw = buffSS.str();
}

int PriorityStrToNum(string priority)
{
    if (priority == USER_PRIORITY_ATTR)
    {
        return 0;
    }
    if (priority == OEM_PRIORITY_ATTR)
    {
        return 1;
    }
    if (priority == MLNX_PRIORITY_ATTR)
    {
        return 3;
    }
    return -1;
}
string PriorityNumToStr(u_int8_t priority)
{
    switch (priority)
    {
        case 0:
            return USER_PRIORITY_ATTR;
        case 1:
            return OEM_PRIORITY_ATTR;
        case 3:
            return MLNX_PRIORITY_ATTR;
        default:
            return "ERROR";
    }
}

void TLVConf::genBin(vector<u_int32_t>& buff, bool withHeader, QueryType qt)
{
    u_int32_t writer_id = 0, rd_en = 0, ovr_en = 0;
    int priority;
    tools_open_nv_hdr_fifth_gen hdr;

    if (withHeader)
    {
        u_int32_t hdrSize = tools_open_nv_hdr_fifth_gen_size();

        buff.resize((_size + hdrSize) >> 2);

        memset(&hdr, 0, sizeof(hdr));
        hdr.length = _size;

        if (!strToNum(_attrs[WRITER_ID_ATTR], writer_id))
        {
            throw MlxcfgException("Illegal value for " WRITER_ID_ATTR);
        }
        hdr.writer_id = (u_int8_t)writer_id;

        if (!strToNum(_attrs[RD_EN_ATTR], rd_en) || (rd_en > 1))
        {
            throw MlxcfgException("Illegal value for " RD_EN_ATTR);
        }
        hdr.rd_en = (u_int8_t)rd_en;

        if (!strToNum(_attrs[OVR_EN_ATTR], ovr_en) || (ovr_en > 1))
        {
            throw MlxcfgException("Illegal value for " OVR_EN_ATTR);
        }
        hdr.over_en = (u_int8_t)ovr_en;
        priority = PriorityStrToNum(_attrs[PRIORITY_ATTR]);
        if (priority < 0)
        {
            throw MlxcfgException("%s is Illegal value for %s", _attrs[PRIORITY_ATTR].c_str(), PRIORITY_ATTR);
        }
        hdr.priority = (u_int8_t)priority;

        hdr.type.tlv_type_dw.tlv_type_dw = __be32_to_cpu(getTlvTypeBe());

        tools_open_nv_hdr_fifth_gen_pack(&hdr, (u_int8_t*)buff.data());

        pack((u_int8_t*)buff.data() + hdrSize, qt);
    }
    else
    {
        buff.resize(_size >> 2);
        pack((u_int8_t*)buff.data(), qt);
    }
}

bool TLVConf::areParamsEqual(TLVConf& rhsTLV, QueryType qt)
{
    std::vector<std::shared_ptr<Param>>* params = getParams(qt);
    std::vector<std::shared_ptr<Param>>* rhsParams = rhsTLV.getParams(qt);
    if (params->size() != rhsParams->size())
    {
        return false;
    }

    for (auto param : *params)
    {
        auto rhsParam =
          std::find_if(rhsParams->begin(), rhsParams->end(),
                       [param](shared_ptr<Param> rhsTLVParam) { return param->_name == rhsTLVParam->_name; });

        if (rhsParam == rhsParams->end() ||
            mft_utils::to_lowercase_copy(param->getVal()) != mft_utils::to_lowercase_copy((*rhsParam)->getVal()))
        {
            return false;
        }
    }

    return true;
}
