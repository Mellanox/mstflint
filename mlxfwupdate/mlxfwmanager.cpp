
/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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

#include "mlxfwmanager.h"
#ifdef _MSC_VER
#include <direct.h>
#include <dirent.h>
#endif
#include <string>
#include <iostream>
#include <algorithm>
#include <set>
#include <thread>
#include <mutex>
#include <vector>
#include <cstdarg>
#include <cstdio>

#include "pldmlib/pldm_utils.h"

#define TUPLE_POS_COMPID 0
#define TUPLE_POS_BUFF_PTR 1
#define TUPLE_POS_BUFF_SIZE 2

// Structure to hold device update results for parallel execution
struct DeviceUpdateResult
{
    int device_index;
    int rc;
    bool imageWasCached;
    string log_message;
    string error_message;

    DeviceUpdateResult()
    {
        device_index = -1;
        rc = 0;
        imageWasCached = false;
        log_message = "";
        error_message = "";
    }
};

// Mutex for thread-safe operations during parallel updates
static std::mutex parallel_update_mutex;

// Local device index for per device progress display in parallel mode.
static thread_local int g_progress_device_index = -1;
// Local line number for cursor positioning.
static thread_local int g_progress_line_number = 0;
// Total number of device lines in parallel mode.
static int g_parallel_device_count = 0;
// Extra lines printed.
static int g_extra_output_lines = 0;
// Progress lines are created on first use.
static bool g_progress_lines_created = false;

// ANSI codes for cursor movement.
#define CURSOR_UP "\033[A"
#define CURSOR_DOWN "\033[B"

static void print_progress_at_line(int line, const char* fmt, ...)
{
    if (g_parallel_device_count <= 0 || line <= 0 || line > g_parallel_device_count)
    {
        return;
    }
    // On first use, create N progress lines at the bottom (below any stage messages already printed)
    if (!g_progress_lines_created)
    {
        for (int i = 0; i < g_parallel_device_count; i++)
        {
            print_out("\n");
        }
        g_progress_lines_created = true;
    }
    // Progress lines are the last N lines; from "home" (below them) we go up (N+1 - slot) steps
    int steps = g_parallel_device_count + 1 - line;
    for (int j = 0; j < steps; j++)
    {
        print_out(CURSOR_UP);
    }
    print_out("\r");
    char buf[256];
    va_list args;
    va_start(args, fmt);
    vsnprintf(buf, sizeof(buf), fmt, args);
    va_end(args);
    print_out("%s", buf);
    print_out("\033[K"); // erase to end of line
    for (int j = 0; j < steps; j++)
    {
        print_out(CURSOR_DOWN);
    }
    print_out("\r");
}

// Function from fw_comps_mgr to set log file for library logging
extern "C" void fwcomps_set_log_file(FILE* log_file);

// Function to update a single device (used for both sequential and parallel updates)
void updateSingleDevice(int device_index,
                       MlnxDev* dev,
                       string mfa_file,
                       bool pldmFlow,
                       map<string, vector<tuple<FwComponent::comps_ids_t, u_int8_t*, u_int32_t>>>& psidPldmComponents,
                       int (*progressCB)(int),
                       bool burnFailsafe,
                       f_prog_func_adv advProgressCB,
                       DeviceUpdateResult& result)
{
    result.device_index = device_index;
    result.rc = 0;
    result.imageWasCached = false;
    
    vector<string> questions;
    bool isTimeConsumingFixesNeeded = false;
    
    // preBurn phase
    int rc0 = dev->preBurn(mfa_file, progressCB, burnFailsafe, isTimeConsumingFixesNeeded, questions, advProgressCB);
    
    if (rc0)
    {
        if (abort_request)
        {
            result.error_message = "Interrupted";
            result.rc = ERR_CODE_INTERRUPTED;
        }
        else
        {
            result.error_message = "Fail : " + dev->getLastErrMsg();
            result.rc = rc0;
        }
        return;
    }
    
    // PLDM flow
    if (pldmFlow)
    {
        for (auto comps : (psidPldmComponents[dev->getPsid()]))
        {
            if (std::get<TUPLE_POS_COMPID>(comps) == FwComponent::comps_ids_t::COMPID_BFB)
            {
                if (dev->isBFBSupported())
                {
                    dev->burnPLDMComponent(std::get<TUPLE_POS_COMPID>(comps),
                                          std::get<TUPLE_POS_BUFF_PTR>(comps),
                                          std::get<TUPLE_POS_BUFF_SIZE>(comps));
                }
            }
        }
    }
    
    // Burn phase
    rc0 = dev->burn(result.imageWasCached);
    result.rc = rc0;
    
    if (!rc0)
    {
        result.log_message = "Done";
    }
    else
    {
        if (abort_request)
        {
            result.error_message = "Interrupted";
            result.rc = ERR_CODE_INTERRUPTED;
        }
        else
        {
            result.error_message = "Fail : " + dev->getLastErrMsg();
        }
    }
}

