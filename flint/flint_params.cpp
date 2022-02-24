/*
 *
 * flint_params.cpp - FLash INTerface
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

#include "flint_params.h"
#include <cstring>

FlintParams::FlintParams()
{
    help = false;
    version = false;
    extended_help = false;
    guids_specified = false;
    guid_specified = false;
    mac_specified = false;
    macs_specified = false;
    uid_specified = false;
    device_specified = false;
    blank_guids = false;
    clear_semaphore = false;
    quick_query = true;  //should now be true by default
    next_boot_fw_ver = false;
    low_cpu = false;
    skip_rom_query = false;
    image_specified = false;
    nonencrypted_image_specified = false;
    mfa2_specified = false;
    nofs = false;
    allow_psid_change = false;
    allow_rom_change = false;
    override_cache_replacement = false;
    use_fw = false; // access flash via FW on CX3/CX3Pro
    no_flash_verify = false;
    silent = false;
    yes = false;
    no = false;
    vsd_specified = false;
    use_image_ps = false;
    use_image_guids = false;
    use_image_rom = false;
    dual_image = false;
    striped_image = false;
    ignore_dev_data = false;
    banks_specified = false;
    banks = -1; // must be -1 for mflash to get default num of flash
    log_specified = false;
    flash_params_specified = false;
    memset(flash_params.type_name, 0, MAX_FLASH_NAME);
    no_devid_check = false;
    cmd = SC_No_Cmd;
    baseUid.h = 0;
    baseUid.l = 0;
    flash_params.num_of_flashes = 0;
    flash_params.log2size = 0;
    use_dev_img_info = false;
    ignore_crc_check = false;
    hexdump_format = false;
    skip_ci_req = false;
    use_dev_rom = false;
    privkey_specified = false;
    pubkey_specified = false;
    privkey2_specified = false;
    uuid_specified = false;
    uuid2_specified = false;
    no_fw_ctrl = false;
    image_reactivation = false;
    num_of_args = 0;
    use_latest_fw_version = false;
    use_psid = false;
    congestion_control = false;
    use_cpu_utilization = false;
    public_key_label_specified = false;
    private_key_label_specified = false;
    hsm_specified = false;
    hsm_password_specified = false;
    linkx_control = false;
    cableDeviceIndex = -1;
    cableDeviceSize = -1;
    cable_device_size_specified = false;
    cable_device_index_specified = false;
    linkx_auto_update = false;
    activate = false;
    downstream_device_ids_specified = false;
    download_transfer = false;
    // if no delay specified, use minimal delay to avoid disconnection in case of activating the connect port
    activate_delay_sec = 1; 
    openssl_engine_usage_specified = false;
}

FlintParams::~FlintParams()
{

}
