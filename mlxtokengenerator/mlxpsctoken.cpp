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

#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cstring>
#include "mlxpsctoken.h"
#include "mlxtkngenerator_utils.h"
#include "dev_mgt/tools_dev_types.h"
#include "mlxconfig/mlxcfg_generic_commander.h"
#include "mft_utils/mft_utils.h"
#include "tools_layouts/reg_access_switch_layouts.h"

/********************************************************************************************************************************/
/*                                             MlxPSCtoken */
/********************************************************************************************************************************/

#define DEVICE_UNIQUE_ID_PREFIX "device_unique_id"
#define NONCE_PREFIX "nonce"
#define VALID_ENTRIES_KEY "Valid_entries"
#define NONCE_VERSION_KEY "nonce_version"

TlvType MlxPSCtoken::StrToTlvType(const std::string& tlvName)
{
    if (tlvName == "TOKEN_IDENTIFIER")
    {
        return TlvType::TOKEN_IDENTIFIER;
    }
    else if (tlvName == "DEVICE_TYPE")
    {
        return TlvType::DEVICE_TYPE;
    }
    else if (tlvName == "TOKEN_TYPE")
    {
        return TlvType::TOKEN_TYPE;
    }
    else if (tlvName == "KEYPAIR_UUID")
    {
        return TlvType::KEYPAIR_UUID;
    }
    else if (tlvName == "PSID")
    {
        return TlvType::PSID;
    }
    else if (tlvName == "FW_VERSION")
    {
        return TlvType::FW_VERSION;
    }
    else if (tlvName == "DEVICE_UNIQUE")
    {
        return TlvType::DEVICE_UNIQUE;
    }
    else if (tlvName == "TOKEN_CONFIGURATION")
    {
        return TlvType::TOKEN_CONFIGURATION;
    }
    else if (tlvName == "RATCHET")
    {
        return TlvType::RATCHET;
    }
    else if (tlvName == "SIGNATURE_STAGE1")
    {
        return TlvType::SIGNATURE_STAGE1;
    }
    else if (tlvName == "SIGNATURE_STAGE2")
    {
        return TlvType::SIGNATURE_STAGE2;
    }
    else
    {
        throw MlxTknGeneratorException("Invalid TLV type");
    }
}

DeviceType MlxPSCtoken::StrToDeviceType(const std::string& deviceType)
{
    if (deviceType == "NVSwitch")
    {
        return DeviceType::NVSwitch;
    }
    else if (deviceType == "CX7")
    {
        return DeviceType::CX7;
    }
    else if (deviceType == "NIC")
    {
        return DeviceType::NIC;
    }
    else if (deviceType == "EthSwitch")
    {
        return DeviceType::EthSwitch;
    }
    else
    {
        throw MlxTknGeneratorException("Invalid device type");
    }
}

std::string MlxPSCtoken::TlvTypeToStr(TlvType typeTLV)
{
    switch (typeTLV)
    {
        case TlvType::TOKEN_IDENTIFIER:
            return "TOKEN_IDENTIFIER";

        case TlvType::DEVICE_TYPE:
            return "DEVICE_TYPE";

        case TlvType::TOKEN_TYPE:
            return "TOKEN_TYPE";

        case TlvType::KEYPAIR_UUID:
            return "KEYPAIR_UUID";

        case TlvType::PSID:
            return "PSID";

        case TlvType::FW_VERSION:
            return "FW_VERSION";

        case TlvType::DEVICE_UNIQUE:
            return "DEVICE_UNIQUE";

        case TlvType::TOKEN_CONFIGURATION:
            return "TOKEN_CONFIGURATION";

        case TlvType::RATCHET:
            return "RATCHET";

        case TlvType::SIGNATURE_STAGE1:
            return "SIGNATURE_STAGE1";

        case TlvType::SIGNATURE_STAGE2:
            return "SIGNATURE_STAGE2";

        default:
            throw MlxTknGeneratorException("Invalid TLV type");
    }
}

