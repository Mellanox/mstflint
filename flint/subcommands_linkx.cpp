/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 *  Created on: oCT , 2020
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>
#include <time.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>

#include "mtcr.h"
#include "common/compatibility.h"
#include "fw_comps_mgr/fw_comps_mgr.h"
#include "fw_comps_mgr/fw_comps_mgr_dma_access.h"
#include "mlxfwops/lib/fw_version.h"
#include "subcommands.h"
#include "nvtoolslogger/NvToolsLogger.h"
#include "mft_utils/mft_utils.h"
#include "common/package_error_codes.h"
#include "tools_layouts/cx4fw_layouts.h"

using namespace std;
const char* ImageAState[] = {
  "Image A is running", "Image A is committed, module boots from image A", "Image A is erased / empty", "Reserved",
  "Image B is running", "Image B is committed, module boots from image B", "Image B is erased / empty", "Reserved"};

const char* FwImageBitmap[] = {"FW image A is present",
                               "FW image B is present",
                               "Factory/boot image is present",
                               "Reserved",
                               "Reserved",
                               "Reserved",
                               "Reserved",
                               "Reserved"};

const char* SupportedProtocol[] = {
  "Does not support either one of the FW update procedures",
  "SFF-8636 management interface and pseudo-CMIS FW. Update is supported",
  "CMIS 4.0 is implemented",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
};

const char* ActivationType[] = {
  "HW reset is required. Host should be prepared to power cycle a cable after sending a Run FW Image command.",
  "Self-activation with HW reset contained in the Run FW Image command. No additional actions required from the host.",
  "Self-activation with hitless reset contained in the Run FW Image command. No additional actions required from the host.",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved",
  "Reserved"};

const char* ComponentStatusName[16] = {"NOT_PRESENT", "PRESENT", "IN_USE", "DOWNSTREAM_DEVICE_PRESENT", "Reserved"};

const char* ComponentUpdateStateName[16] = {"IDLE",   "IN_PROGRESS", "APPLIED", "ACTIVE",  "ACTIVE_PENDING_RESET",
                                            "FAILED", "CANCELED",    "BUSY",    "RESERVED"};

void QuerySubCommand::AddTableHeaderForCSVFormat(string& outputString)
{
    outputString += "Host,Device index,Component Index,Component Status,Component Update State";
    outputString += ",Running state,Information block";
    outputString += ",FW A Version,FW B Version,FW Factory Version,SupportedProtocol,Activation type,Serial number\n";
}

bool QuerySubCommand::PrintLinkXQuery(string& outPutString,
                                      const string& host,
                                      int deviceIndex,
                                      const comp_status_st& ComponentStatus,
                                      const component_linkx_st& linkx_data,
                                      char* delimeter,
                                      bool isCSV)
{
    char buffer[4096] = {0};
    sprintf(buffer,
            isCSV ?
              "%s%s%d%s%d%s%s%s%s%s" :
              "Host : %s%s Device index %d%s Component Index %d%s Component Status %s%s Component Update State %s%s ",
            host.c_str(), delimeter, deviceIndex, delimeter, ComponentStatus.component_index, delimeter,
            ComponentStatusName[ComponentStatus.component_status], delimeter,
            ComponentUpdateStateName[ComponentStatus.component_update_state], delimeter);

    outPutString += buffer;
    if (linkx_data.fw_image_status_bitmap != 0)
    {
        if (!isCSV)
        {
            sprintf(buffer, "Running state is : ");
            outPutString += buffer;
        }
        for (int i = 0; i < 8; i++)
        {
            if (linkx_data.fw_image_status_bitmap & (1 << i))
            {
                sprintf(buffer, isCSV ? "%s" : " %s ", ImageAState[i]);
                outPutString += buffer;
            }
        }
        outPutString += delimeter;
    }
    else
    {
        if (isCSV)
        {
            outPutString += delimeter;
        }
    }

    if (linkx_data.fw_image_info_bitmap != 0)
    {
        if (!isCSV)
        {
            sprintf(buffer, "Information block is : ");
            outPutString += buffer;
        }
        for (int i = 0; i < 8; i++)
        {
            if (linkx_data.fw_image_info_bitmap & (1 << i))
            {
                sprintf(buffer, isCSV ? "%s" : " %s ", FwImageBitmap[i]);
                outPutString += buffer;
            }
        }
        outPutString += delimeter;
    }
    else
    {
        if (isCSV)
        {
            outPutString += delimeter;
        }
    }

    sprintf(buffer, isCSV ? "%02d.%02d.%04d%s" : "FW A Version : %02d.%02d.%04d%s", linkx_data.image_a_major,
            linkx_data.image_a_minor, linkx_data.image_a_subminor, delimeter);
    outPutString += buffer;
    sprintf(buffer, isCSV ? "%02d.%02d.%04d%s" : "FW B Version : %02d.%02d.%04d%s", linkx_data.image_b_major,
            linkx_data.image_b_minor, linkx_data.image_b_subminor, delimeter);
    outPutString += buffer;
    sprintf(buffer, isCSV ? "%02d.%02d.%04d%s" : "FW Factory Version : %02d.%02d.%04d%s",
            linkx_data.factory_image_major, linkx_data.factory_image_minor, linkx_data.factory_image_subminor,
            delimeter);
    outPutString += buffer;
    sprintf(buffer, isCSV ? "%s%s" : "SupportedProtocol: %s%s",
            SupportedProtocol[linkx_data.management_interface_protocol], delimeter);
    outPutString += buffer;
    sprintf(buffer, isCSV ? "%s%s" : "Activation type: %s%s", ActivationType[linkx_data.activation_type], delimeter);
    outPutString += buffer;
    sprintf(buffer, isCSV ? "%d" : "Serial number is %d", linkx_data.vendor_sn);
    outPutString += buffer;
    outPutString += "\n";

    return true;
}

