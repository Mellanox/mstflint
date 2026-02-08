/*
 * Copyright (c) 2006-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
 * End of legal section ......................................................
 *
 *  cmd_line_parser.cpp - mlxfwmanager
 *
 *  Version: $Id$
 *
 *  Author: Sami Salloum (sami@mellanox.com)
 */

#include <iostream>
#include "mft_utils.h"
#include "cmd_line_parser.h"
#include "cmd_line_params.h"
#include "tools_version.h"

#ifdef MST_UL
#define TOOL_NAME "mstfwmanager"
#else
#define TOOL_NAME "mlxfwmanager"
#endif

#define TOOL_VERSION "1.0"
#define TOOL_DESC "Mellanox Firmware Manager"

using namespace std;
using namespace mft_utils;

/* Command line options definitions, _L for long options and _S for short ones. */
#define VERSION_L "version"
#define VERSION_S 'v'

#define CURRENT_DIR_L "current-dir"
#define CURRENT_DIR_S ' '

#define DEVICE_L "dev"
#define DEVICE_S 'd'

#define EXE_REL_PATH_L "exe-rel-path"
#define EXE_REL_PATH_S ' '

#define UPDATE_L "update"
#define UPDATE_S 'u'

#define CLEAR_SEM_L "clear-semaphore"
#define CLEAR_SEM_S ' '

#define USE_IMG_FILE_L "image-file"
#define USE_IMG_FILE_S 'i'

#define USE_IMG_DIR_L "image-dir"
#define USE_IMG_DIR_S 'D'

#define UPDATE_L "update"
#define UPDATE_S 'u'

#define ARCHIVE_NAMES_L "archive-names"
#define ARCHIVE_NAMES_S ' '

#define PROXY_L "proxy"
#define PROXY_S ' '

#define SERVER_URL_L "server-url"
#define SERVER_URL_S ' '

#define CERTIFICATE_L "ssl-certificate"
#define CERTIFICATE_S ' '

#define ONLINE_IMGS_L "online"
#define ONLINE_IMGS_S ' '

#define ONLINE_QUERY_L "online-query-psid"
#define ONLINE_QUERY_S ' '

#define DNLD_KEY_L "key"
#define DNLD_KEY_S ' '

#define USE_DEFAULT_L "download-default"
#define USE_DEFAULT_S ' '

#define DNLD_L "download"
#define DNLD_S ' '

#define DNLD_TYPE_L "download-type"
#define DNLD_TYPE_S ' '

#define DNLD_OS_L "download-os"
#define DNLD_OS_S ' '

#define DNLD_DEV_L "download-device"
#define DNLD_DEV_S ' '

#define GET_DNLD_OPT_L "get-download-opt"
#define GET_DNLD_OPT_S ' '

#define FORCE_L "force"
#define FORCE_S 'f'

#define YES_L "yes"
#define YES_S 'y'

#define NO_L "no"
#define NO_S ' '

#define LIST_CONTENT_L "list-content"
#define LIST_CONTENT_S 'l'

#define FFV_L "ffv"
#define FFV_S ' '

#define PSID_L "psid"
#define PSID_S ' '

#define CRC_L "crc"
#define CRC_S ' '

#define EXTRACT_L "extract"
#define EXTRACT_S ' '

#define EXTRACT_FILE_L "extract-file"
#define EXTRACT_FILE_S ' '

#define EXTRACT_ALL_L "extract-all"
#define EXTRACT_ALL_S ' '

#define EXTRACT_DIR_L "extract-dir"
#define EXTRACT_DIR_S ' '

#define QUERY_L "query"
#define QUERY_S ' '

#define QUERY_XML_L "query-xml"
#define QUERY_XML_S ' '

#define QUERY_FORMAT_L "query-format"
#define QUERY_FORMAT_S ' '

#define LOG_ON_UPDATE_L "log-on-update"
#define LOG_ON_UPDATE_S ' '

#define LOG_L "log"
#define LOG_S ' '