u_int32_t MlxPSCtoken::GetTLVLength(TlvType typeTLV)
{
    switch (typeTLV)
    {
        case TlvType::TOKEN_IDENTIFIER:
            return 4;

        case TlvType::DEVICE_TYPE:
            return 4;

        case TlvType::TOKEN_TYPE:
            return 4;

        case TlvType::KEYPAIR_UUID:
            return 16;

        case TlvType::PSID:
            return 16;

        case TlvType::FW_VERSION:
            return 8;

        case TlvType::DEVICE_UNIQUE:
            return 1280;

        case TlvType::TOKEN_CONFIGURATION:
            return 4;

        case TlvType::RATCHET:
            return 4;

        case TlvType::SIGNATURE_STAGE1:
            return 4736;

        case TlvType::SIGNATURE_STAGE2:
            return 4736;

        default:
            throw MlxTknGeneratorException("Invalid TLV type");
    }
}

DeviceType MlxPSCtoken::GetDeviceTypeEnum() const
{
    return _deviceType;
}

u_int32_t MlxPSCtoken::GetDeviceType() const
{
    return static_cast<u_int32_t>(_deviceType);
}

std::string MlxPSCtoken::GetDeviceTypeString() const
{
    switch (_deviceType)
    {
        case DeviceType::NVSwitch:
            return "NVSwitch";

        case DeviceType::CX7:
            return "CX7";

        case DeviceType::NIC:
            return "NIC";

        case DeviceType::EthSwitch:
            return "EthSwitch";

        default:
            return "Unknown";
    }
    return "";
}

u_int32_t MlxPSCtoken::GetTokenType() const
{
    return static_cast<u_int32_t>(_tokenType);
}

MlxCfgTokenType MlxPSCtoken::GetTokenTypeEnum() const
{
    return _tokenType;
}

std::string MlxPSCtoken::GetRatchetStr() const
{
    stringstream ratchetStream;
    ratchetStream << std::hex << std::setw(8) << std::setfill('0') << _token.ratchet[1] << std::setw(8)
                  << std::setfill('0') << _token.ratchet[0];
    return ratchetStream.str();
}

std::string MlxPSCtoken::GetTokenConfigString() const
{
    return std::to_string(_token.token_config);
}

std::string MlxPSCtoken::GetUUIDString() const
{
    // Convert keypair_uuid data to string
    stringstream keypairUuid;

    for (size_t i = 0; i < sizeof(_token.keypair_uuid.data); i++)
    {
        keypairUuid << std::hex << std::setw(2) << std::setfill('0') << (int)_token.keypair_uuid.data[i];
    }

    return keypairUuid.str();
}

std::string MlxPSCtoken::GetPSIDString() const
{
    stringstream psidStream;

    for (size_t i = 0; i < 4; i++)
    {
        u_int32_t dword = __be32_to_cpu(_token.psid[i]);
        const char* bytes = reinterpret_cast<const char*>(&dword);

        for (int j = 0; j < 4; j++)
        {
            if (bytes[j] != '\0')
                psidStream << bytes[j];
        }
    }

    return psidStream.str();
}

std::string MlxPSCtoken::GetFWVersionString() const
{
    stringstream fwVersionStream;

    if (_deviceType == DeviceType::NIC || _deviceType == DeviceType::CX7 || _deviceType == DeviceType::SOC)
    {
        u_int32_t fw = _token.fw_version[0];
        int major = (fw >> 24) & 0xFF;
        int minor = (fw >> 16) & 0xFF;
        int patch = fw & 0xFFFF;

        fwVersionStream << std::dec << major << "." << std::setw(2) << std::setfill('0') << minor << "." << std::setw(4)
                        << std::setfill('0') << patch;
    }
    else
    {
        u_int32_t fw = _token.fw_version[0];
        int major = (fw >> 16) & 0xFFFF;         // Upper 16 bits
        int minor = fw & 0xFFFF;                 // Lower 16 bits
        int patch = _token.fw_version[1] & 0xFF; // 8 bits

        fwVersionStream << std::uppercase << std::hex << std::setw(4) << std::setfill('0') << major << "."
                        << std::setw(4) << std::setfill('0') << minor << "." << std::setw(2) << std::setfill('0')
                        << patch;
    }

    return fwVersionStream.str();
}

