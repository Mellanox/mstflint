
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

#include "cmd_line_params.h"

CmdLineParams::CmdLineParams()
{
    force_update = 0;
    update_fw = 0;
    use_mfa_file = 0;
    use_mfa_dir = 0;
    yes_no_ = -1;
    compare_ffv = 0;
    write_xml = 0;
    use_output_file = 0;
    create_log = 0;
    use_log_file = 0;
    use_exe_rel_paths = 0;
    use_lookup_file = 0;
    list_file_contents = false;
    display_archive_names = false;
    extract_image = false;
    show_progress = true;
    log_on_update = false;
    calc_crc = false;
    query_device = false;
    query_device_xml = false;
    clear_semaphore = false;
    extract_all = false;
    no_fw_ctrl = false;
    parallel_fwctl = false;
    target_file = "";
    server_url = "https://www.mellanox.com";
    proxy = "";
    update_online = false;
    download = false;
    download_default = false;
    get_download_opt = "";
    download_os = ""; // will be changed to enum
    download_type = "";
    download_dev = "";
    download_key = "last_release";
    psid = "";
    burnFailsafe = true;
    onlineQueryPsids = "";
    queryFormat = "text";
    download_dir = ".";
    extract_dir = ".";
    lvim = false;
    dl = false;
    no_extract_list = false;
    numberOfRetrials = 5;
    component_type = "";
    skip_if_same = false;
#ifdef __WIN__
    char execName[1024];
    char certificatPath[1024];
    GetModuleFileName(GetModuleHandle(mlxfw_MTCR_DLL_NAME), certificatPath, 1024);
    mlxfw_get_exec_name_from_path(certificatPath, execName);
    mlxfw_replace(certificatPath, execName, (char*)"ca-bundle.crt");

    certificate = string(certificatPath);

#else
#ifdef MSTFLINT
    certificate = (string)ROOT_PATH + "etc/mstflint/ca-bundle.crt";
#else
    certificate = (string)ROOT_PATH + "etc/mft/ca-bundle.crt";
#endif
#endif
}

CmdLineParams::~CmdLineParams() {}
