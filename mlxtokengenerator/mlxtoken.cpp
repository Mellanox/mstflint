/*
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
 */

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include "mlxtoken.h"
#include "mlxtkngenerator_utils.h"

/********************************************************************************************************************************/
/*                                             MlxToken */
/********************************************************************************************************************************/

MlxToken::MlxToken(Device_Type deviceType, string aggregatableTLV, vector<string> requiredTLVs) :
    _deviceType(deviceType), _aggregatableTLV(aggregatableTLV), _requiredTLVs(requiredTLVs)
{
}

void MlxToken::LoadFromXMLFile(string filePath)
{
    vector<u_int8_t> token = ReadFromFile(filePath);
    string dbName = "";
    GenericCommander commander(nullptr, dbName, _deviceType);

    _tlvs.clear();

    try
    {
        commander.XML2TLVConf(string(token.begin(), token.end()), _tlvs);
        VerifyTokenStructure();
        VerifyTokenContent();
    }
    catch (const MlxTknGeneratorException& e)
    {
        throw MlxTknGeneratorException("Failed while processing %s, %s", filePath.c_str(), e.what());
    }
}

void MlxToken::LoadFromParams(const vector<TLVParamsData>& paramsData)
{
    string dbName = "";
    GenericCommander commander(nullptr, dbName, _deviceType);
    _tlvs.clear();

    commander.TLVs2TLVConfs(_requiredTLVs, _tlvs);

    for (auto dataEntry : paramsData)
    {
        auto tlv = find_if(_tlvs.begin(), _tlvs.end(),
                           [dataEntry](std::shared_ptr<TLVConf> tlv) { return tlv->_name == dataEntry._tlv; });
        if (tlv != _tlvs.end())
        {
            (*tlv)->updateParamByName(dataEntry._param, dataEntry._data, QueryNext);
        }
        else
        {
            throw MlxTknGeneratorException("Unable to find %s tlv.", dataEntry._tlv.c_str());
        }
    }
}

void MlxToken::SaveToXMLFile(string filePath)
{
    ofstream out(filePath);
    if (!out.is_open())
    {
        throw MlxTknGeneratorException("Failed to open file: %s", filePath.c_str());
    }
    out << ToXML();
    out.close();
}

void MlxToken::Aggregate(const MlxToken& token)
{
    VerifySharedTlvs(token);

    const std::shared_ptr<TLVConf> aggregatableTLV = token.GetTlvConf(_aggregatableTLV);
    Aggregate(aggregatableTLV);
}

void MlxToken::Aggregate(const std::shared_ptr<TLVConf> tlvConf)
{
    for (auto param : tlvConf->_paramsNext)
    {
        if (!param->getVal().empty() && std::isdigit(param->_name.back()))
        {
            shared_ptr<Param> emptyParam = FindNextFreeSlot(tlvConf->_name, param->_name);
            emptyParam->setVal(param->getVal(true));
        }
    }
}

shared_ptr<Param> MlxToken::FindNextFreeSlot(string tlvName, string paramName)
{
    std::shared_ptr<TLVConf> tlv = GetTlvConf(tlvName);

    while (std::isdigit(paramName.back()))
    {
        paramName.pop_back();
    }

    auto emptyParam = find_if(tlv->_paramsNext.begin(), tlv->_paramsNext.end(),
                              [paramName](shared_ptr<Param> param)
                              { return (param->_name.find(paramName) != string::npos && param->getVal().empty()); });

    if (emptyParam == tlv->_paramsNext.end())
    {
        throw MlxTknGeneratorException("Couldn't find an empty field for %s, aggregated token is full.",
                                       paramName.c_str());
    }

    return *emptyParam;
}

void MlxToken::VerifyTokenStructure()
{
    for (auto requiredTLV : _requiredTLVs)
    {
        auto it = std::find_if(_tlvs.begin(), _tlvs.end(),
                               [requiredTLV](std::shared_ptr<TLVConf> tlv) { return tlv->_name == requiredTLV; });

        if (it == _tlvs.end())
        {
            throw MlxTknGeneratorException("Missing tlv %s.", requiredTLV.c_str());
        }
    }
    for (auto tlv : _tlvs)
    {
        auto it = std::find(_requiredTLVs.begin(), _requiredTLVs.end(), tlv->_name);

        if (it == _requiredTLVs.end() && tlv->_name != "file_signature") // new tokens will have the file_signature tlv
                                                                         // as part of key separation feature
        {
            throw MlxTknGeneratorException("redundant tlv %s.", tlv->_name.c_str());
        }
    }
}

std::shared_ptr<TLVConf> MlxToken::GetTlvConf(string tlvName)
{
    auto deviceUniqueTLV = std::find_if(_tlvs.begin(), _tlvs.end(),
                                        [tlvName](std::shared_ptr<TLVConf> tlv) { return tlv->_name == tlvName; });
    if (deviceUniqueTLV == _tlvs.end())
    {
        throw MlxTknGeneratorException("Couldn't find required TLV");
    }
    return *deviceUniqueTLV;
}

const std::shared_ptr<TLVConf> MlxToken::GetTlvConf(string tlvName) const
{
    return (const_cast<MlxToken*>(this))->GetTlvConf(tlvName);
}

string MlxToken::ToXML()
{
    string dbName = "";
    GenericCommander commander(nullptr, dbName, _deviceType);
    string tokenXML("");
    commander.genXMLFromTLVConf(_tlvs, tokenXML, false);
    return tokenXML;
}

