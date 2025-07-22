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

#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <exception>
#include <algorithm>
#include <signal.h>
#include <cstring>
#include "cdb_cable_commander.h"
#include "mft_utils/mft_sig_handler.h"
#include "mft_utils/mft_utils.h"
#include "common/tools_time.h"

#define TOCPUn(s, n)                                \
    do                                              \
    {                                               \
        u_int32_t* p = (u_int32_t*)(s);             \
        for (u_int32_t ii = 0; ii < (n); ii++, p++) \
            *p = __be32_to_cpu(*p);                 \
    } while (0)


/********************************************************************************************************************
 *
 *                                          FwManagementCdbCommander
 *
 ********************************************************************************************************************/

FwManagementCdbCommander::FwManagementCdbCommander(string mstDevName, bool clearCompletionFlag) :
    _modulePasswordSet(false), _fwMngCableAccess(mstDevName, clearCompletionFlag), _timeOutCounter(0)
{
}

void FwManagementCdbCommander::SendFwChunk(CmisCdbAccess::PayloadMethod payloadMethod,
                                           vector<u_int8_t>::const_iterator fwData,
                                           u_int32_t fwChunkSize,
                                           u_int32_t blockAddress)
{
    try
    {
        u_int32_t blockAddressBigEndian = __be32_to_cpu(blockAddress);
        FWManagementCdbAccess::FWManagedCdbCommand command =
          (payloadMethod == CmisCdbAccess::EPL ? FWManagementCdbAccess::CDB_WRITE_FW_BLOCK_EPL :
                                                 FWManagementCdbAccess::CDB_WRITE_FW_BLOCK_LPL);

        if (payloadMethod == CmisCdbAccess::EPL)
        {
            vector<u_int8_t> eplPayload(fwChunkSize, 0);
            vector<u_int8_t> lplPayload(sizeof(blockAddress), 0);

            memcpy(lplPayload.data(), &blockAddressBigEndian, sizeof(blockAddressBigEndian));
            std::copy(fwData, fwData + fwChunkSize, eplPayload.begin());

            _fwMngCableAccess.SendCommand(command, lplPayload, eplPayload);
        }
        else
        {
            vector<u_int8_t> lplPayload(fwChunkSize + sizeof(blockAddress), 0);
            memcpy(lplPayload.data(), &blockAddressBigEndian, sizeof(blockAddressBigEndian));
            std::copy(fwData, fwData + fwChunkSize, lplPayload.begin() + sizeof(blockAddressBigEndian));

            _fwMngCableAccess.SendCommand(command, payloadMethod, lplPayload);
        }
        _timeOutCounter = 0;
    }
    catch (const CmisCdbAccessException& e)
    {
        string msg = "time out while waiting for command completion.";
        if (string(e.what()) == msg)
        {
            _timeOutCounter++;
            if (_timeOutCounter > 7)
            {
                throw e;
            }
            CDB_ACCESS_DPRINTF(("Got timeout, moving on to next chunk"));
        }
        else
        {
            throw e;
        }
    }
}

void FwManagementCdbCommander::DealWithSignalDuringBurn()
{
    int sig;
    sig = mft_signal_is_fired();
    if (sig)
    {
        _fwMngCableAccess.SendCommand(FWManagementCdbAccess::CDB_COMPLETE_FW_DOWNLOAD);
        mft_restore_and_raise();
    }
    else
    {
        mft_signal_set_handling(0);
    }
    return;
}