int main(int argc, char* argv[])
{
    try
    {
        return mainEntry(argc, argv);
    }
    catch (runtime_error& e)
    {
        fprintf(stderr, "-E- %s\n", e.what());
        return ERR_CODE_SERVER_RETRIEVE_FAIL;
    }
    catch (const PLDMException& e)
    {
        fprintf(stderr, "-E- %s\n", e._err.c_str());
        return ERR_CODE_INVALID_PLDM_COMPONENT;
    }
}
int mainEntry(int argc, char* argv[])
{
    int res = 0;
    config_t config;
    bool early_cleanup = true;
    bool os_valid;
    int rc, rc0;
    bool pldmFlow = false;
    bool shouldSkip = false;
    vector<string> dev_names;
    vector<MlnxDev*> devs;
    CmdLineParams cmd_params;
    string arch = "";
    int burn_cnt = 0;
    int burn_success_cnt = 0;
    int require_update_cnt = 0;
    vector<string> status_strings;
    map<string, PsidQueryItem> psidUpdateInfo;
    map<string, vector<tuple<FwComponent::comps_ids_t, u_int8_t*, u_int32_t>>> psidPldmComponents;
    vector<string> psid_list;
    vector<string> fw_version_list;
    vector<dm_dev_id_t> dev_types_list;
    vector<string> downloaded_files_names;
    vector<string> mfa_list;
    vector<string> urls_links;
    string mpath;
    int err_continue = 0;
    int devs_num = 0;
    dev_info* devsinfo = NULL;
    string strbuf;
    OutputFmts outfmts;
    PsidLookupDB psidLookupDB;
    string logFileName;
    string outFileName;
    string xml_query;
    string errorMsg = "";
    string logDir;
    int (*progressCB)(int);
    int (*advProgressCB)(int, const char*, prog_t, void*);
    ServerRequest* srq = NULL;
    initHandler();
    CmdLineParser cmdParser(&cmd_params, argv, argc);
    logDir = getLogDir(toolName);
    // parse command line args
    if (!cmdParser.parse(argv, argc))
    {
        res = ERR_CODE_BAD_CMD_ARGS;
        string cmdLine = "";
        for (int i = 1; i < argc; ++i)
        {
            if (cmdLine.length())
            {
                cmdLine += " ";
            }
            cmdLine += argv[i];
        }
        return res;
    }
    if (!initConfig(config, argv, cmd_params))
    {
        res = ERR_CODE_BAD_INI_FILE;
        return res;
    }

    if (!checkCmdParams(cmd_params, config))
    {
        res = ERR_CODE_BAD_CMD_ARGS;
        return res;
    }
    if (cmd_params.calc_crc)
    {
        if (config.mfa_path == ".")
        {
            fprintf(stderr, "-E- Bad command line arguments, image file is mandatory\n");
            return ERR_CODE_BAD_CMD_ARGS;
        }
        return CalcFileCrc((char*)config.mfa_path.c_str());
    }

    if (isServerRequestorRequired(cmd_params))
    {
        srq = new ServerRequest(cmd_params.server_url.c_str(), cmd_params.proxy.c_str(), cmd_params.compare_ffv,
                                cmd_params.show_progress, cmd_params.download_key, cmd_params.certificate,
                                cmd_params.numberOfRetrials);
        if (srq == NULL)
        {
            res = ERR_CODE_MEM_ALLOC_FAIL;
            return res;
        }
    }
    if (cmd_params.query_device || cmd_params.query_device_xml)
    {
        cmd_params.update_fw = 0;
    }

    if (cmd_params.query_device_xml)
    {
        cmd_params.write_xml = true;
    }

    if (cmd_params.device_names.size() != 0 && cmd_params.write_xml && !cmd_params.query_device_xml)
    {
        fprintf(stdout, "-W- XML is not functional when -d is used in  command line\n");
    }
    progressCB = progressCB_nodisplay;
    advProgressCB = NULL;
    if (cmd_params.show_progress)
    {
        if (cmd_params.update_all_fwctl)
        {
            progressCB = progressCB_display_multi_thread;
            advProgressCB = (f_prog_func_adv)&advProgressFunc_display_multi_thread;
        }
        else
        {
            progressCB = progressCB_display;
            advProgressCB = (f_prog_func_adv)&advProgressFunc_display;
        }
    }

    formatted_output = cmd_params.write_xml;
    if (cmd_params.use_output_file)
    {
        strbuf = adjustRelPath(cmd_params.output_file, config.adjuster_path);
    }

    CompareFFV = cmd_params.compare_ffv;

    outfmts.setForceModeParam(cmd_params.force_update);

    if (cmd_params.use_output_file)
    {
        outFileName = adjustRelPath(cmd_params.output_file, config.adjuster_path);
        FOut = createOutFile(outFileName, true);
        if (FOut == NULL)
        {
            fprintf(stderr, "-E- Failed to create an output file %s\n", outFileName.c_str());
            res = ERR_CODE_CREATE_OUTPUT_FILE_FAIL;
            goto early_err_clean_up;
        }
    }
    if (cmd_params.download_os.length())
    {
        IS_OKAY_To_INTERRUPT = true;
        res = check_valid_os_type(cmd_params, &os_valid);
        if (res)
        {
            goto early_err_clean_up;
        }
        if (!os_valid)
        {
            fprintf(stderr, "-E- Invalid --download-os argument \"%s\"\n", cmd_params.download_os.c_str());
            res = ERR_CODE_INVALID_CHOICE;
            goto early_err_clean_up;
        }
        IS_OKAY_To_INTERRUPT = false;
    }
    if (cmd_params.onlineQueryPsids.length())
    {
        if (cmd_params.queryFormat == "text")
        {
            res = handleOnlinePsidsQuery(srq, cmd_params, config);
        }
        else
        {
            res = handleOnlinePsidsQueryXml(srq, cmd_params, config);
        }
        goto clean_up;
    }

    if (cmd_params.get_download_opt != "")
    {
        IS_OKAY_To_INTERRUPT = true;
        res = handleGetDownloadOptionsRequest(srq, cmd_params);
        goto early_err_clean_up;
    }

    if (cmd_params.download)
    {
        IS_OKAY_To_INTERRUPT = true;
        cmd_params.download_dir = adjustRelPath(cmd_params.download_dir, config.adjuster_path);
        if (ImageAccess::hasMFAs(cmd_params.download_dir))
        {
            print_out("-W- '%s' contains MFA images which might conflict with future update on this directory\n\n",
                      cmd_params.download_dir.c_str());
        }
        res = handleDownloadRequest(srq, cmd_params, config);
        goto early_err_clean_up;
    }

    // Listing of binary files content
    if (cmd_params.list_file_contents)
    {
        res = list_files_content(config);
        goto clean_up;
    }

    if (cmd_params.extract_all)
    {
        IS_OKAY_To_INTERRUPT = true;
        res = extract_all(cmd_params, config, srq);
        goto clean_up;
    }

    if (cmd_params.extract_image)
    {
        res = extract_image(cmd_params, config, srq);
        if (cmd_params.update_online)
        {
            RemoveDir(config.mfa_path);
        }
        goto clean_up;
    }

    if ((cmd_params.device_names.size() == 0 || cmd_params.device_names.size() > 1) && cmd_params.clear_semaphore)
    {
        print_err("-E- Please specify a device to clear semaphore for.\n");
        res = ERR_CODE_CLEAR_SEMAPORE;
        goto clean_up;
    }
    if ((cmd_params.device_names.size() == 0 || cmd_params.device_names.size() > 1) && !cmd_params.burnFailsafe)
    {
        print_err("-E- Please specify a device to burn in non failsafe mode.\n");
        res = ERR_CODE_CLEAR_SEMAPORE;
        goto clean_up;
    }
    // Open a log file
    if (cmd_params.create_log || cmd_params.log_on_update)
    {
        if (cmd_params.use_log_file)
        {
            logFileName = adjustRelPath(cmd_params.log_file, config.adjuster_path);
        }
        FLog = createOutFile(logFileName, cmd_params.use_log_file);
        if (FLog == NULL)
        {
            if (!cmd_params.use_log_file)
            {
                fprintf(stderr, "-E- Failed to create a log file in %s\n", logDir.c_str());
            }
            else
            {
                fprintf(stderr, "-E- Failed to write log file %s\n", logFileName.c_str());
            }
            res = ERR_CODE_CREATE_LOG_FAIL;
            goto early_err_clean_up;
        }
        fwcomps_set_log_file(FLog);
        // Print the command line to the log file
        fprintf(FLog, "CMD: %s ", toolName.c_str());
        for (int i = 1; i < argc; i++)
        {
            fprintf(FLog, "%s ", argv[i]);
        }
        fprintf(FLog, "\n");
    }

    // Create Dev list
    if (cmd_params.device_names.size() != 0)
    {
        devs_num = cmd_params.device_names.size();
    }
    else
    {
        devs_num = getLocalDevices(&devsinfo);
        if (devs_num == 0)
        {
            res = ERR_CODE_NO_DEVICES_FOUND;
            res = mapRetValue(res, config.setupType);
            if (cmd_params.write_xml)
            {
                // devs and psidLookupDB are both empty here
                outfmts.createInventoryXML(devs, psidLookupDB, res, getErrStr(res), strbuf, cmd_params.use_output_file);
                if (!cmd_params.use_output_file)
                {
                    printf("%s", strbuf.c_str());
                }
            }
            else
            {
#if defined(ONLY_PCI_FORMAT) || defined(__WIN__)
                print_err("-E- No devices found or specified\n");
#else
                print_err("-E- No devices found or specified, mst might be stopped, run 'mst start' to load MST "
                          "modules\n");
#endif
            }
            goto clean_up;
        }
        else if (devs_num < 0)
        {
            print_err("-E- Failed to retrieve device(s) names\n");
            res = ERR_CODE_FETCH_LOCAL_DEVICES_FAIL;
            goto clean_up;
        }
    }

    // Read Lookup file
    if (cmd_params.use_lookup_file)
    {
        psidLookupDB.readFile(adjustRelPath(cmd_params.lookup_file, config.adjuster_path));
    }
    if (ImageAccess::getFileSignature(config.mfa_path) == IMG_SIG_TYPE_PLDM)
    {
        pldmFlow = true;
    }

    // Query all Devs
    print_out("Querying Mellanox devices firmware ...\n");
    for (int i = 0; i < devs_num; i++)
    {
        MlnxDev* dev;
        if (cmd_params.device_names.size())
        {
            dev = new MlnxDev(cmd_params.device_names[i].c_str(), cmd_params.compare_ffv);
            dm_dev_id_t deviceType = dev->getDeviceType();
            if (dm_is_gpu(deviceType))
            {
                print_err("-E- GPU device is not supported\n");
                delete dev;
                continue;
            }

            if (cmd_params.clear_semaphore)
            {
                if (!dev->clearSemaphore())
                {
                    print_err("-E- Failed to clear semaphore : %s\n", dev->getLastErrMsg().c_str());
                    res = ERR_CODE_CLEAR_SEMAPORE;
                }
                else
                {
                    print_out("-I- Semaphore is cleared!\n");
                    res = 0;
                }
                devs.push_back(dev);
                goto early_err_clean_up;
            }
        }
        else
        {
            if (cmd_params.update_all_fwctl)
            {
                if (!devsinfo[i].pci.fwctl_dev)
                {
                    print_err("-E- Failed to get fwctl device path for device %s\n", devsinfo[i].dev_name);
                    continue;
                }
                else
                {
                    dev = new MlnxDev(devsinfo[i].pci.fwctl_dev, cmd_params.compare_ffv);
                }
            }
            else
            {
                dev = new MlnxDev(&devsinfo[i], cmd_params.compare_ffv);
            }
            dm_dev_id_t deviceType = dev->getDeviceType();
            if (dm_is_gpu(deviceType))
            {
                delete dev;
                continue;
            }
        }
        if (cmd_params.no_fw_ctrl)
        {
            dev->setNoFwCtrl();
        }
        dev->query();
        if (!dev->isQuerySuccess())
        {
            res = ERR_CODE_QUERY_FAILED;
        }
        else
        {
            dev->patchPsidInfo(psidLookupDB.getPsid(dev->getBoardTypeId()));
            if (cmd_params.use_lookup_file && !psidLookupDB.isPsidExist(dev->getPsid()))
            {
                delete dev;
                continue;
            }
        }
        if (dev->checkExistence(devs) == true)
        {
            delete dev;
            continue;
        }
        devs.push_back(dev);
    }
    if (!devs.size())
    {
        print_out("-W- No devices found that match lookup file\n");
    }
    // Get unique PSID list
    getUniquePsidList(devs, psid_list, dev_types_list, fw_version_list);

    // Query MFAs
    if (psid_list.size() > 0)
    {
        mpath = config.mfa_path;
        if (cmd_params.update_online)
        {
            if (CreateTempDir(mpath, config.mfa_path) < 0)
            {
                print_err("-E- Could not create Temp Directory for update\n");
                res = 1;
                goto early_err_clean_up;
            }
            mpath = config.mfa_path;
        }
        else if (cmd_params.use_mfa_file)
        {
            mpath = adjustRelPath(cmd_params.mfa_file, config.adjuster_path);
        }

        if (pldmFlow)
        {
            rc = queryPLDM(cmd_params.mfa_file, psid_list, psidPldmComponents);
        }
        
        rc = queryMFAs(srq, mpath, psid_list, dev_types_list, psidUpdateInfo, cmd_params.update_online, errorMsg, fw_version_list);

        if (rc < 0)
        {
            // print_err("-E- No relevant image files or info could be found\n");
            err_continue++;
        }

        // Get required list of MFAs to download/burn
        getUniqueMFAList(devs, psidUpdateInfo, cmd_params.force_update, mfa_list, downloaded_files_names,
                         cmd_params.skip_if_same);
    }

    rc = checkAndDisplayDeviceQuery1D(devs,
                                      psidUpdateInfo,
                                      psidLookupDB,
                                      cmd_params.update_fw,
                                      (cmd_params.use_mfa_dir || cmd_params.use_mfa_file),
                                      cmd_params.force_update,
                                      cmd_params.query_device,
                                      cmd_params.query_device_xml,
                                      xml_query,
                                      errorMsg,
                                      cmd_params);

    // Error codes returned from checkAndDisplay...
    res = rc;
    if (cmd_params.query_device_xml)
    {
        xml_query = "<Devices>\n" + xml_query + "\n</Devices>";
        print_out_xml("%s\n", xml_query.c_str());
        goto clean_up;
    }
    else if (cmd_params.query_device && !cmd_params.write_xml)
    {
        goto clean_up;
    }

    if (!cmd_params.update_fw ||
        (cmd_params.update_fw && cmd_params.write_xml && (cmd_params.query_device || cmd_params.yes_no_ != 1)))
    {
        if (!res)
        {
            res = rc;
        }
        if (cmd_params.write_xml && cmd_params.device_names.size() == 0)
        {
            outfmts.createInventoryXML(devs, psidLookupDB, res, getErrStr(res), strbuf, cmd_params.use_output_file);
            if (!cmd_params.use_output_file)
            {
                printf("%s", strbuf.c_str());
            }
        }
        goto clean_up;
    }
    print_out("\n");

    // Update devices FW
    // rc = 0;
    burn_cnt = 0;
    burn_success_cnt = 0;
    status_strings.resize(devs.size() + 1);

    for (int i = 0; i < (int)devs.size(); i++)
    {
        if (!devs[i]->isQuerySuccess())
        {
            status_strings[i] = "Device query failed";
            err_continue++;
            continue;
        }
        if (psidUpdateInfo.find(devs[i]->getPsid()) == psidUpdateInfo.end())
        {
            status_strings[i] = "Error - no matching image found";
            err_continue++;
            continue;
        }
        if (psidUpdateInfo[devs[i]->getPsid()].found != 1)
        {
            status_strings[i] = "Error - no matching image found";
            err_continue++;
            continue;
        }

        shouldSkip = cmd_params.skip_if_same && isSameVersion(devs[i], psidUpdateInfo[devs[i]->getPsid()]);
        if (shouldSkip)
        {
            status_strings[i] = "Skipped (same version)";
            continue;
        }

        if (!cmd_params.force_update)
        {
            if (!devs[i]->doesDevNeedUpdate())
            {
                status_strings[i] = "Up to date";
                continue;
            }
        }
        require_update_cnt++;
    }
    if (!cmd_params.force_update)
    {
        if (require_update_cnt != 0)
        {
            int answer = prompt("Perform FW update? [y/N]: ", cmd_params.yes_no_);
            if (!answer)
            {
                print_out("No updates performed\n");
                // res = rc;
                goto clean_up;
            }
        }
        else
        {
            goto early_err_clean_up;
        }
    }

    if (cmd_params.update_online && require_update_cnt)
    {
        // Download relevant files
        if (mfa_list.size() > 0)
        {
            print_out("\n");
            vector<string> dummy;
            rc = download(srq, mfa_list, downloaded_files_names, dummy, config.mfa_path, false);
            if (rc < 0)
            {
                res = ERR_CODE_SERVER_RETRIEVE_FAIL;
                goto clean_up;
            }
        }
    }
    // Parallel or sequential firmware update based on flag
    if (cmd_params.update_all_fwctl && devs.size() > 1)
    {
        // Parallel update mode
        print_out("Starting parallel firmware update for %d device(s)...\n", (int)devs.size());
        
        vector<std::thread> update_threads;
        vector<DeviceUpdateResult> update_results(devs.size());
        vector<string> mfa_files(devs.size());
        
        // Prepare MFA files for each device
        for (int i = 0; i < (int)devs.size(); i++)
        {
            if (status_strings[i].size() != 0)
            {
                continue;
            }
            
            string mfa_file = config.mfa_path;
            string tmp = psidUpdateInfo[devs[i]->getPsid()].url;
            if (!cmd_params.use_mfa_file && !pldmFlow)
            {
                size_t pos = tmp.rfind("/");
                if (pos != string::npos)
                {
                    tmp = tmp.substr(pos + 1);
                }
                mfa_file += "/";
                mfa_file += tmp;
            }
            else
            {
                mfa_file = tmp;
            }
            mfa_files[i] = mfa_file;
        }
        
        // Set total device line count for multi-line progress (2 lines per device: "Updating..." + progress)
        int parallel_device_count = 0;
        for (int i = 0; i < (int)devs.size(); i++)
        {
            if (status_strings[i].size() != 0)
            {
                continue;
            }
            parallel_device_count++;
        }
        g_parallel_device_count = parallel_device_count;
        g_extra_output_lines = 0;
        g_progress_lines_created = false;
        
        // Print all "Updating FW in parallel..." lines first (no blank lines; progress lines created on first use, below stage messages)
        vector<int> parallel_indices;
        for (int i = 0; i < (int)devs.size(); i++)
        {
            if (status_strings[i].size() != 0)
            {
                print_out("Device #%d: %s\n", (i + 1), status_strings[i].c_str());
                continue;
            }

            print_out("Device #%d: Updating FW in parallel...\n", (i + 1));
            burn_cnt++;
            parallel_indices.push_back(i);
        }
        fflush(FOut);
        
        // Now launch all threads. Progress lines (percent) will be created on first progress update and appear below stage messages.
        for (size_t idx = 0; idx < parallel_indices.size(); idx++)
        {
            int i = parallel_indices[idx];
            int line_num = (int)(idx + 1); // slot 1..N; progress line is one of the last N lines (below FSMST etc.)
            
            update_threads.push_back(std::thread([i, line_num, &devs, &mfa_files, &pldmFlow, &psidPldmComponents, 
                                                   progressCB, &cmd_params, advProgressCB, &update_results]() {
                g_progress_device_index = (i + 1);
                g_progress_line_number = line_num;
                updateSingleDevice(i, devs[i], mfa_files[i], pldmFlow, psidPldmComponents,
                                 progressCB, cmd_params.burnFailsafe, advProgressCB, update_results[i]);
                g_progress_device_index = -1;
                g_progress_line_number = 0;
            }));
        }
        
        // Wait for all threads to complete
        for (auto& thread : update_threads)
        {
            if (thread.joinable())
            {
                thread.join();
            }
        }
        g_parallel_device_count = 0;
        g_extra_output_lines = 0;
        g_progress_lines_created = false;
        
        for (int i = 0; i < (int)devs.size(); i++)
        {
            if (status_strings[i].size() != 0)
            {
                continue;
            }
            
            rc0 = update_results[i].rc;
            
            if (rc0 == 0)
            {
                print_out("Device #%d: Done\n", (i + 1));
                burn_success_cnt++;
            }
            else
            {
                if (abort_request)
                {
                    print_out("Device #%d: Interrupted\n", (i + 1));
                    res = ERR_CODE_INTERRUPTED;
                    devs[i]->clearSemaphore();
                }
                else
                {
                    print_out("Device #%d: %s\n", (i + 1), update_results[i].error_message.c_str());
                }
            }
            
            rc |= rc0;
            if (FLog != NULL)
            {
                fprintf(FLog, "Device #%d: %s\n", (i + 1), devs[i]->getLog().c_str());
            }
        }

        return rc;
    }
    else
    {
        // Sequential update mode (original behavior)
        for (int i = 0; i < (int)devs.size(); i++)
        {
            if (status_strings[i].size() != 0)
            {
                print_out("Device #%d: %s\n", (i + 1), status_strings[i].c_str());
                continue;
            }
            else
            {
                print_out("Device #%d: %s", (i + 1), "Updating FW ...     \n");
            }
            burn_cnt++;
            string mfa_file = config.mfa_path;
            string tmp = psidUpdateInfo[devs[i]->getPsid()].url;
            if (!cmd_params.use_mfa_file && !pldmFlow)
            {
                size_t pos = tmp.rfind("/");
                if (pos != string::npos)
                {
                    tmp = tmp.substr(pos + 1);
                }
                mfa_file += "/";
                mfa_file += tmp;
            }
            else
            {
                mfa_file = tmp;
            }
            bool imageWasCached = false;
            vector<string> questions;
            bool isTimeConsumingFixesNeeded = false;
            rc0 = devs[i]->preBurn(mfa_file, progressCB, cmd_params.burnFailsafe, isTimeConsumingFixesNeeded, questions,
                                   advProgressCB);
            if (rc0)
            {
                if (abort_request)
                {
                    print_out("\b\b\b\bInterrupted\n");
                    res = ERR_CODE_INTERRUPTED;
                    devs[i]->clearSemaphore();
                    goto early_err_clean_up;
                }
                else
                {
                    print_out("\b\b\b\bFail : %s \n", devs[i]->getLastErrMsg().c_str());
                }
            }
            else
            {
                for (unsigned int questionIndex = 0; questionIndex < questions.size(); questionIndex++)
                {
                    print_out("%s", questions[questionIndex].c_str());
                    int answer = prompt("Perform update? [y/N]: ", cmd_params.yes_no_);
                    if (!answer)
                    {
                        print_out("No updates performed\n");
                        goto clean_up;
                    }
                }
                if (isTimeConsumingFixesNeeded)
                {
                    print_out("Preparing...\n");
                }
                if (pldmFlow)
                {
                    for (auto comps : (psidPldmComponents[devs[i]->getPsid()]))
                    {
                        if (std::get<TUPLE_POS_COMPID>(comps) == FwComponent::comps_ids_t::COMPID_BFB)
                        {
                            if (devs[i]->isBFBSupported())
                            {
                                devs[i]->burnPLDMComponent(std::get<TUPLE_POS_COMPID>(comps),
                                                           std::get<TUPLE_POS_BUFF_PTR>(comps),
                                                           std::get<TUPLE_POS_BUFF_SIZE>(comps));
                            }
                        }
                    }
                }
                rc0 = devs[i]->burn(imageWasCached);
                if (!rc0)
                {
                    print_out("\b\b\b\bDone\n");
                    burn_success_cnt++;
                    if (imageWasCached)
                    {
                        print_out("Image was successfully cached by driver.\n");
                    }
                }
                else
                {
                    if (abort_request)
                    {
                        print_out("\b\b\b\bInterrupted\n");
                        res = ERR_CODE_INTERRUPTED;
                        devs[i]->clearSemaphore();
                        goto early_err_clean_up;
                    }
                    else
                    {
                        print_out("\b\b\b\bFail : %s \n", devs[i]->getLastErrMsg().c_str());
                    }
                }
            }
            rc |= rc0;
            if (FLog != NULL)
            {
                fprintf(FLog, "%s\n", devs[i]->getLog().c_str());
            }
        }
    }

    if (burn_cnt > 0)
    {
        if (rc)
        {
            res = ERR_CODE_PROG_FAILED;
        }
    }

    if (burn_success_cnt > 0)
    {
        print_out("\nRestart needed for updates to take effect.\n");
    }
    if (err_continue > 0)
    {
        res = 255; // errors were encountered
        print_err("-E- One or more errors were encountered.\n");
    }
    if (burn_success_cnt > 0 && ((burn_success_cnt < burn_cnt) || (err_continue > 0)))
    {
        res = 254; // At least one device was burnt successfully, a failure was encountered at least on other device
    }

    if (cmd_params.update_online && require_update_cnt)
    { //
        RemoveDir(config.mfa_path);
    }
    if (cmd_params.write_xml && cmd_params.device_names.size() == 0)
    {
        outfmts.createBurnXML(devs, psidUpdateInfo, psidLookupDB, strbuf, cmd_params.use_output_file, CompareFFV);
        if (!cmd_params.use_output_file)
        {
            printf("%s", strbuf.c_str());
        }
    }

clean_up:
    // Add clean up for devices in devs vector
    early_cleanup = false;
early_err_clean_up:
    if (early_cleanup)
    {
        if (cmd_params.write_xml)
        {
            outfmts.createFailXML(res, cmd_params.update_fw, strbuf, cmd_params.use_output_file);
            if (!cmd_params.use_output_file)
            {
                printf("%s", strbuf.c_str());
            }
        }
    }
    if (srq != NULL)
    {
        delete srq;
    }
    if (FLog != NULL)
    {
        fclose(FLog);
        if (((burn_cnt && cmd_params.log_on_update) || cmd_params.create_log) && !cmd_params.write_xml)
        {
            printf("Log File: %s\n", logFileName.c_str());
        }
        else
        {
            // delete log
            unlink(logFileName.c_str());
        }
    }

    if (cmd_params.use_output_file)
    {
        if (FOut != NULL)
        {
            fclose(FOut);
        }
    }

    mdevices_info_destroy(devsinfo, devs_num);

    for (int i = 0; i < (int)devs.size(); i++)
    {
        delete devs[i];
    }
    return mapRetValue(res, config.setupType);
}

