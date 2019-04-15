/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 */

#include <stdio.h>
#include <bit_slice.h>
#include <mtcr.h>

#include "icmd_cif_common.h"
#include "icmd_cif_open.h"
#include "icmd_cif_macros.h"


#define MH_SYNC_OPCODE        0x8402
#define MH_SYNC_STATUS_OPCODE 0x8403

/*
 * gcif_get_fw_info
 */
int gcif_get_fw_info(mfile *mf,
                     OUT struct connectib_icmd_get_fw_info *fw_info)
{
    SEND_ICMD_FLOW(mf, GET_FW_INFO, connectib_icmd_get_fw_info, fw_info, 0, 1);
}

/*
 * get_icmd_query_cap
 */
int get_icmd_query_cap(mfile *mf, struct connectx4_icmd_query_cap_general *icmd_query_caps)
{
    SEND_ICMD_FLOW(mf, GET_ICMD_QUERY_CAP, connectx4_icmd_query_cap_general, icmd_query_caps, 1, 0);
}

int gcif_mh_sync(mfile *mf, struct connectx4_icmd_mh_sync *mh_sync)
{
    SEND_ICMD_FLOW(mf, MH_SYNC_OPCODE, connectx4_icmd_mh_sync, mh_sync, 1, 0);
}

int gcif_mh_sync_status(mfile *mf, struct connectx4_icmd_mh_sync *mh_sync_out)
{
    memset(mh_sync_out, 0x0, sizeof(*mh_sync_out));
    SEND_ICMD_FLOW(mf, MH_SYNC_STATUS_OPCODE, connectx4_icmd_mh_sync, mh_sync_out, 1, 0);
}

int gcif_set_itrace(mfile *mf, struct connectib_itrace *itrace)
{
    SEND_ICMD_FLOW(mf, SET_ITRACE, connectib_itrace, itrace, 1, 0);
}

int gcif_set_port_sniffer(mfile *mf, struct connectib_icmd_set_port_sniffer *set_port_sniffer)
{
    SEND_ICMD_FLOW(mf, SET_PORT_SNIFFER, connectib_icmd_set_port_sniffer, set_port_sniffer, 1, 0);
}
