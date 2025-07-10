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

#include "cdb_cable_access.h"
#include <sstream>
#include <iostream>
#include <exception>
#include <cstring>
#include "common/tools_time.h"

CmisCdbAccessException::CmisCdbAccessException(const string& msg) : _msg(msg) {}
const char* CmisCdbAccessException::what() const throw()
{
    return _msg.c_str();
}

const u_int16_t CmisCdbAccess::CDB_LPL_PAYLOAD_MAX_SIZE = 0x78;  // 120 bytes
const u_int16_t CmisCdbAccess::CDB_EPL_PAYLOAD_MAX_SIZE = 0x800; // EPL spans multiple pages
const u_int16_t CmisCdbAccess::CDB_EPL_PAGE_SIZE = 0x80;
const u_int16_t CmisCdbAccess::CDB_CMD_CODE_ADDRESS = 0x9F80;
const u_int16_t CmisCdbAccess::CDB_DATA_LPL_ADDRESS = 0x9F88;
const u_int16_t CmisCdbAccess::CDB_DATA_EPL_ADDRESS = 0xA080;
const u_int16_t CmisCdbAccess::CDB_CMD_COMPLETE_FLAG_ADDRESS = 0x0008;
const u_int16_t CmisCdbAccess::CDB_CMD_STATUS_ADDRESS = 0x0025;
const u_int16_t CmisCdbAccess::CDB_CMIS_REVISION_ADDRESS = 0x0001;
const u_int16_t CmisCdbAccess::CDB_SUPPORT_ADVERTISEMENT_ADDRESS = 0x01A3;
const u_int16_t CmisCdbAccess::CDB_WRITABLE_BYTES_PER_PAGE = 0x0080;
const u_int16_t CmisCdbAccess::CDB_PAGE_INDEX_IN_ADDRESS = 0x0100;
const u_int16_t CmisCdbAccess::CDB_PASSWORD_ENTRY_AREA_ADDRESS = 0x7A;
const u_int16_t CmisCdbAccess::CDB_IMPLEMENTED_BANKS_ADDRESS = 0x018E;

void CmisCdbAccess::CreateStatusMap()
{
    _cdbStatusMap[0b10000001] = make_pair(false, "Busy capturing command.");
    _cdbStatusMap[0b10000010] = make_pair(false, "Busy checking/validating command.");
    _cdbStatusMap[0b10000011] = make_pair(false, "Busy executing.");
    _cdbStatusMap[0b00000001] = make_pair(true, "Success.");
    _cdbStatusMap[0b01000000] = make_pair(false, "Failed, no specific failure.");
    _cdbStatusMap[0b01000001] = make_pair(false, "Unsupported CDB command.");
    _cdbStatusMap[0b01000010] = make_pair(false, "Input parameters error.");
    _cdbStatusMap[0b01000101] = make_pair(false, "CdbChkCode error.");
    _cdbStatusMap[0b01000110] = make_pair(false, "Unsupported Token type error.");
    _cdbStatusMap[0b01110110] = make_pair(false, "Token type mismatch error.");
    _cdbStatusMap[0b01110111] = make_pair(false, "Token parameters mismatch error.");
    _cdbStatusMap[0b01111000] = make_pair(false, "Token Cryptographic Signature error.");
    _cdbStatusMap[0b01111001] =
      make_pair(false, "Time from LinkX providing the Challenge till the Challenge Response is given exceeded limit.");
    _cdbStatusMap[0b01111010] =
      make_pair(false, "Token Format error (Incremental FILE section tlv size exceeds buffer size while parsing).");
    _cdbStatusMap[0b01111011] = make_pair(false, "LinkX UID Not Found error.");
}

CmisCdbAccess::CmisCdbAccess(string mstDevName, mfile* mf, bool clearCompletionFlag) :
    _cableAccess(mstDevName.c_str(), mf),
    _cmisVersion(CMIS_UNKNOWN),
    _isBackgroundCommand(true),
    _isInitDone(false),
    _statusWaitingTimeMilliSec(1000),
    _completionWaitingTimeMilliSec(1000),
    _maxDurationWriteMilliSec(0),
    _isIgnoreCompletionTimeOut(false),
    _isCompletionWaitingTimeOverridden(false),
    _clearCompletionFlag(clearCompletionFlag)
{
    memset(&_header, 0, sizeof(_header));
    CmisCdbAccess::CreateStatusMap();
}

