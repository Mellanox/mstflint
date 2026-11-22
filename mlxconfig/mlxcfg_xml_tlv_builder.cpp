/*
 * SPDX-FileCopyrightText: NVIDIA CORPORATION & AFFILIATES
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 */

#include "mlxcfg_xml_tlv_builder.h"

#include <algorithm>
#include <strings.h>

#include "mlxcfg_utils.h"

using namespace std;
using mlxcfg::XmlAttrs;
using mlxcfg::XmlTlvBuilder;

namespace
{
const char* getAttr(const XmlAttrs& attrs, const char* attr)
{
    XmlAttrs::const_iterator it = attrs.find(attr);
    return it == attrs.end() ? NULL : it->second.c_str();
}

u_int32_t indexLimit(const Param& param)
{
    bool isArray = param._arrayLength != 0 && param._type != STRING && param._type != BYTES;
    return isArray ? param._arrayLength : 1;
}
} // namespace

XmlTlvBuilder::XmlTlvBuilder(MlxcfgDBManager* dbManager,
                             int maxPort,
                             const string& rootName,
                             const string& rootNs,
                             vector<std::shared_ptr<TLVConf>>& tlvs) :
    _dbManager(dbManager),
    _maxPort(maxPort),
    _rootName(rootName),
    _rootNs(rootNs),
    _tlvs(tlvs),
    _depth(0),
    _paramHasIndex(false)
{
}

void XmlTlvBuilder::OnStartElement(const string& nsUri, const string& name, const XmlAttrs& attrs)
{
    _depth++;
    if (_depth > MAX_LEVEL)
    {
        throw MlxcfgException("Unexpected nested element %s inside the parameter %s", name.c_str(), _paramName.c_str());
    }
    switch (_depth)
    {
        case ROOT_LEVEL:
            checkXmlRoot(nsUri, name, _rootName, _rootNs);
            break;
        case TLV_LEVEL:
            startTlv(name, attrs);
            break;
        case PARAM_LEVEL:
            startParam(name, attrs);
            break;
    }
}

void XmlTlvBuilder::OnText(const char* text, size_t len)
{
    if (_depth == PARAM_LEVEL)
    {
        _paramText.append(text, len);
    }
}

void XmlTlvBuilder::OnEndElement()
{
    if (_depth == PARAM_LEVEL)
    {
        endParam();
    }
    else if (_depth == TLV_LEVEL)
    {
        endTlv();
    }
    _depth--;
}

void XmlTlvBuilder::checkAnyTlvFound() const
{
    if (_tlvs.empty())
    {
        throw MlxcfgException("No TLV configurations were found in the XML");
    }
}

void XmlTlvBuilder::setAttrIfPresent(const XmlAttrs& attrs, const char* attr)
{
    const char* attrVal = getAttr(attrs, attr);
    if (attrVal)
    {
        _tlvConf->setAttr(attr, attrVal);
    }
}