#define LOG_FILE_L "log-file"
#define LOG_FILE_S 'L'

#define NO_PROGRESS_L "no-progress"
#define NO_PROGRESS_S ' '

#define XML_L "xml"
#define XML_S 'x'

#define OUT_FILE_L "outfile"
#define OUT_FILE_S 'o'

#define LOOKUP_FILE_L "lookup"
#define LOOKUP_FILE_S ' '

#define HELP_L "help"
#define HELP_S 'h'

#define HIDDEN_HELP_L "hhelp"
#define HIDDEN_HELP_S ' '

#define BURN_FAIL_SAFE_L "nofs"
#define BURN_FAIL_SAFE_S ' '

#define RET_DL_L "ret-dl"
#define RET_DL_S ' '

#define RET_LVIM_L "ret-lvim"
#define RET_LVIM_S ' '

#define NO_EXTRACT_LIST_L "no_extract_list"
#define NO_EXTRACT_LIST_S ' '

#define NUM_OF_RETRIALS_L "download_retrials"
#define NUM_OF_RETRIALS_S ' '

#define NO_FW_CTRL_L "no_fw_ctrl"
#define NO_FW_CTRL_S ' '

#define FW_UPDATE_PARALLEL_FWCTL_L "fw_update_in_parallel_via_fwctl"
#define FW_UPDATE_PARALLEL_FWCTL_S ' '

#define COMP_TYPE_L "component_type"
#define COMP_TYPE_S ' '

#define SKIP_IF_SAME_L "skip_if_same"
#define SKIP_IF_SAME_S ' '

string toolName = "";
/************************************
 * Function: CmdLineParser
 ************************************/
static void printExamples()
{
    cout << "Examples:" << endl;
    cout << "\t1. Query specific device or all devices (if no device were supplied)" << endl;
    cout << "\t>> " << toolName << " [-d <device>] [--query]" << endl;
    cout << "\t2. Burn device with specific image / MFA / images directory" << endl;
    cout << "\t>> " << toolName << " -d <device> [-i <image file/MFA file> | -D <images dir>]" << endl;
    cout << "\t3. Update the card's firmware" << endl;
    cout << "\t>> " << toolName << " -u" << endl;
    cout << "\t4. Update the card's firmware from latest version on the web" << endl;
    cout << "\t>> " << toolName << " --" << ONLINE_IMGS_L << " -u" << endl;
    cout << "\t5. Download latest FW package from the web" << endl;
    cout << "\t>> " << toolName << " --" << USE_DEFAULT_L << " --" << DNLD_OS_L << " Linux_x64"
         << " --" << DNLD_TYPE_L << " self_extractor" << endl
         << endl;
}
CmdLineParser::CmdLineParser(CmdLineParams* params, char** argv, int argc) : CommandLineRequester(""), _cmdParser("")
{
    toolName = TOOL_NAME;
    _cmdLineParams = params;
    for (int i = 0; i < argc; i++)
    {
        if (strstr((const char*)argv[i], NO_EXTRACT_LIST_L) != NULL)
        {
            _cmdLineParams->no_extract_list = true;
        }
        else if (strstr((const char*)argv[i], CURRENT_DIR_L) != NULL)
        {
            // This option is hidden and only used with self extractors
            toolName = "mlxup";
        }
    }
    setToolName(toolName);
    _cmdParser.setParserName(toolName);
    initOptions();
}

/************************************
 * Function: ~CmdLineParser
 ************************************/
CmdLineParser::~CmdLineParser() {}

/************************************
 * Function: parse
 ************************************/
bool CmdLineParser::parse(char** argv, int argc)
{
    _cmdParser.AddRequester(this);
    int rc = _cmdParser.ParseOptions(argc, argv, false);

    if (rc == PARSE_ERROR_SHOW_USAGE)
    { // parse error and we need to dump usage
        cout << _cmdParser.GetSynopsis().c_str();
        return false;
    }
    else if (rc == PARSE_OK_WITH_EXIT)
    { // OK but need to exit
        exit(0);
        return false;
    }
    else if (rc == PARSE_ERROR)
    { // error but no need to dump usage
        cout << _cmdParser.GetSynopsis().c_str();
        return false;
    }

    return true;
}