CmisCdbAccess::CMISVersion CmisCdbAccess::ToCMISVersion(u_int8_t cmisVersionByte)
{
    CMISVersion cmisVersion = CMIS_UNKNOWN;
    switch (cmisVersionByte)
    {
        case 0x40:
            cmisVersion = CMIS_4_0;
            break;
        case 0x50:
            cmisVersion = CMIS_5_0;
            break;
        default:
            break;
    }
    return cmisVersion;
}

void CmisCdbAccess::InnerInit()
{
    if (!_isInitDone)
    {
        try
        {
            u_int8_t cdbSupport = (u_int8_t)(ReadDWord(CDB_SUPPORT_ADVERTISEMENT_ADDRESS) & 0xff);
            cdbSupport = (cdbSupport >> 6) & 3; // cdb support info 2 is in bits 6-7
            if (cdbSupport == 0)
            {
                throw CmisCdbAccessException("module doesn't support CDB commands");
            }
        }
        catch (...)
        {
            throw CmisCdbAccessException("module doesn't support CDB commands");
        }
        u_int8_t cmis = (u_int8_t)(ReadDWord(CDB_CMIS_REVISION_ADDRESS) & 0xff);
        _cmisVersion = ToCMISVersion(cmis);

        // bool is2ndSource = false;
        // if (!_cableAccess.is2ndSourceCable(is2ndSource))
        // {
        //     throw CmisCdbAccessException("Failed identifying the cable.");
        // }
        // if (is2ndSource)
        // {
        //     second_source_device_info deviceInfo;
        //     if (!_cableAccess.get2ndSourceData(deviceInfo))
        //     {
        //         throw CmisCdbAccessException("Failed getting data from the cable.");
        //     }
        //     _isIgnoreCompletionTimeOut = (deviceInfo.vendorByte == 0x10);
        // }

        _isInitDone = true;
    }
}

void CmisCdbAccess::Init()
{
    if (!_isInitDone)
    {
        if (!_cableAccess.init())
        {
            throw CmisCdbAccessException(_cableAccess.getLastErrMsg());
        }
        this->InnerInit();
        if (_clearCompletionFlag)
        {
            u_int32_t completionFlagByteMask = 0x000000C0;
            u_int32_t completionFlag = ReadDWord(CDB_CMD_COMPLETE_FLAG_ADDRESS) & completionFlagByteMask;
            CDB_ACCESS_DPRINTF(("CmisCdbAccess::Init cleared completion flag, read value: 0x%x\n", completionFlag));
        }
    }
}

void CmisCdbAccess::InitCommandHeader(u_int16_t code, PayloadMethod payloadMethod, const vector<u_int8_t>& payload)
{
    CDB_ACCESS_DPRINTF(("CmisCdbAccess::InitCommandHeader\n"));
    u_int16_t payloadSize = payload.size();
    memset(&_header, 0, sizeof(_header));

    if (payloadMethod == EPL)
    {
        if (payloadSize > CDB_EPL_PAYLOAD_MAX_SIZE)
        {
            throw CmisCdbAccessException("EPL payload size is too big.");
        }
        _header.eplLength = __be16_to_cpu(payloadSize); // eplLength field MSB is the first byte
    }
    else if (payloadMethod == LPL)
    {
        if (payloadSize > CDB_LPL_PAYLOAD_MAX_SIZE)
        {
            throw CmisCdbAccessException("LPL payload size is too big.");
        }
        _header.lplLength = (u_int8_t)payloadSize; // lplLength field MSB is the first byte
    }
    else
    {
        throw CmisCdbAccessException("payload method for CDB command must be EPL or LPL.");
    }
    _header.command = code;

    _header.cdbChkCode = CalcChkCode(payloadMethod, payload);

    SetStatusWaitingTime(code);

    CDB_ACCESS_DPRINTF(("_header.command %#x\n", _header.command));
    CDB_ACCESS_DPRINTF(("_header.eplLength %#x\n", _header.eplLength));
    CDB_ACCESS_DPRINTF(("_header.lplLength %#x\n", _header.lplLength));
    CDB_ACCESS_DPRINTF(("_header.cdbChkCode %#x\n", _header.cdbChkCode));
}