int extract_all(CmdLineParams& cmd_params, config_t& config, ServerRequest* srq)
{
    ImageAccess imgacc(CompareFFV);
    vector<PsidQueryItem> items;
    string fpath = cmd_params.mfa_file;
    if (fpath == "")
    {
        print_err("-E- Please specify image file to extract, use -i option\n");
        return -1;
    }
    // TODO: list content by image type
    int rc = imgacc.get_file_content(fpath, items);
    if (rc)
    {
        print_err("-E- Error parsing file: %s\n", fpath.c_str());
        return -1;
    }
    print_out("-I- Please wait while extracting images ...\n");
    for (unsigned int i = 0; i < items.size(); i++)
    {
        cmd_params.psid = items[i].psid;
        rc = extract_image(cmd_params, config, srq, true);
        if (rc)
        {
            return rc;
        }
    }
    print_out("\n-I- %d image are extracted successfully\n", (int)items.size());
    return rc;
}
int extract_image(CmdLineParams& cmd_params, config_t& config, ServerRequest* srq, bool useExtractDir)
{
    map<string, PsidQueryItem> psidUpdateInfo;
    vector<string> psid_list;
    vector<dm_dev_id_t> dev_types_list;
    vector<string> fw_version_list;
    string mpath;
    string errorMsg = "";
    int res = 0;
    int rc;
    u_int8_t* filebuf = NULL;
    ImageAccess imgacc(CompareFFV);

    if (ImageAccess::getFileSignature(config.mfa_path) == IMG_SIG_TYPE_PLDM)
    {
        ComponentIdentifier compIdentifier = ComponentIdentifier::Identifier_Not_Valid;
        StringToComponentIdentifier(cmd_params.component_type, compIdentifier);

        u_int32_t buffSize;
        if (!imgacc.loadPldmPkg(config.mfa_path))
        {
            print_err("-E- Can't parse PLDM package.\n");
            res = ERR_CODE_INVALID_PLDM_FORMAT;
            return res;
        }
        if (!imgacc.getPldmComponentByPsid(cmd_params.psid, compIdentifier, &filebuf, buffSize))
        {
            print_err("-E- The component wasn't found in the PLDM package.\n");
            res = ERR_CODE_INVALID_PLDM_COMPONENT;
            return res;
        }
        string targetFile = cmd_params.target_file;

        FILE* f = fopen(targetFile.c_str(), "wb");
        u_int32_t sz = 0;
        if (f != NULL)
        {
            sz = fwrite(filebuf, 1, buffSize, f);
            fclose(f);
            if (sz < buffSize)
            {
                print_err("-E- Failed while writing to file.\n");
                res = ERR_CODE_WRITE_FILE_FAIL;
            }
        }
        else
        {
            print_err("-E- Failed to open %s for writing.\n", targetFile.c_str());
            res = ERR_CODE_WRITE_FILE_FAIL;
        }
        print_out("Done!\n");
    }
    else
    {
        if (cmd_params.psid == "")
        {
            print_err("-E- Need to provide PSID for extraction.\n");
            res = ERR_CODE_BAD_CMD_ARGS;
            return res;
        }

        psid_list.push_back(cmd_params.psid);
        mpath = config.mfa_path;

        if (cmd_params.use_mfa_file)
        {
            mpath = adjustRelPath(cmd_params.mfa_file, config.adjuster_path);
        }

        rc = queryMFAs(srq, mpath, psid_list, dev_types_list, psidUpdateInfo, cmd_params.update_online, errorMsg,
                    fw_version_list);
        if (rc < 0)
        {
            print_err("-E- Failed while reading file(s)\n");
            res = ERR_CODE_IMG_NOT_FOUND;
            return res;
        }
        config.mfa_path = mpath;
        int cnt = psidUpdateInfo.size();
        ssize_t sza = 0;
        if (cnt == 1)
        {
            string srcFile = psidUpdateInfo[cmd_params.psid].url;
            string tag = psidUpdateInfo[cmd_params.psid].selector_tag;
            sza = imgacc.getImage(srcFile.c_str(), cmd_params.psid, tag, 1, &filebuf);
            if (sza > 0)
            {
                string targetFile = cmd_params.target_file;
                if (generateProductionName(targetFile, psidUpdateInfo[cmd_params.psid]))
                {
                    res = ERR_CODE_WRITE_FILE_FAIL;
                    goto clean_up;
                }

                if (useExtractDir)
                {
                    targetFile = cmd_params.extract_dir + (string)PATH_SEPARATOR + targetFile;
                }
                targetFile = adjustRelPath(targetFile, config.adjuster_path);
                print_out("Extracting image for psid: %s to %s  ...\n", cmd_params.psid.c_str(), targetFile.c_str());
                FILE* f = fopen(targetFile.c_str(), "wb");
                int sz = 0;
                if (f != NULL)
                {
                    sz = fwrite(filebuf, 1, sza, f);
                    fclose(f);
                    if (sz < sza)
                    {
                        print_err("-E- Failed while writing to file.\n");
                        res = ERR_CODE_WRITE_FILE_FAIL;
                    }
                }
                else
                {
                    print_err("-E- Failed to open %s for writing.\n", targetFile.c_str());
                    res = ERR_CODE_WRITE_FILE_FAIL;
                }
                print_out("Done!\n");
            }
            else
            {
                print_err("-E- Failed to extract image, MFA file might not have requested PSID\n");
                res = ERR_CODE_INTERNAL_ERR;
            }
        }
        else if (cnt > 1)
        {
            print_err("-E- More than one relevant image found. Not performing extraction!\n");
            res = ERR_CODE_IMG_NOT_FOUND;
        }
        else
        {
            print_err("-E- NO mfa file found!\n");
            res = ERR_CODE_IMG_NOT_FOUND;
        }
    }

clean_up:
    if (filebuf)
    {
        free(filebuf);
    }
    return res;
}

bool checkCmdParams(CmdLineParams& cmd_params, config_t& config)
{
    if (cmd_params.use_mfa_dir)
    {
        if (!isDirectory(adjustRelPath(cmd_params.mfa_dir, config.adjuster_path)))
        {
            fprintf(stderr, "-E- Can't find directory %s\n", cmd_params.mfa_dir.c_str());
            return false;
        }
    }

    if ((cmd_params.download_os.length() || cmd_params.download_type.length() || cmd_params.download_dev.length()) ||
        cmd_params.download_default)
    {
        cmd_params.download = true;
    }

    if (cmd_params.download)
    {
        cmd_params.write_xml = 0;
        if (!isDirectory(adjustRelPath(cmd_params.download_dir, config.adjuster_path)))
        {
            fprintf(stderr, "-E- Can't find directory %s\n", cmd_params.download_dir.c_str());
            return false;
        }
    }

    if (!cmd_params.download &&
        (cmd_params.download_os.length() || cmd_params.download_type.length() || cmd_params.download_dev.length()))
    {
        fprintf(stderr, "-E- Please specify download Directory\n");
        return false;
    }

    if (cmd_params.download_os.length() && cmd_params.download_type.length() && cmd_params.download_dev.length())
    {
        cmd_params.download_default = true;
    }

    if (cmd_params.target_file.length() && !cmd_params.extract_image)
    {
        fprintf(stderr, "-E- Please use --extract option along with extract file\n");
        return false;
    }
    if (cmd_params.use_lookup_file)
    {
        cmd_params.lookup_file = adjustRelPath(cmd_params.lookup_file, config.adjuster_path);
        Filesystem::path p(cmd_params.lookup_file);
        if (!Filesystem::is_regular_file(p))
        {
            fprintf(stderr, "-E- Can't find file %s\n", cmd_params.lookup_file.c_str());
            return false;
        }
    }
    if (cmd_params.use_mfa_file)
    {
        Filesystem::path p(adjustRelPath(cmd_params.mfa_file, config.adjuster_path));
        if (!Filesystem::is_regular_file(p))
        {
            fprintf(stderr, "-E- Can't find file %s\n", cmd_params.mfa_file.c_str());
            return false;
        }
    }
    if (cmd_params.onlineQueryPsids.length() || cmd_params.download || cmd_params.update_online)
    {
        cmd_params.certificate = adjustRelPath(cmd_params.certificate, config.adjuster_path);
        Filesystem::path p(cmd_params.certificate);
        if (!Filesystem::is_regular_file(p))
        {
            fprintf(stderr, "-E- Can't find Certificate %s\n", cmd_params.certificate.c_str());
            return false;
        }
    }
    return true;
}

string adjustRelPath(string path, string adjuster)
{
    string tmp;
    if ((path.size() == 0) || (adjuster.size() == 0))
    {
        return path;
    }

#if defined(__WIN__)
    if (path.find("\\") == std::string::npos)
    {
        ;
    }
    else if (path[0] == '.')
    {
        ;
    }
    else
    {
        return path;
    }
#else
    if (path[0] == '/')
    {
        return path;
    }
#endif
    tmp = adjuster;
    tmp += path;

#if defined(__WIN__)
    char result[1024] = {0};
    GetFullPathName(tmp.c_str(), 1024, result, NULL);
    tmp = result;
    return tmp;
#else
    char* result;
    if ((result = realpath(tmp.c_str(), NULL)) == NULL)
    {
        return tmp;
    }
    else
    {
        tmp.assign(result);
        free(result);
        return tmp;
    }
#endif
}

bool isServerRequestorRequired(CmdLineParams& cmd_params)
{
    return (cmd_params.download || cmd_params.onlineQueryPsids.length() || cmd_params.update_online ||
            cmd_params.get_download_opt.length());
}

