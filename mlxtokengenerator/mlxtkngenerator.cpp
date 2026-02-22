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

#include <exception>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>
#include "mlxfwops/lib/mlxfwops_com.h"
#include "mlxfwops/lib/fw_ops.h"
#include "mlxconfig/mlxcfg_utils.h"
#include "mlxconfig/mlxcfg_tlv.h"
#include "mlxconfig/mlxcfg_commander.h"
#include "mlxconfig/mlxcfg_generic_commander.h"
#include "mlxtkngenerator.h"
#include "mlxtkngenerator_utils.h"
#include <tools_layouts/reg_access_switch_layouts.h>
#include <tools_layouts/tokens_layout_layouts.h>

#ifdef ENABLE_MST_DEV_I2C
#include "mtcr_ul/mtcr_ul_com.h"
#endif

#include <dirent.h>

#define INDENT  "    "
#define INDENT2 INDENT INDENT
#define INDENT3 "\t\t"

const string MlxTknGenerator::DEVICE_FLAG = "device";
const char   MlxTknGenerator::DEVICE_FLAG_SHORT = 'd';
const string MlxTknGenerator::HELP_FLAG = "help";
const char   MlxTknGenerator::HELP_FLAG_SHORT = 'h';
const string MlxTknGenerator::VERSION_FLAG = "version";
const char   MlxTknGenerator::VERSION_FLAG_SHORT = 'v';
const string MlxTknGenerator::DEVICE_TYPE_FLAG = "device_type";
const char   MlxTknGenerator::DEVICE_TYPE_FLAG_SHORT = 't';
const string MlxTknGenerator::TOKEN_TYPE_FLAG = "token_type";
const char   MlxTknGenerator::TOKEN_TYPE_FLAG_SHORT = 'k';
const string MlxTknGenerator::NESTED_TOKEN_FLAG = "nested_token";
const char   MlxTknGenerator::NESTED_TOKEN_FLAG_SHORT = 'n';
const string MlxTknGenerator::DEBUG_FW_FILE_FLAG = "debug_fw";
const char   MlxTknGenerator::DEBUG_FW_FILE_FLAG_SHORT = 'f';
const string MlxTknGenerator::NESTED_DEBUG_FW_FILE_FLAG = "nested_debug_fw";
const char   MlxTknGenerator::NESTED_DEBUG_FW_FILE_FLAG_SHORT = 'e';
const string MlxTknGenerator::OUTPUT_FILE_FLAG = "output_file";
const char   MlxTknGenerator::OUTPUT_FILE_FLAG_SHORT = 'o';
const string MlxTknGenerator::TOKENS_DIR_FLAG = "tokens_dir";
const char   MlxTknGenerator::TOKENS_DIR_FLAG_SHORT = 'p';
const string MlxTknGenerator::CHALLENGE_BLOB_FLAG = "blob";
const char   MlxTknGenerator::CHALLENGE_BLOB_FLAG_SHORT = 'b';
const string MlxTknGenerator::SECONDARY_ADDR_FLAG = "i2c_secondary";
const char   MlxTknGenerator::SECONDARY_ADDR_FLAG_SHORT = 's';

vector < string > GetListOfFiles(string dirPath)
{
#ifdef __WIN__
    const string seperator = "\\";
#else
    const string seperator = "/";
#endif
    const string CWD = ".";
    const string PARENT = "..";
    vector < string > files;
    DIR          * dir;
    struct dirent* ent;

    if ((dir = opendir(dirPath.c_str())) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            if ((string(ent->d_name) != CWD) && (string(ent->d_name) != PARENT)) {
                files.push_back(dirPath + seperator + ent->d_name);
            }
        }
        closedir(dir);
    } else {
        throw MlxTknGeneratorException("Failed to process tokens: %s.", strerror(errno));
    }
    return files;
}

static void printFlagLine(string flag_l, char flag_s, string param, string desc)
{
    string shortFlag(1, flag_s);
    string flags = "-" + shortFlag + "|--" + flag_l + (param.length() ? " <" + param + ">" : "");

    printf(INDENT2 "%-40s", flags.c_str());
    printf(INDENT3 ": %s\n", desc.c_str());
}

string DWordToAscii(u_int32_t dword)
{
    u_int8_t* byteArray = (u_int8_t*)&dword;
    string    str;

    for (int j = 3; j >= 0; --j) {
        if (byteArray[j] == 0) {
            continue;
        }
        str.push_back(char(byteArray[j]));
    }

    return str;
}

string MacToString(u_int64_t dDword)
{
    std::stringstream ss;
    u_int32_t         mac[2];

    mac[0] = dDword & 0xffffffff;
    mac[1] = (dDword >> 32) & 0xffffffff;

    ss << std::hex << std::setfill('0');
    ss << std::setw(8) << mac[1];
    ss << std::setw(8) << mac[0];

    return ss.str();
}

