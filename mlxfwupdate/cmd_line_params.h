
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
 */

#ifndef __CMDLINEPARAMS_H__
#define __CMDLINEPARAMS_H__

#include <vector>
#include <string>
#include "mlxfwmanager_common.h"

using namespace std;

class CmdLineParams
{
public:
    CmdLineParams();
    ~CmdLineParams();
    vector<string> device_names;
    int force_update;
    int update_fw;
    int use_mfa_file;
    int use_mfa_dir;
    bool skip_if_same;

    string mfa_dir;
    string mfa_file;
    int yes_no_;
    int write_xml;
    int use_exe_rel_paths;
    int use_output_file;
    string output_file;
    int create_log;
    int compare_ffv;
    int use_log_file;
    string log_file;
    int use_lookup_file;
    string lookup_file;
    string psid;
    string target_file;
    bool extract_image;
    bool extract_all;
    string extract_dir;
    bool list_file_contents;
    bool display_archive_names;
    bool show_progress;
    bool log_on_update;
    bool calc_crc;
    bool query_device;
    bool query_device_xml;
    bool clear_semaphore;
    string current_dir;
    string server_url;
    string proxy;

    bool download;
    bool download_default;
    string get_download_opt;
    string download_dir;
    string download_os;
    string download_type;
    string download_dev;
    string download_key;
    string onlineQueryPsids;
    bool update_online;
    bool burnFailsafe;
    string certificate;
    string queryFormat;
    bool lvim;
    bool dl;
    bool no_extract_list;
    int numberOfRetrials;
    bool no_fw_ctrl;
    bool parallel_fwctl;
    string component_type;
};

#endif
