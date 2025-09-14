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
 *
 */

#include "mft_utils/mft_sig_handler.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <exception>
#include <algorithm>
#include "mlxcfg_ui.h"
#include "mlxcfg_ui_tokens.h"
#include "mlxcfg_generic_commander.h"
#include "tools_layouts/reg_access_switch_layouts.h"
#include "common/tools_time.h"

MlxCfgToken::MlxCfgToken(mfile* mf) : _mf(mf)
{}

MlxCfgTokenStatusType MlxCfgToken::GetTokenStatusType(string token)
{
    MlxCfgTokenStatusType tokenType = McTokenStatusTypeUnknown;

    if (token == "CS")
    {
        tokenType = McTokenStatusTypeCS;
    }
    else if (token == "DBG")
    {
        tokenType = McTokenStatusTypeDBG;
    }
    else if (token == "FRC")
    {
        tokenType = McTokenStatusTypeFRC;
    }
    else if (token == "RMCS")
    {
        tokenType = McTokenStatusTypeRMCS;
    }
    else if (token == "RMDT")
    {
        tokenType = McTokenStatusTypeRMDT;
    }
    else if (token == "CRCS")
    {
        tokenType = McTokenStatusTypeCRCS;
    }
    else if (token == "CRDT")
    {
        tokenType = McTokenStatusTypeCRDT;
    }

    return tokenType;
}

MlxCfgTokenType MlxCfgToken::GetTokenType(string token)
{
    MlxCfgTokenType tokenType = McTokenTypeUnknown;

    if (token == "RMCS")
    {
        tokenType = McTokenTypeRMCS;
    }
    else if (token == "RMDT")
    {
        tokenType = McTokenTypeRMDT;
    }
    else if (token == "CRCS")
    {
        tokenType = McTokenTypeCRCS;
    }
    else if (token == "CRDT")
    {
        tokenType = McTokenTypeCRDT;
    }
    else if (token == "FRC")
    {
        tokenType = McTokenTypeFRC;
    }
    else if (token == "CS")
    {
        tokenType = McTokenTypeCS;
    }
    else if (token == "DBG")
    {
        tokenType = McTokenTypeDBG;
    }

    return tokenType;
}

string MlxCfgToken::getTokenString(MlxCfgTokenType token)
{
    string tokenStr = "";

    switch (token)
    {
        case McTokenTypeRMCS:
            tokenStr = "RMCS";
            break;
        case McTokenTypeRMDT:
            tokenStr = "RMDT";
            break;
        case McTokenTypeCRCS:
            tokenStr = "CRCS";
            break;
        case McTokenTypeCRDT:
            tokenStr = "CRDT";
            break;
        case McTokenTypeFRC:
            tokenStr = "FRC";
            break;
        case McTokenTypeCS:
            tokenStr = "CS";
            break;
        case McTokenTypeDBG:
            tokenStr = "DBG";
            break;
        default:
            throw MlxcfgException("Invalid token code %d.", token);
    }

    return tokenStr;
}

string MlxCfgToken::getTokenString(MlxCfgTokenStatusType token)
{
    string tokenStr = "";

    switch (token)
    {
        case McTokenStatusTypeCS:
            tokenStr = "CS";
            break;
        case McTokenStatusTypeDBG:
            tokenStr = "DBG";
            break;
        case McTokenStatusTypeFRC:
            tokenStr = "FRC";
            break;
        case McTokenStatusTypeRMCS:
            tokenStr = "RMCS";
            break;
        case McTokenStatusTypeRMDT:
            tokenStr = "RMDT";
            break;
        case McTokenStatusTypeCRCS:
            tokenStr = "CRCS";
            break;
        case McTokenStatusTypeCRDT:
            tokenStr = "CRDT";
            break;
        default:
            throw MlxcfgException("Invalid token code.");
    }

    return tokenStr;
}