string DWordArrayToString(u_int32_t arr[], u_int32_t length)
{
    ostringstream ss;

    ss << std::hex << std::setfill('0');
    for (u_int32_t i = 0; i < length; ++i) {
        ss << std::setw(8) << static_cast < unsigned > (arr[i]);
    }
    return ss.str();
}

u_int64_t FlipDWords(u_int64_t num)
{
    return ((num >> 32) & 0xffffffff) | ((num & 0xffffffff) << 32);
}

const map < string, MlxTknGenerator::MlxTknGeneratorCmd > MlxTknGenerator::_cmdStringToEnum = {
    {"generate_token", GenerateToken},
    {"aggregate_tokens", AggregateTokens}
};

MlxTknGenerator::MlxTknGenerator() :
    CommandLineRequester("mlxtkngenerator OPTIONS"),
    _cmdParser("mlxtkngenerator"),
    _device(),
    _deviceType(UNSUPPORTED_DEVICE),
    _tokenType(McTokenTypeUnknown),
    _isNestedToken(false),
    _outputFile(),
    _tokensDir(),
    _command(Unknown),
    _i2cSecondaryAddr(0)
{
    InitCmdParser();
}

MlxTknGenerator::~MlxTknGenerator()
{
}

string MlxTknGenerator::GetDebugFwVersion(string filePath)
{
    char          errBuff[1024];
    fw_info_t     fwQueryResult;
    string        fwVersion;
    FwOperations* ops =
        FwOperations::FwOperationsCreate((void*)filePath.c_str(), nullptr, nullptr, FHT_FW_FILE, errBuff, 1024);

    if (ops == nullptr) {
        throw MlxTknGeneratorException("Failed to open the image.");
    }
    if (!ops->FwQuery(&fwQueryResult, false, false)) {
        throw MlxTknGeneratorException("Failed to query the image.");
    }

    FwVersion image_version = FwOperations::createFwVersion(&fwQueryResult.fw_info);

    fwVersion = image_version.get_primary_version("%x%x%04x", false);

    return fwVersion;
}

vector < TLVParamsData >
MlxTknGenerator::GetTokenDataFromQuery(string device, MlxCfgTokenType tokenType, Device_Type deviceType)
{
    MLX_TOKEN_DPRINTF(("%s.\n", __FUNCTION__));
    char errBuff[1024];

    vector < TLVParamsData > data;
    std::stringstream stream;
    string            fwVersion;
    string            debugFwVersion;
    fw_info_t         fwQueryResult;

    unique_ptr < FwOperations > ops = unique_ptr < FwOperations > (
        FwOperations::FwOperationsCreate((void*)device.c_str(), nullptr, nullptr, FHT_MST_DEV, errBuff, 1024));
    if (ops == nullptr) {
        throw MlxTknGeneratorException("Failed to open the device.");
    }
    if (!ops->FwQuery(&fwQueryResult, false, false)) {
        throw MlxTknGeneratorException("Failed to query the device.");
    }

    data.push_back(TLVParamsData("file_applicable_to", "psid", fwQueryResult.fw_info.psid));

    /* if (fwQueryResult.fs3_info.fs3_uids_info.guid_format == IMAGE_LAYOUTS_UIDS) */
    /* { */
    stream << std::hex << std::setfill('0') << std::setw(16)
           << fwQueryResult.fs3_info.fs3_uids_info.image_layout_uids.base_mac.uid;
    /* } */
    /* else */
    /* { */
    /*     stream << std::hex << std::setfill('0') << std::setw(16) */
    /*            << fwQueryResult.fs3_info.fs3_uids_info.cib_uids.macs[0].uid; */
    /* } */
    data.push_back(TLVParamsData("file_mac_addr_list", "mac_address", stream.str()));
    stream.str("");

    FwVersion image_version = FwOperations::createFwVersion(&fwQueryResult.fw_info);
    FwVersion running_version = FwOperations::createRunningFwVersion(&fwQueryResult.fw_info);

    if (image_version.is_set()) {
        if ((image_version != running_version) && running_version.is_set()) {
            cout << "-W- Pending image found on the device, installing debug fw will override it." << endl;
            fwVersion = running_version.get_primary_version("%x%x%04x", false);
        } else {
            fwVersion = image_version.get_primary_version("%x%x%04x", false);
        }
    } else {
        throw MlxTknGeneratorException("Failed to get FW Version from the device.");
    }

    if (tokenType == McTokenTypeDBG) {
        debugFwVersion = GetDebugFwVersion(_debugFwFile);
    }

    if (deviceType == Switch) {
        if (tokenType == McTokenTypeCS) {
            data.push_back(TLVParamsData("file_cs_token_id", "running_version_39_32", fwVersion.substr(0, 2)));
            data.push_back(TLVParamsData("file_cs_token_id", "running_version_31_0", fwVersion.substr(2, 8)));
        } else {
            data.push_back(TLVParamsData("file_dbg_fw_token_id", "running_version_39_32", fwVersion.substr(0, 2)));
            data.push_back(TLVParamsData("file_dbg_fw_token_id", "running_version_31_0", fwVersion.substr(2, 8)));
            data.push_back(
                TLVParamsData("file_dbg_fw_token_id", "debug_version_39_32", debugFwVersion.substr(0, 2)));
            data.push_back(TLVParamsData("file_dbg_fw_token_id", "debug_version_31_0", debugFwVersion.substr(2, 8)));
        }
    } else {
        if (tokenType == McTokenTypeCS) {
            data.push_back(TLVParamsData("file_cs_token_id", "running_version", fwVersion));
        } else {
            data.push_back(TLVParamsData("file_dbg_fw_token_id", "running_version", fwVersion));
            data.push_back(TLVParamsData("file_dbg_fw_token_id", "debug_version", debugFwVersion));
        }
    }

    return data;
}