int download(ServerRequest* srq,
             vector<string>& url,
             vector<string>& fileNames,
             vector<string>& os,
             string orgPath,
             bool show_location)
{
    int res = 0;
    int rc;
    string error;
    string path = orgPath;
    string newFileName = "";
    if (show_location)
    {
        print_out("Please wait while downloading Files to : '%s'\n", path.c_str());
    }
    else
    {
        IS_OKAY_To_INTERRUPT = true;
        print_out("Please wait while downloading MFA(s) ... ");
    }
    for (unsigned i = 0; i < url.size(); i++)
    {
        if (show_location)
        {
            path = orgPath;
            newFileName = fileNames[i];
            if (os[i] != "all")
            {
                path = path + PATH_SEPARATOR + os[i];
                newFileName = path + PATH_SEPARATOR + newFileName;
                if ((rc = MkDir(path)) != 0 && rc != EEXIST)
                {
                    error += "-E- Failed to download " + newFileName + " " + strerror(rc) + "\n";
                    print_out("\t%d - %s : Failed\n", i, (os[i] + PATH_SEPARATOR + fileNames[i]).c_str());
                    res--;
                    continue;
                }
                newFileName = os[i] + PATH_SEPARATOR + fileNames[i];
            }
            print_out("\t%d - %s : ...", i, (newFileName).c_str());
        }
        if ((rc = srq->download(url[i], path)))
        {
            string errmsg;
            int errnum;
            srq->getError(errnum, errmsg);
            if (show_location)
            {
                error += "-E- Failed to download " + fileNames[i] + ", Error :" + errmsg + "\n";
            }
            else
            {
                error = "-E- Failed to download MFA file(s) from server, Error : " + errmsg + "\n";
            }
            res--;
        }

        if (show_location)
        {
            print_out("%s\n", (rc == 0) ? "\b\b\b\b Done" : "\b\b\b\b Failed");
        }
    }
    print_out("\n");
    if (!show_location)
    {
        IS_OKAY_To_INTERRUPT = false;
    }

    if (res)
    {
        print_err("%s\n", error.c_str());
    }
    return res;
}

int prompt(const char* str, int yes_no_)
{
    int a;
    int res = 0;
    if (yes_no_ == -1)
    {
        if (!formatted_output && (FOut == stdout))
        {
            printf("%s", str);
            std::string answer;
            std::getline(std::cin, answer);
            if (answer.length() > 0)
            {
                a = answer[0];
            }
            else
            {
                a = 'n';
            }
        }
        else
        {
            a = 'n';
        }
    }
    else
    {
        a = (yes_no_) ? 'y' : 'n';
    }

    if (a == 'y' || a == 'Y')
    {
        res = 1;
    }
    return res;
}

int getLocalDevices(dev_info** devs)
{
    int len = 0;

    *devs = mdevices_info(MDEVS_TAVOR_CR, &len);
    if (!len)
    {
        return 0;
    }
    return len;
}

int checkAndDisplayDeviceQuery1D(vector<MlnxDev*>& devs,
                                 map<string, PsidQueryItem>& psidUpdateInfo,
                                 PsidLookupDB& psidLookupDB,
                                 int update_query_,
                                 int img_path_provided,
                                 int force_update,
                                 bool is_query,
                                 bool is_query_xml,
                                 string& xml_query,
                                 string& errorMsg,
                                 CmdLineParams& cmd_params)
{
    unsigned w;
    int res = 0;
    int update_cnt = 0;
    int no_img_cnt = 0;
    int multiple_img_cnt = 0;
    int query_failed_cnt = 0;
    int mixed_versions_cnt = 0;
    int unknown_expansion_rom = 0;
    char fmtdev[64];
    string print_out_str = "";
    string print_err_str = "";
    string xml_output = "";
    string tmpstr;
    bool shouldSkip = false;
    print_out("\n");
    if (devs.size() > 0)
    {
        w = 14;
        sprintf(fmtdev, "%%-%ds", w + 3);
    }

    for (int i = 0; i < (int)devs.size(); i++)
    {
        map<string, bool> expRomTypes;
        map<string, int> devRomTypeIndex;
        map<string, int> availRomTypeIndex;
        string devname = devs[i]->getDevDisplayName();
        string deviceType = devs[i]->getDeviceTypeStr();
        string description;
        string pn = "--";
        string ver = "--";
        string availVer = "";
        bool devQuerySuccess = false;
        bool imgFound = false;
        bool multiple_images_found = false;
        string statusStr;
        bool device_has_unknown_expansionRom = false;
        bool image_has_unknown_expansionRom = false;
        if (devs[i]->isQuerySuccess())
        {
            devQuerySuccess = true;
            pn = devs[i]->getPartNumber();
            if (pn.length())
            {
                ;
                ;
            }
            else if (psidLookupDB.getPN(devs[i]->getBoardTypeId()) != "")
            {
                pn = psidLookupDB.getPN(devs[i]->getBoardTypeId());
            }
            else
            {
                if (psidUpdateInfo.find(devs[i]->getPsid()) != psidUpdateInfo.end())
                {
                    pn = psidUpdateInfo[devs[i]->getPsid()].pns;
                }
                else
                {
                    pn = "";
                }
            }

            ver = devs[i]->getFWVersion(false);
            for (unsigned int j = 0; j < devs[i]->_imageVers.size(); j++)
            {
                expRomTypes[devs[i]->_imageVers[j].getTypeStr()] = true;
                devRomTypeIndex[devs[i]->_imageVers[j].getTypeStr()] = j;
                availRomTypeIndex[devs[i]->_imageVers[j].getTypeStr()] = -1;
            }

            availVer = "N/A";
            description = devs[i]->getDescription();

            if (psidUpdateInfo.find(devs[i]->getPsid()) != psidUpdateInfo.end())
            {
                if (!description.length())
                {
                    description = psidUpdateInfo[devs[i]->getPsid()].description;
                }
                if (psidUpdateInfo[devs[i]->getPsid()].found)
                {
                    imgFound = true;
                    vector<ImgVersion>* imgVers = &psidUpdateInfo[devs[i]->getPsid()].imgVers;
                    for (unsigned int j = 0; j < imgVers->size(); j++)
                    {
                        expRomTypes[(*imgVers)[j].getTypeStr()] = true;
                        availRomTypeIndex[(*imgVers)[j].getTypeStr()] = j;
                        if (devRomTypeIndex.find((*imgVers)[j].getTypeStr()) == devRomTypeIndex.end())
                        {
                            devRomTypeIndex[(*imgVers)[j].getTypeStr()] = -1;
                        }
                    }

                    ImgVersion* fwImgVer = (ImgVersion*)psidUpdateInfo[devs[i]->getPsid()].findImageVersion("FW");
                    if (fwImgVer != NULL)
                    {
                        availVer = fwImgVer->getPrintableVersion(CompareFFV, false);
                    }
                    if (psidUpdateInfo[devs[i]->getPsid()].found > 1)
                    {
                        multiple_img_cnt++;
                        multiple_images_found = true;
                        availVer = "N/A";
                    }
                }
            }
        }

        int nKeepReasons = 0;
        int nUpdateReasons = 0;

        // Check versions of FW components on device against available images for update
        for (map<string, bool>::iterator iter = expRomTypes.begin(); iter != expRomTypes.end(); ++iter)
        {
            string k = iter->first;
            if (k != "FW")
            {
                continue;
            }
            /*
               if (devRomTypeIndex[k] != -1 && devs[i]->_imageVers[devRomTypeIndex[k]].isExpansionRomUnknown()) {
                device_has_unknown_expansionRom = true;
               }

               if (availRomTypeIndex[k] != -1 &&
               psidUpdateInfo[devs[i]->getPsid()].imgVers[availRomTypeIndex[k]].isExpansionRomUnknown()) {
                image_has_unknown_expansionRom = true;
               }*/
            if ((devRomTypeIndex[k] != -1) && (availRomTypeIndex[k] == -1))
            {
                nKeepReasons++;
            }
            if ((devRomTypeIndex[k] == -1) && (availRomTypeIndex[k] != -1))
            {
                nUpdateReasons++;
            }
            if ((devRomTypeIndex[k] != -1) && (availRomTypeIndex[k] != -1))
            {
                ImgVersion* devImgVer = &devs[i]->_imageVers[devRomTypeIndex[k]];
                ImgVersion* fileImgVer = &psidUpdateInfo[devs[i]->getPsid()].imgVers[availRomTypeIndex[k]];

                // u_int16_t fwVer[3] = {3,4,141};
                // psidUpdateInfo[devs[i]->getPsid()].imgVers[1].setVersion("PXE", 3, fwVer);
                if (devImgVer->compareFw(*fileImgVer) < 0)
                {
                    nUpdateReasons++;
                }
                else if (devImgVer->compareFw(*fileImgVer) > 0)
                {
                    nKeepReasons++;
                }
            }
        }

        // Set operation status string per device
        if (!devQuerySuccess)
        {
            statusStr = "Failed to open device";
            tmpstr = "-E- Failed to query " + devs[i]->getDevDisplayName() +
                     " device, error : " + devs[i]->getLastErrMsg() + "\n";
            print_err_str += tmpstr;
            query_failed_cnt++;
            res = ERR_CODE_QUERY_FAILED;
        }
        else
        {
            statusStr = "No matching image found";
            if (multiple_images_found)
            {
                statusStr = "Multiple image files found";
            }
            else if (device_has_unknown_expansionRom)
            {
                statusStr = "Device has unknown expansion rom";
                unknown_expansion_rom++;
            }
            else if (image_has_unknown_expansionRom)
            {
                statusStr = "Image has unknown expansion rom";
                unknown_expansion_rom++;
            }
            else if (imgFound)
            {
                shouldSkip = cmd_params.skip_if_same && isSameVersion(devs[i], psidUpdateInfo[devs[i]->getPsid()]);
                if (shouldSkip)
                {
                    statusStr = "Skipped (same version)";
                }
                else if ((nUpdateReasons > 0) && (nKeepReasons == 0))
                {
                    statusStr = "Update required";
                    devs[i]->setDevToNeedUpdate();
                    update_cnt++;
                }
                else if (force_update)
                {
                    statusStr = "Forced update required";
                    update_cnt++;
                }
                else if ((nUpdateReasons > 0) && (nKeepReasons > 0))
                {
                    statusStr = "N/A (Mixed versions)";
                    mixed_versions_cnt++;
                }
                else if ((nUpdateReasons == 0) && (nKeepReasons >= 0))
                {
                    statusStr = "Up to date";
                }
            }
            else
            {
                no_img_cnt++;
            }
        }

        pn = (pn == "") ? "N/A" : pn;
        if (!is_query_xml)
        {
#if 0
            if (!is_query) {
                printDeviceInfo(i, devname, deviceType, pn, description,
                                statusStr, devs, ver, availVer, expRomTypes, devRomTypeIndex,
                                availRomTypeIndex, psidUpdateInfo, multiple_images_found);
            } else {
                printDeviceInfoQuery(i, devname, deviceType, pn, description,
                                     statusStr, devs, ver, availVer, expRomTypes, devRomTypeIndex,
                                     availRomTypeIndex, psidUpdateInfo, multiple_images_found);
            }
#endif
            printDeviceInfoQuery(i, devname, deviceType, pn, description, statusStr, devs, ver, availVer, expRomTypes,
                                 devRomTypeIndex, availRomTypeIndex, psidUpdateInfo, multiple_images_found);
        }
        else
        {
            if (xml_query.length())
            {
                xml_query += "\n";
            }
            xml_query +=
              generateQueryXML(i, devname, deviceType, pn, description, statusStr, devs, ver, availVer, expRomTypes,
                               devRomTypeIndex, availRomTypeIndex, psidUpdateInfo, multiple_images_found);
        }
    }

    if (is_query || is_query_xml)
    {
        return res;
    }

    if ((update_query_ == 0) || (update_cnt == 0))
    {
        if (update_cnt)
        {
            tmpstr = "Found " + int_to_string(update_cnt) +
                     " device(s) requiring firmware update. Please use -u flag to perform the update.\n";
            print_out_str += tmpstr;
        }
        if (query_failed_cnt > 0)
        {
            res = ERR_CODE_QUERY_FAILED;
        }
        if (img_path_provided)
        {
            if (no_img_cnt > 0)
            {
                tmpstr =
                  "-E- Could not find matching firmware images for " + int_to_string(no_img_cnt) + " device(s).\n";
                print_err_str += tmpstr;
                res = ERR_CODE_IMG_NOT_FOUND;
            }
        }
        if (unknown_expansion_rom)
        {
            tmpstr = "-E- Found Unknown expansion ROM  for " + int_to_string(unknown_expansion_rom) + " device(s).\n";
            print_err_str += tmpstr;
            res = ERR_CODE_UNKNOWN_EXPANSION_ROM;
        }
        if (mixed_versions_cnt > 0)
        {
            tmpstr =
              "-E- Found mixed component image versions for " + int_to_string(mixed_versions_cnt) + " device(s).\n";
            print_err_str += tmpstr;
            res = ERR_CODE_MIXED_VERSIONS_FOUND;
        }
        if (multiple_img_cnt || errorMsg.length())
        {
            print_err_str += errorMsg;
            res = ERR_CODE_MULTI_IMG_SRC_FOUND;
        }

        if (img_path_provided && (no_img_cnt == 0) && (update_cnt == 0) && (query_failed_cnt == 0) &&
            (multiple_img_cnt == 0) && (mixed_versions_cnt == 0) && unknown_expansion_rom == 0)
        {
            tmpstr = "All listed device(s) firmware images are up to date.\n";
            print_out_str += tmpstr;
        }
    }

    if (update_query_)
    {
        if ((no_img_cnt > 0) || (multiple_img_cnt > 0))
        {
            if (no_img_cnt > 0)
            {
#if 0
                sprintf(tmpstr, "-E- Could not find matching firmware images for %d device(s).\n", no_img_cnt);
                print_err_str += tmpstr;
#endif
                res = ERR_CODE_IMG_NOT_FOUND;
            }
#if 0
            if (multiple_img_cnt) {
                sprintf(tmpstr, "-E- Multiple images found for %d device(s) in the provided path.\n", multiple_img_cnt);
                print_err_str += tmpstr;
                res = ERR_CODE_MULTI_IMG_SRC_FOUND;
            }
#endif
        }
        if (update_cnt)
        {
            tmpstr = "Found " + int_to_string(update_cnt) + " device(s) requiring firmware update...\n";
            print_out_str += tmpstr;
        }
    }

    if (print_out_str.size() > 0)
    {
        print_out("---------\n");
        if (update_query_ == 0)
        {
            print_out("%s", print_out_str.c_str());
        }
    }
    if (print_err_str.size() > 0)
    {
        if (print_out_str.size() == 0)
        {
            print_err("---------\n");
        }
        print_err("%s", print_err_str.c_str());
    }

    if (update_query_ != 0)
    {
        if (print_out_str.size() > 0)
        {
            print_out("%s", print_out_str.c_str());
        }
    }
    (void)cmd_params;
    return res;
}