int MlxPSCtoken::GetValidEntries() const
{
    int validEntries = 0;

    for (int i = 0; i < 32; i++)
    {
        if (_token.device_unique[i].serial_number[0] != 0 || _token.device_unique[i].serial_number[1] != 0)
        {
            validEntries++;
        }
    }

    return validEntries;
}

std::string MlxPSCtoken::GetNonceVersionString() const
{
    return "0x" + std::to_string(_nonceVersion);
}

DeviceType MlxPSCtoken::GetDeviceTypeFromDeviceId(dm_dev_id_t deviceId)
{
    DeviceType deviceType;

    // PSC tokens in mstflint: SPC6 only
    if (dm_is_spc6(deviceId))
    {
        deviceType = DeviceType::EthSwitch;
    }
    else
    {
        throw MlxTknGeneratorException("Unsupported device type");
    }

    return deviceType;
}

void MlxPSCtoken::SetDeviceTypeToToken(mfile* mf)
{
    dm_dev_id_t deviceId = DeviceUnknown;
    u_int32_t hwDevId = 0, hwRevId = 0;

    if (dm_get_device_id(mf, &deviceId, &hwDevId, &hwRevId))
    {
        throw MlxTknGeneratorException("Failed to identify the device");
    }

    _deviceType = GetDeviceTypeFromDeviceId(deviceId);
}

void MlxPSCtoken::InitTlvValue(TlvType typeTLV)
{
    switch (typeTLV)
    {
        case TlvType::TOKEN_IDENTIFIER:
            _token.token_identifier = 0x4e424454; // NBDT
            break;
        case TlvType::DEVICE_TYPE:
            _token.device_type = GetDeviceType();
            break;
        case TlvType::TOKEN_TYPE:
            _token.token_type = GetTokenType();
            break;
        case TlvType::KEYPAIR_UUID:
            memset(_token.keypair_uuid.data, 0, sizeof(_token.keypair_uuid.data));
            break;
        case TlvType::PSID:
            memset(_token.psid, 0, sizeof(_token.psid));
            break;
        case TlvType::FW_VERSION:
            memset(_token.fw_version, 0, sizeof(_token.fw_version));
            break;
        case TlvType::DEVICE_UNIQUE:
            memset(_token.device_unique, 0, sizeof(_token.device_unique));
            break;
        case TlvType::TOKEN_CONFIGURATION:
            _token.token_config = 0;
            break;
        case TlvType::RATCHET:
            memset(_token.ratchet, 0, sizeof(_token.ratchet));
            break;
        case TlvType::SIGNATURE_STAGE1:
            memset(_token.signature_stage1, 0, sizeof(_token.signature_stage1));
            break;
        case TlvType::SIGNATURE_STAGE2:
            memset(_token.signature_stage2, 0, sizeof(_token.signature_stage2));
            break;
        default:
            throw MlxTknGeneratorException("Invalid TLV type");
    }
}

void MlxPSCtoken::InitTlvHeader(tokens_layout_psc_debug_token_tlv_header& tlvHeader, TlvType typeTLV)
{
    tlvHeader.tlv_length = GetTLVLength(typeTLV);
    tlvHeader.tlv_type = static_cast<u_int16_t>(typeTLV);
}