vector < TLVParamsData > MlxTknGenerator::GetRemoteTokenData(struct reg_access_switch_mtcq_reg_ext challenge,
                                                             MlxCfgTokenType tokenType,
                                                             string debugFwVersion)
{
    vector < TLVParamsData > data;
    std::stringstream stream;
    string            tlvConfName;

    stream << DWordToAscii(challenge.psid[0]) << DWordToAscii(challenge.psid[1]) << DWordToAscii(challenge.psid[2])
           << DWordToAscii(challenge.psid[3]);
    data.push_back(TLVParamsData("file_applicable_to", "psid", stream.str()));
    stream.str("");

    stream << MacToString(challenge.base_mac);
    data.push_back(TLVParamsData("file_mac_addr_list", "mac_address", stream.str()));
    stream.str("");

    if (tokenType == McTokenTypeRMCS) {
        tlvConfName = "file_rmcs_token_id";
        stream << std::hex << (short)challenge.fw_version_39_32;
        data.push_back(TLVParamsData(tlvConfName, "running_version_39_32", stream.str()));
        stream.str("");
        stream << std::hex << challenge.fw_version_31_0;
        data.push_back(TLVParamsData(tlvConfName, "running_version_31_0", stream.str()));
        stream.str("");
        stream << std::hex << challenge.session_id;
        data.push_back(TLVParamsData(tlvConfName, "session_id", stream.str()));
        stream.str("");
    } else {
        tlvConfName = "file_rmdt_token_id";
        stream << std::hex << (short)challenge.fw_version_39_32;
        data.push_back(TLVParamsData(tlvConfName, "running_version_39_32", stream.str()));
        stream.str("");
        stream << std::hex << challenge.fw_version_31_0;
        data.push_back(TLVParamsData(tlvConfName, "running_version_31_0", stream.str()));
        stream.str("");
        data.push_back(TLVParamsData(tlvConfName, "debug_version_39_32", debugFwVersion.substr(0, 2)));
        data.push_back(TLVParamsData(tlvConfName, "debug_version_31_0", debugFwVersion.substr(2, 8)));
    }

    stream << DWordArrayToString(challenge.source_address, 4);
    data.push_back(TLVParamsData(tlvConfName, "source_address", stream.str()));
    stream.str("");

    stream << DWordArrayToString(challenge.challenge, 8);
    data.push_back(TLVParamsData(tlvConfName, "challenge", stream.str()));
    stream.str("");

    return data;
}