FlintStatus QuerySubCommand::QueryLinkX(string deviceName, string outputFile, std::vector<int> deviceIds)
{
    if (preFwOps() == FLINT_FAILED)
    {
        reportErr(true, FLINT_OPEN_FWOPS_DEVICE_ERROR_1, deviceName.c_str());
        return FLINT_FAILED;
    }
    if (_fwOps->IsCableQuerySupported() == false)
    {
        reportErr(true, LINKX_QUERY_DEVICE_NOT_SUPPORTED, deviceName.c_str());
        return FLINT_FAILED;
    }
    FwComponent bootImageComponent;
    std::vector<FwComponent> compsToBurn;
    for (unsigned int i = 0; i < deviceIds.size(); i++)
    {
        if (deviceIds[i] < 0)
        {
            printf("-E- Downstream device id's must be non-negative integers.\n");
            return FLINT_FAILED;
        }
    }
    mfile* mfile = mopen_adv((const char*)deviceName.c_str(), (MType)(MST_DEFAULT));
    if (!mfile)
    {
        reportErr(true, "-E- Failed to open device.\n");
        return FLINT_FAILED;
    }

    string outPutString;
    bool isCSV = false;
    bool finalResult = true;
    char* delimeter = (char*)"\n";
    if (outputFile.empty() == false)
    {
        isCSV = true;
        delimeter = (char*)",";
        AddTableHeaderForCSVFormat(outPutString);
    }

    FwCompsMgr fwCompsAccess(mfile, FwCompsMgr::DEVICE_HCA_SWITCH, 0);
    for (unsigned int i = 0; i < deviceIds.size(); i++)
    {
        int deviceIndex = deviceIds[i] + 1;
        fwCompsAccess.SetIndexAndSize(deviceIndex, 1);
        comp_status_st ComponentStatus;
        if (!fwCompsAccess.RefreshComponentsStatus(&ComponentStatus))
        {
            printf("-E- Refresh components failed, error is %s.\n", fwCompsAccess.getLastErrMsg());
            finalResult = false;
            continue;
        }
        component_linkx_st linkx_data;
        if (!fwCompsAccess.GetComponentLinkxProperties(FwComponent::COMPID_LINKX, &linkx_data))
        {
            printf("-E- Cable query failed, the error is %s.\n", fwCompsAccess.getLastErrMsg());
            finalResult = false;
            continue;
        }
        if (PrintLinkXQuery(outPutString, deviceName, deviceIndex - 1, ComponentStatus, linkx_data, delimeter, isCSV) ==
            false)
        {
            printf("-E- Query function failed.\n");
            finalResult = false;
        }
    }
    if (outputFile.empty() == true)
    {
        printf("%s\n", outPutString.c_str());
    }
    else
    {
        FILE* f = fopen(outputFile.c_str(), "w");
        if (f == NULL)
        {
            printf("-E- Can not open output file %s.\n", outputFile.c_str());
            return FLINT_FAILED;
        }
        fprintf(f, "%s", outPutString.c_str());
        fclose(f);
    }
    if (finalResult == false)
    {
        return FLINT_FAILED;
    }
    return FLINT_SUCCESS;
}

