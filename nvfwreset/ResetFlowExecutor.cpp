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

#include "ResetFlowExecutor.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "reg_access/reg_access.h"
#include "ResetParameterDefs.h"

using namespace mft_core;

#if defined(__linux__) && !defined(__VMKERNEL_UW_NATIVE__)
#include "LinuxResetPlatform.h"
#endif

ResetFlowExecutor::ResetFlowExecutor(mfile* mf,
                                     const ResetFlowParameters& resetParams,
                                     const std::vector<std::string>& asicDBDFTargets) :
    _mf(mf), _resetParams(resetParams)
{
#if defined(__linux__) && !defined(__VMKERNEL_UW_NATIVE__)
    _resetPlatform = new LinuxResetPlatform(mf, _resetParams, asicDBDFTargets);
#else
    (void)asicDBDFTargets;
    throw MftGeneralException("Reset platform not supported for this operating system");
#endif
}

void ResetFlowExecutor::RunResetFlow(const NVFWresetParams& params) const
{
    std::map<ResetKey, std::vector<ResetFlowStep>> resetFlowMap = BuildResetFlow(params.resetFlowSteps);
    std::vector<ResetFlowStep> flowSteps = FindFlowSteps(resetFlowMap);
    ExecuteResetSteps(flowSteps, params.driverIgnoreList);
}

std::map<ResetKey, std::vector<ResetFlowStep>>
  ResetFlowExecutor::BuildResetFlow(const std::vector<unsigned int>& resetFlowSteps) const
{
    std::map<ResetKey, std::vector<ResetFlowStep>> resetFlowMap;

    if (!resetFlowSteps.empty())
    {
        for (const auto& step : resetFlowSteps)
        {
            resetFlowMap[{ResetLevel::PCI_RESET, ResetType::FULL_CHIP, ResetSync::FW_FLOW, ResetMethod::HOT_RESET}]
              .push_back(static_cast<ResetFlowStep>(step));
        }
    }
    else
    {
        resetFlowMap[{ResetLevel::PCI_RESET, ResetType::FULL_CHIP, ResetSync::FW_FLOW, ResetMethod::HOT_RESET}] = {
          ResetFlowStep::PreConditionForHotReset,
          ResetFlowStep::SaveUptimeBeforeReset,
          ResetFlowStep::StopNicDriver,
          ResetFlowStep::SendMFRL,
          ResetFlowStep::HotReset,
          ResetFlowStep::WaitForFWReady,
          ResetFlowStep::StartNicDriver,
          ResetFlowStep::CheckUptimeAfterReset};
    }

    return resetFlowMap;
}

std::vector<ResetFlowStep>
  ResetFlowExecutor::FindFlowSteps(std::map<ResetKey, std::vector<ResetFlowStep>>& resetFlowMap) const
{
    for (const auto& resetFlow : resetFlowMap)
    {
        if (resetFlow.first.level == _resetParams.level && resetFlow.first.type == _resetParams.type &&
            resetFlow.first.sync == _resetParams.sync && resetFlow.first.method == _resetParams.method)
        {
            std::cout << "Reset flow is going to be performed with the reset level: "
                      << static_cast<int>(resetFlow.first.level) << ", type: " << static_cast<int>(resetFlow.first.type)
                      << ", sync: " << static_cast<int>(resetFlow.first.sync)
                      << ", method: " << static_cast<int>(resetFlow.first.method) << std::endl;
            return resetFlow.second;
        }
    }
    throw MftGeneralException("No flow steps found for the given reset parameters");
}

void ResetFlowExecutor::ExecuteResetSteps(std::vector<ResetFlowStep>& flowSteps,
                                          const std::vector<std::string>& driverIgnoreList) const
{
    try
    {
        for (auto step : flowSteps)
        {
            switch (step)
            {
                case ResetFlowStep::StopNicDriver:
                    _resetPlatform->StopNicDriver();
                    break;
                case ResetFlowStep::DisableLinks:
                    _resetPlatform->DisableLinks();
                    break;
                case ResetFlowStep::SendMFRL:
                    _resetPlatform->SendMFRL();
                    break;
                case ResetFlowStep::HotReset:
                    _resetPlatform->HotReset();
                    break;
                case ResetFlowStep::LinkDisableReset:
                    _resetPlatform->LinkDisableReset();
                    break;
                case ResetFlowStep::PciReset:
                    _resetPlatform->PciReset();
                    break;
                case ResetFlowStep::StartNicDriver:
                    _resetPlatform->StartNicDriver();
                    break;
                case ResetFlowStep::WaitForFWReady:
                    _resetPlatform->WaitForFWReady();
                    break;
                case ResetFlowStep::MSTRestart:
                    _resetPlatform->MSTRestart();
                    break;
                case ResetFlowStep::SaveUptimeBeforeReset:
                    _resetPlatform->SaveUptimeBeforeReset();
                    break;
                case ResetFlowStep::CheckUptimeAfterReset:
                    _resetPlatform->CheckUptimeAfterReset();
                    break;
                case ResetFlowStep::PreConditionForHotReset:
                    _resetPlatform->PreConditionForHotReset(driverIgnoreList);
                    break;
                default:
                    throw MftGeneralException("Invalid reset flow step: " + std::to_string(static_cast<int>(step)));
            }
        }
    }
    catch (const std::exception& e)
    {
        throw MftGeneralException(e.what());
    }

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Reset flow completed successfully" << std::endl;
    std::cout << "----------------------------------------" << std::endl;
}