void MlxPSCtoken::InitTLV(TlvType typeTLV)
{
    switch (typeTLV)
    {
        case TlvType::TOKEN_IDENTIFIER:
            InitTlvHeader(_token.token_identifier_hdr, TlvType::TOKEN_IDENTIFIER);
            InitTlvValue(TlvType::TOKEN_IDENTIFIER);
            break;
        case TlvType::DEVICE_TYPE:
            InitTlvHeader(_token.device_type_hdr, TlvType::DEVICE_TYPE);
            InitTlvValue(TlvType::DEVICE_TYPE);
            break;
        case TlvType::TOKEN_TYPE:
            InitTlvHeader(_token.token_type_hdr, TlvType::TOKEN_TYPE);
            InitTlvValue(TlvType::TOKEN_TYPE);
            break;
        case TlvType::KEYPAIR_UUID:
            InitTlvHeader(_token.keypair_uuid_hdr, TlvType::KEYPAIR_UUID);
            InitTlvValue(TlvType::KEYPAIR_UUID);
            break;
        case TlvType::PSID:
            InitTlvHeader(_token.psid_hdr, TlvType::PSID);
            InitTlvValue(TlvType::PSID);
            break;
        case TlvType::FW_VERSION:
            InitTlvHeader(_token.fw_version_hdr, TlvType::FW_VERSION);
            InitTlvValue(TlvType::FW_VERSION);
            break;
        case TlvType::DEVICE_UNIQUE:
            InitTlvHeader(_token.device_unique_hdr, TlvType::DEVICE_UNIQUE);
            InitTlvValue(TlvType::DEVICE_UNIQUE);
            break;
        case TlvType::TOKEN_CONFIGURATION:
            InitTlvHeader(_token.token_config_hdr, TlvType::TOKEN_CONFIGURATION);
            InitTlvValue(TlvType::TOKEN_CONFIGURATION);
            break;
        case TlvType::RATCHET:
            InitTlvHeader(_token.ratchet_hdr, TlvType::RATCHET);
            InitTlvValue(TlvType::RATCHET);
            break;
        case TlvType::SIGNATURE_STAGE1:
            InitTlvHeader(_token.signature_stage1_hdr, TlvType::SIGNATURE_STAGE1);
            InitTlvValue(TlvType::SIGNATURE_STAGE1);
            break;
        case TlvType::SIGNATURE_STAGE2:
            InitTlvHeader(_token.signature_stage2_hdr, TlvType::SIGNATURE_STAGE2);
            InitTlvValue(TlvType::SIGNATURE_STAGE2);
            break;
        default:
            throw MlxTknGeneratorException("Invalid TLV type");
    }
}

void MlxPSCtoken::InitToken()
{
    _token.header_identifier = 0x544C5631; // 'TLV1'
    _token.header_version = 0x0001;
    _token.structure_size = 0x2a8c;
    memset(_token.reserved_header, 0, sizeof(_token.reserved_header));

    TlvType tlvTypes[] = {TlvType::TOKEN_IDENTIFIER,
                          TlvType::DEVICE_TYPE,
                          TlvType::TOKEN_TYPE,
                          TlvType::KEYPAIR_UUID,
                          TlvType::PSID,
                          TlvType::FW_VERSION,
                          TlvType::DEVICE_UNIQUE,
                          TlvType::TOKEN_CONFIGURATION,
                          TlvType::RATCHET,
                          TlvType::SIGNATURE_STAGE1,
                          TlvType::SIGNATURE_STAGE2};
    for (TlvType tlvType : tlvTypes)
    {
        InitTLV(tlvType);
    }
}

void MlxPSCtoken::SetKeypairUUID(const u_int32_t* keypairUUID)
{
    u_int8_t keypair_uuid_bytes[16];
    for (int i = 0; i < 4; i++)
    {
        u_int32_t val = __cpu_to_be32(keypairUUID[i]);
        memcpy(&keypair_uuid_bytes[i * 4], &val, sizeof(u_int32_t));
    }
    memcpy(_token.keypair_uuid.data, keypair_uuid_bytes, sizeof(_token.keypair_uuid.data));
}

void MlxPSCtoken::SetPSID(const u_int32_t* psid)
{
    memcpy(_token.psid, psid, sizeof(_token.psid));
}

void MlxPSCtoken::SetFWVersion(u_int32_t fwVersion31_0, u_int32_t fwVersion39_32)
{
    _token.fw_version[0] = fwVersion31_0;
    _token.fw_version[1] = fwVersion39_32;
}

void MlxPSCtoken::SetDeviceUnique(u_int64_t baseMac, const u_int32_t* challenge)
{
    _token.device_unique[0].serial_number[0] = (u_int32_t)(baseMac & 0xFFFFFFFF);
    _token.device_unique[0].serial_number[1] = (u_int32_t)(baseMac >> 32);
    memcpy(_token.device_unique[0].nonce, challenge, sizeof(_token.device_unique[0].nonce));
}

std::vector<std::string> MlxPSCtoken::SplitByComma(const std::string& tokenConfig)
{
    std::vector<std::string> tokenConfigVector;
    std::stringstream configStream(tokenConfig);
    std::string tokenTmp;

    while (std::getline(configStream, tokenTmp, ','))
    {
        if (!tokenTmp.empty())
            tokenConfigVector.push_back(tokenTmp);
    }
    return tokenConfigVector;
}