void CmisCdbAccess::SendCommand(u_int16_t code)
{
    // LPL is dummy here
    SendCommand(code, LPL, vector<u_int8_t>(), 0);
}

void CmisCdbAccess::SendCommand(u_int16_t code, PayloadMethod payloadMethod, const vector<u_int8_t>& payload)
{
    SendCommand(code, payloadMethod, payload, 0);
}

vector<u_int8_t> CmisCdbAccess::SendCommand(u_int16_t code, PayloadMethod payloadMethod, u_int32_t outputByteSize)
{
    return SendCommand(code, payloadMethod, vector<u_int8_t>(), outputByteSize);
}

vector<u_int8_t> CmisCdbAccess::SendCommand(u_int16_t code,
                                            PayloadMethod payloadMethod,
                                            const vector<u_int8_t>& payload,
                                            u_int32_t outputByteSize)
{
    CDB_ACCESS_DPRINTF(("CmisCdbAccess::SendCommand - command code %#x, payload size %#x, outputByteSize %#x\n", code,
                        (u_int32_t)payload.size(), outputByteSize));
    vector<u_int8_t> output;
    u_int32_t payloadSize = payload.size();
    u_int16_t payloadAddress = (payloadMethod == EPL) ? CDB_DATA_EPL_ADDRESS : CDB_DATA_LPL_ADDRESS;

    InitCommandHeader(code, payloadMethod, payload);

    if (payloadSize > 0)
    {
        WriteData(payloadAddress, payload.data(), payloadSize);
    }

    // set CDB command header to the selected command.
    // _header.command field triggers the FW to execute the command, so first we set the other fields in the header.
    // when the CDB command header is ready, we write the _header.command.
    WriteData(CDB_CMD_CODE_ADDRESS + sizeof(_header.command), (u_int8_t*)&_header.eplLength,
              sizeof(_header) - sizeof(_header.command));
    WriteData(CDB_CMD_CODE_ADDRESS, (u_int8_t*)&_header.command, sizeof(_header.command));

    CheckStatus();

    if (outputByteSize > 0)
    {
        output = ReadData(payloadAddress, outputByteSize, payloadMethod);
    }

    return output;
}

void CmisCdbAccess::SendCommand(u_int16_t code, const vector<u_int8_t>& lplPayload, const vector<u_int8_t>& eplPayload)
{
    CDB_ACCESS_DPRINTF(("CmisCdbAccess::SendCommand - command code %#x, lpl payload size %#x, epl payload size %#x\n",
                        code, (u_int32_t)lplPayload.size(), (u_int32_t)eplPayload.size()));
    vector<u_int8_t> output;
    u_int32_t eplPayloadSize = eplPayload.size();

    memset(&_header, 0, sizeof(_header));

    _header.eplLength = __be16_to_cpu(eplPayloadSize); // eplLength field MSB is the first byte
    _header.lplLength = (u_int8_t)lplPayload.size();   // lplLength field MSB is the first byte
    _header.command = code;
    _header.cdbChkCode = CalcChkCode(LPL, lplPayload);

    SetStatusWaitingTime(code);

    CDB_ACCESS_DPRINTF(("_header.command %#x\n", _header.command));
    CDB_ACCESS_DPRINTF(("_header.eplLength %#x\n", _header.eplLength));
    CDB_ACCESS_DPRINTF(("_header.lplLength %#x\n", _header.lplLength));
    CDB_ACCESS_DPRINTF(("_header.cdbChkCode %#x\n", _header.cdbChkCode));

    WriteData(CDB_DATA_EPL_ADDRESS, eplPayload.data(), eplPayload.size());
    WriteData(CDB_DATA_LPL_ADDRESS, lplPayload.data(), lplPayload.size());

    // set CDB command header to the selected command.
    // _header.command field triggers the FW to execute the command, so first we set the other fields in the header.
    // when the CDB command header is ready, we write the _header.command.
    WriteData(CDB_CMD_CODE_ADDRESS + sizeof(_header.command), (u_int8_t*)&_header.eplLength,
              sizeof(_header) - sizeof(_header.command));
    WriteData(CDB_CMD_CODE_ADDRESS, (u_int8_t*)&_header.command, sizeof(_header.command));

    CheckStatus();
}