vector < TLVParamsData > MlxTknGenerator::GetChallengeBasedTokenData(struct reg_access_switch_mtcq_reg_ext challenge,
                                                                     MlxCfgTokenType tokenType,
                                                                     string debugFwVersion)
{
    vector < TLVParamsData > data;
    std::stringstream stream;
    string            tlvConfName;

    stream << DWordToAscii(challenge.psid[0]) << DWordToAscii(challenge.psid[1]) << DWordToAscii(challenge.psid[2])
           << DWordToAscii(challenge.psid[3]);
    data.push_back(TLVParamsData("file_applicable_to", "psid", stream.str()));
    stream.str("");

    if (tokenType == McTokenTypeCRCS) {
        tlvConfName = "file_cs_token_id";
        if (_deviceType == HCA) {
            stream << std::hex << challenge.fw_version_31_0;
            data.push_back(TLVParamsData(tlvConfName, "running_version", stream.str()));
            stream.str("");
        } else {
            stream << std::hex << (short)challenge.fw_version_39_32;
            data.push_back(TLVParamsData(tlvConfName, "running_version_39_32", stream.str()));
            stream.str("");
            stream << std::hex << challenge.fw_version_31_0;
            data.push_back(TLVParamsData(tlvConfName, "running_version_31_0", stream.str()));
            stream.str("");
        }
    } else {
        tlvConfName = "file_dbg_fw_token_id";
        if (_deviceType == HCA) {
            stream << std::hex << challenge.fw_version_31_0;
            data.push_back(TLVParamsData(tlvConfName, "running_version", stream.str()));
            data.push_back(TLVParamsData(tlvConfName, "debug_version", debugFwVersion));
            stream.str("");
        } else {
            stream << std::hex << (short)challenge.fw_version_39_32;
            data.push_back(TLVParamsData(tlvConfName, "running_version_39_32", stream.str()));
            stream.str("");
            stream << std::hex << challenge.fw_version_31_0;
            data.push_back(TLVParamsData(tlvConfName, "running_version_31_0", stream.str()));
            stream.str("");
            data.push_back(TLVParamsData(tlvConfName, "debug_version_39_32", debugFwVersion.substr(0, 2)));
            data.push_back(TLVParamsData(tlvConfName, "debug_version_31_0", debugFwVersion.substr(2, 8)));
        }
    }

    stream << MacToString(challenge.base_mac);
    data.push_back(TLVParamsData("file_device_unique", "device_unique_id0", stream.str()));
    stream.str("");

    stream << DWordArrayToString(challenge.challenge, 8);
    data.push_back(TLVParamsData("file_device_unique", "nonce0", stream.str()));
    stream.str("");

    data.push_back(TLVParamsData("file_device_unique", "valid_entries", "1"));

    stream << DWordArrayToString(challenge.keypair_uuid, 4);
    data.push_back(TLVParamsData("file_signature", "keypair_uuid", stream.str()));
    stream.str("");

    data.push_back(TLVParamsData("file_signature", "signature_uuid", "00000000"));
    data.push_back(TLVParamsData("file_signature", "signature", "00000000"));

    return data;
}

vector < TLVParamsData > MlxTknGenerator::GetTokenDataFromChallenge(mfile * mf,
                                                                    MlxCfgTokenType tokenType,
                                                                    bool isNestedToken)
{
    MLX_TOKEN_DPRINTF(("%s.\n", __FUNCTION__));
    MlxCfgToken mlxCfgToken(mf);
    vector < TLVParamsData > data;
    std::stringstream stream;
    string            debugFwVersion;
    string            debugFwVersionNested;

    if ((tokenType == McTokenTypeCRDT) || (tokenType == McTokenTypeRMDT)) {
        debugFwVersion = GetDebugFwVersion(_debugFwFile);
        if (isNestedToken) {
            debugFwVersionNested = GetDebugFwVersion(_debugFwNestedFile);
        }
    }

    struct reg_access_switch_mtcq_reg_ext challenge = mlxCfgToken.GetChallengeFromSwitchOrHCA(tokenType);

    if ((tokenType == McTokenTypeRMCS) || (tokenType == McTokenTypeRMDT)) {
        data = GetRemoteTokenData(challenge, tokenType, debugFwVersion);
    } else {
        data = GetChallengeBasedTokenData(challenge, tokenType, debugFwVersion);
    }

    return data;
}

vector < TLVParamsData >
MlxTknGenerator::GetDataForToken(MlxCfgTokenType tokenType, Device_Type deviceType, bool isNestedToken)
{
#ifdef ENABLE_MST_DEV_I2C
    if (_i2cSecondaryAddr != -1) {
        set_force_i2c_address(_i2cSecondaryAddr);
    }
#endif
    mfile* mf = mopen_adv(_device.c_str(), (MType)(MST_DEFAULT | MST_CABLE));

    if (mf == NULL) {
        throw MlxTknGeneratorException("Failed to open the device.");
    }
    ValidateDeviceType(mf, _deviceType);

    vector < TLVParamsData > tlvsConfsData;
    if ((tokenType == McTokenTypeCS) || (tokenType == McTokenTypeDBG)) {
        tlvsConfsData = GetTokenDataFromQuery(_device, tokenType, deviceType);
    } else {
        tlvsConfsData = GetTokenDataFromChallenge(mf, tokenType, isNestedToken);
    }
    mclose(mf);
    return tlvsConfsData;
}

bool MlxTknGenerator::IsGetMeasurementIndex50(const vector < u_int8_t >& tokenData)
{
    bool          isGetMeasurementIndex50 = false;
    size_t        nbtrOffset = 0x24;
    const uint8_t nbtr[4] = {'N', 'B', 'T', 'R'};

    if ((tokenData.size() >= nbtrOffset + 4) && (std::memcmp(&tokenData[nbtrOffset], nbtr, 4) == 0)) {
        isGetMeasurementIndex50 = true;
    }
    return isGetMeasurementIndex50;
}

void MlxTknGenerator::FromGetMeasurementIndex50ToChallenge(
    struct tokens_layout_get_measurment_index_50& getMeasurementIndex50,
    struct reg_access_switch_mtcq_reg_ext&        challenge)
{
    std::memcpy(challenge.psid, getMeasurementIndex50.psid, sizeof(challenge.psid));

    challenge.base_mac = ((u_int64_t)getMeasurementIndex50.ecid[0] << 32) | getMeasurementIndex50.ecid[1];