string MlxCfgToken::ToString(MTCQStatus status)
{
    switch (status)
    {
        case MtcqOk:
            return "OK";
        case MtcqTokenAlreadyApplied:
            return "TOKEN_ALREADY_APPLIED";
        case MtcqTokenNotSupported:
            return "TOKEN_NOT_SUPPORTED";
        case MtcqNoKeyConfigured:
            return "NO_KEY_CONFIGURED";
        case MtcqInterfaceNotAllowed:
            return "INTERFACE_NOT_ALLOWED";
        default:
            return "Unknown";
    }
}

void MlxCfgToken::RemoteTokenKeepAlive(u_int32_t sessionId,
                                       u_int32_t sessionTimeInSec,
                                       bool isSleepTimeBetweenCommandsInput,
                                       u_int32_t keepAliveSleepTimeBetweenCommands,
                                       bool isSleepTimeOnCommandTOInput,
                                       u_int32_t keepAliveSleepTimeOnCommandTO)
{
    KeepAliveSession session(_mf, sessionId, sessionTimeInSec);

    if (isSleepTimeBetweenCommandsInput)
    {
        session.setSleepTimeBetweenCommands(keepAliveSleepTimeBetweenCommands);
    }
    if (isSleepTimeOnCommandTOInput)
    {
        session.setSleepTimeOnCommandTO(keepAliveSleepTimeOnCommandTO);
    }

    session.runSession();
}

void MlxCfgToken::runMTCQ(mfile* mf, struct reg_access_switch_mtcq_reg_ext* mtcq_reg)
{
    reg_access_status_t rc = ME_REG_ACCESS_OK;

    mft_signal_set_handling(1);
    rc = reg_access_mtcq(mf, REG_ACCESS_METHOD_GET, mtcq_reg);
    dealWithSignal();
    if (rc)
    {
        throw MlxcfgException("Failed getting response from the device, error: %s.\n", m_err2str((MError)rc));
    }
}

void MlxCfgToken::printArray(const u_int32_t arr[], int len)
{
    int i = 0;

    if (len < 0)
    {
        throw MlxcfgException("Invalid array length was given.\n");
    }

    for (; i < len; ++i)
    {
        printf("%08x", arr[i]);
    }
    printf("\n");
}

void MlxCfgToken::printHexArrayAsAscii(const u_int32_t arr[], int len)
{
    u_int8_t byteArray[4];
    int i = 0, j = 0;

    if (len < 0)
    {
        throw MlxcfgException("Invalid array length was given.\n");
    }

    for (i = 0; i < len; ++i)
    {
        memcpy(byteArray, &arr[i], 4);
        for (j = 3; j >= 0; --j)
        {
            printf("%c", byteArray[j]);
        }
    }
    printf("\n");
}

void MlxCfgToken::QueryTokenSupport()
{
    reg_access_status_t rc = ME_REG_ACCESS_OK;
    reg_access_hca_mcam_reg_ext mcam;
    memset(&mcam, 0, sizeof(mcam));

    // TODO add all token types
    rc = reg_access_mcam(_mf, REG_ACCESS_METHOD_GET, &mcam);
    if (rc)
    {
        throw MlxcfgException("Failed getting response from the device, error: %s.\n", m_err2str((MError)rc));
    }

    dm_dev_id_t deviceId = DeviceUnknown;
    u_int32_t hwDevId, hwRevId;
    if (dm_get_device_id(_mf, &deviceId, &hwDevId, &hwRevId))
    {
        throw MlxcfgException("Failed to identify the device");
    }
    if (dm_dev_is_cable(deviceId))
    {
        throw MlxcfgException("Not supported for cables.\n");
    }
    if (!dm_dev_is_switch(deviceId))
    {
        std::swap(mcam.mng_feature_cap_mask[0], mcam.mng_feature_cap_mask[3]);
        std::swap(mcam.mng_feature_cap_mask[1], mcam.mng_feature_cap_mask[2]);
    }

    printf("CS token supported:             %d\n", EXTRACT(mcam.mng_feature_cap_mask[0], 14, 1));
    printf("Debug FW token supported:       %d\n", EXTRACT(mcam.mng_feature_cap_mask[0], 15, 1));
    printf("CRCS and CRDT tokens supported: %d\n", EXTRACT(mcam.mng_feature_cap_mask[1], 17, 1));

    if (dm_dev_is_switch(deviceId) && (dm_is_ib_access(_mf)) != 0)
    {
        printf("RMCS and RMDT tokens supported: %d\n", EXTRACT(mcam.mng_feature_cap_mask[1], 7, 1));
    }
}

