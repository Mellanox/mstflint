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

#ifndef CDB_CABLE_ACCESS_H
#define CDB_CABLE_ACCESS_H

#include <map>
#include <vector>
#include <string>

#include "mtcr.h"
#include "common/compatibility.h"
#include "cable_access.h"

#define CDB_ACCESS_DPRINTF(args)                      \
    do                                                \
    {                                                 \
        char* reacDebug = getenv("CDB_ACCESS_DEBUG"); \
        if (reacDebug != NULL)                        \
        {                                             \
            printf("\33[2K\r");                       \
            printf("[CDB_ACCESS_DEBUG]: ");           \
            printf args;                              \
            fflush(stdout);                           \
        }                                             \
    } while (0)

typedef u_int8_t cdb_status_code;
typedef std::map<cdb_status_code, std::pair<bool, string>> CdbStatusToErrorMap;
static CdbStatusToErrorMap _cdbStatusMap;

class CmisCdbAccessException : public exception
{
public:
    CmisCdbAccessException(const string& msg);
    virtual ~CmisCdbAccessException() throw(){};
    virtual const char* what() const throw();

private:
    string _msg;
    CmisCdbAccessException();
};

class UnknownStatusCdbAccessException : public CmisCdbAccessException
{
public:
    UnknownStatusCdbAccessException(const string& msg) :
        CmisCdbAccessException("got unknown status (0x" + msg + ") in response to cdb command.")
    {
    }
    virtual ~UnknownStatusCdbAccessException() throw(){};
};

class CmisCdbAccess
{
public:
    typedef enum
    {
        LPL,
        EPL,
        OTHER
    } PayloadMethod;

    static const u_int16_t CDB_LPL_PAYLOAD_MAX_SIZE;

    explicit CmisCdbAccess(string mstDevName, mfile* mf = NULL, bool clearCompletionFlag = false);
    virtual ~CmisCdbAccess(){};
    void Init();
    void InnerInit(); // bypass to the cable access init()

    void SendCommand(u_int16_t code);
    void SendCommand(u_int16_t code, PayloadMethod payloadMethod, const vector<u_int8_t>& payload);
    std::vector<u_int8_t> SendCommand(u_int16_t code, PayloadMethod payloadMethod, u_int32_t outputByteSize);
    std::vector<u_int8_t> SendCommand(u_int16_t code,
                                      PayloadMethod payloadMethod,
                                      const vector<u_int8_t>& payload,
                                      u_int32_t outputByteSize);
    void SendCommand(u_int16_t code, const vector<u_int8_t>& lplPayload, const vector<u_int8_t>& eplPayload);

    void SetBackgroundCommand() { _isBackgroundCommand = true; }
    void SetForegroundCommand() { _isBackgroundCommand = false; }
    virtual u_int32_t GetMaxPayloadSizeInBytes(PayloadMethod payloadMethod);
    bool IsActivationWANeeded() { return _isIgnoreCompletionTimeOut; }
    void OverrideCommandCompletionWaitingTime(u_int32_t waitTime);

protected:
    enum CMISVersion
    {
        CMIS_4_0,
        CMIS_5_0,
        CMIS_UNKNOWN
    };

    struct CdbCommandHeader
    {
        u_int16_t command;
        u_int16_t eplLength;
        u_int8_t lplLength;
        u_int8_t cdbChkCode; // checksum
        u_int8_t eLPLLen;
        u_int8_t rLPLChkCode;
    };

    void InitCommandHeader(u_int16_t code, PayloadMethod payloadMethod, const std::vector<u_int8_t>& payload);
    std::vector<u_int8_t> ReadData(u_int32_t address, u_int32_t outputByteSize, PayloadMethod method);
    u_int32_t ReadDWord(u_int32_t address);
    void WriteData(u_int32_t address, const u_int8_t* payload, u_int32_t payloadSize);

    virtual void WaitForCommandCompletion();
    virtual void WaitForStatusBusyBit();
    virtual void SetStatusWaitingTime(u_int16_t command) { (void)command; };
    void CheckStatus();
    u_int8_t CalcChecksum(const u_int8_t* byteArray, u_int32_t len);
    u_int8_t CalcChkCode(PayloadMethod payloadMethod, const std::vector<u_int8_t>& payload);

    CMISVersion ToCMISVersion(u_int8_t cmisVersionByte);