/************************************
 * Function: initOptions
 ************************************/
void CmdLineParser::initOptions()
{
    AddDescription(TOOL_DESC);

#ifdef ONLY_PCI_FORMAT
    this->AddOptions(DEVICE_L,
                     DEVICE_S,
                     "DeviceName",
                     "Perform operation for specified PCI (using the format <Bus>:<Device>.<Function>) or IB device(s)."
                     " Multiple devices can be specified delimited by semicolons. A device list containing semicolons "
                     "must be quoted.");
#else
    this->AddOptions(
      DEVICE_L,
      DEVICE_S,
      "DeviceName",
      "Perform operation for specified mst device(s). Run 'mst status' command to list the available devices. Multiple "
      "devices can be specified delimited by semicolons. A device list containing semicolons must be quoted.");
#endif

    this->AddOptions(NUM_OF_RETRIALS_L, NUM_OF_RETRIALS_S, "NumOfRetrials", "Number of download retrials default is 5",
                     true);

    this->AddOptions(HELP_L, HELP_S, "", "Show this message and exit");

    this->AddOptions(CURRENT_DIR_L, CURRENT_DIR_S, "currentDir", "current directory used only with self extractor",
                     true);

    this->AddOptions(HIDDEN_HELP_L, HIDDEN_HELP_S, "", "Show hidden options help and exit",
                     true); // Hidden

    this->AddOptions(VERSION_L, VERSION_S, "", "Show the executable version and exit");

    this->AddOptions(QUERY_L, QUERY_S, "", "Query device(s) info");

    this->AddOptions(QUERY_XML_L, QUERY_XML_S, "", "Query device(s) info (xml format)", true);

    this->AddOptions(QUERY_FORMAT_L, QUERY_FORMAT_S, "Format",
                     "(Query | Online query) output format, XML | Text - default Text");

    this->AddOptions(UPDATE_L, UPDATE_S, "", "Update firmware image(s) on the device(s)");

    this->AddOptions(USE_IMG_FILE_L, USE_IMG_FILE_S, "FileName", "Specified image file to use");

    this->AddOptions(USE_IMG_DIR_L, USE_IMG_DIR_S, "DirectoryName",
                     "Specified directory instead of default to locate image files");

    this->AddOptions(LOOKUP_FILE_L,
                     LOOKUP_FILE_S,
                     "LookupFileName",
                     "Provide PSID-Description lookup file",
                     true); // Hidden

    this->AddOptions(FORCE_L, FORCE_S, "", "Force image update");

    this->AddOptions(NO_FW_CTRL_L, NO_FW_CTRL_S, "", "Don't use FW Ctrl update");

    this->AddOptions(FW_UPDATE_PARALLEL_FWCTL_L, FW_UPDATE_PARALLEL_FWCTL_S, "", "Enable firmware update in parallel via fwctl");

    this->AddOptions(YES_L, YES_S, "", "Answer is yes in prompts");

    this->AddOptions(NO_L, NO_S, "", "Answer is no in prompts");

    this->AddOptions(FFV_L, FFV_S, "", "Compare Firmware family version",
                     true); // Hidden

    this->AddOptions(CLEAR_SEM_L,
                     CLEAR_SEM_S,
                     "",
                     "Force clear the flash semaphore on the device, No command is allowed when this flag is used. "
                     "NOTE: May result in system instability or flash corruption if the device or another application "
                     "is currently using the flash. Exercise caution.");

    this->AddOptions(EXE_REL_PATH_L, EXE_REL_PATH_S, "", "Use paths relative to the location of the executable", false);

    this->AddOptions(PSID_L, PSID_S, "PSID", "specify PSID",
                     true); // Hidden

    this->AddOptions(CRC_L, CRC_S, "", "CRC calculation of raw file provided with -i option",
                     true); // Hidden

    this->AddOptions(
      EXTRACT_L,
      EXTRACT_S,
      "",
      "Extract image, if " + (string)EXTRACT_FILE_L + " not specified, will be exported in production format",
      true); // Hidden

    this->AddOptions(EXTRACT_FILE_L, EXTRACT_FILE_S, "FileName", "Write to target file",
                     true); // Hidden

    if (_cmdLineParams->no_extract_list == false)
    {
        this->AddOptions(EXTRACT_DIR_L,
                         EXTRACT_DIR_S,
                         "ExtractDir",
                         "If specified image files will"
                         " be extracted to this directory",
                         true); // Hidden

        this->AddOptions(EXTRACT_ALL_L, EXTRACT_ALL_S, "", "Extract all images in production format",
                         true); // Hidden

        this->AddOptions(LIST_CONTENT_L,
                         LIST_CONTENT_S,
                         "",
                         "List file/Directory content, used with --" USE_IMG_DIR_L " and --" USE_IMG_FILE_L " flags");

        this->AddOptions(ARCHIVE_NAMES_L, ARCHIVE_NAMES_S, "", "Display archive names in listing");
        this->AddOptions(BURN_FAIL_SAFE_L, BURN_FAIL_SAFE_S, "", "Burn image in a non failsafe manner", false);
    }
    else
    {
        this->AddOptions(BURN_FAIL_SAFE_L, BURN_FAIL_SAFE_S, "", "Burn image in a non failsafe manner", true);
    }
    this->AddOptions(LOG_ON_UPDATE_L, LOG_ON_UPDATE_S, "", "Create log file on update",
                     true); // Hidden

    this->AddOptions(LOG_L, LOG_S, "", "Create log file");

    this->AddOptions(LOG_FILE_L, LOG_FILE_S, "LogFileName", "Use specified log file");

    this->AddOptions(NO_PROGRESS_L, NO_PROGRESS_S, "", "Do not show progress");

    this->AddOptions(XML_L, XML_S, "", "Output in XML format",
                     true); // Hidden

    this->AddOptions(OUT_FILE_L, OUT_FILE_S, "OutputFileName", "Write to specified output file");

    this->AddOptions(ONLINE_IMGS_L, ONLINE_IMGS_S, "", "Fetch required FW images online from Mellanox server", false);

    this->AddOptions(ONLINE_QUERY_L, ONLINE_QUERY_S, "PSIDs", "Query FW info, PSID(s) are comma separated", false);

    this->AddOptions(DNLD_KEY_L, DNLD_KEY_S, "key", "Key for custom download/update");

    this->AddOptions(DNLD_L,
                     DNLD_S,
                     "DirectoryName",
                     "Download files from server to a specified directory",
                     false); // Hidden

    this->AddOptions(USE_DEFAULT_L, USE_DEFAULT_S, "", "Use Default values for download");

    this->AddOptions(GET_DNLD_OPT_L, GET_DNLD_OPT_S, "OPT",
                     "Get download options for OS or Device\nOptions are: OS, Device", false);

    this->AddOptions(DNLD_DEV_L,
                     DNLD_DEV_S,
                     "Device",
                     "Use '--" GET_DNLD_OPT_L " Device' option to view available devices for device specific downloads",
                     false);

    this->AddOptions(DNLD_OS_L,
                     DNLD_OS_S,
                     "OS",
                     "Only for self_extractor download: Use '--" GET_DNLD_OPT_L
                     " OS' option to view available OS for sfx download",
                     false);

    this->AddOptions(DNLD_TYPE_L, DNLD_TYPE_S, "Type", "MFA | self_extractor - default All", false);

    this->AddOptions(SERVER_URL_L, SERVER_URL_S, "URL", "Server URL for online operations", true);

    this->AddOptions(CERTIFICATE_L, CERTIFICATE_S, "Certificate", "SSL certificate For secure connection");

    this->AddOptions(RET_DL_L, RET_DL_S, "", "Change return Value", true);

    this->AddOptions(RET_LVIM_L, RET_LVIM_S, "", "change return Value", true);

    this->AddOptions(NO_EXTRACT_LIST_L, NO_EXTRACT_LIST_S, "", "Do not extract or list binaries",
                     true); // Hidden
    
    this->AddOptions(COMP_TYPE_L, COMP_TYPE_S, "componentName", "Specify the PLDM component type to extract");

    this->AddOptions(SKIP_IF_SAME_L, SKIP_IF_SAME_S, "", "Skip firmware update if current and new versions match");
}