void MlxCfgToken::runMDSR(mfile* mf, struct reg_access_switch_mdsr_reg_ext* mdsr_reg, reg_access_method_t method)
{
    reg_access_status_t rc = ME_REG_ACCESS_OK;

    mft_signal_set_handling(1);
    rc = reg_access_mdsr(mf, method, mdsr_reg);
    dealWithSignal();

    if (rc)
    {
        throw MlxcfgException("MDSR reg access failed, %s.", m_err2str((MError)rc));
    }
}

void MlxCfgToken::QueryTokenSession(MlxCfgTokenStatusType token)
{
    struct reg_access_switch_mdsr_reg_ext mdsr_reg;
    memset(&mdsr_reg, 0, sizeof(mdsr_reg));
    mdsr_reg.type_of_token = token;
    runMDSR(_mf, &mdsr_reg, REG_ACCESS_METHOD_GET);
    processMDSRData(mdsr_reg, true);
}

void MlxCfgToken::processMDSRData(const struct reg_access_switch_mdsr_reg_ext& mdsr_reg, bool isQuery)
{
    static const char* additional_info_to_string[6] = {"No additional information available.",
                                                       "There is no debug session in progress.",
                                                       "FW is not secured, debug session cannot be ended.",
                                                       "Fail - Debug end request cannot be accepted.",
                                                       "Fail - Host is not allowed to query debug session.",
                                                       "Debug session active."};
    static const char* status_to_string[7] = {"The debug session ended successfully.",
                                              "Failed to execute the operation.",
                                              "Debug session active.",
                                              "No token applied.",
                                              "Challenge provided, no token installed yet.",
                                              "Timeout before token installed.",
                                              "Timeout of active token."};
    u_int32_t minutes = mdsr_reg.time_left / 60;
    u_int32_t hours = minutes / 60;
    u_int32_t days = hours / 24;

    if (mdsr_reg.status > 6)
    {
        printf("-E- invalid code in info.\n");
    }
    else
    {
        if (mdsr_reg.status == 0)
        {
            if (isQuery)
            {
                printf("%s\n", additional_info_to_string[mdsr_reg.additional_info]);
            }
            else
            {
                printf("%s\n", status_to_string[mdsr_reg.status]);
            }
        }
        else if (mdsr_reg.status == 1)
        {
            cout << status_to_string[mdsr_reg.status] << endl;
            cout << additional_info_to_string[mdsr_reg.additional_info] << endl;
        }
        else if (mdsr_reg.status == 2)
        {
            cout << status_to_string[mdsr_reg.status] << endl;
            // Backward compatibility, if the FW is before MDSR update it won't have the time field and it will be zeros
            if (mdsr_reg.time_left != 0)
            {
                cout << days << " days, " << (hours % 24) << " hours, " << (minutes % 60) << " minutes, "
                     << (mdsr_reg.time_left & 60) << " seconds left for token operation." << endl;
            }
        }
        else if (mdsr_reg.status == 4)
        {
            cout << status_to_string[mdsr_reg.status] << endl;
            // Backward compatibility, if the FW is before MDSR update it won't have the time field and it will be zeros
            if (mdsr_reg.time_left != 0)
            {
                cout << days << " days, " << (hours % 24) << " hours, " << (minutes % 60) << " minutes, "
                     << (mdsr_reg.time_left & 60) << " seconds left for token installation." << endl;
            }
        }
        else
        {
            printf("%s\n", additional_info_to_string[mdsr_reg.additional_info]);
        }
    }
}

