/*
 * Copyright (c) 2021-2024 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef CDB_CABLE_COMMANDER_H
#define CDB_CABLE_COMMANDER_H

#include "cdb_cable_access.h"

typedef int (*f_prog_func)(int completion);

struct CmisFWVersion
{
    u_int8_t major;
    u_int8_t minor;
    u_int16_t build;
    u_int8_t extraString[32];
};

struct FirmwareInfoReply
{
    u_int8_t firmwareStatus;
    u_int8_t imageInformation;
    CmisFWVersion imageAFwVersion;
    CmisFWVersion imageBFwVersion;
    CmisFWVersion factoryFwVersion;
};

class FwManagementCdbCommander
{
public:
    explicit FwManagementCdbCommander(string mstDevName, bool clearCompletionFlag = false);

    string GetCmisFWIndicationStrings();
    void DownloadFWImage(const vector<u_int8_t>& image, const vector<u_int8_t>& vendorData, f_prog_func progressFunc);
    void SetPassword(string password);
    void SetCommandWaitingTime(string waitTime);
    void SetFWMngFeatures(FWManagementCdbAccess::FWMngFeatures fwMngFeatures);
    void ActivateImage();
    void RunImage(bool performInit = true);
    void CommitImage();

private:
    struct StartFWDownloadPayload
    {
        u_int32_t imageSize;
        u_int32_t reserved;
    };

    struct WriteFWBlockLPLPayload
    {
        u_int32_t blockAddress;
        u_int8_t firmwareBlock[116];
    };

    struct QueryStatusResponse
    {
        u_int8_t lengthOfStatus;
        u_int8_t unlockLevelAndPrivileges;
        u_int8_t firmwareDownloadAllowed;
    };

    FirmwareInfoReply GetCmisFWIndication();
    string ParseCmisFWVersion(const CmisFWVersion& fwVersion, string fwImage);
    void QueryStatus();
    void EnterPassword();
    bool IsActivationNeeded();
    void SendFwChunk(CmisCdbAccess::PayloadMethod payloadMethod,
                     vector<u_int8_t>::const_iterator fwChunk,
                     u_int32_t chunkSize,
                     u_int32_t blockAddress);
    void DownloadFWImageData(CmisCdbAccess::PayloadMethod payloadMethod,
                             u_int32_t vendorDataSize,
                             const vector<u_int8_t>& image,
                             f_prog_func progressFunc);
    void StartFWDownload(const vector<u_int8_t>& image, const vector<u_int8_t>& vendorData);
    void DealWithSignalDuringBurn();

    bool _modulePasswordSet;
    vector<u_int8_t> _modulePassword;
    FWManagementCdbAccess _fwMngCableAccess;
    u_int8_t _timeOutCounter;
};

#endif // CDB_CABLE_COMMANDER_H
