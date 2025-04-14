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

#ifndef MLXTOKEN_H_
#define MLXTOKEN_H_

#include <vector>
#include "mlxconfig/mlxcfg_generic_commander.h"
#include "mlxconfig/mlxcfg_ui_tokens.h"

struct TLVParamsData
{
    TLVParamsData(string tlv, string param, string data) : _tlv(tlv), _param(param), _data(data), _isFromNested(false)
    {
    }

    void SetNested() { _isFromNested = true; }

    string _tlv;
    string _param;
    string _data;
    bool _isFromNested;
};

class MlxToken
{
public:
    void LoadFromXMLFile(string filePath);
    void LoadFromParams(const vector<TLVParamsData>& paramsData);
    void SaveToXMLFile(string filePath);
    void Aggregate(const MlxToken& token);

protected:
    MlxToken(Device_Type deviceType, string aggregatableTLV, vector<string> requiredTLVs);
    virtual ~MlxToken() {}
    std::shared_ptr<TLVConf> GetTlvConf(string tlvName);
    const std::shared_ptr<TLVConf> GetTlvConf(string tlvName) const;
    void Aggregate(const std::shared_ptr<TLVConf> tlvConf);
    virtual string ToXML();
    void AddTLV(string tlv) { _requiredTLVs.push_back(tlv); };

private:
    std::shared_ptr<Param> FindNextFreeSlot(string tlvName, string paramName);
    void VerifyTokenStructure();
    virtual void VerifyTokenContent(){};
    void VerifySharedTlvs(const MlxToken& token);

    Device_Type _deviceType;
    string _aggregatableTLV;
    vector<string> _requiredTLVs;
    vector<std::shared_ptr<TLVConf>> _tlvs;
};

class MlxChallengeBasedToken : public MlxToken
{
protected:
    MlxChallengeBasedToken(Device_Type deviceType, vector<string> requiredTLVs) :
        MlxToken(deviceType, "file_device_unique", requiredTLVs)
    {
    }

private:
    void DeleteEmptyParams(std::shared_ptr<TLVConf> tlvConf);
    void UpdateNumberOfEntries();
    void VerifyTokenContent() override;
    string ToXML() override;

    static const u_int8_t _maxNumOfDeviceUniquePairs;
};

class MlxCRCSToken : public MlxChallengeBasedToken
{
public:
    MlxCRCSToken(Device_Type deviceType) :
        MlxChallengeBasedToken(deviceType,
                               {"file_cs_token_id", "file_device_unique", "file_applicable_to", "file_signature"})
    {
    }
};

class MlxCRDTToken : public MlxChallengeBasedToken
{
public:
    MlxCRDTToken(Device_Type deviceType) :
        MlxChallengeBasedToken(deviceType,
                               {"file_dbg_fw_token_id", "file_device_unique", "file_applicable_to", "file_signature"})
    {
    }
};

class MlxCSToken : public MlxToken
{
public:
    MlxCSToken(Device_Type deviceType) :
        MlxToken(deviceType, "", {"file_cs_token_id", "file_mac_addr_list", "file_applicable_to"})
    {
    }
};

class MlxDBGToken : public MlxToken
{
public:
    MlxDBGToken(Device_Type deviceType) :
        MlxToken(deviceType, "", {"file_dbg_fw_token_id", "file_mac_addr_list", "file_applicable_to"})
    {
    }
};

class MlxRMCSToken : public MlxToken
{
public:
    MlxRMCSToken(Device_Type deviceType) :
        MlxToken(deviceType, "", {"file_mac_addr_list", "file_applicable_to", "file_rmcs_token_id"})
    {
    }
};

class MlxRMDTToken : public MlxToken
{
public:
    MlxRMDTToken(Device_Type deviceType) :
        MlxToken(deviceType, "", {"file_mac_addr_list", "file_applicable_to", "file_rmdt_token_id"})
    {
    }
};

class MlxFRCToken : public MlxChallengeBasedToken
{
public:
    MlxFRCToken(Device_Type deviceType) :
        MlxChallengeBasedToken(deviceType, {"file_frc_token_id", "file_device_unique", "file_applicable_to"})
    {
    }
};

class MlxTokenFactory
{
public:
    static shared_ptr<MlxToken> CreateToken(MlxCfgTokenType tokenType, Device_Type deviceType);
};

#endif /* MLXTOKEN_H_ */