void FwManagementCdbCommander::DownloadFWImageData(CmisCdbAccess::PayloadMethod payloadMethod,
                                                   u_int32_t fwStartAddress,
                                                   const vector<u_int8_t>& image,
                                                   f_prog_func progressFunc)
{
    u_int32_t blockAddress = 0;
    u_int32_t payloadMaxSize = _fwMngCableAccess.GetMaxPayloadSizeInBytes(payloadMethod);
    if (payloadMethod == CmisCdbAccess::LPL)
    {
        payloadMaxSize -= sizeof(blockAddress);
    }

    vector<u_int8_t>::const_iterator fwData = image.begin() + fwStartAddress;
    u_int32_t fwDatasize = image.end() - fwData;
    u_int32_t maxSizePayloadIterations = fwDatasize / payloadMaxSize;
    int precentage = 0;
    progressFunc(precentage);

    for (u_int32_t i = 0; i < maxSizePayloadIterations; ++i)
    {
        mft_signal_set_handling(1); // Ignoring signals during CMIS download flow
        SendFwChunk(payloadMethod, fwData, payloadMaxSize, blockAddress);
        fwData += payloadMaxSize;
        blockAddress += payloadMaxSize;
        precentage = (i * 100) / maxSizePayloadIterations;
        progressFunc(precentage);
        DealWithSignalDuringBurn();
    }
    // burn image leftover
    u_int32_t remainingImageData = fwDatasize % payloadMaxSize;
    if (remainingImageData > 0)
    {
        mft_signal_set_handling(1); // Ignoring signals during CMIS download flow
        SendFwChunk(payloadMethod, fwData, remainingImageData, blockAddress);
        progressFunc(100);
        DealWithSignalDuringBurn();
    }
}

void FwManagementCdbCommander::StartFWDownload(const vector<u_int8_t>& image, const vector<u_int8_t>& vendorData)
{
    u_int8_t expectedVendorDataSize = _fwMngCableAccess.GetVendorDataSize();
    struct StartFWDownloadPayload startFWDownloadData;
    vector<u_int8_t> payload(sizeof(startFWDownloadData) + expectedVendorDataSize, 0);
    memset(&startFWDownloadData, 0, sizeof(startFWDownloadData));
    u_int32_t imageSize = image.size();

    if (vendorData.empty())
    {
        std::copy(image.data(), image.data() + expectedVendorDataSize, payload.data() + sizeof(startFWDownloadData));
    }
    else
    {
        if (vendorData.size() != expectedVendorDataSize)
        {
            throw CmisCdbAccessException("vendor data file size is not as expected, module accepts " +
                                         to_string(expectedVendorDataSize) + " bytes but " +
                                         to_string(vendorData.size()) + " given.");
        }
        std::copy(vendorData.data(), vendorData.data() + expectedVendorDataSize,
                  payload.data() + sizeof(startFWDownloadData));
        imageSize += expectedVendorDataSize;
    }

    TOCPUn(&imageSize, 1);
    startFWDownloadData.imageSize = imageSize;
    memcpy(payload.data(), &startFWDownloadData, sizeof(startFWDownloadData));

    _fwMngCableAccess.SendCommand(FWManagementCdbAccess::CDB_START_FW_DOWNLOAD, CmisCdbAccess::LPL, payload);
}

void FwManagementCdbCommander::DownloadFWImage(const vector<u_int8_t>& image,
                                               const vector<u_int8_t>& vendorData,
                                               f_prog_func progressFunc)
{
    _fwMngCableAccess.Init(_modulePassword);
    QueryStatus();
    // TODO sig handler with CDB_COMPLETE_FW_DOWNLOAD
    try
    {
        mft_signal_set_handling(1); // Ignoring signals during CMIS download flow
        StartFWDownload(image, vendorData);
        DealWithSignalDuringBurn();
    }
    catch (const CmisCdbAccessException& e)
    {
        string err = "Failed, no specific failure.";

        if (e.what() == err)
        {
            mft_signal_set_handling(1); // Ignoring signals during CMIS download flow
            StartFWDownload(image, vendorData);
            DealWithSignalDuringBurn();
        }
        else
        {
            throw e;
        }
    }
    try
    {
        u_int8_t fwDataStart = (vendorData.size() == 0 ? _fwMngCableAccess.GetVendorDataSize() : 0);
        DownloadFWImageData(_fwMngCableAccess.GetPayloadMechanism(), fwDataStart, image, progressFunc);
    }
    catch (const CmisCdbAccessException& e)
    {
        cout << "FW update failed, " << e.what() << endl << "Aborting..." << endl;
        try
        {
            _fwMngCableAccess.SendCommand(FWManagementCdbAccess::CDB_COMPLETE_FW_DOWNLOAD);
        }
        catch (...)
        {
        }
        throw e;
    }

    _fwMngCableAccess.SendCommand(FWManagementCdbAccess::CDB_COMPLETE_FW_DOWNLOAD);
}