bool csvSplit(string str, vector<string>& strv)
{
    size_t pos;
    bool res = true;

    while ((pos = str.find(';')) != string::npos)
    {
        string tmp = str.substr(0, pos);
        strv.push_back(tmp);
        str = str.substr(pos + 1);
    }

    strv.push_back(str);
    return res;
}

/************************************
 * Function: HandleOption
 ************************************/
ParseStatus CmdLineParser::HandleOption(string name, string value)
{
    if (name == DEVICE_L)
    {
        _cmdLineParams->device_names.clear();
        if (!csvSplit(value, _cmdLineParams->device_names))
        {
            return PARSE_ERROR_SHOW_USAGE;
        }
        return PARSE_OK;
    }
    else if (name == EXE_REL_PATH_L)
    {
        _cmdLineParams->use_exe_rel_paths = 1;
        return PARSE_OK;
    }
    else if (name == CURRENT_DIR_L)
    {
        _cmdLineParams->current_dir = value;
        return PARSE_OK;
    }
    else if (name == CLEAR_SEM_L)
    {
        _cmdLineParams->clear_semaphore = true;
        return PARSE_OK;
    }
    else if (name == UPDATE_L)
    {
        _cmdLineParams->update_fw = 1;
        return PARSE_OK;
    }
    else if (name == ARCHIVE_NAMES_L)
    {
        _cmdLineParams->display_archive_names = true;
        return PARSE_OK;
    }
    else if (name == SERVER_URL_L)
    {
        _cmdLineParams->server_url = value;
        return PARSE_OK;
    }
    else if (name == PROXY_L)
    {
        _cmdLineParams->proxy = value;
        return PARSE_OK;
    }
    else if (name == CERTIFICATE_L)
    {
        _cmdLineParams->certificate = value;
        return PARSE_OK;
    }
    else if (name == ONLINE_IMGS_L)
    {
        _cmdLineParams->update_online = true;
        return PARSE_OK;
    }
    else if (name == ONLINE_QUERY_L)
    {
        _cmdLineParams->onlineQueryPsids = value;
        return PARSE_OK;
    }
    else if (name == USE_IMG_FILE_L)
    {
        // Check if --image-dir was already parsed
        if (_cmdLineParams->use_mfa_dir == 1)
        {
            printf("-E- Flags --" USE_IMG_FILE_L " and --" USE_IMG_DIR_L " are not to be used in the same command\n");
            return PARSE_ERROR;
        }
        _cmdLineParams->use_mfa_file = 1;
        _cmdLineParams->mfa_file = value;
        return PARSE_OK;
    }
    else if (name == USE_IMG_DIR_L)
    {
        // Check if --image-file was already parsed
        if (_cmdLineParams->use_mfa_file == 1)
        {
            printf("-E- Flags --" USE_IMG_FILE_L " and --" USE_IMG_DIR_L " are not to be used in the same command\n");
            return PARSE_ERROR;
        }
        _cmdLineParams->use_mfa_dir = 1;
        _cmdLineParams->mfa_dir = value;
        return PARSE_OK;
    }
    else if (name == USE_DEFAULT_L)
    {
        _cmdLineParams->download_default = 1;
        return PARSE_OK;
    }
    else if (name == DNLD_L)
    {
        _cmdLineParams->download = true;
        _cmdLineParams->download_dir = value;
        return PARSE_OK;
    }
    else if (name == GET_DNLD_OPT_L)
    {
        trim(value);
        to_lowercase(value);
        if (value != "os" && value != "device")
        {
            printf("-E- Invalid value %s. please specify: OS | Device\n ", value.c_str());
            return PARSE_ERROR;
        }
        _cmdLineParams->get_download_opt = value;
        return PARSE_OK;
    }
    else if (name == DNLD_DEV_L)
    {
        trim(value);
        to_lowercase(value);
        _cmdLineParams->download_dev = value;
        return PARSE_OK;
    }
    else if (name == DNLD_OS_L)
    {
        trim(value);
        to_lowercase(value);
        _cmdLineParams->download_os = value;
        return PARSE_OK;
    }
    else if (name == DNLD_TYPE_L)
    {
        trim(value);
        to_lowercase(value);
        if (value != "mfa" && value != "self_extractor" && value != "all")
        {
            printf("-E- Value :'%s' is not valid, valid values are : MFA | self_extractor|All\n", value.c_str());
            return PARSE_ERROR;
        }
        _cmdLineParams->download_type = value;
        return PARSE_OK;
    }
    else if (name == DNLD_KEY_L)
    {
        _cmdLineParams->download_key = value;
        return PARSE_OK;
    }
    else if (name == LOG_ON_UPDATE_L)
    {
        _cmdLineParams->log_on_update = true;
        return PARSE_OK;
    }
    else if (name == LOG_L)
    {
        _cmdLineParams->create_log = 1;
        return PARSE_OK;
    }
    else if (name == PSID_L)
    {
        _cmdLineParams->psid = value;
        return PARSE_OK;
    }
    else if (name == CRC_L)
    {
        _cmdLineParams->calc_crc = true;
        return PARSE_OK;
    }
    else if (name == EXTRACT_L)
    {
        _cmdLineParams->extract_image = true;
        return PARSE_OK;
    }
    else if (name == EXTRACT_ALL_L)
    {
        _cmdLineParams->extract_all = true;
        return PARSE_OK;
    }
    else if (name == EXTRACT_DIR_L)
    {
        _cmdLineParams->extract_dir = value;
        return PARSE_OK;
    }
    else if (name == EXTRACT_FILE_L)
    {
        _cmdLineParams->target_file = value;
        return PARSE_OK;
    }
    else if (name == COMP_TYPE_L)
    {
        _cmdLineParams->component_type = value;
        return PARSE_OK;
    }
    else if (name == QUERY_L)
    {
        _cmdLineParams->query_device = true;
        return PARSE_OK;
    }
    else if (name == QUERY_XML_L)
    {
        _cmdLineParams->query_device_xml = true;
        return PARSE_OK;
    }
    else if (name == QUERY_FORMAT_L)
    {
        trim(value);
        to_lowercase(value);
        if (value != "xml" && value != "text")
        {
            printf("-E- Value :'%s' is not valid, valid values are : XML | Text\n", value.c_str());
            return PARSE_ERROR;
        }
        _cmdLineParams->queryFormat = value;
        if (_cmdLineParams->queryFormat == "xml")
        {
            _cmdLineParams->query_device_xml = true;
        }
        return PARSE_OK;
    }
    else if (name == LOG_FILE_L)
    {
        _cmdLineParams->create_log = 1;
        _cmdLineParams->use_log_file = 1;
        _cmdLineParams->log_file = value;
        return PARSE_OK;
    }
    else if (name == NO_PROGRESS_L)
    {
        _cmdLineParams->show_progress = false;
        return PARSE_OK;
    }
    else if (name == XML_L)
    {
        _cmdLineParams->write_xml = 1;
        _cmdLineParams->dl = true;
        return PARSE_OK;
    }
    else if (name == OUT_FILE_L)
    {
        _cmdLineParams->use_output_file = 1;
        _cmdLineParams->output_file = value;
        return PARSE_OK;
    }
    else if (name == LOOKUP_FILE_L)
    {
        _cmdLineParams->use_lookup_file = 1;
        _cmdLineParams->lookup_file = value;
        return PARSE_OK;
    }
    else if (name == FORCE_L)
    {
        _cmdLineParams->force_update = 1;
        return PARSE_OK;
    }
    else if (name == NO_FW_CTRL_L)
    {
        _cmdLineParams->no_fw_ctrl = true;
        return PARSE_OK;
    }
    else if (name == FW_UPDATE_PARALLEL_FWCTL_L)
    {
        _cmdLineParams->fw_update_in_parallel_via_fwctl = true;
        return PARSE_OK;
    }
    else if (name == YES_L)
    {
        // Check if --no was already parsed
        if (_cmdLineParams->yes_no_ == 0)
        {
            printf("-E- Flags --" YES_L " and --" NO_L " are not to be used in the same command\n");
            return PARSE_ERROR;
        }
        _cmdLineParams->yes_no_ = 1;
        return PARSE_OK;
    }
    else if (name == NO_L)
    {
        // Check if --yes was already parsed
        if (_cmdLineParams->yes_no_ == 1)
        {
            printf("-E- Flags --" YES_L " and --" NO_L " are not to be used in the same command\n");
            return PARSE_ERROR;
        }
        _cmdLineParams->yes_no_ = 0;
        return PARSE_OK;
    }
    else if (name == LIST_CONTENT_L)
    {
        _cmdLineParams->list_file_contents = true;
        return PARSE_OK;
    }
    else if (name == FFV_L)
    {
        _cmdLineParams->compare_ffv = 1;
        return PARSE_OK;
    }
    else if (name == HELP_L)
    {
        cout << _cmdParser.GetUsage();
        printExamples();
        return PARSE_OK_WITH_EXIT;
    }
    else if (name == HIDDEN_HELP_L)
    {
        cout << _cmdParser.GetUsage(true);
        printExamples();
        return PARSE_OK_WITH_EXIT;
    }
    else if (name == VERSION_L)
    {
        print_version_string((const char*)toolName.c_str(), TOOL_VERSION);
        return PARSE_OK_WITH_EXIT;
    }
    else if (name == BURN_FAIL_SAFE_L)
    {
        _cmdLineParams->burnFailsafe = false;
        return PARSE_OK;
    }
    else if (name == RET_DL_L)
    {
        _cmdLineParams->dl = true;
        return PARSE_OK;
    }
    else if (name == RET_LVIM_L)
    {
        _cmdLineParams->lvim = true;
        return PARSE_OK;
    }
    else if (name == NO_EXTRACT_LIST_L)
    {
        _cmdLineParams->no_extract_list = true;
        return PARSE_OK;
    }
    else if (name == NUM_OF_RETRIALS_L)
    {
        std::istringstream iss(value);
        iss >> _cmdLineParams->numberOfRetrials >> std::ws;
        if (!iss.eof())
        {
            cout << "-E- Could not parse val: " << value << "\n";
            return PARSE_ERROR_SHOW_USAGE;
        }
#if !defined(__FreeBSD__)
        if (iss.fail())
        {
            cout << "-E- Could not parse val: " << value << "\n";
            return PARSE_ERROR_SHOW_USAGE;
        }
#endif
        if (_cmdLineParams->numberOfRetrials < 0)
        {
            cout << "-E- Negative value is not allowed " << value << "\n";
            return PARSE_ERROR;
        }
        return PARSE_OK;
    }
    else if (name == SKIP_IF_SAME_L)
    {
        _cmdLineParams->skip_if_same = true;
        return PARSE_OK;
    }
    else
    {
        cout << "Unknown Flag: " << name << "\n";
        return PARSE_ERROR_SHOW_USAGE;
    }
}
