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

#ifndef MLXCFG_TOKENS_H_
#define MLXCFG_TOKENS_H_

#include "mlxcfg_utils.h"

/* Forward declaration */
struct reg_access_switch_mdsr_reg_ext;
struct reg_access_switch_mtcq_reg_ext;
struct reg_access_switch_mkdc_reg_ext;
/* End of forward declaration */

// aligned to MTCQ register definitions
typedef enum
{
    McTokenTypeRMCS = 0x0,
    McTokenTypeRMDT = 0x1,
    McTokenTypeCRCS = 0x2,
    McTokenTypeCRDT = 0x3,
    McTokenTypeFRC = 0x4,
    McTokenTypeCS = 0x5,
    McTokenTypeDBG = 0x6,
    McTokenTypeUnknown
} MlxCfgTokenType;

// aligned to MDSR register definitions
typedef enum
{
    McTokenStatusTypeCS = 0x0,
    McTokenStatusTypeDBG = 0x1,
    McTokenStatusTypeFRC = 0x2,
    McTokenStatusTypeRMCS = 0x3,
    McTokenStatusTypeRMDT = 0x4,
    McTokenStatusTypeCRCS = 0x5,
    McTokenStatusTypeCRDT = 0x6,
    McTokenStatusTypeUnknown
} MlxCfgTokenStatusType;

typedef enum
{
    KEEP_ALIVE_OK,
    KEEP_ALIVE_ERROR
} keepAliveStatus;

class MlxCfgToken
{
public:
    MlxCfgToken(mfile* mf);

    void QueryTokenSupport();
    void QueryTokenSession(MlxCfgTokenStatusType token);
    void EndTokenSession(MlxCfgTokenStatusType token);
    void RemoteTokenKeepAlive(u_int32_t sessionId,
                              u_int32_t sessionTimeInSec,
                              bool isSleepTimeBetweenCommandsInput,
                              u_int32_t keepAliveSleepTimeBetweenCommands,
                              bool isSleepTimeOnCommandTOInput,
                              u_int32_t keepAliveSleepTimeOnCommandTO);

    static MlxCfgTokenType GetTokenType(string token);
    static MlxCfgTokenStatusType GetTokenStatusType(string token);
    static string getTokenString(MlxCfgTokenType token);
    static string getTokenString(MlxCfgTokenStatusType token);

    void GetAndPrintChallenge(MlxCfgTokenType token, bool nestedToken);
    struct reg_access_switch_mtcq_reg_ext GetChallengeFromSwitchOrHCA(MlxCfgTokenType token);
    void PrintChallenge(const struct reg_access_switch_mtcq_reg_ext& challenge);

private:
    typedef enum
    {
        MtcqOk = 0,
        MtcqTokenAlreadyApplied = 1,
        MtcqTokenNotSupported = 2,
        MtcqNoKeyConfigured = 3,
        MtcqInterfaceNotAllowed = 4
    } MTCQStatus;

    void processMDSRData(const struct reg_access_switch_mdsr_reg_ext& mdsr_reg, bool isQuery);
    void runMDSR(mfile* mf, struct reg_access_switch_mdsr_reg_ext* mdsr_reg, reg_access_method_t method);
    void runMTCQ(mfile* mf, struct reg_access_switch_mtcq_reg_ext* mtcq_reg);
    void printArray(const u_int32_t arr[], int len);
    void printHexArrayAsAscii(const u_int32_t arr[], int len);
    static string ToString(MTCQStatus status);

    mfile* _mf;
};

class KeepAliveSession
{
public:
    KeepAliveSession(mfile* mf, u_int16_t sessionId, u_int32_t sessionTimeInSec);

    void runSession();
    void setSleepTimeOnCommandTO(u_int32_t sleepTime);
    void setSleepTimeBetweenCommands(u_int32_t sleepTime);

private:
    void runMKDC(mfile* mf, struct reg_access_switch_mkdc_reg_ext* mkdc_reg, time_t& timer);
    void processMKDCData(struct reg_access_switch_mkdc_reg_ext* mkdc_reg);
    keepAliveStatus err(bool report, const char* fmt, ...);

    static const char* _mkdcErrorToString[5];

    static const u_int32_t _keepAliveTimestampInSec;

    mfile* _mf;
    u_int16_t _sessionId;
    u_int32_t _current_keep_alive_counter;
    u_int32_t _sessionTimeLeftInSec;
    u_int32_t _SleepTimeOnCommandTO;
    u_int32_t _SleepTimeBetweenCommands;
};

#endif /* MLXCFG_TOKENS_H_ */
