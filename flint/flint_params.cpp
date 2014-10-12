/*
 *
 * flint_params.cpp - FLash INTerface
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

#include "flint_params.h"

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
    uids_specified = false;
    device_specified = false;
    blank_guids = false;
    clear_semaphore = false;
    quick_query = true;  //should now be true by default
    image_specified = false;
    nofs = false;
    allow_psid_change = false;
    allow_rom_change = false;
    override_cache_replacement = false;
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
    banks = -1;
    log_specified = false;
    flash_params_specified = false;
    flash_params.type_name = (char*)NULL;
    no_devid_check = false;
    cmd = SC_No_Cmd;
    baseUid.h = 0;
    baseUid.l = 0;
    flash_params.num_of_flashes = 0;
    flash_params.log2size = 0;
}

FlintParams::~FlintParams()
{

}
