/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

#include "fs_checks.h"
#ifndef UEFI_BUILD
   #include <iostream>
   #include <sstream>
#endif

const char*FsChecks::AlignmentUserMessage = "An update is needed for the flash layout.\n"
                                            "The Operation is not failsafe and terminating the process is not allowed.\n";

const char*FsChecks::ShiftingUserMessage = "Shifting between different image partition sizes requires current image "
                                           "to be re-programmed on the flash.\n"
                                           "Once the operation is done, "
                                           "reload FW and run the command again.\n";

bool FsChecks::ExecuteChecks(FwOperations **devFwOps, FwOperations::ExtBurnParams& burnParams, fw_info_t& devInfo)
{
    bool isFsCtrlOperations = false;
    u_int8_t fwType = _devFwOps->FwType();

    if (fwType != FIT_FS3 && fwType != FIT_FS4) {
        return true;
    }

    if (_devInfo.fs3_info.security_mode & SMM_SECURE_FW) {
        return true;
    }

    FwOperations *tempDevFwOps = _devFwOps;

    if (tempDevFwOps->IsFsCtrlOperations()) {
        //Reopen fwops with no fw ctrl
        isFsCtrlOperations = true;
        _isItWasFwControlFlow = true;
        _fwParams.noFwCtrl = true;
        _fwParams.uefiExtra.dev_info.no_fw_ctrl = true;
        tempDevFwOps = FwOperations::FwOperationsCreate(_fwParams);
        if (!tempDevFwOps) {
            return true;
        }
        //We need to query again (no need for rom)
        fw_info_t devInfo2;
        if (!tempDevFwOps->FwQuery(&devInfo2, false)) {
            tempDevFwOps->FwCleanUp();
            delete tempDevFwOps;
            return true;
        }
    }

    //Check if alignment is needed in CX5
    if (fwType == FIT_FS4 &&
        (_burnParams.burnFailsafe ||
         (!_burnParams.burnFailsafe && !_burnParams.useImgDevData))) {
        if (tempDevFwOps->CheckIfAlignmentIsNeeded(_imageFwOps)) {
            _isAlignmentNeeded = true;
            if (isFsCtrlOperations) {
                _isFallBackToRegularFlowNeeded = true;
            }
            _isTimeConsumingFixesNeeded = true;
        }
    }

    //Check if we can burn with mcc:
    if (isFsCtrlOperations && (tempDevFwOps->FwCheckIfWeCanBurnWithFwControl(_imageFwOps) ||
                              (_fwParams.hndlType == FHT_UEFI_DEV && _burnParams.allowPsidChange))) {
        _isFallBackToRegularFlowNeeded = true;
    }

    //Check if shifting is needed
    if (tempDevFwOps->FwCheckIf8MBShiftingNeeded(_imageFwOps, _burnParams)) {
        _is8MBShiftingNeeded = true;
        if (isFsCtrlOperations) {
            _isFallBackToRegularFlowNeeded = true;
        }
        _burnParams.shift8MBIfNeeded = true;
        _isTimeConsumingFixesNeeded = true;
    }

    if (isFsCtrlOperations) {
        if (_isFallBackToRegularFlowNeeded) {
            //do the query again with queryRom = true
            memset(&_devInfo, 0, sizeof(_devInfo));
            _devQueryRes = tempDevFwOps->FwQuery(&_devInfo);
            if (!_devQueryRes) {
                tempDevFwOps->FwCleanUp();
                delete tempDevFwOps;
                return false;
            }
            _devFwOps = tempDevFwOps;
        } else {
            tempDevFwOps->FwCleanUp();
            delete tempDevFwOps;
        }
    }

    UpdateContext(devFwOps, burnParams, devInfo);

    return true;
}

void FsChecks::UpdateContext(FwOperations **devFwOps, FwOperations::ExtBurnParams& burnParams, fw_info_t& devInfo)
{
    if (_isFallBackToRegularFlowNeeded) {
        (*devFwOps)->FwCleanUp();
        delete (*devFwOps);
        (*devFwOps) = _devFwOps;
        devInfo = _devInfo;
    }
    if (_is8MBShiftingNeeded) {
        burnParams = _burnParams;
    }
}

#if !defined(UEFI_BUILD)
string AddIdentToString(const string& ident, const string& s)
{
    std::stringstream ss(s);
    vector<string> lines;

    while (ss.good()) {
        string line;
        getline(ss, line, '\n');
        lines.push_back(line);
    }

    if (lines.size() == 0) {
        return s;
    }

    string newS = "";
    for (size_t i = 0; i < lines.size(); i++) {
        newS += ident + lines[i] + "\n";
    }

    return newS;
}


void FsChecks::GetUserQuestions(vector<string>& questions, const string& ident)
{
    if (_is8MBShiftingNeeded) {
        string question = FsChecks::ShiftingUserMessage;
        questions.push_back(AddIdentToString(ident, question));
    }
    if (_isAlignmentNeeded) {
        string question = FsChecks::AlignmentUserMessage;
        questions.push_back(AddIdentToString(ident, question));
    }

}

#endif