std::string MlxPSCtoken::FixedTokenConfig(const string& tokenConfig)
{
    string cfgTkn = tokenConfig;
    cfgTkn.erase(0, cfgTkn.find_first_not_of(" \t\n\r"));
    cfgTkn.erase(cfgTkn.find_last_not_of(" \t\n\r") + 1);
    mft_utils::to_lowercase(cfgTkn);
    return cfgTkn;
}

void MlxPSCtoken::SetTokenConfig(const string& tokenConfig)
{
    if (_tokenType == McTokenTypeCRDT)
    {
        string cfgTkn = FixedTokenConfig(tokenConfig);
        if (cfgTkn == "debug_fw" || cfgTkn == "")
        {
            _token.token_config = 0x0;
        }
        else if (cfgTkn == "hci_fw")
        {
            _token.token_config = 0x1;
        }
    }
    else if (_tokenType == McTokenTypeCRCS)
    {
        std::vector<std::string> tokenConfigVector = SplitByComma(tokenConfig);
        _token.token_config = 0x0000;
        for (string cfgTkn : tokenConfigVector)
        {
            cfgTkn.erase(0, cfgTkn.find_first_not_of(" \t\n\r"));
            cfgTkn.erase(cfgTkn.find_last_not_of(" \t\n\r") + 1);
            mft_utils::to_uppercase(cfgTkn);

            if (cfgTkn == "OOBHUB")
            {
                _token.token_config |= (1 << 12); // 0x1000
            }
            else if (cfgTkn == "NCORE")
            {
                _token.token_config |= (1 << 8); // 0x0100
            }
            else if (cfgTkn == "VMOD")
            {
                _token.token_config |= (1 << 4); // 0x0010
            }
            else if (cfgTkn == "PSCFW")
            {
                _token.token_config |= (1 << 0); // 0x0001
            }
            else
            {
                throw MlxTknGeneratorException("Unknown token config: '%s'", cfgTkn.c_str());
            }
        }
    }
    else
    {
        _token.token_config = 0x0;
    }
}

void MlxPSCtoken::SetRatchet(u_int64_t ratchet)
{
    _token.ratchet[0] = (u_int32_t)(ratchet & 0xFFFFFFFF);
    _token.ratchet[1] = (u_int32_t)(ratchet >> 32);
}

void MlxPSCtoken::GetChallengeBasedTokenData(const reg_access_switch_mtcq_reg_ext& challenge, const string& tokenConfig)
{
    SetPSID(challenge.psid);
    SetKeypairUUID(challenge.keypair_uuid);

    SetFWVersion(challenge.fw_version_31_0, challenge.fw_version_39_32);
    SetDeviceUnique(challenge.base_mac, challenge.challenge);
    SetRatchet(challenge.token_ratchet);
    SetTokenConfig(tokenConfig);
    _nonceVersion = challenge.challenge_version;
}