void getUniquePsidList(vector<MlnxDev*>& devs,
                       vector<string>& psid_list,
                       vector<dm_dev_id_t>& dev_types_list,
                       vector<string>& fw_version_list)
{
    for (int i = 0; i < (int)devs.size(); i++)
    {
        if (!devs[i]->isQuerySuccess())
        {
            continue;
        }
        int found = 0;
        for (int j = 0; j < (int)psid_list.size(); j++)
        {
            if (!psid_list[j].compare(devs[i]->getPsid()))
            {
                found = 1;
                break;
            }
        }
        if (!found)
        {
            dev_types_list.push_back(devs[i]->getDeviceType());
            psid_list.push_back(devs[i]->getPsid());
            fw_version_list.push_back(devs[i]->getFWVersion(false, false).c_str());
        }
    }
}

// helper function to check if the current firmware version matches the target version
bool isSameVersion(MlnxDev* dev, PsidQueryItem& psidUpdateInfo)
{
    ImgVersion* fwImgVer = (ImgVersion*)psidUpdateInfo.findImageVersion("FW");
    if (fwImgVer != NULL && dev->compareFWVer(*fwImgVer) == 0)
    {
        return true;
    }
    return false;
}

void getUniqueMFAList(vector<MlnxDev*>& devs,
                      map<string, PsidQueryItem>& psidUpdateInfo,
                      int force_update,
                      vector<string>& mfa_list,
                      vector<string>& mfa_base_name_list,
                      bool skip_if_same)
{
    map<string, int> mfa2download;
    bool shouldSkip = false;

    for (int i = 0; i < (int)devs.size(); i++)
    {
        if (!devs[i]->isQuerySuccess())
        {
            continue;
        }
        if (psidUpdateInfo.find(devs[i]->getPsid()) == psidUpdateInfo.end())
        {
            continue;
        }
        if (!psidUpdateInfo[devs[i]->getPsid()].found)
        {
            continue;
        }

        shouldSkip = skip_if_same && isSameVersion(devs[i], psidUpdateInfo[devs[i]->getPsid()]);
        if (shouldSkip)
        {
            printf("Device %s: Current firmware version matches target version. Skipping update.\n",
                   devs[i]->getDevName().c_str());
            continue;
        }

        if (force_update || (devs[i]->compareFWVer(psidUpdateInfo[devs[i]->getPsid()].imgVers[0]) < 0))
        {
            if (mfa2download.count(psidUpdateInfo[devs[i]->getPsid()].url) == 0)
            {
                mfa_list.push_back(psidUpdateInfo[devs[i]->getPsid()].url);
                mfa_base_name_list.push_back(psidUpdateInfo[devs[i]->getPsid()].name);
            }
            mfa2download[psidUpdateInfo[devs[i]->getPsid()].url] = 1;
        }
    }
}

int isDirectory(string path)
{
    int status;
    struct stat st;

    status = stat(path.c_str(), &st);
    if (status != 0)
    {
        return 0;
    }

    return (S_ISDIR(st.st_mode));
}

int getPLDMCompsListFromPSIDs(string file,
                              vector<string>& psid_list,
                              vector<tuple<PsidQueryItem, u_int8_t*, u_int32_t>>& results,
                              ComponentIdentifier compIdentifier)
{
    int rc = 0;
    ImageAccess imgacc(CompareFFV);
    vector<PsidQueryItem> comps;
    imgacc.loadPldmPkg(file);
    imgacc.getPldmContent(comps, compIdentifier);
    for (auto& comp : comps)
    {
        for (string psid : psid_list)
        {
            if (comp.psid == psid)
            {
                u_int8_t* buff;
                u_int32_t buffSize = 0;
                if (!imgacc.getPldmComponentByPsid(psid, compIdentifier, &buff, buffSize))
                {
                    print_out("-E- can't extract component data from PLDM package.\n");
                    rc = -1;
                }
                comp.compId = imgacc.ToCompId(compIdentifier);
                results.push_back(std::make_tuple(comp, buff, buffSize));
            }
        }
    }
    return rc;
}

int isFile(string path)
{
    int status;
    struct stat st;

    status = stat(path.c_str(), &st);
    if (status != 0)
    {
        return 0;
    }

    return (S_ISREG(st.st_mode));
}

int getMFAListFromPSIDs(string mfa_path, vector<string>& psid_list, vector<PsidQueryItem>& results, string& errorMsg)
{
    int rc;
    ImageAccess imgacc(CompareFFV);
    string arch = "";
    int res = 0;

    for (unsigned i = 0; i < psid_list.size(); i++)
    {
        int _FileOrDir = 0;
        vector<PsidQueryItem> riv;
        PsidQueryItem ri;
        if (isDirectory(mfa_path))
        {
            _FileOrDir = 1;
            rc = imgacc.queryDirPsid(mfa_path, psid_list[i], arch, 1, riv);
            if (imgacc.getlastWarning().length())
            {
                errorMsg += imgacc.getlastWarning();
            }
        }
        else if (Filesystem::is_regular_file(Filesystem::path(mfa_path)))
        {
            _FileOrDir = 2;
            rc = imgacc.queryPsid(mfa_path, psid_list[i], arch, 1, ri);
            if (imgacc.getlastWarning().length())
            {
                errorMsg += imgacc.getlastWarning();
            }
        }
        else
        {
            errorMsg += "-E- Bad path: " + mfa_path + "\n";
            return -1;
        }
        if (rc == 1)
        {
            res++;
        }
        else if (rc == 0)
        {
            // print_err("No image files found for PSID:%s in path: %s\n", psid_list[i].c_str(), mfa_path.c_str());
        }
        else if (rc == -1)
        {
            // print_err("Error querying files for PSID: %s\n",psid_list[i].c_str());
            return -1;
        }
        else if (rc < -1)
        {
            errorMsg +=
              "-E- There are multiple image sources for device with PSID=" + psid_list[i] + " found in files:\n";
            for (unsigned j = 0; j < riv.size(); j++)
            {
                errorMsg += riv[j].url + "\n";
            }
            res = -2;
        }
        if (_FileOrDir == 1)
        {
            if (riv.size() > 0)
            {
                results.push_back(riv[0]);
            }
        }
        else if (_FileOrDir == 2)
        {
            results.push_back(ri);
        }
    }
    return 0;
}

int queryPLDM(string file,
              vector<string>& psid_list,
              map<string, vector<tuple<FwComponent::comps_ids_t, u_int8_t*, u_int32_t>>>& psidPldmComponents)
{
    vector<tuple<PsidQueryItem, u_int8_t*, u_int32_t>> pldmCompsResults;
    getPLDMCompsListFromPSIDs(file, psid_list, pldmCompsResults, ComponentIdentifier::Identifier_BFB_Comp);
    for (unsigned i = 0; i < pldmCompsResults.size(); i++)
    {
        tuple<FwComponent::comps_ids_t, u_int8_t*, u_int32_t> compTuple =
          std::make_tuple(get<TUPLE_POS_COMPID>(pldmCompsResults[i]).compId,
                          get<TUPLE_POS_BUFF_PTR>(pldmCompsResults[i]), get<TUPLE_POS_BUFF_SIZE>(pldmCompsResults[i]));
        psidPldmComponents[get<0>(pldmCompsResults[i]).psid].push_back(compTuple);
    }
    return 0;
}

int queryMFAs(ServerRequest* srq,
              string& mfa_path,
              vector<string>& psid_list,
              vector<dm_dev_id_t>& dev_types_list,
              map<string, PsidQueryItem>& psidUpdateInfo,
              int online_update,
              string& errorMsg,
              vector<string>& fw_version_list)
{
    int res = -1;
    int rc = 0;
    vector<PsidQueryItem> results;
    vector<string> mfaLinks;
    vector<string> fileNames;
    if (online_update && dev_types_list.size())
    {
        // Query online MFAs
        if (srq->updateMFAsRequest(psid_list, dev_types_list, fw_version_list, results) < 0)
        {
            // fprintf(stderr, "-E- Failed during PSID query on server.\n");
            srq->getError(res, errorMsg);
            goto clean_up;
        }
        srq->getError(res, errorMsg);
    }
    else
    {
        // Query Local MFAs
        rc = getMFAListFromPSIDs(mfa_path, psid_list, results, errorMsg);
        if (rc == -1)
        {
            // fprintf(stderr, "-E- Failed during PSID local query.\n");
            goto clean_up;
        }
    }
    for (unsigned i = 0; i < results.size(); i++)
    {
        psidUpdateInfo[results[i].psid] = results[i];
    }
    res = rc; // rc == 0 or rc == -2 (-2 in case of multiple sources per psid)

clean_up:
    return res;
}

FILE* createOutFile(string& fileName, bool fileSpecified)
{
    int rc;
    time_t now;
    tm* ltm;
    char name[100];
    unsigned pid;
    string logDir = getLogDir(toolName);
    if (!fileSpecified)
    {
#if defined(__WIN__)
        pid = (unsigned)GetCurrentProcessId();
        rc = mkdir(logDir.c_str());
#else
        pid = (unsigned)getpid();
        rc = mkdir(logDir.c_str(), 0777);
#endif
        if (rc)
        {
            if (errno != EEXIST)
            {
                return NULL;
            }
        }

        now = time(0);
        ltm = localtime(&now);
        if (ltm == NULL)
        {
            return NULL;
        }
        sprintf(name, "%s-%d%02d%02d_%02d%02d%02d_%u.log", toolName.c_str(), ltm->tm_year + 1900, ltm->tm_mon + 1,
                ltm->tm_mday, ltm->tm_hour, ltm->tm_min, ltm->tm_sec, pid);

        fileName = logDir;
#if defined(__WIN__)
        fileName += "\\";
#else
        fileName += "/";
#endif
        fileName += name;
    }

    FILE* f = fopen(fileName.c_str(), "w");

    return f;
}

int progressCB_display_multi_thread(int completion)
{
    if (g_progress_device_index >= 0 && g_progress_line_number > 0)
    {
        std::lock_guard<std::mutex> lock(parallel_update_mutex);
        print_progress_at_line(g_progress_line_number, "Device #%d: %3d%%   ", g_progress_device_index, completion);
    }
    else if (g_progress_device_index >= 0)
    {
        std::lock_guard<std::mutex> lock(parallel_update_mutex);
        print_out("\rDevice #%d: %3d%%   ", g_progress_device_index, completion);
    }
    else
    {
        print_out("\b\b\b\b%3d%%", completion);
    }
    return abort_request;
}

int advProgressFunc_display_multi_thread(int completion, const char* stage, prog_t type, int* unknownProgress)
{
    if (g_progress_device_index >= 0 && g_progress_line_number > 0)
    {
        std::lock_guard<std::mutex> lock(parallel_update_mutex);
        switch (type)
        {
            case PROG_WITH_PRECENTAGE:
                print_progress_at_line(g_progress_line_number, "Device #%d: %s - %3d%%   ",
                                       g_progress_device_index, stage, completion);
                break;

            case PROG_OK:
                print_out("Device #%d: %s -   OK          \n", g_progress_device_index, stage);
                g_extra_output_lines++;
                break;

            case PROG_STRING_ONLY:
                print_out("Device #%d: %s\n", g_progress_device_index, stage);
                g_extra_output_lines++;
                break;

            case PROG_WITHOUT_PRECENTAGE:
                if (unknownProgress)
                {
                    static const char* progStr[] = {"[.    ]", "[..   ]", "[...  ]", "[.... ]", "[.....]",
                                                    "[ ....]", "[  ...]", "[   ..]", "[    .]", "[     ]"};
                    int size = sizeof(progStr) / sizeof(progStr[0]);
                    print_progress_at_line(g_progress_line_number, "Device #%d: %s - %s   ",
                                           g_progress_device_index, stage, progStr[(*unknownProgress) % size]);
                    (*unknownProgress)++;
                }
                break;
        }
    }
    else if (g_progress_device_index >= 0)
    {
        std::lock_guard<std::mutex> lock(parallel_update_mutex);
        switch (type)
        {
            case PROG_WITH_PRECENTAGE:
                print_out("\rDevice #%d: %s - %3d%%   ", g_progress_device_index, stage, completion);
                break;

            case PROG_OK:
                print_out("\rDevice #%d: %s -   OK          \n", g_progress_device_index, stage);
                break;

            case PROG_STRING_ONLY:
                print_out("Device #%d: %s\n", g_progress_device_index, stage);
                break;

            case PROG_WITHOUT_PRECENTAGE:
                if (unknownProgress)
                {
                    static const char* progStr[] = {"[.    ]", "[..   ]", "[...  ]", "[.... ]", "[.....]",
                                                    "[ ....]", "[  ...]", "[   ..]", "[    .]", "[     ]"};
                    int size = sizeof(progStr) / sizeof(progStr[0]);
                    print_out("\rDevice #%d: %s - %s   ", g_progress_device_index, stage,
                              progStr[(*unknownProgress) % size]);
                    (*unknownProgress)++;
                }
                break;
        }
    }
    else
    {
        switch (type)
        {
            case PROG_WITH_PRECENTAGE:
                print_out("\r%s - %3d%%", stage, completion);
                break;

            case PROG_OK:
                print_out("\r%s -   OK          \n", stage);
                break;

            case PROG_STRING_ONLY:
                print_out("%s\n", stage);
                break;

            case PROG_WITHOUT_PRECENTAGE:
                if (unknownProgress)
                {
                    static const char* progStr[] = {"[.    ]", "[..   ]", "[...  ]", "[.... ]", "[.....]",
                                                    "[ ....]", "[  ...]", "[   ..]", "[    .]", "[     ]"};
                    int size = sizeof(progStr) / sizeof(progStr[0]);
                    print_out("\r%s - %s", stage, progStr[(*unknownProgress) % size]);
                    (*unknownProgress)++;
                }
                break;
        }
    }
    return abort_request;
}

