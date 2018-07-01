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


#ifndef FS_CHECKS_
#define FS_CHECKS_


#include "fw_ops.h"
#if !defined(UEFI_BUILD)
#include <string>
#endif

class MLXFWOP_API FsChecks {
public:
    FsChecks(fw_info_t devInfo, FwOperations *devFwOps, FwOperations *imageFwOps,
             FwOperations::ExtBurnParams burnParams,
             FwOperations::fw_ops_params_t fwParams) :
        _is8MBShiftingNeeded(false), _isAlignmentNeeded(false),
        _isFallBackToRegularFlowNeeded(false), _isItWasFwControlFlow(false),
        _isTimeConsumingFixesNeeded(false), _devQueryRes(false), _devFwOps(devFwOps),
        _imageFwOps(imageFwOps), _burnParams(burnParams), _devInfo(devInfo),
        _fwParams(fwParams) {}
    bool ExecuteChecks(FwOperations **devFwOps, FwOperations::ExtBurnParams& burnParams, fw_info_t& devInfo);
    void UpdateContext(FwOperations **devFwOps, FwOperations::ExtBurnParams& burnParams, fw_info_t& devInfo);
#if !defined(UEFI_BUILD)
    void GetUserQuestions(vector<string>& questions, const string& ident = "");
#endif
    //virtual ~FsChecks()  {};

    static const char *AlignmentUserMessage;
    static const char *ShiftingUserMessage;

    bool _is8MBShiftingNeeded;
    bool _isAlignmentNeeded;
    bool _isFallBackToRegularFlowNeeded;
    bool _isItWasFwControlFlow;
    bool _isTimeConsumingFixesNeeded;
    bool _devQueryRes;
    FwOperations *_devFwOps;
    FwOperations *_imageFwOps;
    FwOperations::ExtBurnParams _burnParams;
    fw_info_t _devInfo;
    FwOperations::fw_ops_params_t _fwParams;

};

#endif // FS_CHECKS_