std::vector<std::pair<std::string, std::string>> MlxPSCtoken::LoadFromParams()
{
    vector<pair<string, string>> tlvs;

    tlvs.push_back(make_pair(TlvTypeToStr(TlvType::DEVICE_TYPE), GetDeviceTypeString()));
    tlvs.push_back(make_pair(TlvTypeToStr(TlvType::TOKEN_TYPE), MlxCfgToken::getTokenString(_tokenType)));
    tlvs.push_back(make_pair(TlvTypeToStr(TlvType::KEYPAIR_UUID), GetUUIDString()));
    tlvs.push_back(make_pair(TlvTypeToStr(TlvType::PSID), GetPSIDString()));
    tlvs.push_back(make_pair(TlvTypeToStr(TlvType::FW_VERSION), GetFWVersionString()));

    tlvs.push_back(make_pair(TlvTypeToStr(TlvType::DEVICE_UNIQUE), PSC_TLV_TYPE_START));
    tlvs.push_back(make_pair(VALID_ENTRIES_KEY, std::to_string(GetValidEntries())));
    tlvs.push_back(make_pair(NONCE_VERSION_KEY, GetNonceVersionString()));

    for (int i = 0; i < GetValidEntries(); i++)
    {
        // Device unique ID (serial number)
        stringstream serialStream;
        serialStream << std::hex << std::setw(8) << std::setfill('0') << _token.device_unique[i].serial_number[1]
                     << std::setw(8) << std::setfill('0') << _token.device_unique[i].serial_number[0];
        tlvs.push_back(make_pair(DEVICE_UNIQUE_ID_PREFIX + std::to_string(i), serialStream.str()));

        // Nonce
        stringstream nonceStream;
        for (int j = 0; j < 8; j++)
        {
            nonceStream << std::hex << std::setw(8) << std::setfill('0') << _token.device_unique[i].nonce[j];
        }
        tlvs.push_back(make_pair(NONCE_PREFIX + std::to_string(i), nonceStream.str()));
    }
    tlvs.push_back(make_pair(TlvTypeToStr(TlvType::DEVICE_UNIQUE), PSC_TLV_TYPE_END));

    // Format token_config as hexadecimal string (without 0x prefix)
    stringstream tokenConfigStream;
    tokenConfigStream << std::hex << _token.token_config;
    tlvs.push_back(make_pair(TlvTypeToStr(TlvType::TOKEN_CONFIGURATION), tokenConfigStream.str()));
    tlvs.push_back(make_pair(TlvTypeToStr(TlvType::RATCHET), GetRatchetStr()));

    return tlvs;
}

std::string MlxPSCtoken::ToXML(const std::vector<std::pair<std::string, std::string>>& tlvs)
{
    string dbName = "";
    GenericCommander commander(nullptr, dbName);
    string tokenXML("");
    commander.genXMLPSCTemplateAux(tlvs, tokenXML);
    return tokenXML;
}

void MlxPSCtoken::SaveToXMLFile(const std::string& filePath,
                                const std::vector<std::pair<std::string, std::string>>& tlvs)
{
    ofstream out(filePath);
    if (!out.is_open())
    {
        throw MlxTknGeneratorException("Failed to open file: %s", filePath.c_str());
    }
    out << ToXML(tlvs);
    out.close();
}

void MlxPSCtoken::SetPSIDFromMap(const string& psid)
{
    memset(_token.psid, 0, sizeof(_token.psid));

    size_t len = psid.length();
    size_t maxLen = sizeof(_token.psid);

    for (size_t i = 0; i < len && i < maxLen; i++)
    {
        size_t dwordIdx = i / 4;
        size_t byteIdx = i % 4;

        u_int32_t currentDword = __be32_to_cpu(_token.psid[dwordIdx]);
        char* bytes = reinterpret_cast<char*>(&currentDword);
        bytes[byteIdx] = psid[i];
        _token.psid[dwordIdx] = __cpu_to_be32(currentDword);
    }
}

void MlxPSCtoken::SetFWVersionFromMap(const string& fwVersion)
{
    if (_deviceType == DeviceType::NIC || _deviceType == DeviceType::CX7 || _deviceType == DeviceType::SOC)
    {
        int major, minor, patch;
        if (sscanf(fwVersion.c_str(), "%d.%d.%d", &major, &minor, &patch) == 3)
        {
            _token.fw_version[0] = (major << 24) | (minor << 16) | patch;
            _token.fw_version[1] = 0;
        }
    }
    else
    {
        unsigned int major, minor, patch;
        if (sscanf(fwVersion.c_str(), "%x.%x.%x", &major, &minor, &patch) == 3)
        {
            _token.fw_version[0] = (major << 16) | minor;
            _token.fw_version[1] = patch;
        }
    }
}

void MlxPSCtoken::SetKeypairUUIDFromMap(const string& keypairUUID)
{
    memset(_token.keypair_uuid.data, 0, sizeof(_token.keypair_uuid.data));

    size_t strLen = keypairUUID.length();
    size_t maxBytes = sizeof(_token.keypair_uuid.data);
    size_t numBytes = std::min(strLen / 2, maxBytes);

    for (size_t i = 0; i < numBytes; i++)
    {
        string byteStr = keypairUUID.substr(i * 2, 2);
        _token.keypair_uuid.data[i] = static_cast<u_int8_t>(std::stoul(byteStr, nullptr, 16));
    }
}