void MlxCfgToken::EndTokenSession(MlxCfgTokenStatusType token)
{
    struct reg_access_switch_mdsr_reg_ext mdsr_reg;
    memset(&mdsr_reg, 0, sizeof(mdsr_reg));
    mdsr_reg.type_of_token = (u_int8_t)token;
    mdsr_reg.end = 1;
    runMDSR(_mf, &mdsr_reg, REG_ACCESS_METHOD_SET);
    processMDSRData(mdsr_reg, false);
}

void MlxCfgToken::PrintChallenge(const struct reg_access_switch_mtcq_reg_ext& challenge)
{
    u_int32_t base_mac[2];
    base_mac[0] = challenge.base_mac & 0xffffffff;
    base_mac[1] = (challenge.base_mac >> 32) & 0xffffffff;

    printf("Token opcode:       %x\n", challenge.token_opcode);
    printf("Keypair uuid:       ");
    printArray(challenge.keypair_uuid, 4);
    printf("Base mac:           %08x%08x\n", base_mac[1], base_mac[0]);
    printf("PSID:               ");
    printHexArrayAsAscii(challenge.psid, 4);
    printf("FW version:         %x%08x\n", challenge.fw_version_39_32, challenge.fw_version_31_0);
    printf("Source address:     ");
    printArray(challenge.source_address, 4);
    printf("Session id:         %x\n", challenge.session_id);
    printf("Challenge version:  %x\n", challenge.challenge_version);
    printf("Challenge:          ");
    printArray(challenge.challenge, 8);
}

struct reg_access_switch_mtcq_reg_ext MlxCfgToken::GetChallengeFromSwitchOrHCA(MlxCfgTokenType token)
{
    struct reg_access_switch_mtcq_reg_ext mtcq_reg;
    memset(&mtcq_reg, 0, sizeof(mtcq_reg));
    mtcq_reg.token_opcode = token;
    runMTCQ(_mf, &mtcq_reg);
    if (mtcq_reg.status != MtcqOk)
    {
        throw MlxcfgException("Challenge failed: %s.", MlxCfgToken::ToString((MTCQStatus)mtcq_reg.status).c_str());
    }

    return mtcq_reg;
}

void MlxCfgToken::GetAndPrintChallenge(MlxCfgTokenType token, bool)
{
    if (token == McTokenTypeRMCS || token == McTokenTypeRMDT)
    {
        if (dm_is_ib_access(_mf) == 0) // not IB device
        {
            throw MlxcfgException("Specified device is not an IB device.\n");
        }
    }
    struct reg_access_switch_mtcq_reg_ext challenge = GetChallengeFromSwitchOrHCA(token);
    PrintChallenge(challenge);
}

const char* KeepAliveSession::_mkdcErrorToString[5] = {"OK", "BAD_SESSION_ID", "BAD_KEEP_ALIVE_COUNTER",
                                                       "BAD_SOURCE_ADDRESS", "SESSION_TIMEOUT"};

const u_int32_t KeepAliveSession::_keepAliveTimestampInSec = 600;

KeepAliveSession::KeepAliveSession(mfile* mf, u_int16_t sessionId, u_int32_t sessionTimeInSec) :
    _mf(mf),
    _sessionId(sessionId),
    _sessionTimeLeftInSec(sessionTimeInSec),
    _SleepTimeOnCommandTO(1),
    _SleepTimeBetweenCommands(300)
{
    srand(time(NULL));
    _current_keep_alive_counter = rand();
}