/* A stage can only count up to MCC_MAX_ERROR_COUNT, so one that reached it reports a lower bound, not a total. */
static string formatCableCount(u_int32_t count, bool isCapped)
{
    std::stringstream text;

    text << count << (isCapped ? " or more" : "");
    return text.str();
}

/*
 * The device counts the transfer and the activation separately, so both are always named - a stage that failed
 * nothing reports 0 rather than being left out. The total is a lower bound only when one of the stages actually
 * reached the cap - a large sum on its own is still exact.
 */
/* Cells are built first so the columns can be sized to what is actually in them - the error names vary widely in
 * length and a fixed width would either waste space or push the last column out of line.
 */
string BurnSubCommand::FormatFailureTable(FwCompsMgr& fwCompsAccess,
                                          const std::vector<FwCompsMgr::burn_failure_t>& details)
{
    std::stringstream table;
    std::vector<string> cableCells, mccCells, cdbCells;
    const string cableHeader = "Cable";
    const string mccHeader = "MCC error";
    size_t cableWidth = cableHeader.size();
    size_t mccWidth = mccHeader.size();

    for (std::vector<FwCompsMgr::burn_failure_t>::const_iterator it = details.begin(); it != details.end(); ++it)
    {
        std::stringstream cable;
        /* Reported as the device gives it, matching the index MCC names in the rejection error, so the same cable
         * carries one number in both. */
        cable << (unsigned int)it->module_id;
        std::stringstream mcc;
        mcc << fwCompsAccess.GetMccErrorString(it->mcc_error_code) << " (0x" << std::hex
            << (unsigned int)it->mcc_error_code << ")";
        std::stringstream cdb;
        if (it->cdb_error_code == MCCE_CDB_ERROR_NOT_RELEVANT)
        {
            cdb << "Not Relevant";
        }
        else
        {
            /* MCCE reports the CDB error as a bare 16-bit code - unlike the CDB FW-info reply it carries no
             * component index, so like the MCC column this shows the code alone. */
            cdb << PackageErrorCodeToString(it->cdb_error_code) << " (0x" << std::hex
                << (unsigned int)it->cdb_error_code << ")";
        }
        cableCells.push_back(cable.str());
        mccCells.push_back(mcc.str());
        cdbCells.push_back(cdb.str());
        cableWidth = cable.str().size() > cableWidth ? cable.str().size() : cableWidth;
        mccWidth = mcc.str().size() > mccWidth ? mcc.str().size() : mccWidth;
    }

    const size_t columnGap = 2;
    table << std::left << std::setw((int)(cableWidth + columnGap)) << cableHeader
          << std::setw((int)(mccWidth + columnGap)) << mccHeader << "CDB error\n";
    for (size_t row = 0; row < cableCells.size(); row++)
    {
        table << std::left << std::setw((int)(cableWidth + columnGap)) << cableCells[row]
              << std::setw((int)(mccWidth + columnGap)) << mccCells[row] << cdbCells[row] << "\n";
    }
    return table.str();
}

/* A sibling temp file rather than a fixed name, so a second burn cannot overwrite the previous report. The helper
 * hands back a path rather than an open handle, so the file is reopened here; the report carries nothing sensitive
 * and this matches how the helper is used elsewhere. A report that cannot be saved is not worth failing the burn
 * over, so this stays quiet and the caller has already printed the same text.
 */