void CmisCdbAccess::CheckStatus()
{
    u_int32_t cdbCommandStatus = 0;
    u_int8_t cdbCommandStatusByte = 0;
    const u_int32_t cdbCommandStatusByteMask = 0x000000FF;
    CdbStatusToErrorMap::const_iterator status = _cdbStatusMap.end();

    WaitForStatusBusyBit();

    // Background commands should raise the completion flag
    if (_isBackgroundCommand)
    {
        WaitForCommandCompletion();
    }

    // in some cases it takes some time for the status to update
    if (_statusWaitingTimeMilliSec != 0)
    {
        msleep(_statusWaitingTimeMilliSec);
    }

    cdbCommandStatus = ReadDWord(CDB_CMD_STATUS_ADDRESS);
    cdbCommandStatusByte = (cdbCommandStatus & cdbCommandStatusByteMask);
    status = _cdbStatusMap.find(cdbCommandStatusByte);

    if (status != _cdbStatusMap.end())
    {
        CDB_ACCESS_DPRINTF(("CheckStatus: code: %#x, msg: %s\n", cdbCommandStatusByte, status->second.second.c_str()));

        if (status->first == 0x81 || status->first == 0x82 || status->first == 0x83)
        {
            int timeoutTimerMillisec = _maxDurationWriteMilliSec;
            const u_int32_t pollingIntervalMillisec = 100;
            while ((status->first == 0x81 || status->first == 0x82 || status->first == 0x83) && timeoutTimerMillisec > 0)
            {
                msleep(pollingIntervalMillisec);
                timeoutTimerMillisec -= pollingIntervalMillisec;

                cdbCommandStatus = ReadDWord(CDB_CMD_STATUS_ADDRESS);
                cdbCommandStatusByte = (cdbCommandStatus & cdbCommandStatusByteMask);
                status = _cdbStatusMap.find(cdbCommandStatusByte);
            }
        }

        if (status->second.first == false)
        {
            throw CmisCdbAccessException(status->second.second);
        }
    }
    else
    {
        std::ostringstream ss;
        ss << std::hex << (int)cdbCommandStatusByte;
        throw UnknownStatusCdbAccessException(ss.str());
    }
}

void CmisCdbAccess::WaitForStatusBusyBit()
{
    CDB_ACCESS_DPRINTF(("Polling CDB status busy bit.\n"));

    const u_int32_t pollingIntervalMillisec = 10;
    const u_int32_t busyBitMask = 0x80;
    int timeoutTimerMillisec = _completionWaitingTimeMilliSec;

    u_int32_t cdbCommandStatus = ReadDWord(CDB_CMD_STATUS_ADDRESS);
    while ((cdbCommandStatus & busyBitMask) && timeoutTimerMillisec > 0)
    {
        msleep(pollingIntervalMillisec);
        timeoutTimerMillisec -= pollingIntervalMillisec;
        cdbCommandStatus = ReadDWord(CDB_CMD_STATUS_ADDRESS);
    }

    if (timeoutTimerMillisec > 0)
    {
        CDB_ACCESS_DPRINTF(("CDB status busy cleared!\n"));
    }
    else
    {
        CDB_ACCESS_DPRINTF(("Timeout while polling CDB status busy bit!\n"));
    }
}

