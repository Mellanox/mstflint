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
#include <map>
#include <iostream>
#include <vector>
#include <compatibility.h>
#include <mtcr.h>
#include <mfa.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <ctime>
#include <signal.h>
#include <errno.h>
#include <string.h>
#include <iniparser.h>
#include <mft_sig_handler.h>
#include <fcntl.h>
#include <dirent.h>
#include <stdlib.h>
#include "mlnx_dev.h"
#include "server_request.h"
#include "cmd_line_parser.h"
#include "cmd_line_params.h"
#include "image_access.h"
#include "psid_lookup_db.h"
#include "psid_query_item.h"
#include "output_fmts.h"
#include "mlxfwmanager_common.h"
#include "menu.h"

#include "common/tools_filesystem.h"
namespace Filesystem = mstflint::common::filesystem;

FILE* FLog = NULL;
FILE* FOut = stdout;
FILE* FErr = stderr;
extern string toolName;

#define print_out(...)                  \
    do                                  \
    {                                   \
        if (!formatted_output)          \
        {                               \
            fprintf(FOut, __VA_ARGS__); \
            fflush(FOut);               \
        }                               \
        if (FLog != NULL)               \
        {                               \
            fprintf(FLog, __VA_ARGS__); \
        }                               \
    } while (0)

#define print_err(...)                  \
    do                                  \
    {                                   \
        if (!formatted_output)          \
        {                               \
            fprintf(FErr, __VA_ARGS__); \
            fflush(FErr);               \
        }                               \
        if (FLog != NULL)               \
        {                               \
            fprintf(FLog, __VA_ARGS__); \
        }                               \
    } while (0)
#define print_out_xml(...)              \
    do                                  \
    {                                   \
        fprintf(FOut, __VA_ARGS__);     \
        fflush(FOut);                   \
        if (FLog != NULL)               \
        {                               \
            fprintf(FLog, __VA_ARGS__); \
        }                               \
    } while (0)

int formatted_output = 0;

using namespace std;

typedef struct
{
    string mfa_path;
    bool path_is_file;
    bool display_file_names;
    string exe_path;
    string adjuster_path;
    string http_server;
    string http_proxy;
    string psid;
    mlxFWMSetupType::T setupType;
} config_t;

int mainEntry(int argc, char* argv[]);
string getline();
// void    displayFilesToBeDownloaded(filesOPtions filterOPtions, CmdLineParams cmd_params);
int displayReleaseNoteFiles(const filesOPtions& filterOPtions, const CmdLineParams& cmd_params);
void displayReleaseNoteMFAs(map<string, PsidQueryItem> psidUpdateInfo, vector<MlnxDev*> devs, int deviceIndex);
void display_file_listing(vector<PsidQueryItem>& items,
                          string psid,
                          bool show_titles,
                          int signature = IMG_SIG_TYPE_UNKNOWN);
int getLocalDevices(dev_info** devs);
void getUniquePsidList(vector<MlnxDev*>& devs,
                       vector<string>& psid_list,
                       vector<dm_dev_id_t>& dev_types_list,
                       vector<string>& fw_version_list);
void getUniqueMFAList(vector<MlnxDev*>& devs,
                      map<string, PsidQueryItem>& psidUpdateInfo,
                      int force_update,
                      vector<string>& mfa_list,
                      vector<string>& mfa_base_name_list,
                      bool skip_if_same);
int queryMFAs(ServerRequest* srq,
              string& mfa_path,
              vector<string>& psid_list,
              vector<dm_dev_id_t>& dev_types_list,
              map<string, PsidQueryItem>& psidUpdateInfo,
              int online_update,
              string& errorMsg,
              vector<string>& fw_version_list);
int getPLDMImgListFromPSIDs(string file, vector<string>& psid_list, vector<PsidQueryItem>& results);
int getPLDMCompsListFromPSIDs(string file,
                              vector<string>& psid_list,
                              vector<tuple<PsidQueryItem, u_int8_t*, u_int32_t>>& results,
                              ComponentIdentifier compId);
int queryPLDM(string file,
              vector<string>& psid_list,
              map<string, vector<tuple<FwComponent::comps_ids_t, u_int8_t*, u_int32_t>>>& psidPldmComponents);
int download(ServerRequest* srq,
             vector<string>& url,
             vector<string>& fileNames,
             vector<string>& os,
             string path,
             bool show_location = true);
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
                                 CmdLineParams& cmd_params);

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
                          bool multiple_images_found);

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
                        bool multiple_images_found);

int prompt(const char* str, int yes_no_);
FILE* createOutFile(string& fileName, bool fileSpecified);
int progressCB_nodisplay(int completion);
int progressCB_display(int completion);
int progressCB_display_multi_thread(int completion);
int advProgressFunc_display(int completion, const char* stage, prog_t type, int* unknownProgress);
int advProgressFunc_display_multi_thread(int completion, const char* stage, prog_t type, int* unknownProgress);
bool checkCmdParams(CmdLineParams& cmd_params, config_t& config);
bool initConfig(config_t& config, char* argv[], CmdLineParams& cmd_params);
bool getIniParams(config_t& config);
string adjustRelPath(string path, string adjuster);
int isDirectory(string path);
int isFile(string path);
int list_files_content(config_t& config);
int extract_all(CmdLineParams& cmd_params, config_t& config, ServerRequest* srq);
int extract_image(CmdLineParams& cmd_params, config_t& config, ServerRequest* srq, bool useExtractDir = false);
int CalcFileCrc(char* fileName);
void TerminationHandler(int signum);
void initHandler();
void replaceStringInPlace(string& subject, const string& search, const string& replace);
void fixXmlString(string& stringToFix);

bool isServerRequestorRequired(CmdLineParams& cmd_params);

int check_valid_os_type(CmdLineParams& cmd_params, bool* os_valid);

int handleGetDownloadOptionsRequest(ServerRequest* srq, CmdLineParams& cmd_params);

int handleDownloadRequest(ServerRequest* srq, CmdLineParams& cmd_params, config_t config);

int handleOnlinePsidsQuery(ServerRequest* srq, CmdLineParams& cmd_params, config_t config);
int handleOnlinePsidsQueryXml(ServerRequest* srq, CmdLineParams& cmd_params, config_t config);
void filterFiles(vector<DownloadedFileProperties> files,
                 vector<DownloadedFileProperties>& filtered_files,
                 int file_type,
                 int os,
                 int family);

int generateProductionName(string& targetFile, PsidQueryItem ri);
bool isSameVersion(MlnxDev* dev, PsidQueryItem& psidUpdateInfo);

int abort_request = 0;
int CompareFFV = 0;
bool IS_OKAY_To_INTERRUPT = false;