static void saveFailureReport(const string& report)
{
    string reportFile = mft_utils::CreateSiblingTempFile("flint_cable_burn_failures");
    if (reportFile.empty())
    {
        MLXFWOPS_LOG_DEBUG("saveFailureReport: no temp file could be created, the report was printed only");
        return;
    }
    FILE* fh = fopen(reportFile.c_str(), "w");
    if (!fh)
    {
        MLXFWOPS_LOG_DEBUG("saveFailureReport: cannot open %s for writing, errno %d", reportFile.c_str(), errno);
        return;
    }
    bool written = fputs(report.c_str(), fh) != EOF;
    /* fclose is where a full disk usually surfaces, since it flushes what fputs buffered. */
    written = (fclose(fh) == 0) && written;
    if (!written)
    {
        MLXFWOPS_LOG_DEBUG("saveFailureReport: writing %s failed, errno %d", reportFile.c_str(), errno);
        return;
    }
    printf("-I- The above was also saved to %s.\n", reportFile.c_str());
}

/* Split from the check below so that this side never has to consider the case where nothing failed: by the time it
 * runs there is something to say, and the only question left is whether the device gave per-cable detail.
 */
void BurnSubCommand::ReportBurnFailures(FwCompsMgr& fwCompsAccess, u_int32_t transfer, u_int32_t activate)
{
    /* The count is a 4-bit field, so reaching MCC_MAX_ERROR_COUNT is the most it can report. */
    bool transferCapped = transfer == MCC_MAX_ERROR_COUNT;
    bool activateCapped = activate == MCC_MAX_ERROR_COUNT;
    /* Built up rather than printed as it goes, so the saved file holds the summary as well as the table. */
    std::stringstream report;
    report << "-W- " << formatCableCount(transfer + activate, transferCapped || activateCapped)
           << " cable(s) failed to burn and were skipped (" << formatCableCount(transfer, transferCapped)
           << " during the image transfer, " << formatCableCount(activate, activateCapped) << " during activation).\n";

    const std::vector<FwCompsMgr::burn_failure_t>& details = fwCompsAccess.GetBurnFailures();
    if (details.empty())
    {
        /* The counters say cables failed but the device logged none of them, so the summary is all there is to
         * show. Either MCCE is unsupported here or the log came back empty, and both are worth knowing about. */
        MLXFWOPS_LOG_DEBUG("ReportBurnFailures: %u transfer and %u activate failures, but the device logged no detail",
                           transfer, activate);
        printf("%s", report.str().c_str());
        return;
    }
    report << FormatFailureTable(fwCompsAccess, details);
    printf("%s", report.str().c_str());
    saveFailureReport(report.str());
}

void BurnSubCommand::ReportSkippedCables(FwCompsMgr& fwCompsAccess)
{
    u_int32_t transfer = fwCompsAccess.GetTransferErrorCount();
    u_int32_t activate = fwCompsAccess.GetActivateErrorCount();

    if (transfer != 0 || activate != 0)
    {
        ReportBurnFailures(fwCompsAccess, transfer, activate);
    }
}

/* Every LinkX burn leads with eight 0xFF bytes ahead of the image. */
#define LINKX_BURN_IMAGE_PREFIX_SIZE 8

