/*
 *
 * flint_params.h - FLash INTerface
 *
 * Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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
 *  Version: $Id$
 *
 */

#ifndef __FLINTPARAMS__
#define __FLINTPARAMS__

#include <string>
#include <vector>
#include "mlxfwops/lib/mlxfwops_com.h"
#include "mflash/mflash.h"

using namespace std;

typedef enum {
    SC_No_Cmd = 0,
    SC_Burn,
    SC_Query,
    SC_Verify,
    SC_Swreset,
    SC_ResetCfg,
    SC_Brom,
    SC_Drom,
    SC_Rrom,
    SC_Bb,
    SC_Sg,
    SC_Smg,
    SC_Set_Vpd,
    SC_Set_Cert_Chain,
    SC_Sv,
    SC_Ri,
    SC_Dc,
    SC_Dh,
    SC_Set_Key,
    SC_Hw_Access,
    SC_Hw,
    SC_Erase,
    SC_Rw,
    SC_Ww,
    SC_Wwne,
    SC_Wbne,
    SC_Wb,
    SC_Rb,
    SC_Clear_Sem,
    SC_Fix_Img,
    SC_Qrom,
    SC_Check_Sum,
    SC_Time_Stamp,
    SC_Cache_Image,
    SC_Sign,
    SC_Add_Hmac,
    SC_Extract_4MB_Image,
    SC_Set_Public_Keys,
    SC_Set_Forbidden_Versions,
    SC_Image_Reactivation,
    SC_RSA_Sign,
    SC_Binary_Compare,
    SC_Import_Hsm_Key,
    SC_Export_Public_Key
} sub_cmd_t;

class FlintParams {
public:
    //add more params
    FlintParams();
    ~FlintParams();
    bool device_specified;
    string device;
    bool guids_specified;
    bool guid_specified;
    std::vector<guid_t> user_guids;
    bool mac_specified;
    bool macs_specified;
    std::vector<guid_t> user_macs;
    bool uid_specified;
    guid_t baseUid;
    bool help;
    bool version;
    bool extended_help;
    bool blank_guids;
    bool clear_semaphore;
    bool quick_query;
    bool low_cpu;
    bool next_boot_fw_ver;
    bool skip_rom_query;
    bool image_specified;
    bool nonencrypted_image_specified;
    bool mfa2_specified;
    string image;
    string nonencrypted_image;
    bool nofs;
    bool allow_psid_change;
    bool allow_rom_change;
    bool override_cache_replacement;
    bool use_fw;
    bool no_flash_verify;
    bool silent;
    bool yes;
    bool no;
    bool vsd_specified;
    string vsd;
    bool use_image_ps;
    bool use_image_guids;
    bool use_image_rom;
    bool dual_image;
    bool striped_image;
    bool ignore_dev_data;
    bool banks_specified;
    int banks;
    bool log_specified;
    string log;
    bool flash_params_specified;
    flash_params_t flash_params;
    bool no_devid_check;
    sub_cmd_t cmd;
    vector<string> cmd_params;
    string fullCmd;
    bool use_dev_img_info;
    bool ignore_crc_check;
    bool hexdump_format;
    bool skip_ci_req;
    bool use_dev_rom;
    bool privkey_specified;
    bool pubkey_specified;
    string privkey_file;
    string pubkey_file;

    bool uuid_specified;
    string privkey_uuid;
    bool privkey2_specified;
    bool key_specified;
    string key;
    string privkey2_file;
    bool uuid2_specified;
    string privkey2_uuid;
    bool no_fw_ctrl;
    bool image_reactivation;
    int num_of_args;
    bool use_latest_fw_version;
    string psid;
    bool use_psid;
    bool congestion_control;
    string congestion_control_param;
    bool use_cpu_utilization;
    int cpu_percent;
    bool hsm_specified;
    string private_key_label;
    string public_key_label;
    bool private_key_label_specified;
    bool public_key_label_specified;
    bool output_file_specified;
    string output_file;
    bool hsm_password_specified;
    string hsm_password;
    bool linkx_control;
    int  cableDeviceIndex;
    int cableDeviceSize;
    bool cable_device_index_specified;
    bool cable_device_size_specified;
    bool linkx_auto_update;
    bool activate;
    bool download_downstream_specified;
    bool downstream_device_ids_specified;
    std::vector<int>  downstream_device_ids;
    bool download_transfer;
    u_int8_t activate_delay_sec;
    string openssl_engine;
    string openssl_key_id;
    bool openssl_engine_usage_specified;
};

#endif
