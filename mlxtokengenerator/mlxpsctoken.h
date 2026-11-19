/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *  Version: $Id$
 *
 */

#ifndef MLXPSCTOKEN_H_
#define MLXPSCTOKEN_H_

#include <vector>
#include <string>
#include <map>
#include <memory>
#include "tokens_layout_layouts.h"
#include "mlxconfig/mlxcfg_ui.h"

#define PSC_TLV_TYPE_START "PSC_TLV_TYPE_START"
#define PSC_TLV_TYPE_END "PSC_TLV_TYPE_END"

enum class DeviceType
{
    NVSwitch = 0x3,
    CX7 = 0x4,
    NIC = 0x6,
    SOC = 0x7,
    EthSwitch = 0x9
};

enum class TlvType
{
    TOKEN_IDENTIFIER = 0x0008,
    DEVICE_TYPE = 0x0001,
    TOKEN_TYPE = 0x0009,
    KEYPAIR_UUID = 0x4400,
    PSID = 0x4401,
    FW_VERSION = 0x0005,
    DEVICE_UNIQUE = 0x4402,
    TOKEN_CONFIGURATION = 0x000A,
    RATCHET = 0x0011,
    SIGNATURE_STAGE1 = 0x000B,
    SIGNATURE_STAGE2 = 0x000C
};

class MlxPSCtoken
{
public:
    MlxPSCtoken(DeviceType deviceType, MlxCfgTokenType tokenType);

    // Initialization
    void InitToken();

    // Device type operations
    static DeviceType GetDeviceTypeFromDeviceId(dm_dev_id_t deviceId);
    void SetDeviceTypeToToken(mfile* mf);
    void GetChallengeBasedTokenData(const reg_access_switch_mtcq_reg_ext& challenge, const string& tokenConfig);

    std::string ToXML(const std::vector<std::pair<std::string, std::string>>& tlvs);
    void SaveToXMLFile(const std::string& filePath, const std::vector<std::pair<std::string, std::string>>& tlvs);
    void SaveToXMLFile(const std::string& filePath);

    TlvType StrToTlvType(const std::string& tlvTypeStr);
    static std::string TlvTypeToStr(TlvType typeTLV);

    std::vector<std::pair<std::string, std::string>> LoadFromParams();
    void LoadParamsFromMap(const std::map<std::string, std::string>& tokenData);
    void LoadFromXMLFile(std::string xmlContent, std::string filePath);
    void Aggregate(const MlxPSCtoken& token);
    static DeviceType GetDeviceTypeFromXML(const std::string& xmlContent);
    static MlxCfgTokenType GetTokenTypeFromXML(const std::string& xmlContent);

    static DeviceType StrToDeviceType(const std::string& deviceType);

    // Public getters
    DeviceType GetDeviceTypeEnum() const;
    u_int32_t GetTokenType() const;
    MlxCfgTokenType GetTokenTypeEnum() const;

    friend class MlxTknGenerator;

private:
    void InitTlvValue(TlvType typeTLV);
    static void InitTlvHeader(tokens_layout_psc_debug_token_tlv_header& tlvHeader, TlvType typeTLV);
    void InitTLV(TlvType typeTLV);

    // Setters for token fields
    void SetKeypairUUID(const u_int32_t* keypairUUID);
    void SetPSID(const u_int32_t* psid);
    void SetFWVersion(u_int32_t fwVersion31_0, u_int32_t fwVersion39_32);
    void SetDeviceUnique(u_int64_t baseMac, const u_int32_t* challenge);
    void SetTokenConfig(const std::string& tokenConfig);
    void SetRatchet(u_int64_t ratchet);

    // Setters from map data
    void SetPSIDFromMap(const std::string& psid);
    void SetFWVersionFromMap(const std::string& fwVersion);
    void SetTokenConfigFromMap(const std::string& tokenConfig);
    void SetDeviceUniqueFromMap(const std::map<std::string, std::string>& tokenData);
    void SetKeypairUUIDFromMap(const std::string& keypairUUID);

    // Getters
    static u_int32_t GetTLVLength(TlvType typeTLV);
    u_int32_t GetDeviceType() const;
    std::string GetDeviceTypeString() const;
    std::string GetUUIDString() const;
    std::string GetPSIDString() const;
    std::string GetFWVersionString() const;
    int GetValidEntries() const;
    std::string GetNonceVersionString() const;
    std::string GetRatchetStr() const;
    std::string GetTokenConfigString() const;

    std::string FindValueInDeviceUnique(const std::string& value, const std::string& key);
    std::vector<std::string> SplitByComma(const std::string& tokenConfig);

    void AddDeviceUnique(const u_int64_t& deviceUnique);
    void AddNonce(const u_int32_t* nonce);
    void UpdateValidEntries();
    u_int64_t GetDeviceUnique() const;
    const u_int32_t* GetNonce() const;
    void ValidateValidEntries(const MlxPSCtoken& token);
    void ValidatePSID(const string& psid);
    void ValidateDeviceType(DeviceType deviceType);
    void ValidateTokenType(MlxCfgTokenType tokenType);
    void ValidateFWVersion(const string& fwVersion);
    void ValidateTokenConfig(const string& tokenConfig);
    void ValidateKeypairUUID(const string& keypairUUID);
    // Member variables
    DeviceType _deviceType;
    MlxCfgTokenType _tokenType;
    u_int8_t _nonceVersion;
    tokens_layout_psc_debug_token _token;
    int _validEntries;
};

class MlxPSCtokenFactory
{
public:
    static std::shared_ptr<MlxPSCtoken> CreatePSCtoken(MlxCfgTokenType tokenType, DeviceType deviceType);
};

#endif /* MLXPSCTOKEN_H_ */