void CmisCdbAccess::WaitForCommandCompletion()
{
    u_int32_t completionFlag = 0;
    u_int32_t completionFlagByteMask = 0x000000C0;
    int timeoutTimerMillisec = _completionWaitingTimeMilliSec;
    const u_int32_t pollingIntervalMillisec = 10;

    // first bit indicating module state change,  modules with one bank might set this bit after CMD 109h instead of
    // completion bit
    if (_header.command == FWManagementCdbAccess::CDB_RUN_FW_IMAGE)
    {
        completionFlagByteMask = 0x000000C1;
    }

    completionFlag = ReadDWord(CDB_CMD_COMPLETE_FLAG_ADDRESS);
    completionFlag &= completionFlagByteMask;

    while (completionFlag == 0 && timeoutTimerMillisec > 0)
    {
        msleep(pollingIntervalMillisec);
        timeoutTimerMillisec -= pollingIntervalMillisec;

        completionFlag = ReadDWord(CDB_CMD_COMPLETE_FLAG_ADDRESS);
        completionFlag &= completionFlagByteMask;
    }

    if (completionFlag != 0)
    {
        CDB_ACCESS_DPRINTF(("Completion flag was raised.\n"));
    }
    else
    {
        if (_isIgnoreCompletionTimeOut)
        {
            CDB_ACCESS_DPRINTF(("Timeout ignored, polling status.\n"));
        }
        else
        {
            throw CmisCdbAccessException("time out while waiting for command completion.");
        }
    }
}

void CmisCdbAccess::WriteData(u_int32_t address, const u_int8_t* payload, u_int32_t payloadSize)
{
    u_int32_t bytesWritten = 0;
    int bytesToWrite = 0;

    while (bytesWritten < payloadSize)
    {
        bytesToWrite = (payloadSize - bytesWritten) > CDB_WRITABLE_BYTES_PER_PAGE ? CDB_WRITABLE_BYTES_PER_PAGE :
                                                                                    (payloadSize - bytesWritten);

        CDB_ACCESS_DPRINTF(("Writing to cable: address %#x, payloadSize %#x\n", address, bytesToWrite));
        if (!_cableAccess.write(address, bytesToWrite, (u_int8_t*)payload + bytesWritten))
        {
            throw CmisCdbAccessException(_cableAccess.getLastErrMsg());
        }

        bytesWritten += bytesToWrite;
        address += CDB_PAGE_INDEX_IN_ADDRESS;
    }
}

vector<u_int8_t> CmisCdbAccess::ReadData(u_int32_t address, u_int32_t outputByteSize, PayloadMethod method)
{
    vector<u_int8_t> output(outputByteSize, 0);
    u_int32_t bytesLeftToRead = outputByteSize;
    u_int32_t bytesToRead = 0;
    int bytesRead = 0;

    if (method == EPL)
    {
        while (bytesLeftToRead > 0)
        {
            bytesToRead = (bytesLeftToRead > CDB_EPL_PAGE_SIZE) ? CDB_EPL_PAGE_SIZE : bytesLeftToRead;

            CDB_ACCESS_DPRINTF(("Reading from cable: address %#x, outputByteSize %#x\n", address, bytesToRead));
            if (!_cableAccess.read(address, bytesToRead, output.data() + bytesRead))
            {
                throw CmisCdbAccessException(_cableAccess.getLastErrMsg());
            }

            bytesRead += bytesToRead;
            bytesLeftToRead -= bytesToRead;
            address += CDB_PAGE_INDEX_IN_ADDRESS;
        }
    }
    else
    {
        CDB_ACCESS_DPRINTF(("Reading from cable: address %#x, outputByteSize %#x\n", address, outputByteSize));
        if (!_cableAccess.read(address, outputByteSize, output.data()))
        {
            throw CmisCdbAccessException(_cableAccess.getLastErrMsg());
        }
    }

    return output;
}

u_int32_t CmisCdbAccess::ReadDWord(u_int32_t address)
{
    vector<u_int8_t> output = ReadData(address, 4, OTHER);
    u_int32_t data = *((u_int32_t*)output.data());
    CDB_ACCESS_DPRINTF(("Reading from cable dword: address %#x, data %#x, \n", address, data));
    return data;
}