void KeepAliveSession::runSession()
{
    time_t mkdcRunTime;
    u_int32_t sleepTimeInSec = 0;
    u_int32_t sleepBetweenCommandsInSec = _SleepTimeBetweenCommands;
    reg_access_switch_mkdc_reg_ext mkdc_reg;
    memset(&mkdc_reg, 0, sizeof(mkdc_reg));
    mkdc_reg.session_id = _sessionId;
    mkdc_reg.current_keep_alive_counter = _current_keep_alive_counter;

    if (sleepBetweenCommandsInSec >= _keepAliveTimestampInSec)
    {
        throw MlxcfgException("Specified cycle time must be shorter than %d seconds.", _keepAliveTimestampInSec);
    }

    if (_sessionTimeLeftInSec < _keepAliveTimestampInSec)
    {
        throw MlxcfgException("Specified session time must be longer than %d minutes.", _keepAliveTimestampInSec / 60);
    }

    while (_sessionTimeLeftInSec >= _keepAliveTimestampInSec)
    {
        mkdcRunTime = 0;
        runMKDC(_mf, &mkdc_reg, mkdcRunTime);
        processMKDCData(&mkdc_reg);
        _sessionTimeLeftInSec -= mkdcRunTime;

        if (_sessionTimeLeftInSec > _keepAliveTimestampInSec)
        {
            if (sleepBetweenCommandsInSec > (_sessionTimeLeftInSec - _keepAliveTimestampInSec))
            {
                //* sleep until last MKDC is needed (which is when _keepAliveTimestampInSec seconds are left for the
                // session)
                sleepBetweenCommandsInSec = _sessionTimeLeftInSec - _keepAliveTimestampInSec;
            }
        }
        else
        {
            //* sleep until session time ends
            sleepBetweenCommandsInSec = _sessionTimeLeftInSec;
        }

        sleepTimeInSec = sleepBetweenCommandsInSec;
        msleep(sleepTimeInSec * 1000);
        _sessionTimeLeftInSec -= sleepBetweenCommandsInSec;
    }
}

void KeepAliveSession::runMKDC(mfile* mf, struct reg_access_switch_mkdc_reg_ext* mkdc_reg, time_t& timer)
{
    reg_access_status_t rc = ME_REG_ACCESS_OK;
    time_t start = 0;

    start = time(NULL);
    mft_signal_set_handling(1);
    rc = reg_access_mkdc(mf, REG_ACCESS_METHOD_GET, mkdc_reg);
    dealWithSignal();
    timer = time(NULL) - start;

    while ((rc == ME_ICMD_STATUS_EXECUTE_TO) && ((u_int32_t)timer < _keepAliveTimestampInSec))
    {
        u_int32_t sleep_time_in_sec = _SleepTimeOnCommandTO;

        msleep(sleep_time_in_sec * 1000);

        mft_signal_set_handling(1);
        rc = reg_access_mkdc(mf, REG_ACCESS_METHOD_GET, mkdc_reg);
        dealWithSignal();

        timer = time(NULL) - start;
    }

    if (rc == ME_REG_ACCESS_REG_NOT_SUPP)
    {
        throw MlxcfgException("MKDC access register is not supported.");
    }
    else if (rc)
    {
        throw MlxcfgException("cannot access MKDC register, error code is %d.");
    }
}

void KeepAliveSession::processMKDCData(struct reg_access_switch_mkdc_reg_ext* mkdc_reg)
{
    if (mkdc_reg->error_code != 0)
    {
        throw MlxcfgException("keep alive session failed. error code: %s.", _mkdcErrorToString[mkdc_reg->error_code]);
    }
    if (mkdc_reg->session_id != _sessionId)
    {
        throw MlxcfgException("received wrong session id.");
    }

    mkdc_reg->current_keep_alive_counter = mkdc_reg->next_keep_alive_counter;
    _current_keep_alive_counter = mkdc_reg->current_keep_alive_counter;
}

void KeepAliveSession::setSleepTimeOnCommandTO(u_int32_t sleepTime)
{
    _SleepTimeOnCommandTO = sleepTime;
}

void KeepAliveSession::setSleepTimeBetweenCommands(u_int32_t sleepTime)
{
    _SleepTimeBetweenCommands = sleepTime;
}

keepAliveStatus KeepAliveSession::err(bool report, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char errBuff[MAX_ERR_STR_LEN] = {0};

    if (vsnprintf(errBuff, MAX_ERR_STR_LEN, fmt, args) >= MAX_ERR_STR_LEN)
    {
        strcpy(&errBuff[MAX_ERR_STR_LEN - 5], "...");
    }
    if (report)
    {
        fprintf(stdout, PRE_ERR_MSG " %s\n", errBuff);
    }
    va_end(args);
    return KEEP_ALIVE_ERROR;
}