    static void CreateStatusMap();

    cableAccess _cableAccess;
    CdbCommandHeader _header;
    CMISVersion _cmisVersion;
    bool _isBackgroundCommand;
    bool _isInitDone;
    u_int32_t _statusWaitingTimeMilliSec;
    u_int32_t _completionWaitingTimeMilliSec;
    u_int32_t _maxDurationWriteMilliSec;
    bool _isIgnoreCompletionTimeOut;
    bool _isCompletionWaitingTimeOverridden;
    bool _clearCompletionFlag;

    static const u_int16_t CDB_EPL_PAYLOAD_MAX_SIZE;
    static const u_int16_t CDB_EPL_PAGE_SIZE;
    static const u_int16_t CDB_CMD_CODE_ADDRESS;
    static const u_int16_t CDB_DATA_LPL_ADDRESS;
    static const u_int16_t CDB_DATA_EPL_ADDRESS;
    static const u_int16_t CDB_CMD_COMPLETE_FLAG_ADDRESS;
    static const u_int16_t CDB_CMD_STATUS_ADDRESS;
    static const u_int16_t CDB_WRITABLE_BYTES_PER_PAGE;
    static const u_int16_t CDB_PAGE_INDEX_IN_ADDRESS;
    static const u_int16_t CDB_CMIS_REVISION_ADDRESS;
    static const u_int16_t CDB_SUPPORT_ADVERTISEMENT_ADDRESS;
    static const u_int16_t CDB_PASSWORD_ENTRY_AREA_ADDRESS;
    static const u_int16_t CDB_IMPLEMENTED_BANKS_ADDRESS;
};

class FWManagementCdbAccess : public CmisCdbAccess
{
public:
    enum WriteReadMechanism
    {
        NONE_SUPPORTED = 0,
        LPL_SUPPORTED = 0x1,
        EPL_SUPPORTED = 0x10,
        BOTH_SUPPORTED = 0x11
    };

    typedef enum
    {
        // cdb cmd MSB on cable is first byte, so the command are "reversed"
        CDB_FW_MNG_FEATURES = 0x4100,
        CDB_START_FW_DOWNLOAD = 0x0101,
        CDB_WRITE_FW_BLOCK_LPL = 0x0301,
        CDB_WRITE_FW_BLOCK_EPL = 0x0401,
        CDB_COMPLETE_FW_DOWNLOAD = 0x0701,
        CDB_RUN_FW_IMAGE = 0x0901,
        CDB_COMMIT_FW_IMAGE = 0x0A01,
        CDB_QUERY_STATUS = 0x0
    } FWManagedCdbCommand;

    struct FWMngFeatures
    {
        u_int8_t reserved;
        u_int8_t maxDurationCoding;
        u_int8_t startCmdPayloadSize;
        u_int8_t erasedByte;
        u_int8_t readWriteLengthExt;
        u_int8_t writeMechanism;
        u_int8_t readMechanism;
        u_int8_t hitlessRestart;
        u_int16_t maxDurationStart;
        u_int16_t maxDurationAbort;
        u_int16_t maxDurationWrite;
        u_int16_t maxDurationComplete;
    };

    FWManagementCdbAccess(string mstDevName, bool clearCompletionFlag = false);
    virtual ~FWManagementCdbAccess();

    void Init(vector<u_int8_t> password);
    void EnterPassword(vector<u_int8_t> password);
    u_int32_t GetMaxPayloadSizeInBytes(PayloadMethod payloadMethod) override;
    u_int8_t GetVendorDataSize() { return _startCmdPayloadSize; }
    PayloadMethod GetPayloadMechanism() { return _selectedPayloadMechanism; }
    void SetFWMngFeatures(FWMngFeatures fwMngfeatures);
    u_int8_t GetNumOfSupportedBanks();

private:
    void SetStatusWaitingTime(u_int16_t command) override;
    void SelectPayloadMechanism();

    PayloadMethod _selectedPayloadMechanism;
    WriteReadMechanism _fwUpdateMechanism;
    u_int8_t _startCmdPayloadSize;
    static u_int16_t _lplPayloadMaxSizeBytes;
    static u_int16_t _eplPayloadMaxSizeBytes;
    bool _FwMngFeaturesInitialized;
};

#endif // CDB_CABLE_ACCESS_H
