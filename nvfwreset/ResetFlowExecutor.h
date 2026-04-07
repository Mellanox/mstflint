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

#ifndef RESET_FLOW_EXECUTOR_H
#define RESET_FLOW_EXECUTOR_H

#include <string>
#include <vector>
#include <map>
#include "ResetParameterDefs.h"
#include "ResetPlatformInterface.h"
#include "NVFWresetParams.h"
#include "mtcr.h"

class ResetFlowExecutor
{
public:
    ResetFlowExecutor(mfile* mf,
                      const ResetFlowParameters& resetParams,
                      const std::vector<std::string>& asicDBDFTargets);
    void RunResetFlow(const NVFWresetParams& params) const;

private:
    mfile* _mf;
    const ResetFlowParameters& _resetParams;
    ResetPlatformInterface* _resetPlatform;

    std::map<ResetKey, std::vector<ResetFlowStep>> BuildResetFlow(const std::vector<unsigned int>& resetFlowSteps) const;
    std::vector<ResetFlowStep> FindFlowSteps(std::map<ResetKey, std::vector<ResetFlowStep>>& resetFlowMap) const;
    void ExecuteResetSteps(std::vector<ResetFlowStep>& flowSteps,
                           const std::vector<std::string>& driverIgnoreList) const;
};

#endif // RESET_FLOW_EXECUTOR_H