u_int8_t CmisCdbAccess::CalcChkCode(PayloadMethod payloadMethod, const vector<u_int8_t>& payload)
{
    if (payloadMethod == EPL)
    {
        return CalcChecksum((u_int8_t*)&_header, sizeof(_header));
    }
    else
    {
        vector<u_int8_t> data(sizeof(_header) + payload.size(), 0);
        memcpy(data.data(), &_header, sizeof(_header));
        std::copy(payload.begin(), payload.end(), data.begin() + sizeof(_header));
        return CalcChecksum(data.data(), data.size());
    }
}

u_int8_t CmisCdbAccess::CalcChecksum(const u_int8_t* byteArray, u_int32_t len)
{
    u_int32_t checksumXORMask = 0xFF;
    u_int32_t tmp = 0x0;
    u_int32_t i = 0;

    for (; i < len; ++i)
    {
        tmp += byteArray[i];
    }

    tmp &= checksumXORMask;

    return (u_int8_t)(tmp ^ checksumXORMask);
}

u_int32_t CmisCdbAccess::GetMaxPayloadSizeInBytes(PayloadMethod payloadMethod)
{
    if (payloadMethod == EPL)
    {
        return CDB_EPL_PAYLOAD_MAX_SIZE;
    }
    else
    {
        return CDB_LPL_PAYLOAD_MAX_SIZE;
    }
}

void CmisCdbAccess::OverrideCommandCompletionWaitingTime(u_int32_t waitTime)
{
    _isCompletionWaitingTimeOverridden = true;
    _completionWaitingTimeMilliSec = waitTime;
}

/********************************************************************************************************************************
 *
 * FWManagementCdbAccess
 *
 ********************************************************************************************************************************/

u_int16_t FWManagementCdbAccess::_lplPayloadMaxSizeBytes = 0;
u_int16_t FWManagementCdbAccess::_eplPayloadMaxSizeBytes = 0;

FWManagementCdbAccess::FWManagementCdbAccess(string mstDevName, bool clearCompletionFlag) :
    CmisCdbAccess(mstDevName, nullptr, clearCompletionFlag),
    _fwUpdateMechanism(NONE_SUPPORTED),
    _startCmdPayloadSize(0),
    _FwMngFeaturesInitialized(false)
{
    _cableAccess.setBurnFlow(true);
}

FWManagementCdbAccess::~FWManagementCdbAccess()
{
    _cableAccess.setBurnFlow(false);
}

void FWManagementCdbAccess::Init(vector<u_int8_t> password)
{
    if (!_isInitDone)
    {
        FWMngFeatures fwMngfeatures;
        vector<u_int8_t> data(sizeof(fwMngfeatures), 0);

        CmisCdbAccess::Init();
        if (!password.empty())
        {
            EnterPassword(password);
        }

        if (!_FwMngFeaturesInitialized)
        {
            SetForegroundCommand();
            data = SendCommand(CDB_FW_MNG_FEATURES, LPL, data.size());
            SetBackgroundCommand();
            memcpy(&fwMngfeatures, data.data(), sizeof(fwMngfeatures));

            SetFWMngFeatures(fwMngfeatures);
        }

        SelectPayloadMechanism();
    }
}

