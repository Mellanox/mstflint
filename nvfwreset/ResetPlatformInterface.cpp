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