/*
 *
 * flint_params.h - FLash INTerface
 *
 * Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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
    SC_Qrom
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
    bool uids_specified;
    guid_t baseUid;
    std::vector<guid_t> user_uids;
    bool help;
    bool version;
    bool extended_help;
    bool blank_guids;
    bool clear_semaphore;
    bool quick_query;
    bool image_specified;
    string image;
    bool nofs;
    bool allow_psid_change;
    bool allow_rom_change;
    bool override_cache_replacement;
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
};

#endif