void MlxToken::VerifySharedTlvs(const MlxToken& token)
{
    for (auto tlv : _tlvs)
    {
        if (tlv->_name != _aggregatableTLV)
        {
            const std::shared_ptr<TLVConf> sharedTLV = token.GetTlvConf(tlv->_name);
            if (!tlv->areParamsEqual(*sharedTLV, QueryNext))
            {
                throw MlxTknGeneratorException("data in %s tlv must be identical in all given tokens.",
                                               tlv->_name.c_str());
            }
        }
    }
}

/********************************************************************************************************************************/
/*                                              MlxChallengeBasedToken */
/********************************************************************************************************************************/

const u_int8_t MlxChallengeBasedToken::_maxNumOfDeviceUniquePairs = 12;

void MlxChallengeBasedToken::DeleteEmptyParams(std::shared_ptr<TLVConf> tlvConf)
{
    auto param = tlvConf->_paramsNext.begin();
    while (param != tlvConf->_paramsNext.end())
    {
        if ((*param)->getVal().empty())
        {
            param = tlvConf->_paramsNext.erase(param);
        }
        else
        {
            param++;
        }
    }
}

void MlxChallengeBasedToken::UpdateNumberOfEntries()
{
    auto deviceUniqueTLV = GetTlvConf("file_device_unique");

    u_int8_t validEntries =
      std::count_if(deviceUniqueTLV->_paramsNext.begin(), deviceUniqueTLV->_paramsNext.end(),
                    [](shared_ptr<Param> param) { return param->_name.find("device_unique_id") != string::npos; });

    auto validEntriesParam = find_if(deviceUniqueTLV->_paramsNext.begin(), deviceUniqueTLV->_paramsNext.end(),
                                     [](shared_ptr<Param> param) { return (param->_name == "valid_entries"); });

    if (validEntriesParam == deviceUniqueTLV->_paramsNext.end())
    {
        throw MlxTknGeneratorException("Missing valid_entries field in token");
    }

    std::stringstream ss;
    ss << std::hex << (int)validEntries;
    (*validEntriesParam)->setVal(ss.str());
}

void MlxChallengeBasedToken::VerifyTokenContent()
{
    auto deviceUniqueTLV = GetTlvConf("file_device_unique");
    bool deviceUniqueIdFound[_maxNumOfDeviceUniquePairs] = {false};
    bool nonceFound[_maxNumOfDeviceUniquePairs] = {false};

    for (auto param : deviceUniqueTLV->_paramsNext)
    {
        if (param->_name.find("device_unique_id") != string::npos && std::isdigit(param->_name.back()) &&
            !param->getVal().empty())
        {
            size_t lastIndex = param->_name.find_last_not_of("0123456789");
            int slotNumber = std::stoi(param->_name.substr(lastIndex + 1));
            if (slotNumber < 0 || slotNumber >= _maxNumOfDeviceUniquePairs)
            {
                throw MlxTknGeneratorException("%s is corrupted", param->_name.c_str());
            }
            deviceUniqueIdFound[slotNumber] = true;
        }
        if (param->_name.find("nonce") != string::npos && std::isdigit(param->_name.back()) && !param->getVal().empty())
        {
            size_t lastIndex = param->_name.find_last_not_of("0123456789");
            int slotNumber = std::stoi(param->_name.substr(lastIndex + 1));
            if (slotNumber < 0 || slotNumber >= _maxNumOfDeviceUniquePairs)
            {
                throw MlxTknGeneratorException("%s is corrupted.", param->_name.c_str());
            }
            nonceFound[slotNumber] = true;
        }
    }

    for (u_int8_t i = 0; i < _maxNumOfDeviceUniquePairs; ++i)
    {
        if (deviceUniqueIdFound[i] != nonceFound[i])
        {
            throw MlxTknGeneratorException("file_device_unique is corrupted.");
        }
    }
}

string MlxChallengeBasedToken::ToXML()
{
    DeleteEmptyParams(GetTlvConf("file_device_unique"));

    UpdateNumberOfEntries();

    return MlxToken::ToXML();
}

/********************************************************************************************************************************/
/*                                              MlxTokenFactory */
/********************************************************************************************************************************/

shared_ptr<MlxToken> MlxTokenFactory::CreateToken(MlxCfgTokenType tokenType, Device_Type deviceType)
{
    switch (tokenType)
    {
        case McTokenTypeCRCS:
            return shared_ptr<MlxToken>(new MlxCRCSToken(deviceType));
        case McTokenTypeCRDT:
            return shared_ptr<MlxToken>(new MlxCRDTToken(deviceType));
        case McTokenTypeCS:
            return shared_ptr<MlxToken>(new MlxCSToken(deviceType));
        case McTokenTypeDBG:
            return shared_ptr<MlxToken>(new MlxDBGToken(deviceType));
        case McTokenTypeRMCS:
            return shared_ptr<MlxToken>(new MlxRMCSToken(deviceType));
        case McTokenTypeRMDT:
            return shared_ptr<MlxToken>(new MlxRMDTToken(deviceType));
        case McTokenTypeFRC:
            return shared_ptr<MlxToken>(new MlxFRCToken(deviceType));
        default:
            throw MlxTknGeneratorException("%s is not supported.", MlxCfgToken::getTokenString(tokenType).c_str());
    }
}