    std::memcpy(challenge.challenge, getMeasurementIndex50.nonce, sizeof(challenge.challenge));

    for (int i = 0; i < 4; i++) {
        challenge.keypair_uuid[i] = __be32_to_cpu(((u_int32_t*)getMeasurementIndex50.keypair_uuid.data)[i]);
    }

    challenge.fw_version_31_0 = getMeasurementIndex50.fw_version[1];
    challenge.fw_version_39_32 = getMeasurementIndex50.fw_version[0];
}

void MlxTknGenerator::ValidateNewTlvType(u_int16_t actual, u_int16_t expected, const string& fieldName)
{
    if (__be16_to_cpu(actual) != expected) {
        throw MlxTknGeneratorException(("Invalid " + fieldName).c_str());
    }
}

/* This function will be removed once support for the new token infrastructure is added */
void MlxTknGenerator::IsValidGetMeasurementIndex50(
    const struct tokens_layout_get_measurment_index_50& getMeasurementIndex50)
{
    /* Validate header identifier */
    if (getMeasurementIndex50.header_identifier != 0x544c5631) {
        throw MlxTknGeneratorException("Invalid header identifier");
    }

    /* Validate header version */
    if (__be32_to_cpu(getMeasurementIndex50.header_version) != 0x1) {
        throw MlxTknGeneratorException("Invalid header version");
    }

    /* Validate TLV headers */
    ValidateNewTlvType(getMeasurementIndex50.token_identifier_hdr.tlv_type, 0x8, "token identifier");
    ValidateNewTlvType(getMeasurementIndex50.device_type_hdr.tlv_type, 0x1, "device type");
    ValidateNewTlvType(getMeasurementIndex50.status_hdr.tlv_type, 0x000D, "status");
    ValidateNewTlvType(getMeasurementIndex50.keypair_uuid_hdr.tlv_type, 0x4400, "keypair uuid");
    ValidateNewTlvType(getMeasurementIndex50.ecid_hdr.tlv_type, 0x0003, "ecid");
    ValidateNewTlvType(getMeasurementIndex50.psid_hdr.tlv_type, 0x4401, "psid");
    ValidateNewTlvType(getMeasurementIndex50.fw_version_hdr.tlv_type, 0x0005, "fw version");
    ValidateNewTlvType(getMeasurementIndex50.nonce_hdr.tlv_type, 0x0002, "nonce");
    ValidateNewTlvType(getMeasurementIndex50.ratchet_hdr.tlv_type, 0x0011, "ratchet");
}

vector < TLVParamsData > MlxTknGenerator::GetDataForToken(MlxCfgTokenType tokenType, string blobFile)
{
    /* Challenge data taken from given blob file */
    vector < u_int8_t > tokenData = ReadFromFile(blobFile);
    struct reg_access_switch_mtcq_reg_ext challenge;
    memset(&challenge, 0, sizeof(struct reg_access_switch_mtcq_reg_ext));
    if (IsGetMeasurementIndex50(tokenData)) {
        struct tokens_layout_get_measurment_index_50 getMeasurementIndex50;
        tokens_layout_get_measurment_index_50_unpack(&getMeasurementIndex50, tokenData.data());
        IsValidGetMeasurementIndex50(getMeasurementIndex50);
        FromGetMeasurementIndex50ToChallenge(getMeasurementIndex50, challenge);
    } else {
        reg_access_switch_mtcq_reg_ext_unpack(&challenge, tokenData.data());
    }

    string debugFwVersion;

    if (tokenType == McTokenTypeCRDT) {
        debugFwVersion = GetDebugFwVersion(_debugFwFile);
    }

    vector < TLVParamsData > tlvsConfsData = GetChallengeBasedTokenData(challenge, tokenType, debugFwVersion);
    return tlvsConfsData;
}

void MlxTknGenerator::GenerateTokenXML()
{
    MLX_TOKEN_DPRINTF(("%s.\n", __FUNCTION__));
    vector < string > tlvs;
    vector < TLVConf * > tlvsConfs;
    string tokenXml;

    vector < TLVParamsData > tlvsConfsData;

    try
    {
        if (!_blobFile.empty()) {
            tlvsConfsData = GetDataForToken(_tokenType, _blobFile);
        } else {
            tlvsConfsData = GetDataForToken(_tokenType, _deviceType, _isNestedToken);

            if (_isNestedToken) {
                vector < TLVParamsData > tlvsConfsDataNested;
                shared_ptr < MlxToken > nestedToken =
                    MlxTokenFactory::CreateToken(_tokenType, Device_Type::Retimer); /* ArcusE type */

                while (!tlvsConfsData.empty() && tlvsConfsData.back()._isFromNested) {
                    tlvsConfsDataNested.push_back(tlvsConfsData.back());
                    tlvsConfsData.pop_back();
                }

                nestedToken->LoadFromParams(tlvsConfsDataNested);
                nestedToken->SaveToXMLFile(_outputFile + ".nested.xml");
            }
        }
        shared_ptr < MlxToken > token = MlxTokenFactory::CreateToken(_tokenType, _deviceType);
        token->LoadFromParams(tlvsConfsData);
        token->SaveToXMLFile(_outputFile);
    }
    catch(MlxcfgException & e)
    {
        throw MlxTknGeneratorException(e._err.c_str());
    }
}