void XmlTlvBuilder::startTlv(const string& name, const XmlAttrs& attrs)
{
    u_int32_t port = 0;
    u_int32_t u_module = 0;
    int32_t tlvModule;
    bool isAllPorts = false;
    bool isAllModules = false;

    const char* portAttr = getAttr(attrs, PORT_ATTR);
    const char* moduleAttr = getAttr(attrs, MODULE_ATTR);

    if (!portAttr)
    {
        port = 0;
    }
    else if (!strcasecmp(portAttr, ALL_ATTR_VAL))
    {
        isAllPorts = true;
        port = 1;
    }
    else if (!strToNum(portAttr, port) || !(1 <= port && (int32_t)port <= _maxPort))
    {
        throw MlxcfgException("Illegal value of port attribute %s", portAttr);
    }

    if (!moduleAttr)
    {
        tlvModule = -1;
    }
    else if (!strcasecmp(moduleAttr, ALL_ATTR_VAL))
    {
        isAllModules = true;
        tlvModule = 0;
    }
    else if (!strToNum(moduleAttr, u_module) || !(u_module <= (u_int32_t)TLVConf::getMaxModule()))
    {
        throw MlxcfgException("Illegal value of module attribute %s", moduleAttr);
    }
    else
    {
        tlvModule = u_module;
    }

    _tlvConf = _dbManager->getCloneTLVByName(name, port, tlvModule);
    if (isAllPorts)
    {
        _tlvConf->setAttr(PORT_ATTR, ALL_ATTR_VAL);
    }
    if (isAllModules)
    {
        _tlvConf->setAttr(MODULE_ATTR, ALL_ATTR_VAL);
    }
    setAttrIfPresent(attrs, WRITER_ID_ATTR);
    setAttrIfPresent(attrs, OVR_EN_ATTR);
    setAttrIfPresent(attrs, RD_EN_ATTR);
    setAttrIfPresent(attrs, PRIORITY_ATTR);
    setAttrIfPresent(attrs, HOST_ATTR);
    setAttrIfPresent(attrs, FUNC_ATTR);

    _collectedParams.clear();
    _arrayValues.clear();
}

void XmlTlvBuilder::startParam(const string& name, const XmlAttrs& attrs)
{
    const char* indexAttr = getAttr(attrs, INDEX_ATTR);
    _paramName = name;
    _paramHasIndex = indexAttr != NULL;
    _paramIndex = indexAttr ? indexAttr : "";
    _paramText.clear();
}

void XmlTlvBuilder::endParam()
{
    if (!_paramText.empty())
    {
        if (_paramHasIndex)
        {
            u_int32_t leftIndex = 0, rightIndex = 0;
            parseIndexRange(_paramIndex, leftIndex, rightIndex);
            std::shared_ptr<Param> param = _tlvConf->findParamByName(_paramName, QueryNext);
            if (!param)
            {
                throw MlxcfgException(
                  "Unknown parameter %s of the configuration %s", _paramName.c_str(), _tlvConf->_name.c_str());
            }
            if (rightIndex >= indexLimit(*param))
            {
                throw MlxcfgException("Illegal index %u of the parameter %s", rightIndex, _paramName.c_str());
            }
            for (u_int32_t index = leftIndex; index <= rightIndex; index++)
            {
                _arrayValues[_paramName][index] = _paramText;
            }
        }
        else
        {
            if (find(_collectedParams.begin(), _collectedParams.end(), _paramName) != _collectedParams.end())
            {
                throw MlxcfgException("Duplicate use of same parameter: %s\n", _paramName.c_str());
            }
            _collectedParams.push_back(_paramName);
            _tlvConf->updateParamByName(_paramName, _paramText, QueryNext);
        }
    }
    else if (_tlvConf->isAStringParam(_paramName))
    {
        _tlvConf->updateParamByName(_paramName, "", QueryNext);
    }
    else
    {
        throw MlxcfgException("The Parameter %s of the configuration %s "
                              "does not have value",
                              _paramName.c_str(),
                              _tlvConf->_name.c_str());
    }
}

void XmlTlvBuilder::endTlv()
{
    for (map<string, map<u_int32_t, string>>::iterator arrayParam = _arrayValues.begin();
         arrayParam != _arrayValues.end();
         ++arrayParam)
    {
        string paramName = arrayParam->first;
        vector<string> vals(arrayParam->second.size());
        for (map<u_int32_t, string>::iterator indexValue = arrayParam->second.begin();
             indexValue != arrayParam->second.end();
             ++indexValue)
        {
            if (indexValue->first >= vals.size())
            {
                throw MlxcfgException("Illegal index %u of the parameter %s", indexValue->first, paramName.c_str());
            }
            vals[indexValue->first] = indexValue->second;
        }
        _tlvConf->updateParamByName(paramName, vals, QueryNext);
    }
    _tlvs.push_back(_tlvConf);
    _tlvConf = nullptr;
}