void FWManagementCdbAccess::SetFWMngFeatures(FWMngFeatures fwMngfeatures)
{
    // the following calculations are according to the CMIS 5 spec
    u_int8_t lplNumOfAdditionalBytes = fwMngfeatures.readWriteLengthExt > 15 ? 15 : fwMngfeatures.readWriteLengthExt;
    _lplPayloadMaxSizeBytes = (8 * (1 + lplNumOfAdditionalBytes)) - 8;
    _eplPayloadMaxSizeBytes = (8 * (1 + fwMngfeatures.readWriteLengthExt));

    _fwUpdateMechanism = (WriteReadMechanism)fwMngfeatures.writeMechanism;
    _startCmdPayloadSize = fwMngfeatures.startCmdPayloadSize;

    _FwMngFeaturesInitialized = true;

    CDB_ACCESS_DPRINTF(("lplNumOfAdditionalBytes %#x\n", lplNumOfAdditionalBytes));
    CDB_ACCESS_DPRINTF(("_lplPayloadMaxSizeBytes %#x\n", _lplPayloadMaxSizeBytes));
    CDB_ACCESS_DPRINTF(("_eplPayloadMaxSizeBytes %#x\n", _eplPayloadMaxSizeBytes));
    CDB_ACCESS_DPRINTF(("_fwUpdateMechanism %#x\n", _fwUpdateMechanism));
    CDB_ACCESS_DPRINTF(("_startCmdPayloadSize %#x\n", _startCmdPayloadSize));
    CDB_ACCESS_DPRINTF(("maxDurationCoding %x\n", ((fwMngfeatures.maxDurationCoding >> 3) & 0x1)));
    CDB_ACCESS_DPRINTF(("maxDurationWrite %x\n", fwMngfeatures.maxDurationWrite));

    _maxDurationWriteMilliSec = (fwMngfeatures.maxDurationStart > fwMngfeatures.maxDurationWrite) ?
                                  fwMngfeatures.maxDurationStart :
                                  fwMngfeatures.maxDurationWrite;

    if (_cmisVersion == CMIS_5_0)
    {
        u_int8_t durationMultiplier = (fwMngfeatures.maxDurationCoding >> 3) & 0x1;
        if (durationMultiplier == 1)
        {
            _maxDurationWriteMilliSec *= 10;
        }
    }
}

void FWManagementCdbAccess::SelectPayloadMechanism()
{
    switch (_fwUpdateMechanism)
    {
        case EPL_SUPPORTED:
        case BOTH_SUPPORTED:
            _selectedPayloadMechanism = CmisCdbAccess::PayloadMethod::EPL;
            CDB_ACCESS_DPRINTF(("Using EPL Payload Mechanism\n"));
            break;
        case LPL_SUPPORTED:
            _selectedPayloadMechanism = CmisCdbAccess::PayloadMethod::LPL;
            CDB_ACCESS_DPRINTF(("Using LPL Payload Mechanism\n"));
            break;
        case NONE_SUPPORTED:
            throw CmisCdbAccessException("FW update mechanism is not supported");
        default:
            throw CmisCdbAccessException("Unknown payload mechanism was read from the cable");
    }
}

u_int32_t FWManagementCdbAccess::GetMaxPayloadSizeInBytes(PayloadMethod payloadMethod)
{
    if (payloadMethod == EPL)
    {
        return _eplPayloadMaxSizeBytes;
    }
    else if (payloadMethod == LPL)
    {
        return _lplPayloadMaxSizeBytes;
    }
    else
    {
        throw CmisCdbAccessException("Unknown payload method was provided for max payload size");
    }
}

void FWManagementCdbAccess::SetStatusWaitingTime(u_int16_t command)
{
    switch (command)
    {
        case CDB_WRITE_FW_BLOCK_LPL:
        case CDB_WRITE_FW_BLOCK_EPL:
            if (!_isCompletionWaitingTimeOverridden)
            {
                _completionWaitingTimeMilliSec = 250;
            }
            _statusWaitingTimeMilliSec = 0;
            break;
        default:
            _statusWaitingTimeMilliSec = 1000;
            if (!_isCompletionWaitingTimeOverridden)
            {
                _completionWaitingTimeMilliSec = 10000;
            }
            break;
    }
}

void FWManagementCdbAccess::EnterPassword(vector<u_int8_t> password)
{
    WriteData(CDB_PASSWORD_ENTRY_AREA_ADDRESS, password.data(), password.size());
}

u_int8_t FWManagementCdbAccess::GetNumOfSupportedBanks()
{
    u_int8_t implementedBanks = (u_int8_t)(ReadDWord(CDB_IMPLEMENTED_BANKS_ADDRESS) & 0x3);
    u_int8_t numOfBanks = 0;

    switch (implementedBanks)
    {
        case 0:
            numOfBanks = 1;
            break;
        case 1:
            numOfBanks = 2;
            break;
        case 2:
            numOfBanks = 4;
            break;
        default:
            throw CmisCdbAccessException("Unknown num of implemented banks");
            break;
    }

    return numOfBanks;
}
