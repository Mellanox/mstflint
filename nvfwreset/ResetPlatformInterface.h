/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef RESET_PLATFORM_INTERFACE_H
#define RESET_PLATFORM_INTERFACE_H

#include "mtcr.h"
#include "ResetParameterDefs.h"
#include <vector>
#include <string>

class ResetPlatformInterface
{
public:
    ResetPlatformInterface(mfile* mf,
                           const ResetFlowParameters& resetParams,
                           const std::vector<std::string>& asicDBDFTargets) :
        _mf(mf), _resetParams(resetParams), _asicDBDFTargets(asicDBDFTargets)
    {
    }
    virtual ~ResetPlatformInterface() {}
    static std::string ShowResetFlowSteps();
    virtual void StopNicDriver() = 0;
    virtual void DisableLinks() = 0;
    virtual void SendMFRL() = 0;
    virtual void HotReset() = 0;
    virtual void LinkDisableReset() = 0;
    virtual void PciReset() = 0;
    virtual void StartNicDriver() = 0;
    virtual void WaitForFWReady() = 0;
    virtual void MSTRestart() = 0;
    virtual void SaveUptimeBeforeReset() = 0;
    virtual void CheckUptimeAfterReset() = 0;
    virtual void PreConditionForHotReset(const std::vector<std::string>& ignoreList) = 0;

protected:
    mfile* _mf;
    unsigned long long _uptimeBeforeReset;
    const ResetFlowParameters _resetParams;
    const std::vector<std::string> _asicDBDFTargets;
    void PrintStartResetFlowMessage(ResetFlowStep step);
    void PrintEndResetFlowMessage();
};

#endif // RESET_PLATFORM_INTERFACE_H