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

#ifndef MLXTKNGNERATOR_H_
#define MLXTKNGNERATOR_H_

#include <string>
#include <cmdparser/cmdparser.h>
#include <map>
#include "mlxtoken.h"
#include "mlxconfig/mlxcfg_ui.h"
#include "mlxconfig/mlxcfg_ui_tokens.h"

class MlxTknGenerator: public CommandLineRequester
{
public:
    MlxTknGenerator();
    ~MlxTknGenerator();

    void Run(int argc, char** argv);
    void GenerateTokenXML();
    void AggregateTokensXML();

private:
    void InitCmdParser();
    void PrintHelp();
    ParseStatus ParseCommandLine(int argc, char** argv);
    bool ParseAndFindCommand(int argc, char** argv);
    ParseStatus HandleOption(string name, string value);
    void ParamValidate();
    void ValidateDeviceType(mfile* mf, Device_Type deviceType);

    string GetDebugFwVersion(string filePath);
    vector < TLVParamsData > GetDataForToken(MlxCfgTokenType tokenType, Device_Type deviceType, bool isNestedToken);
    vector < TLVParamsData > GetDataForToken(MlxCfgTokenType tokenType, string blobFile);
    void ValidateNewTlvType(u_int16_t actual, u_int16_t expected, const string& fieldName);
    bool IsGetMeasurementIndex50(const vector < u_int8_t >& tokenData);
    void FromGetMeasurementIndex50ToChallenge(struct tokens_layout_get_measurment_index_50& getMeasurementIndex50,
                                              struct reg_access_switch_mtcq_reg_ext&        challenge);
    void IsValidGetMeasurementIndex50(const struct tokens_layout_get_measurment_index_50& getMeasurementIndex50);
    vector < TLVParamsData >
    GetTokenDataFromChallenge(mfile * mf, MlxCfgTokenType tokenType, bool isNestedToken);
    vector < TLVParamsData > GetRemoteTokenData(struct reg_access_switch_mtcq_reg_ext challenge,
                                                MlxCfgTokenType tokenType,
                                                string debugFwVersion);
    vector < TLVParamsData > GetChallengeBasedTokenData(struct reg_access_switch_mtcq_reg_ext challenge,
                                                        MlxCfgTokenType tokenType,
                                                        string debugFwVersion);
    vector < TLVParamsData > GetTokenDataFromQuery(string device, MlxCfgTokenType tokenType, Device_Type deviceType);

    enum MlxTknGeneratorCmd {
        GenerateToken,
        AggregateTokens,
        Unknown
    };

    static const        map < string, MlxTknGeneratorCmd > _cmdStringToEnum;
    static const string DEVICE_FLAG;
    static const char   DEVICE_FLAG_SHORT;
    static const string HELP_FLAG;
    static const char   HELP_FLAG_SHORT;
    static const string VERSION_FLAG;
    static const char   VERSION_FLAG_SHORT;
    static const string DEVICE_TYPE_FLAG;
    static const char   DEVICE_TYPE_FLAG_SHORT;
    static const string TOKEN_TYPE_FLAG;
    static const char   TOKEN_TYPE_FLAG_SHORT;
    static const string NESTED_TOKEN_FLAG;
    static const char   NESTED_TOKEN_FLAG_SHORT;
    static const string DEBUG_FW_FILE_FLAG;
    static const char   DEBUG_FW_FILE_FLAG_SHORT;
    static const string NESTED_DEBUG_FW_FILE_FLAG;
    static const char   NESTED_DEBUG_FW_FILE_FLAG_SHORT;
    static const string OUTPUT_FILE_FLAG;
    static const char   OUTPUT_FILE_FLAG_SHORT;
    static const string TOKENS_DIR_FLAG;
    static const char   TOKENS_DIR_FLAG_SHORT;
    static const string CHALLENGE_BLOB_FLAG;
    static const char   CHALLENGE_BLOB_FLAG_SHORT;
    static const string SECONDARY_ADDR_FLAG;
    static const char   SECONDARY_ADDR_FLAG_SHORT;

    CommandLineParser  _cmdParser;
    string             _device;
    Device_Type        _deviceType;
    MlxCfgTokenType    _tokenType;
    bool               _isNestedToken;
    string             _outputFile;
    string             _tokensDir;
    string             _debugFwFile;
    string             _debugFwNestedFile;
    string             _blobFile;
    MlxTknGeneratorCmd _command;
    int                _i2cSecondaryAddr;
};

#endif /* MLXTKNGNERATOR_H_ */