void MlxPSCtoken::SetTokenConfigFromMap(const string& tokenConfig)
{
    // Parse as hexadecimal (without 0x prefix)
    _token.token_config = std::stoul(tokenConfig, nullptr, 16);
}

string MlxPSCtoken::FindValueInDeviceUnique(const string& value, const string& key)
{
    string result;
    size_t pos = value.find(key + "=");
    if (pos != string::npos)
    {
        pos += key.length() + 1;
        size_t end = value.find(',', pos);
        result = value.substr(pos, end == string::npos ? string::npos : end - pos);
    }
    return result;
}

void MlxPSCtoken::SetDeviceUniqueFromMap(const map<string, string>& tokenData)
{
    auto it = tokenData.find(TlvTypeToStr(TlvType::DEVICE_UNIQUE));
    if (it == tokenData.end())
        return;

    const string& value = it->second;

    string nonceVer = FindValueInDeviceUnique(value, NONCE_VERSION_KEY);
    if (!nonceVer.empty())
        _nonceVersion = std::stoul(nonceVer, nullptr, 0);

    string validEntriesStr = FindValueInDeviceUnique(value, VALID_ENTRIES_KEY);
    _validEntries = validEntriesStr.empty() ? 1 : std::stoi(validEntriesStr);

    for (int i = 0; i < _validEntries; i++)
    {
        string ecid = FindValueInDeviceUnique(value, DEVICE_UNIQUE_ID_PREFIX + std::to_string(i));
        if (ecid.length() >= 16)
        {
            _token.device_unique[i].serial_number[0] = std::stoul(ecid.substr(0, 8), nullptr, 16);
            _token.device_unique[i].serial_number[1] = std::stoul(ecid.substr(8, 8), nullptr, 16);
        }

        string nonce = FindValueInDeviceUnique(value, NONCE_PREFIX + std::to_string(i));
        if (nonce.length() >= 64)
            for (int j = 0; j < 8; j++)
                _token.device_unique[i].nonce[j] = std::stoul(nonce.substr(j * 8, 8), nullptr, 16);
    }
}

void MlxPSCtoken::AddDeviceUnique(const u_int64_t& deviceUnique)
{
    _token.device_unique[_validEntries].serial_number[0] = deviceUnique;
    _token.device_unique[_validEntries].serial_number[1] = deviceUnique >> 32;
}

void MlxPSCtoken::AddNonce(const u_int32_t* nonce)
{
    if (nonce != nullptr)
    {
        memcpy(_token.device_unique[_validEntries].nonce, nonce, sizeof(_token.device_unique[_validEntries].nonce));
    }
}

void MlxPSCtoken::UpdateValidEntries()
{
    _validEntries++;
}

void MlxPSCtoken::ValidatePSID(const string& psid)
{
    if (psid != GetPSIDString())
    {
        throw MlxTknGeneratorException("PSID mismatch");
    }
}

void MlxPSCtoken::ValidateDeviceType(DeviceType deviceType)
{
    if (deviceType != GetDeviceTypeEnum())
    {
        throw MlxTknGeneratorException("Device type mismatch");
    }
}

void MlxPSCtoken::ValidateTokenType(MlxCfgTokenType tokenType)
{
    if (tokenType != GetTokenTypeEnum())
    {
        throw MlxTknGeneratorException("Token type mismatch");
    }
}

void MlxPSCtoken::ValidateFWVersion(const string& fwVersion)
{
    if (fwVersion != GetFWVersionString())
    {
        throw MlxTknGeneratorException("FW version mismatch");
    }
}

void MlxPSCtoken::ValidateTokenConfig(const string& tokenConfig)
{
    if (tokenConfig != GetTokenConfigString())
    {
        throw MlxTknGeneratorException("Token config mismatch");
    }
}

void MlxPSCtoken::ValidateKeypairUUID(const string& keypairUUID)
{
    if (keypairUUID != GetUUIDString())
    {
        throw MlxTknGeneratorException("Keypair UUID mismatch");
    }
}

void MlxPSCtoken::ValidateValidEntries(const MlxPSCtoken& token)
{
    ValidateDeviceType(token.GetDeviceTypeEnum());
    ValidateTokenType(token.GetTokenTypeEnum());
    ValidatePSID(token.GetPSIDString());
    ValidateKeypairUUID(token.GetUUIDString());
    ValidateFWVersion(token.GetFWVersionString());
    ValidateTokenConfig(token.GetTokenConfigString());
}

