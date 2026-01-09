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

#include <iostream>
#include <map>
#include "ResetPlatformInterface.h"
#include "ResetParameterDefs.h"

std::map<ResetFlowStep, std::string> ResetFlowStepToStringMap = {
  {ResetFlowStep::StopNicDriver, "Stopping NIC driver"},
  {ResetFlowStep::DisableLinks, "Disabling links"},
  {ResetFlowStep::SendMFRL, "Sending MFRL"},
  {ResetFlowStep::PreConditionForHotReset, "Pre-condition for Hot Reset"},
  {ResetFlowStep::HotReset, "Performing Hot Reset"},
  {ResetFlowStep::LinkDisableReset, "Performing Link Disable Reset"},
  {ResetFlowStep::PciReset, "Performing PCI Reset"},
  {ResetFlowStep::StartNicDriver, "Starting NIC driver"},
  {ResetFlowStep::WaitForReady, "Waiting for ready"},
  {ResetFlowStep::MSTRestart, "Restarting MST"},
  {ResetFlowStep::SaveUptimeBeforeReset, "Saving reset uptime before reset"},
  {ResetFlowStep::CheckUptimeAfterReset, "Checking reset uptime after reset"}};

void ResetPlatformInterface::PrintStartResetFlowMessage(ResetFlowStep step)
{
    std::cout << ResetFlowStepToStringMap.at(step) << " - ";
}

void ResetPlatformInterface::PrintEndResetFlowMessage()
{
    std::cout << "Completed successfully" << std::endl;
}

std::string ResetPlatformInterface::ShowResetFlowSteps()
{
    std::string steps = "";
    for (const auto& entry : ResetFlowStepToStringMap)
    {
        steps += std::to_string(static_cast<int>(entry.first)) + ": " + entry.second + "\n";
    }
    return steps;
}