int progressCB_display(int completion)
{
    print_out("\b\b\b\b%3d%%", completion);

    return abort_request;
}

int advProgressFunc_display(int completion, const char* stage, prog_t type, int* unknownProgress)
{
    switch (type)
    {
        case PROG_WITH_PRECENTAGE:
            print_out("\r%s - %3d%%", stage, completion);
            break;

        case PROG_OK:
            print_out("\r%s -   OK          \n", stage);
            break;

        case PROG_STRING_ONLY:
            print_out("%s\n", stage);
            break;

        case PROG_WITHOUT_PRECENTAGE:
            if (unknownProgress)
            {
                static const char* progStr[] = {"[.    ]", "[..   ]", "[...  ]", "[.... ]", "[.....]",
                                                "[ ....]", "[  ...]", "[   ..]", "[    .]", "[     ]"};
                int size = sizeof(progStr) / sizeof(progStr[0]);
                print_out("\r%s - %s", stage, progStr[(*unknownProgress) % size]);
                (*unknownProgress)++;
            }
            break;
    }

    return abort_request;
}

int progressCB_nodisplay(int completion)
{
    (void)completion;
    return abort_request;
}

void getExePath(char* argv[], string& exe_path)
{
    exe_path = argv[0];
    size_t pos = exe_path.rfind("/");
    if (pos != string::npos)
    {
        exe_path = exe_path.substr(0, pos + 1); // Include the slash
    }
    else
    {
        exe_path = "./";
    }
}

#define INI_FILESYSTEM_SECTION "filesystem"
#define INI_SRCDIR_KEY "srcdir"
#define INI_SERVER_SECTION "server"
#define INI_PROXY_KEY "proxy"

bool getIniParams(config_t& config)
{
    string file = config.exe_path;
    file += "/mlxfwmanager.ini";

    Filesystem::path p(file);
    if (!Filesystem::is_regular_file(p))
    { // If file does not exist then ignore
        return true;
    }
    dictionary* ini_dict = iniparser_load(file.c_str());
    if (!ini_dict)
    {
        print_err("-E- Failed to load ini file %s: %s\n", file.c_str(), strerror(errno));
        return false;
    }

    config.mfa_path =
      iniparser_getstring(ini_dict, INI_FILESYSTEM_SECTION ":" INI_SRCDIR_KEY, (char*)config.mfa_path.c_str());
    config.http_proxy =
      iniparser_getstring(ini_dict, INI_SERVER_SECTION ":" INI_PROXY_KEY, (char*)config.http_proxy.c_str());

    if (ini_dict)
    {
        iniparser_freedict(ini_dict);
    }
    return true;
}

bool initConfig(config_t& config, char* argv[], CmdLineParams& cmd_params)
{
    config.display_file_names = false;
    config.path_is_file = false;
    config.adjuster_path = "";
    if (cmd_params.lvim)
    {
        config.setupType = mlxFWMSetupType::lvim;
    }
    else if (cmd_params.dl)
    {
        config.setupType = mlxFWMSetupType::dl;
    }
    else
    {
        config.setupType = mlxFWMSetupType::normal;
    }
    if (cmd_params.current_dir.length())
    {
        config.exe_path = cmd_params.current_dir;
        cmd_params.use_exe_rel_paths = 1;
    }
    else
    {
        char tmpPath[1024] = {0};
#ifdef __WIN__
        DWORD rc = GetCurrDir(1024, tmpPath);
#else
        char* rc = GetCurrDir(1024, tmpPath);
#endif
        (void)rc; // Adrianc: avoiding warrnings the Owner should deal with the return code.
        config.adjuster_path = tmpPath;
        config.adjuster_path += PATH_SEPARATOR;
        getExePath(argv, config.exe_path);
    }

    if (cmd_params.use_exe_rel_paths == 1)
    {
        config.adjuster_path = config.exe_path;
    }

    config.mfa_path = ".";
    config.http_server = cmd_params.server_url;
    config.http_proxy = cmd_params.proxy;

    if (config.adjuster_path[config.adjuster_path.length() - 1] == ' ')
    {
        config.adjuster_path.erase(config.adjuster_path.length() - 1);
    }

    if (cmd_params.update_online)
    {
        config.mfa_path = (string)TMP_DIR + "/online_update_mfa_";
    }

    if (!getIniParams(config))
    {
        return false;
    }

    if (cmd_params.use_mfa_dir)
    {
        config.mfa_path = adjustRelPath(cmd_params.mfa_dir, config.adjuster_path);
    }

    if (cmd_params.use_mfa_file)
    {
        config.mfa_path = adjustRelPath(cmd_params.mfa_file, config.adjuster_path);
        config.path_is_file = true;
    }

    if (cmd_params.display_archive_names)
    {
        config.display_file_names = true;
    }
    cmd_params.extract_dir = adjustRelPath(cmd_params.extract_dir, config.adjuster_path);
    config.psid = cmd_params.psid;
    return true;
}

int list_files_content(config_t& config)
{
    string fname;
    DIR* d;
    struct dirent* dir;
    int rc;
    int res = MLX_FWM_SUCCESS;
    ImageAccess imgacc(CompareFFV);
    bool show_titles = true;
    int displayed_files_cnt = 0;

    if (config.path_is_file)
    {
        vector<PsidQueryItem> items;
        string fpath = config.mfa_path;
        // TODO: list content by image type
        rc = imgacc.get_file_content(fpath, items);
        if (rc)
        {
            print_err("-E- Error parsing file: %s\n", fpath.c_str());
            res = ERR_CODE_FILE_PARSE_FAILED;
        }
        else
        {
            display_file_listing(items, config.psid, show_titles, ImageAccess::getFileSignature(fpath));
        }
    }
    else
    {
        d = opendir(config.mfa_path.c_str());
        if (d == NULL)
        {
            return -1;
        }

        while ((dir = readdir(d)) != NULL)
        {
            string fl = dir->d_name;
            if (fl == "." || fl == "..")
            {
                continue;
            }
            string fpath = config.mfa_path;
            if (fpath.length() > 0)
            {
#if defined(__WIN__)
                if (fpath[fpath.length() - 1] != '\\')
                {
                    fpath += "\\";
                }
#else
                if (fpath[fpath.length() - 1] != '/')
                {
                    fpath += "/";
                }
#endif
            }
            fpath += fl;

            if (imgacc.getFileSignature(fpath) <= 0)
            {
                continue;
            }
            vector<PsidQueryItem> items;
            rc = imgacc.get_file_content(fpath, items);
            if (rc)
            {
                print_err("-E- Error parsing file: %s\n", fpath.c_str());
                res = ERR_CODE_FILE_PARSE_FAILED;
                continue;
            }
            if (config.display_file_names)
            {
                printf("Supported Boards in File: %s\n", fpath.c_str());
                show_titles = true;
            }
            display_file_listing(items, config.psid, show_titles, ImageAccess::getFileSignature(fpath));
            items.clear();
            show_titles = false;
            displayed_files_cnt++;
        }
        closedir(d);
        if (displayed_files_cnt == 0)
        {
            print_out("No image files found\n");
            if (res != ERR_CODE_FILE_PARSE_FAILED)
            {
                res = ERR_CODE_IMG_NOT_FOUND;
            }
        }
    }

    return res;
}

void display_field_str(string field, int size, string display_if_empty = "")
{
    char fmt[50];
    string f;

    if (field.size() == 0)
    {
        f = display_if_empty;
    }
    else
    {
        f = field;
    }
    sprintf(fmt, "%%%ds", -size);
    print_out(fmt, f.c_str());
}

void display_file_listing(vector<PsidQueryItem>& items, string psid, bool show_titles, int signature)
{
    int max_pn_length = 25;
    int tmpLen = 0;
    bool breakFlag = false;
    for (unsigned i = 0; i < items.size(); i++)
    { // to make all fields aligned
        tmpLen = items[i].pns.length();
        if (tmpLen > max_pn_length)
        {
            max_pn_length = tmpLen;
        }
    }
    if (show_titles)
    {
        display_field_str("PN", max_pn_length);
        print_out(" ");
        display_field_str("PSID", 18);
        print_out(" ");
        display_field_str("Version", 28);
        print_out(" ");
        display_field_str("Tag", 14);
        print_out(" ");
        display_field_str("Description", 32);
        print_out(" ");
        print_out("\n");
        for (int i = 0; i < 110; i++)
        {
            print_out("-");
        }
        print_out("\n");
    }

    vector<PsidQueryItem> notNicComps;
    bool pldmFile = signature == IMG_SIG_TYPE_PLDM;
    for (unsigned i = 0; i < items.size(); i++)
    {
        if (pldmFile && !items[i].isNicComp)
        {
            notNicComps.push_back(items[i]);
            continue;
        }
        if (psid.length())
        {
            if (psid.compare(items[i].psid))
            {
                continue;
            }
            breakFlag = true;
        }

        ImgVersion* imv;

        display_field_str(items[i].pns, max_pn_length, "N/A");
        print_out(" ");
        display_field_str(items[i].psid, 18);
        print_out(" ");
        if ((imv = (ImgVersion*)items[i].findImageVersion("FW")))
        {
            display_field_str(imv->getPrintableVersion(0), 28);
        }
        else if (pldmFile)
        {
            display_field_str(items[i].type, 28);
        }
        else
        {
            display_field_str("", 16);
        }
        print_out(" ");
        display_field_str(items[i].selector_tag, 14, "--");
        print_out(" ");
        display_field_str(items[i].description, 32);
        print_out("\n");

        for (unsigned int j = 0; j < items[i].imgVers.size(); j++)
        {
            if (!items[i].imgVers[j].getTypeStr().compare("FW"))
            {
                continue;
            }
            display_field_str("", max_pn_length, "");
            print_out(" ");
            display_field_str("", 18);
            print_out(" ");
            display_field_str(items[i].imgVers[j].getPrintableVersion(0), 12);
            print_out(" ");
            // display_field_str("", 16, "");
            // display_field_str("", 32);
            print_out("\n");
        }

        if (breakFlag)
        {
            break;
        }
    }

    print_out("\n");
    if (signature == IMG_SIG_TYPE_PLDM && notNicComps.size() > 0)
    {
        if (show_titles)
        {
            display_field_str("Type", max_pn_length);
            print_out(" ");
            display_field_str("Version", 28);
            print_out(" ");
            print_out("\n");
            for (int i = 0; i < 110; i++)
            {
                print_out("-");
            }
            print_out("\n");
        }
        for (unsigned i = 0; i < notNicComps.size(); i++)
        {
            display_field_str(notNicComps[i].name, max_pn_length, "N/A");
            print_out(" ");
            display_field_str(notNicComps[i].type, 18);
            print_out(" ");
            print_out("\n");
        }
    }
}

int CalcFileCrc(char* fileName)
{
    FILE* fp;
    u_int8_t* buf = NULL;
    long fsize;
    int total = 0;
    int sz;
    int res = 0;

    if ((fp = fopen(fileName, "rb")) == NULL)
    {
        return -1;
    }

    if (fseek(fp, 0L, SEEK_END))
    {
        printf("Failed to seek end of file : '%s'\n", fileName);
        goto err_clean_up;
    }

    if ((fsize = ftell(fp)) == -1)
    {
        printf("Failed to ftell file : '%s'\n", fileName);
        goto err_clean_up;
    }

    rewind(fp);
    buf = (u_int8_t*)malloc(fsize);
    if (buf == NULL)
    {
        printf("Memory Allocation failure\n");
        goto err_clean_up;
    }

    while (total < fsize)
    {
        sz = fread(&buf[total], 1, fsize, fp);
        if (sz < 0)
        {
            break;
        }
        total += sz;
    }

    if (total != fsize)
    {
        goto err_clean_up;
    }
    res = 0;

    u_int32_t calc_crc;
    calc_crc = mfasec_crc32(buf, total, 0);
    printf("CRC32 = %08x\n", calc_crc);

err_clean_up:
    if (buf != NULL)
    {
        free(buf);
    }
    fclose(fp);
    return res;
}

void fixXmlKey(string& k)
{
    std::replace(k.begin(), k.end(), ' ', '_');
    k.erase(std::remove(k.begin(), k.end(), '('), k.end());
    k.erase(std::remove(k.begin(), k.end(), ')'), k.end());
}