void FwManagementCdbCommander::RunImage(bool performInit)
{
    if (performInit)
    {
        _fwMngCableAccess.Init(_modulePassword);
        QueryStatus();

        cout << "Running FW image..." << endl;
    }
    try
    {
        // CDB_RUN_FW_IMAGE - "Traffic affecting Reset to Inactive Image"
        // Use 30ms delay to avoid R/W errors due to cable reset
        vector<u_int8_t> commandPayload = {0, 0, 0, 30};
        _fwMngCableAccess.SendCommand(FWManagementCdbAccess::CDB_RUN_FW_IMAGE, CmisCdbAccess::LPL, commandPayload);
    }
    catch (const UnknownStatusCdbAccessException& e)
    {
        // due to switching fw banks, the status isn't being updated and we get an error while waiting for it
    }
    if (performInit)
    {
        cout << "Done." << endl;
    }
}

void FwManagementCdbCommander::CommitImage()
{
    _fwMngCableAccess.Init(_modulePassword);
    QueryStatus();

    cout << "Committing FW image..." << endl;
    _fwMngCableAccess.SendCommand(FWManagementCdbAccess::CDB_COMMIT_FW_IMAGE);
    cout << "Done." << endl;
}

void FwManagementCdbCommander::ActivateImage()
{
    _fwMngCableAccess.Init(_modulePassword);
    QueryStatus();

    cout << "Activating burned FW image..." << endl;

    RunImage(false);

    if (_fwMngCableAccess.IsActivationWANeeded())
    {
        msleep(5000); // WA for Hydra - CDB 0h stuck in 0x82
    }
    if (_modulePasswordSet)
    {
        EnterPassword();
    }
    QueryStatus();
    _fwMngCableAccess.SendCommand(FWManagementCdbAccess::CDB_COMMIT_FW_IMAGE);

    cout << "Done." << endl;
}

void FwManagementCdbCommander::QueryStatus()
{
    // sending zeros to CDB_QUERY_STATUS sets response delay to zero
    vector<u_int8_t> commandResponse = _fwMngCableAccess.SendCommand(FWManagementCdbAccess::CDB_QUERY_STATUS,
                                                                     CmisCdbAccess::LPL, vector<u_int8_t>(2, 0), 3);
    QueryStatusResponse status;
    memcpy(&status, commandResponse.data(), sizeof(status));

    if (status.unlockLevelAndPrivileges == 0)
    {
        CDB_ACCESS_DPRINTF(("Module Boot Up.\n"));
    }
    if (status.unlockLevelAndPrivileges == 1)
    {
        CDB_ACCESS_DPRINTF(("Password Accepted.\n"));
    }
    if ((status.unlockLevelAndPrivileges & 0x80) != 0)
    {
        CDB_ACCESS_DPRINTF(("Vendor password accepted.\n"));
    }
}

void FwManagementCdbCommander::SetCommandWaitingTime(string waitTime)
{
    u_int32_t num = 0;
    mft_utils::strToNum(waitTime.c_str(), num, 10);

    _fwMngCableAccess.OverrideCommandCompletionWaitingTime(num);
}

void FwManagementCdbCommander::SetPassword(string password)
{
    vector<u_int8_t> passwordBytes(4, 0);
    u_int32_t num = 0;

    for (u_int32_t i = 0; i < 8; i += 2)
    {
        mft_utils::strToNum(password.substr(i, 2), num, 16);
        passwordBytes[i / 2] = num;
    }

    _modulePassword = passwordBytes;
    _modulePasswordSet = true;
}

void FwManagementCdbCommander::EnterPassword()
{
    _fwMngCableAccess.EnterPassword(_modulePassword);
}

void FwManagementCdbCommander::SetFWMngFeatures(FWManagementCdbAccess::FWMngFeatures fwMngFeatures)
{
    _fwMngCableAccess.SetFWMngFeatures(fwMngFeatures);
}

bool FwManagementCdbCommander::IsActivationNeeded()
{
    u_int8_t numOfBanks = _fwMngCableAccess.GetNumOfSupportedBanks();

    return numOfBanks != 1;
}