void MlxTknGenerator::AggregateTokensXML()
{
    MLX_TOKEN_DPRINTF(("%s.\n", __FUNCTION__));
    vector < string > tokensXML = GetListOfFiles(_tokensDir);
    shared_ptr < MlxToken > token = MlxTokenFactory::CreateToken(_tokenType, _deviceType);
    shared_ptr < MlxToken > tokenForAggregation = MlxTokenFactory::CreateToken(_tokenType, _deviceType);

    if (tokensXML.empty()) {
        throw MlxTknGeneratorException("Given tokens directory is empty.");
    }

    token->LoadFromXMLFile(tokensXML.back());
    tokensXML.pop_back();

    for (auto file : tokensXML) {
        tokenForAggregation->LoadFromXMLFile(file);
        token->Aggregate(*tokenForAggregation);
    }

    token->SaveToXMLFile(_outputFile);
}

void MlxTknGenerator::PrintHelp()
{
    printf(INDENT "NAME:\n" INDENT2 "mlxtkngenerator"
           "\n" INDENT "SYNOPSIS:\n" INDENT2 "mlxtkngenerator"
           " [Options] <Commands>\n");

    printf(INDENT "DESCRIPTION:\n" INDENT2
           "Generates token XMLs for HCAs, Switches automatically.\n" INDENT2
           "The XML will be filled with the required data, ready for signing and installation afterwards.");

    printf("\n");
    printf(INDENT "OPTIONS:\n");
    printFlagLine(DEVICE_FLAG, DEVICE_FLAG_SHORT, "MstDevice", "Mellanox mst device name");
    printFlagLine(DEVICE_TYPE_FLAG, DEVICE_TYPE_FLAG_SHORT, "Switch/HCA", "Mellanox mst device type");
    printFlagLine(TOKEN_TYPE_FLAG, TOKEN_TYPE_FLAG_SHORT, "CS/DBG/CRCS/CRDT/RMCS/RMDT/FRC", "Token type");
    printFlagLine(NESTED_TOKEN_FLAG, NESTED_TOKEN_FLAG_SHORT, "", "Get nested token");
    printFlagLine(OUTPUT_FILE_FLAG, OUTPUT_FILE_FLAG_SHORT, "Path", "Path to output file");
    printFlagLine(TOKENS_DIR_FLAG, TOKENS_DIR_FLAG_SHORT, "Path", "Path to a directory of tokens for aggregation");
    printFlagLine(DEBUG_FW_FILE_FLAG, DEBUG_FW_FILE_FLAG_SHORT, "Path", "Path to debug fw file");
    printFlagLine(
        NESTED_DEBUG_FW_FILE_FLAG, NESTED_DEBUG_FW_FILE_FLAG_SHORT, "Path", "Path to debug fw file for nested device");
    printFlagLine(CHALLENGE_BLOB_FLAG,
                  CHALLENGE_BLOB_FLAG_SHORT,
                  "Path",
                  "Path to challenge blob file (relevant for CRCS/CRDT token types)");
    printFlagLine(SECONDARY_ADDR_FLAG, SECONDARY_ADDR_FLAG_SHORT, "i2c_secondary", "I2C secondary address");
    printFlagLine(HELP_FLAG, HELP_FLAG_SHORT, "", "Show help message and exit");
    printFlagLine(VERSION_FLAG, VERSION_FLAG_SHORT, "", "Show version and exit");

    printf("\n");
    printf(INDENT "COMMANDS SUMMARY\n");
    printf(INDENT2 "%-24s: %s\n", "generate_token", "generates a token xml automatically.");
    printf(INDENT2 "%-24s: %s\n", "aggregate_tokens", "aggregates token xml files to a single xml file.");

    printf("\n");
    printf(INDENT "Examples:\n");
    printf(INDENT2 "%-24s: %s\n",
           "To create a CS token",
           "mlxtokengenerator -d /dev/mst/mt4123_pciconf0 -k CS -t HCA -o /tmp/cs_token.xml generate_token");
    printf(
        INDENT2 "%-24s: %s\n",
        "To create a DBG token",
        "mlxtokengenerator -d /dev/mst/mt4123_pciconf0 -k DBG -t HCA -f /tmp/dbg_fw.bin -o /tmp/dbg_token.xml generate_token");
    printf("\n");
}