void TerminationHandler(int signum)
{
    (void)signum;
    abort_request = 1;
    if (IS_OKAY_To_INTERRUPT)
    {
        print_out("\nInterrupted\n");
        exit(0);
    }
}

#ifdef __WIN__
#include <windows.h>

static BOOL CtrlHandler(DWORD fdwCtrlType)
{
    switch (fdwCtrlType)
    {
        // Handle the CTRL-C signal.
        case CTRL_C_EVENT:
        // CTRL-CLOSE: confirm that the user wants to exit.
        case CTRL_CLOSE_EVENT:
        // Pass other signals to the next handler.
        case CTRL_BREAK_EVENT:
        case CTRL_LOGOFF_EVENT:
        case CTRL_SHUTDOWN_EVENT:
            TerminationHandler(SIGINT);
            return TRUE;

        default:
            return FALSE;
    }
}

#endif

void initHandler()
{
#ifdef __WIN__
#define SIGNAL_NUM 3
    int signalList[SIGNAL_NUM] = {SIGINT, SIGTERM, SIGABRT};
    SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, true);
#else
#define SIGNAL_NUM 4
    int signalList[SIGNAL_NUM] = {SIGINT, SIGTERM, SIGPIPE, SIGHUP};
#endif

    // set the signal handler
    for (int i = 0; i < SIGNAL_NUM; i++)
    {
        void (*prevFunc)(int);
        prevFunc = signal(signalList[i], TerminationHandler);
        if (prevFunc == SIG_ERR)
        {
            printf("-E- failed to set signal Handler.");
            exit(ERR_CODE_INTERRUPTED);
        }
    }
}

string generateQueryXML(int dev_index,
                        string devname,
                        string deviceType,
                        string pn,
                        string description,
                        string statusStr,
                        vector<MlnxDev*>& devs,
                        string ver,
                        string availVer,
                        map<string, bool> expRomTypes,
                        map<string, int> devRomTypeIndex,
                        map<string, int> availRomTypeIndex,
                        map<string, PsidQueryItem>& psidUpdateInfo,
                        bool multiple_images_found)
{
    string output = "";
    output += "    <Device pciName=\"" + devname + "\" type=\"" + deviceType + "\" psid=\"" +
              devs[dev_index]->getPsid().c_str() + "\" partNumber=\"" + pn + "\">\n";
    output += "      <Versions>\n";
    output += "        <FW current=\"" + ver + "\" available=\"" + availVer + "\"/>\n";
    for (map<string, bool>::iterator iter = expRomTypes.begin(); iter != expRomTypes.end(); ++iter)
    {
        string k = iter->first;
        string dver = "N/A";
        string aver = "N/A";
        string fwType = string(k);
        if (!k.compare("FW"))
        {
            continue;
        }

        if (devRomTypeIndex[k] != -1)
        {
            dver = devs[dev_index]->_imageVers[devRomTypeIndex[k]].getPrintableVersion(0, false);
        }
        if (availRomTypeIndex[k] != -1)
        {
            aver =
              psidUpdateInfo[devs[dev_index]->getPsid()].imgVers[availRomTypeIndex[k]].getPrintableVersion(0, false);
        }
        fixXmlKey(fwType);
        if (multiple_images_found)
        {
            output += "        <" + fwType + " current=\"" + dver + "\" available=\"N/A\"/>\n";
        }
        else
        {
            output += "        <" + fwType + " current=\"" + dver + "\" available=\"" + aver + "\"/>\n";
        }
    }
    output += "      </Versions>\n";
    fixXmlString(description);
    if (devs[dev_index]->isOnlyBase)
    {
        if (devs[dev_index]->portOneType == MlnxDev::PORT_ETH)
        {
            output += "      <MACs Base_Mac=\"" + devs[dev_index]->macPortOne + "\" />\n";
        }
        else if (devs[dev_index]->portOneType == MlnxDev::PORT_IB)
        {
            output += "      <GUIDs Base_Guid=\"" + devs[dev_index]->guidPortOne + "\" />\n";
        }
        else
        {
            output += "      <MACs Base_Mac=\"" + devs[dev_index]->macPortOne + "\" />\n";
            output += "      <GUIDs Base_Guid=\"" + devs[dev_index]->guidPortOne + "\" />\n";
        }
    }
    else
    {
        if (devs[dev_index]->portOneType == MlnxDev::PORT_IB || devs[dev_index]->portTwoType == MlnxDev::PORT_IB)
        {
            string ports = "";
            if (devs[dev_index]->portOneType == MlnxDev::PORT_IB)
            {
                ports = "port1=\"" + devs[dev_index]->guidPortOne + "\" ";
            }

            if (devs[dev_index]->portTwoType == MlnxDev::PORT_IB)
            {
                ports += "port2=\"" + devs[dev_index]->guidPortTwo + "\"";
            }
            output += "      <GUIDs " + ports + "/>\n";
        }

        if (devs[dev_index]->portOneType == MlnxDev::PORT_ETH || devs[dev_index]->portTwoType == MlnxDev::PORT_ETH)
        {
            string ports = "";
            if (devs[dev_index]->portOneType == MlnxDev::PORT_ETH)
            {
                ports = "port1=\"" + devs[dev_index]->macPortOne + "\" ";
            }

            if (devs[dev_index]->portTwoType == MlnxDev::PORT_ETH)
            {
                ports += "port2=\"" + devs[dev_index]->macPortTwo + "\"";
            }
            output += "      <MACs " + ports + "/>\n";
        }
    }
    output += "      <Status>" + statusStr + "</Status>\n";
    output += "      <Description>" + description + "</Description>\n";
    output += "    </Device>";
    return output;
}

void printDeviceInfoQuery(int dev_index,
                          string devname,
                          string deviceType,
                          string pn,
                          string description,
                          string statusStr,
                          vector<MlnxDev*>& devs,
                          string ver,
                          string availVer,
                          map<string, bool> expRomTypes,
                          map<string, int> devRomTypeIndex,
                          map<string, int> availRomTypeIndex,
                          map<string, PsidQueryItem>& psidUpdateInfo,
                          bool multiple_images_found)
{
    print_out("Device #%d:\n", dev_index + 1);
    print_out("----------\n\n");
    print_out("  Device Type:      %s\n", deviceType.c_str());
    print_out("  Part Number:      %s\n", pn.c_str());
    print_out("  Description:      %s\n", description.c_str());
    print_out("  PSID:             %s\n", devs[dev_index]->getPsid().c_str());
    print_out("  PCI Device Name:  %s\n", devname.c_str());
    if (devs[dev_index]->isOnlyBase)
    {
        if (devs[dev_index]->portOneType == MlnxDev::PORT_ETH)
        {
            print_out("  Base MAC:         %s\n", devs[dev_index]->macPortOne.c_str());
            if (devs[dev_index]->portTwoType == MlnxDev::PORT_IB)
            {
                print_out("  Base GUID:        %s\n", devs[dev_index]->guidPortOne.c_str());
            }
        }
        else if (devs[dev_index]->portOneType == MlnxDev::PORT_IB)
        {
            if (!devs[dev_index]->systemGuid.empty() && !devs[dev_index]->nodeGuid.empty() &&
                devs[dev_index]->systemGuid != devs[dev_index]->nodeGuid)
            {
                print_out("  System GUID:      %s\n", devs[dev_index]->systemGuid.c_str());
                print_out("  Node GUID:        %s\n", devs[dev_index]->nodeGuid.c_str());
                print_out("  Base GUID:        %s\n", devs[dev_index]->guidPortOne.c_str());
            }
            else
            {
                print_out("  Base GUID:        %s\n", devs[dev_index]->guidPortOne.c_str());
            }
            if (devs[dev_index]->portTwoType == MlnxDev::PORT_ETH)
            {
                print_out("  Base MAC:         %s\n", devs[dev_index]->macPortOne.c_str());
            }
        }
        else
        {
            print_out("  Base GUID:        %s\n", devs[dev_index]->guidPortOne.c_str());
            print_out("  Base MAC:         %s\n", devs[dev_index]->macPortOne.c_str());
        }
    }
    else
    {
        if (devs[dev_index]->portOneType == MlnxDev::PORT_ETH)
        {
            print_out("  Port1 MAC:        %s\n", devs[dev_index]->macPortOne.c_str());
        }
        else if (devs[dev_index]->portOneType == MlnxDev::PORT_IB)
        {
            print_out("  Port1 GUID:       %s\n", devs[dev_index]->guidPortOne.c_str());
        }
        else
        {
            print_out("  Port1 MAC:        %s\n", devs[dev_index]->macPortOne.c_str());
            print_out("  Port1 GUID:       %s\n", devs[dev_index]->guidPortOne.c_str());
        }
        if (devs[dev_index]->portTwoType == MlnxDev::PORT_ETH)
        {
            print_out("  Port2 MAC:        %s\n", devs[dev_index]->macPortTwo.c_str());
        }
        else if (devs[dev_index]->portTwoType == MlnxDev::PORT_IB)
        {
            print_out("  Port2 GUID:       %s\n", devs[dev_index]->guidPortTwo.c_str());
        }
        else
        {
            print_out("  Port2 MAC:        %s\n", devs[dev_index]->macPortTwo.c_str());
            print_out("  Port2 GUID:       %s\n", devs[dev_index]->guidPortTwo.c_str());
        }
    }
    print_out("  Versions:         %-14s %-14s\n", "Current", "Available");
    print_out("     FW             %-14s %-14s\n", ver.c_str(), availVer.c_str());

    for (map<string, bool>::iterator iter = expRomTypes.begin(); iter != expRomTypes.end(); ++iter)
    {
        string k = iter->first;
        string dver = "N/A";
        string aver = "N/A";
        if (!k.compare("FW"))
        {
            continue;
        }
        if (devRomTypeIndex[k] != -1)
        {
            dver = devs[dev_index]->_imageVers[devRomTypeIndex[k]].getPrintableVersion(0, false);
        }
        if (availRomTypeIndex[k] != -1)
        {
            aver =
              psidUpdateInfo[devs[dev_index]->getPsid()].imgVers[availRomTypeIndex[k]].getPrintableVersion(0, false);
        }

        print_out("     %-12s   %-14s %-14s\n", k.c_str(), dver.c_str(), (multiple_images_found) ? "--" : aver.c_str());
    }
    print_out("\n  Status:           %s\n\n", statusStr.c_str());
    if (devs[dev_index]->doesDevNeedUpdate())
    {
        displayReleaseNoteMFAs(psidUpdateInfo, devs, dev_index);
    }
}

void fixXmlString(string& stringToFix)
{
    string rep[5] = {"\"", "&", "'", ">", "<"};
    for (int i = 0; i < 5; i++)
    {
        replaceStringInPlace(stringToFix, rep[i], "");
    }
}