void MlxPSCtoken::Aggregate(const MlxPSCtoken& token)
{
    ValidateValidEntries(token);
    AddDeviceUnique(token.GetDeviceUnique());
    AddNonce(token.GetNonce());
    UpdateValidEntries();
}

void MlxPSCtoken::LoadFromXMLFile(string xmlContent, string filePath)
{
    map<string, string> tokenData;
    string dbName = "";
    GenericCommander commander(nullptr, dbName);
    commander.XML2MapPSCToken(xmlContent, tokenData);
    if (tokenData.empty())
    {
        throw MlxTknGeneratorException("Failed to parse the XML document: %s", filePath.c_str());
    }
    LoadParamsFromMap(tokenData);
}

void MlxPSCtoken::LoadParamsFromMap(const std::map<std::string, std::string>& tokenData)
{
    for (const auto& entry : tokenData)
    {
        TlvType key = StrToTlvType(entry.first);
        const std::string& value = entry.second;
        switch (key)
        {
            case TlvType::PSID:
                SetPSIDFromMap(value);
                break;
            case TlvType::FW_VERSION:
                SetFWVersionFromMap(value);
                break;
            case TlvType::DEVICE_UNIQUE:
                SetDeviceUniqueFromMap(tokenData);
                break;
            case TlvType::TOKEN_CONFIGURATION:
                SetTokenConfigFromMap(value);
                break;
            case TlvType::KEYPAIR_UUID:
                SetKeypairUUIDFromMap(value);
                break;
            default:
                break;
        }
    }
}

MlxPSCtoken::MlxPSCtoken(DeviceType deviceType, MlxCfgTokenType tokenType) :
    _deviceType(deviceType), _tokenType(tokenType), _validEntries(0)
{
    InitToken();
}

u_int64_t MlxPSCtoken::GetDeviceUnique() const
{
    if (_validEntries <= 0)
    {
        return 0;
    }
    u_int64_t deviceUnique = _token.device_unique[_validEntries - 1].serial_number[0];
    deviceUnique |= (static_cast<u_int64_t>(_token.device_unique[_validEntries - 1].serial_number[1]) << 32);
    return deviceUnique;
}

const u_int32_t* MlxPSCtoken::GetNonce() const
{
    if (_validEntries <= 0)
    {
        return nullptr;
    }
    return _token.device_unique[_validEntries - 1].nonce;
}

void MlxPSCtoken::SaveToXMLFile(const std::string& filePath)
{
    std::vector<std::pair<std::string, std::string>> tlvs = LoadFromParams();
    SaveToXMLFile(filePath, tlvs);
}

MlxCfgTokenType MlxPSCtoken::GetTokenTypeFromXML(const std::string& xmlContent)
{
    map<string, string> tokenData;
    string dbName = "";
    GenericCommander commander(nullptr, dbName);
    commander.XML2MapPSCToken(xmlContent, tokenData);
    return MlxCfgToken::GetTokenType(tokenData[(TlvTypeToStr(TlvType::TOKEN_TYPE))]);
}

DeviceType MlxPSCtoken::GetDeviceTypeFromXML(const std::string& xmlContent)
{
    map<string, string> tokenData;
    string dbName = "";
    GenericCommander commander(nullptr, dbName);
    commander.XML2MapPSCToken(xmlContent, tokenData);

    auto it = tokenData.find(TlvTypeToStr(TlvType::DEVICE_TYPE));
    if (it != tokenData.end())
    {
        return StrToDeviceType(it->second);
    }

    throw MlxTknGeneratorException("DEVICE_TYPE not found in XML");
}

/********************************************************************************************************************************/
/*                                              MlxTokenFactory */
/********************************************************************************************************************************/

shared_ptr<MlxPSCtoken> MlxPSCtokenFactory::CreatePSCtoken(MlxCfgTokenType tokenType, DeviceType deviceType)
{
    return shared_ptr<MlxPSCtoken>(new MlxPSCtoken(deviceType, tokenType));
}