void MlxTknGenerator::InitCmdParser()
{
    AddOptions(DEVICE_FLAG, DEVICE_FLAG_SHORT, "MstDevice", "Mellanox mst device name");
    AddOptions(DEVICE_TYPE_FLAG, DEVICE_TYPE_FLAG_SHORT, "Switch/HCA", "Mellanox mst device type");
    AddOptions(TOKEN_TYPE_FLAG, TOKEN_TYPE_FLAG_SHORT, "CS/DBG/CRCS/CRDT/RMCS/RMDT/FRC", "Token type");
    AddOptions(NESTED_TOKEN_FLAG, NESTED_TOKEN_FLAG_SHORT, "", "Get nested token");
    AddOptions(OUTPUT_FILE_FLAG, OUTPUT_FILE_FLAG_SHORT, "Path", "Path to output file");
    AddOptions(TOKENS_DIR_FLAG, TOKENS_DIR_FLAG_SHORT, "Path", "Path to a directory of tokens for aggregation");
    AddOptions(DEBUG_FW_FILE_FLAG, DEBUG_FW_FILE_FLAG_SHORT, "Path", "Path to debug fw file");
    AddOptions(
        NESTED_DEBUG_FW_FILE_FLAG, NESTED_DEBUG_FW_FILE_FLAG_SHORT, "Path", "Path to debug fw file for nested device");
    AddOptions(CHALLENGE_BLOB_FLAG,
               CHALLENGE_BLOB_FLAG_SHORT,
               "Path",
               "Path to challenge blob file (relevant for CRCS/CRDT token types)");
    AddOptions(SECONDARY_ADDR_FLAG, SECONDARY_ADDR_FLAG_SHORT, "i2c_secondary", "I2C secondary address");
    AddOptions(HELP_FLAG, HELP_FLAG_SHORT, "", "Show help message and exit");
    AddOptions(VERSION_FLAG, VERSION_FLAG_SHORT, "", "Show version and exit");

    _cmdParser.AddRequester(this);
}

ParseStatus MlxTknGenerator::HandleOption(string name, string value)
{
    if (name == HELP_FLAG) {
        PrintHelp();
        return PARSE_OK_WITH_EXIT;
    } else if (name == VERSION_FLAG) {
        print_version_string("mlxtokengenerator", NULL);
        return PARSE_OK_WITH_EXIT;
    } else if (name == DEVICE_FLAG) {
        _device = value;
        return PARSE_OK;
    } else if (name == DEVICE_TYPE_FLAG) {
        _deviceType = getDeviceTypeFromString(value);
        return PARSE_OK;
    } else if (name == TOKEN_TYPE_FLAG) {
        _tokenType = MlxCfgToken::GetTokenType(value.c_str());
        return PARSE_OK;
    } else if (name == NESTED_TOKEN_FLAG) {
        _isNestedToken = true;
        return PARSE_OK;
    } else if (name == OUTPUT_FILE_FLAG) {
        _outputFile = value;
        return PARSE_OK;
    } else if (name == TOKENS_DIR_FLAG) {
        _tokensDir = value;
        return PARSE_OK;
    } else if (name == DEBUG_FW_FILE_FLAG) {
        _debugFwFile = value;
        return PARSE_OK;
    } else if (name == NESTED_DEBUG_FW_FILE_FLAG) {
        _debugFwNestedFile = value;
        return PARSE_OK;
    } else if (name == CHALLENGE_BLOB_FLAG) {
        _blobFile = value;
        return PARSE_OK;
    } else if (name == SECONDARY_ADDR_FLAG) {
        char* endp;
        int   i2c_secondary_address = (int)strtol(value.c_str(), &endp, 0);

        if (*endp || (i2c_secondary_address < 0)) {
            printf("Invalid I2C secondary address.\n");
            return PARSE_ERROR;
        }
        _i2cSecondaryAddr = i2c_secondary_address;
        return PARSE_OK;
    }
    return PARSE_ERROR;
}

bool MlxTknGenerator::ParseAndFindCommand(int argc, char** argv)
{
    /* first argument is tool name */
    if (argc == 1) {
        throw MlxTknGeneratorException("No commands or flags have been specified.");
    }

    /* a command must be specified as the last argument */
    for (int i = 1; i < argc - 1; ++i) {
        if (_cmdStringToEnum.find(argv[i]) != _cmdStringToEnum.end()) {
            throw MlxTknGeneratorException("Commands must be specified at the end of the CLI.");
        }
    }

    auto lastArg = _cmdStringToEnum.find(argv[argc - 1]);

    if (lastArg != _cmdStringToEnum.end()) {
        _command = lastArg->second;
        return true;
    }

    return false;
}