void replaceStringInPlace(string& subject, const string& search, const string& replace)
{
    int pos = 0;
    while ((pos = subject.find(search, pos)) != (int)std::string::npos)
    {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}

string getline()
{
    std::string str;
    std::getline(std::cin, str);
    return str;
}

int handleOnlinePsidsQueryXml(ServerRequest* srq, CmdLineParams& cmd_params, config_t config)
{
    int res = 0;
    (void)config;
    vector<PsidQueryItem> psidUpdateInfo;
    if (srq->queryPsids(cmd_params.onlineQueryPsids, psidUpdateInfo))
    {
        print_err("<Psids>\n </Psids>\n");
        res = ERR_CODE_SERVER_QUERY_FAILED;
        return res;
    }

    string output = "<Psids>\n";
    for (unsigned int i = 0; i < psidUpdateInfo.size(); i++)
    {
        PsidQueryItem ri = psidUpdateInfo[i];
        string status;
        string ver = "N/A";
        string mfa = "N/A";
        string release_note = "";
        if (ri.found)
        {
            status = "Found";
            ImgVersion* img = (ImgVersion*)ri.findImageVersion("FW");
            if (img)
            {
                ver = img->getPrintableVersion(cmd_params.compare_ffv, false);
            }
            mfa = ri.name;
            release_note = ri.release_note.length() ? "\n" + ri.release_note : "";
        }
        else
        {
            status = "Not Found";
            res = 1;
        }
        output += "    <Psid psid=\"" + ri.psid + "\" MFA=\"" + mfa + "\" partNumber=\"" + ri.pns + "\">\n";
        output += "      <Versions>\n";
        output += "        <FW available=\"" + ver + "\"/>\n";
        if (ri.found)
        {
            for (unsigned int j = 0; j < ri.imgVers.size(); j++)
            {
                string type = ri.imgVers[j].getTypeStr();
                if (type == "FW")
                {
                    continue;
                }
                output += "        <" + type + " available=\"" +
                          ri.imgVers[j].getPrintableVersion(cmd_params.compare_ffv, false) + "\"/>\n";
            }
        }
        output += "      </Versions>\n";
        if (release_note.length())
        {
            std::istringstream stream(release_note);
            string line;
            getline(stream, line);
            release_note = line;
            while (!stream.eof())
            {
                getline(stream, line);
                release_note += "\\n" + line;
            }
            output += "      <ReleaseNotes>" + release_note + "</ReleaseNotes>\n";
        }

        output += "      <Status>" + status + "</Status>\n";
        output += "    </Psid>\n";
    }
    output += "</Psids>\n";
    printf("%s\n", output.c_str());
    return res;
}
int handleOnlinePsidsQuery(ServerRequest* srq, CmdLineParams& cmd_params, config_t config)
{
    int res = 0;
    (void)config;
    vector<PsidQueryItem> psidUpdateInfo;
    if (srq->queryPsids(cmd_params.onlineQueryPsids, psidUpdateInfo))
    {
        print_err("-E- Failed to query PSIDs from server\n");
        string errorMsg;
        srq->getError(res, errorMsg);
        print_err("%s\n", errorMsg.c_str());
        res = ERR_CODE_SERVER_QUERY_FAILED;
        return res;
    }

    for (unsigned int i = 0; i < psidUpdateInfo.size(); i++)
    {
        PsidQueryItem ri = psidUpdateInfo[i];
        string status;
        string ver = "N/A";
        string mfa = "N/A";
        string release_note = "N/A";
        if (ri.found)
        {
            status = "Found";
            ImgVersion* img = (ImgVersion*)ri.findImageVersion("FW");
            if (img)
            {
                ver = img->getPrintableVersion(cmd_params.compare_ffv, false);
            }
            mfa = ri.name;
            release_note = ri.release_note.length() ? "\n" + ri.release_note : "N/A";
        }
        else
        {
            status = "Not Found";
            res = 1;
        }
        print_out("PSID #%d:\n", i + 1);
        print_out("----------\n\n");
        print_out("  PSID:             %s\n", ri.psid.c_str());
        print_out("  Part Number:      %s\n", ri.pns.c_str());
        print_out("  MFA Name:         %s\n", mfa.c_str());
        print_out("  Versions:         %-14s\n", "Available");
        print_out("     FW             %-14s\n", ver.c_str());
        if (ri.found)
        {
            for (unsigned int j = 0; j < ri.imgVers.size(); j++)
            {
                string type = ri.imgVers[j].getTypeStr();
                if (type == "FW")
                {
                    continue;
                }
                print_out("     %-12s   %-14s\n", type.c_str(),
                          ri.imgVers[j].getPrintableVersion(cmd_params.compare_ffv, false).c_str());
            }
        }

        std::istringstream stream(release_note);
        string line;
        getline(stream, line);
        print_out("  Release Notes:     %-14s\n", line.c_str());
        while (!stream.eof())
        {
            getline(stream, line);
            print_out("                    %-14s\n", line.c_str());
        }
        print_out("\n  Status:           %s\n\n", status.c_str());
    }
    return res;
}

static int getFileProperties(ServerRequest* srq,
                             vector<DownloadedFileProperties>& filePropVec,
                             string osFilter = "",
                             string devFilter = "",
                             string fileTypeFilter = "")
{
    if (!srq)
    {
        return ERR_CODE_INTERNAL_ERR;
    }

    if (srq->DownloadFilesRequest(filePropVec, osFilter, devFilter, fileTypeFilter))
    {
        return ERR_CODE_SERVER_DOWNLOAD_FAILED;
    }
    return MLX_FWM_SUCCESS;
}

int check_valid_os_type(CmdLineParams& cmd_params, bool* os_valid)
{
    vector<DownloadedFileProperties> filePropVec;
    int res = MLX_FWM_SUCCESS;
    *os_valid = false;
    if (cmd_params.download_os == "all")
    {
        *os_valid = true;
        return res;
    }
    ServerRequest* srq = new ServerRequest(cmd_params.server_url.c_str(), cmd_params.proxy.c_str(),
                                           cmd_params.compare_ffv, cmd_params.show_progress, cmd_params.download_key,
                                           cmd_params.certificate, cmd_params.numberOfRetrials);
    if (srq == NULL)
    {
        return ERR_CODE_MEM_ALLOC_FAIL;
    }
    res = getFileProperties(srq, filePropVec, "", "", "self_extractor");
    if (res)
    {
        print_err("-E- Failed to query files on server\n");
        string errorMsg;
        srq->getError(res, errorMsg);
        print_err("%s\n", errorMsg.c_str());
    }
    for (std::vector<DownloadedFileProperties>::iterator it = filePropVec.begin(); it != filePropVec.end(); it++)
    {
        if (cmd_params.download_os == it->os)
        {
            *os_valid = true;
            break;
        }
    }
    delete srq;
    return res;
}

int handleGetDownloadOptionsRequest(ServerRequest* srq, CmdLineParams& cmd_params)
{
    std::set<string> availOpt;
    vector<DownloadedFileProperties> filePropVec;
    int res = MLX_FWM_SUCCESS;

    res = getFileProperties(srq, filePropVec, "", "", cmd_params.get_download_opt == "os" ? "self_extractor" : "mfa");
    if (res)
    {
        if (cmd_params.download_key != "last_release")
        {
            print_err("-E- Failed to Query files on server, might be invalid key?\n");
        }
        else
        {
            print_err("-E- Failed to query files on server\n");
            string errorMsg;
            srq->getError(res, errorMsg);
            print_err("%s\n", errorMsg.c_str());
        }
        return res;
    }

    bool insertOS = cmd_params.get_download_opt == "os";
    for (std::vector<DownloadedFileProperties>::iterator it = filePropVec.begin(); it != filePropVec.end(); it++)
    {
        availOpt.insert(insertOS ? it->os : it->family);
    }

    for (std::set<string>::iterator it = availOpt.begin(); it != availOpt.end(); it++)
    {
        print_out("%s\n", (*it).c_str());
    }
    return res;
}

int handleDownloadRequest(ServerRequest* srq, CmdLineParams& cmd_params, config_t config)
{
    int res = 0;
    (void)config;
    vector<DownloadedFileProperties> files;
    filesOPtions filterOPtions;

    // print_out("\n");
    if (getFileProperties(srq, files, cmd_params.download_os, cmd_params.download_dev, cmd_params.download_type))
    {
        if (cmd_params.download_key != "last_release")
        {
            print_err("-E- Failed to download files from server, might be invalid key?\n");
        }
        else
        {
            print_err("-E- Failed to download files from server\n");
            string errorMsg;
            srq->getError(res, errorMsg);
            print_err("%s\n", errorMsg.c_str());
        }
        res = ERR_CODE_SERVER_DOWNLOAD_FAILED;
        return res;
    }

    if (!cmd_params.download_default)
    {
        filterOPtions.files.swap(files);
        BaseMenu* currentMenu = new FileTypeMenu;

        while (currentMenu != NULL)
        {
            bool isPrev = false;
            bool isExit = false;
            int choice = 0;
            int invalid = false;
            BaseMenu* aNewmenu;
            currentMenu->generateMenu(cmd_params, filterOPtions);
            if (currentMenu->isValid(cmd_params, filterOPtions))
            {
                std::istringstream iss(getline());
                iss.clear();
                iss >> choice;
                if (!iss.eof())
                {
                    sleep(1);
                    invalid = true;
                }
                if (iss.fail())
                {
                    sleep(1);
                    invalid = true;
                }
                print_out("\n");
            }
            else
            {
                aNewmenu = currentMenu->getNextMenu(cmd_params, filterOPtions);
                delete currentMenu;
                currentMenu = aNewmenu;
                continue;
            }
            if (abort_request)
            {
                delete currentMenu;
                return res;
            }
            if (!abort_request && invalid)
            {
                delete currentMenu;
                print_err("-E- Invalid choice\n");
                return 1;
            }
            if (!currentMenu->parseChoice(choice, isExit, isPrev, filterOPtions))
            {
                delete currentMenu;
                return -1;
            }
            if (isExit)
            {
                delete currentMenu;
                return 0;
            }

            if (isPrev)
            {
                aNewmenu = currentMenu->getPrevMenu(cmd_params, filterOPtions);
            }
            else
            {
                aNewmenu = currentMenu->getNextMenu(cmd_params, filterOPtions);
            }
            delete currentMenu;
            currentMenu = aNewmenu;
        }

        filterOPtions.filtered.clear();
        for (unsigned int i = 0; i < filterOPtions.files.size(); i++)
        {
            if (filterOPtions.files[i].file_type != filterOPtions.file_type && filterOPtions.file_type != "all")
            {
                continue;
            }
            else if (filterOPtions.files[i].family != filterOPtions.family && filterOPtions.family != "all")
            {
                continue;
            }
            else if (filterOPtions.files[i].os != filterOPtions.os && filterOPtions.os != "all" &&
                     filterOPtions.files[i].os != "all")
            {
                continue;
            }
            filterOPtions.filtered.push_back(filterOPtions.files[i]);
        }

        for (unsigned int i = 0; i < filterOPtions.filtered.size(); i++)
        {
            filterOPtions.urls.push_back(filterOPtions.filtered[i].url);
            filterOPtions.names.push_back(filterOPtions.filtered[i].name);
            filterOPtions.osDirName.push_back(filterOPtions.filtered[i].os);
        }
    }
    else
    { // take files as is
        for (unsigned int i = 0; i < files.size(); i++)
        {
            filterOPtions.urls.push_back(files[i].url);
            filterOPtions.names.push_back(files[i].name);
            filterOPtions.osDirName.push_back(files[i].os);
        }
        filterOPtions.filtered.swap(files);
    }
    print_out("\n");
    if (!filterOPtions.urls.size())
    {
        print_err("-E- Failed to find files that match your request\n");
        return 1;
    }

    // displayFilesToBeDownloaded(filterOPtions, cmd_params);

    if (!displayReleaseNoteFiles(filterOPtions, cmd_params))
    {
        return res;
    }
    res = download(srq, filterOPtions.urls, filterOPtions.names, filterOPtions.osDirName, cmd_params.download_dir);
    if (res < 0)
    {
        print_err("-E- Failed to download files from server\n");
        res = ERR_CODE_SERVER_RETRIEVE_FAIL;
    }
    else
    {
        print_out("Downloading file(s) to : '%s' is done successfully\n", cmd_params.download_dir.c_str());
    }
    return res;
}

int generateProductionName(string& targetFile, PsidQueryItem ri)
{
    int res = 0;

    if (targetFile.length())
    {
        return res;
    }

    string IC_code_name;
    dm_dev_id_t devType;

    if (dm_get_device_id_offline(ri.devId, ri.revId, &devType))
    {
        IC_code_name = "X";
    }
    else
    {
        
        IC_code_name = dm_dev_type2str(devType);
    }

    ImgVersion* fwImgVer = (ImgVersion*)ri.findImageVersion("FW");
    if (fwImgVer == NULL)
    {
        print_err("-E- UnExpected error getting version\n");
        return 1;
    }
    string fw = fwImgVer->getPrintableVersion(0, false);
    targetFile = "fw-" + IC_code_name + "-rel-" + fw + "-";
    if (ri.iniName != "")
    {
        targetFile += ri.iniName;
    }
    else if (ri.pns != "")
    {
        targetFile += ri.pns;
    }
    else
    {
        targetFile += ri.psid;
    }
    for (unsigned int i = 0; i < ri.imgVers.size(); i++)
    {
        if (ri.imgVers[i].getTypeStr() == "FW")
        {
            continue;
        }
        else
        {
            targetFile += "-";
            targetFile += ri.imgVers[i].getTypeStr();
            targetFile += "-";
            targetFile += ri.imgVers[i].getPrintableVersion(0, false);
        }
    }
    targetFile += ".bin";
    return res;
}

void displayReleaseNoteMFAs(map<string, PsidQueryItem> psidUpdateInfo, vector<MlnxDev*> devs, int deviceIndex)
{
    if (psidUpdateInfo[devs[deviceIndex]->getPsid()].release_note.length())
    {
        print_out("Release notes for the available Firmware:\n");
        print_out("-----------------------------------------\n\n");
        print_out("  %s\n", psidUpdateInfo[devs[deviceIndex]->getPsid()].release_note.c_str());
    }
}

/*
   void displayFilesToBeDownloaded(filesOPtions filterOPtions, CmdLineParams cmd_params) {
    print_out("------ Files To Be Downloaded ------\n\n");
    for (int i = 0; i < filterOPtions.filtered.size(); i++){
        print_out("%d - %s\n", i, filterOPtions.filtered[i].name.c_str());
    }
    print_out("\n");
   }*/

int displayReleaseNoteFiles(const filesOPtions& filterOPtions, const CmdLineParams& cmd_params)
{
    map<std::string, std::string> releaseNote;
    map<std::string, vector<string> > os;
    map<std::string, vector<string> > files;
    string tmp = "";
    for (unsigned int i = 0; i < filterOPtions.filtered.size(); i++)
    {
        files[filterOPtions.filtered[i].family].push_back(filterOPtions.filtered[i].name);
        os[filterOPtions.filtered[i].family].push_back(filterOPtions.filtered[i].os);
        if (filterOPtions.filtered[i].release_note.length())
        {
            releaseNote[filterOPtions.filtered[i].family] = filterOPtions.filtered[i].release_note;
        }
    }

    print_out("------ Files To Be Downloaded ------\n\n");
    for (map<std::string, vector<string> >::iterator p = files.begin(); p != files.end(); ++p)
    {
        print_out("\n%s :\n", beautify_device_name(p->first).c_str());
        print_out("%.*s\n\n", p->first.length() + 2 < 40 ? (int)p->first.length() + 2 : 39,
                  "----------------------------------------");
        print_out("<Files>:\n");
        for (unsigned int i = 0; i < p->second.size(); i++)
        {
            tmp = "";
            if (os[p->first][i] != "all")
            {
                tmp = os[p->first][i] + PATH_SEPARATOR;
            }
            print_out("%d - %s\n", i, (tmp + p->second[i]).c_str());
        }
        print_out("\n");

        if (releaseNote.count(p->first))
        {
            print_out("<Release Notes>:\n");
            print_out("%s\n", releaseNote[p->first].c_str());
        }
        print_out("\n");
    }
    int answer = prompt("Perform Download? [y/N]: ", cmd_params.yes_no_);
    if (!answer && !abort_request)
    {
        sleep(1);
        if (!abort_request && IS_OKAY_To_INTERRUPT)
        {
            print_out("\nNo download performed\n");
        }
    }
    return answer;
}
