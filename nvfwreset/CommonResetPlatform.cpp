#include "CommonResetPlatform.h"
#include "mft_core/mft_core_utils/mft_exceptions/MftGeneralException.h"
#include "ResetParameterDefs.h"
#include "reg_access/reg_access.h"
#include "tools_layouts/reg_access_hca_layouts.h"
#include "mft_core/mft_core_utils/logger/Logger.h"
#include "common/tools_string.h"

CommonResetPlatform::CommonResetPlatform(mfile* mf,
                                         const ResetFlowParameters& resetParams,
                                         const std::vector<std::string>& asicDBDFTargets) :
    ResetPlatformInterface(mf, resetParams, asicDBDFTargets)
{
    _operatingSystemAPI = FactoryOperatingSystemAPI::GetInstance();
}

void CommonResetPlatform::SaveUptimeBeforeReset()
{
    PrintStartResetFlowMessage(ResetFlowStep::SaveUptimeBeforeReset);
    LOG.Debug("CommonResetPlatform::SaveUptimeBeforeReset");

    reg_access_hca_mgir_ext mgir;
    memset(&mgir, 0, sizeof(mgir));
    reg_access_status_t status = reg_access_mgir(_mf, REG_ACCESS_METHOD_GET, &mgir);
    if (status != ME_REG_ACCESS_OK)
    {
        throw mft_core::MftGeneralException(
          nbu::mft::common::string_format("Failed to send %s: %s", "MGIR", reg_access_err2str(status)));
    }
    _uptimeBeforeReset = mgir.hw_info.uptime;
    LOG.Debug("CommonResetPlatform::SaveUptimeBeforeReset - MGIR.uptime=" + std::to_string(_uptimeBeforeReset));
    PrintEndResetFlowMessage();
}

void CommonResetPlatform::CheckUptimeAfterReset()
{
    PrintStartResetFlowMessage(ResetFlowStep::CheckUptimeAfterReset);
    LOG.Debug("CommonResetPlatform::CheckUptimeAfterReset");

    reg_access_hca_mgir_ext mgir;
    memset(&mgir, 0, sizeof(mgir));
    reg_access_status_t status = reg_access_mgir(_mf, REG_ACCESS_METHOD_GET, &mgir);
    if (status != ME_REG_ACCESS_OK)
    {
        throw mft_core::MftGeneralException(
          nbu::mft::common::string_format("Failed to send %s: %s", "MGIR", reg_access_err2str(status)));
    }
    if (mgir.hw_info.uptime < _uptimeBeforeReset)
    {
        throw mft_core::MftGeneralException(
          nbu::mft::common::string_format("Uptime after reset is less than uptime before reset, reset not completed"));
    }
    LOG.Debug("CommonResetPlatform::CheckUptimeAfterReset - MGIR.uptime=" + std::to_string(mgir.hw_info.uptime));
    PrintEndResetFlowMessage();
}

void CommonResetPlatform::SendMFRL()
{
    PrintStartResetFlowMessage(ResetFlowStep::SendMFRL);
    struct reg_access_hca_mfrl_reg_ext mfrl;
    memset(&mfrl, 0, sizeof(mfrl));
    mfrl.reset_trigger = static_cast<u_int8_t>(_resetParams.level);
    mfrl.rst_type_sel = static_cast<u_int8_t>(_resetParams.type);
    mfrl.pci_sync_for_fw_update_start = static_cast<u_int8_t>(_resetParams.sync);
    mfrl.pci_reset_req_method = static_cast<u_int8_t>(_resetParams.method);
    LOG.Info("CommonResetPlatform::SendMFRL: reset_trigger: " + std::to_string(mfrl.reset_trigger) +
             ", rst_type_sel: " + std::to_string(mfrl.rst_type_sel) +
             ", pci_sync_for_fw_update_start: " + std::to_string(mfrl.pci_sync_for_fw_update_start) +
             ", pci_reset_req_method: " + std::to_string(mfrl.pci_reset_req_method));
    reg_access_status_t status = reg_access_mfrl(_mf, REG_ACCESS_METHOD_SET, &mfrl);
    if (status != ME_REG_ACCESS_OK)
    {
        throw mft_core::MftGeneralException(
          nbu::mft::common::string_format("Failed to send %s: %s", "MFRL", reg_access_err2str(status)));
    }
    PrintEndResetFlowMessage();
    LOG.Info("CommonResetPlatform::SendMFRL: MFRL sent successfully");
}