void MlxTknGenerator::ValidateDeviceType(mfile* mf, Device_Type deviceType)
{
    dm_dev_id_t deviceId = DeviceUnknown;
    u_int32_t   hwDevId = 0, hwRevId = 0;

    if (dm_get_device_id(mf, &deviceId, &hwDevId, &hwRevId)) {
        throw MlxTknGeneratorException("Failed to identify the device");
    }

    if (dm_is_livefish_mode(mf)) {
        throw MlxTknGeneratorException("Device in Livefish mode is not supported");
    }

    if ((deviceType == HCA) && !dm_is_5th_gen_hca(deviceId)) {
        throw MlxTknGeneratorException("Provided device is not a 5th gen HCA device.");
    }

    if ((deviceType == Switch) && !dm_dev_is_switch(deviceId)) {
        throw MlxTknGeneratorException("Provided device is not a Switch device.");
    }

    if ((deviceType == Retimer) && !dm_dev_is_retimer(deviceId)) {
        throw MlxTknGeneratorException("Provided device is not a Retimer device.");
    }
}

void MlxTknGenerator::ParamValidate()
{
    if (_command == GenerateToken) {
        if (_blobFile.empty() && _device.empty()) {
            throw MlxTknGeneratorException("A device or blob file must be specified to generate a token.");
        } else if (!_blobFile.empty() && !_device.empty()) {
            throw MlxTknGeneratorException("Blob file can't be specified with device.");
        }
        if (!_blobFile.empty() && _isNestedToken) {
            throw MlxTknGeneratorException("Generating a nested token based on a blob file is not supported.");
        }
        if (_deviceType == UNSUPPORTED_DEVICE) {
            throw MlxTknGeneratorException("Device type must be specified to generate a token.");
        }
        if (_tokenType == McTokenTypeUnknown) {
            throw MlxTknGeneratorException("Token type must be specified to generate a token.");
        }
        if (_outputFile.empty()) {
            throw MlxTknGeneratorException("Output file path must be specified to generate a token.");
        }
        if (((_tokenType == McTokenTypeDBG) || (_tokenType == McTokenTypeCRDT)) && _debugFwFile.empty()) {
            throw MlxTknGeneratorException("Debug fw path must be specified to generate %s token.",
                                           MlxCfgToken::getTokenString(_tokenType).c_str());
        }
        if ((_deviceType == HCA) && !((_tokenType == McTokenTypeCS) || (_tokenType == McTokenTypeDBG) ||
                                      (_tokenType == McTokenTypeCRCS) || (_tokenType == McTokenTypeCRDT))) {
            throw MlxTknGeneratorException("%s token is unsupported for HCA devices.",
                                           MlxCfgToken::getTokenString(_tokenType).c_str());
        }
    } else if (_command == AggregateTokens) {
        if (_tokensDir.empty()) {
            throw MlxTknGeneratorException("A directory of tokens for aggregation must be specified.");
        }
        if (_outputFile.empty()) {
            throw MlxTknGeneratorException("Output file path must be specified.");
        }
        if (_deviceType == UNSUPPORTED_DEVICE) {
            throw MlxTknGeneratorException("Device type must be specified to aggregate tokens.");
        }
        if (_tokenType == McTokenTypeUnknown) {
            throw MlxTknGeneratorException("Token type must be specified to aggregate tokens.");
        }
        if ((_tokenType != McTokenTypeCRCS) && (_tokenType != McTokenTypeCRDT)) {
            throw MlxTknGeneratorException("Aggregation is not supported for %s token on given device.",
                                           MlxCfgToken::getTokenString(_tokenType).c_str());
        }
    } else if (_command == Unknown) {
        throw MlxTknGeneratorException("Please specify a command.");
    }
}

ParseStatus MlxTknGenerator::ParseCommandLine(int argc, char** argv)
{
    MLX_TOKEN_DPRINTF(("MlxTknGenerator::ParseCommandLine.\n"));
    ParseStatus rc = PARSE_OK;

    if (ParseAndFindCommand(argc, argv)) {
        argc--;
    }

    rc = _cmdParser.ParseOptions(argc, argv);
    if (rc == PARSE_OK_WITH_EXIT) {
        return rc;
    } else if (rc == PARSE_ERROR) {
        PrintHelp();
        throw MlxTknGeneratorException("Failed to parse arguments. %s", _cmdParser.GetErrDesc());
    }

    ParamValidate();

    return rc;
}

void MlxTknGenerator::Run(int argc, char** argv)
{
    if (ParseCommandLine(argc, argv) != PARSE_OK) {
        return;
    }

    switch (_command) {
    case GenerateToken:
        GenerateTokenXML();
        break;

    case AggregateTokens:
        AggregateTokensXML();
        break;

    default:
        throw MlxTknGeneratorException("Unknown command code. %d", _command);
    }
}

int main(int argc, char** argv)
{
    try
    {
        MlxTknGenerator mlxCfgGen;
        mlxCfgGen.Run(argc, argv);
    }
    catch(const MlxTknGeneratorException& ex)
    {
        cerr << "-E- " << ex.what() << endl;
        return 1;
    }
    catch(const std::exception& ex)
    {
        cerr << "-E- General Exception: " << ex.what() << endl;
        return 1;
    }
    return 0;
}