FlintStatus BurnSubCommand::BurnLinkX(string deviceName,
                                      int deviceIndex,
                                      int deviceSize,
                                      string binaryFileName,
                                      bool linkx_auto_update,
                                      bool activationNeeded,
                                      bool downloadTransferNeeded,
                                      int activate_delay_sec,
                                      ProgressCallBackAdvSt* funcAdv,
                                      FwComponent::comps_ids_t fwComponent,
                                      bool noStopOnError)
{
    if (preFwOps() == FLINT_FAILED)
    {
        reportErr(true, FLINT_OPEN_FWOPS_DEVICE_ERROR_1, deviceName.c_str());
        return FLINT_FAILED;
    }
    if (_fwOps->IsCableQuerySupported() == false)
    {
        reportErr(true, LINKX_BURN_DEVICE_NOT_SUPPORTED, deviceName.c_str());
        return FLINT_FAILED;
    }
    vector<u_int8_t> binaryData(LINKX_BURN_IMAGE_PREFIX_SIZE, 0xff);
    if (downloadTransferNeeded)
    {
        if (!readFromFile(binaryFileName, binaryData))
        {
            reportErr(true, "Cannot read data from file %s\n.", binaryFileName.c_str());
            return FLINT_FAILED;
        }
    }
    mfile* mfile = mopen_adv((const char*)deviceName.c_str(), (MType)(MST_DEFAULT));
    if (!mfile)
    {
        reportErr(true, "Cannot open device %s\n.", deviceName.c_str());
        return FLINT_FAILED;
    }
    if (linkx_auto_update && activationNeeded && activate_delay_sec == 0 && (mfile->flags & MDEVS_IB) != 0)
    { // IB device
        if (!askUser(
              "The autoupdate activation process may cause a disconnection from the InBand connection, do you want to continue?"))
        {
            mclose(mfile);
            return FLINT_FAILED;
        }
    }
    FwComponent bootImageComponent;
    FwCompsMgr fwCompsAccess(mfile, FwCompsMgr::DEVICE_HCA_SWITCH, 0);
    fwCompsAccess.GenerateHandle();
    if (IS_HCA(_devInfo.fw_info.chip_type) || (!linkx_auto_update && deviceSize == 1 && deviceIndex > 0))
    {
        bool isSecondary = false;
        if (fwComponent != FwComponent::COMPID_LINKX_ELS)
        {
            if (/*(mfile->flags & MDEVS_IB) && */ !fwCompsAccess.IsSecondaryHost(isSecondary)) // TODO - check if limitation
                                                                                            // applicable to IB only
            {
                printf("-E- Failed to query if device is secondary\n");
                return FLINT_FAILED;
            }
            if (isSecondary)
            {
                printf("-E- LinkX burn is not supported by secondary.\n");
                return FLINT_FAILED;
            }
        }
    }
    fwCompsAccess.SetIndexAndSize(deviceIndex + 1, deviceSize, linkx_auto_update, activationNeeded,
                                  downloadTransferNeeded, activate_delay_sec, noStopOnError);
    // With a delay the activate command is only handed to the FW, so its outcome is never read and the failure
    // summary can name transfer errors only. Asked after the call above, which turns the flag off where the FW has no
    // per-cable error reporting and says so itself.
    if (fwCompsAccess.GetNoStopOnError() && activationNeeded && activate_delay_sec > 0)
    {
        printf("-W- With an activation delay, flint does not wait for the activation, so only transfer errors can be "
               "reported.\n"
               "    For activation errors, rerun with --activate_delay_sec 0.\n");
    }
    if (!fwCompsAccess.RefreshComponentsStatus())
    {
        printf("-E- Refresh components failed, error is %s.\n", fwCompsAccess.getLastErrMsg());
        return FLINT_FAILED;
    }

    bootImageComponent.init(binaryData, binaryData.size(), fwComponent);
    if (downloadTransferNeeded)
    {
        printf("-I- Downloading FW ...\n");
        if (fwCompsAccess.isMCDDSupported())
        {
            // Checking if BME is disabled to print indication to user
            bool isBmeSet = DMAComponentAccess::isBMESet(fwCompsAccess.getMfileObj());
            if (!isBmeSet)
            {
                MLXFWOPS_LOG_WARNING("DMA access is not supported due to BME is unset (Bus Master Enable).");
            }
        }
    }
    if (!fwCompsAccess.burnComponents(bootImageComponent, funcAdv))
    {
        char* err_msg = (char*)fwCompsAccess.getLastErrMsg();
        bool IbError = (strcmp("Unknown MAD error", err_msg) == 0);
        if (linkx_auto_update && activationNeeded && activate_delay_sec == 0 && ((mfile->flags & MDEVS_IB) != 0) &&
            IbError)
        { // IB device

            printf(
              "-W- The activation process caused a disconnection from the InBand connection for a few minutes, please wait for reconnection. The error is %s \n",
              fwCompsAccess.getLastErrMsg());
            return FLINT_SUCCESS;
        }
        else
        {
            printf("-E- Cable burn failed, error is %s.\n", fwCompsAccess.getLastErrMsg());
            return FLINT_FAILED;
        }
    }
    else
    {
        printf("-I- Cable burn finished successfully.\n");
        if (noStopOnError)
        {
            ReportSkippedCables(fwCompsAccess);
        }
    }
    return FLINT_SUCCESS;
}
