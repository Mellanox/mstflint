/*
 * Copyright (c) 2026 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

/* Remote device access over the MST HTTP server.
 *
 * A remote device is named "<host>:<port>,<device>" (MFT-compatible), where
 * <device> is the device path as it exists on the remote host and '@' stands
 * for '/' so the name survives shells and paths. Example:
 *
 *     mstmread -d 10.0.0.7:8080,@dev@mst@mt4125_pciconf0 0xf0014
 *
 * The whole file is a no-op unless configure was run with --enable-remote.
 */

#ifndef MTCR_REMOTE_H
#define MTCR_REMOTE_H

#include "mtcr_com_defs.h"

/* Directory scanned for remote-device marker files. A marker is an empty file
 * whose name is the remote device name; creating one is the mstflint
 * equivalent of MFT's "mst remote add".
 *
 * mstflint's own directory, not MFT's /dev/mst, even though the marker
 * convention is MFT's. Two reasons, in order of severity:
 *
 *   - MFT owns /dev/mst and clears it. "mst stop" runs "rm -fr /dev/mst", and
 *     "mst remote del <host>" runs "rm -f /dev/mst/<host>:<port>,*" - which is
 *     exactly the name pattern written here. An MFT service restart, or a
 *     removal aimed at MFT's own registration, would silently take ours with
 *     it, leaving devices that mstflint reports and cannot open.
 *   - mstflint already owns /dev/mstflint: mdevices_v_ul() scans it for cable
 *     devices a few lines below where it scans this one.
 *
 * The cost is that a device registered by "mst remote add" is not visible to
 * mstflint and vice versa. That interoperability was never real - each side
 * needs a session token the other did not obtain - and it is not worth having
 * another package able to delete our state. */
#define MTCR_REMOTE_DEV_DIR "/dev/mstflint"

/* Protocol constants shared with the MST HTTP server. Both sides have to agree
 * on them: the server static_asserts its own cable chunk size against the
 * first, and reports the second from its /capabilities endpoint. */

/* Largest cable transfer the server accepts in one request. A longer transfer
 * is split into chunks of this size by the caller. */
#define CABLES_REMOTE_BUF_DATA_SIZE 2048

/* Capability bit: the server accepts the 64-bit address form. */
#define LONG_ADDRESS_SUPPORT      0
#define LONG_ADDRESS_SUPPORT_MASK (1 << LONG_ADDRESS_SUPPORT)

#ifdef __cplusplus
extern "C"
{
#endif

/* Directory actually scanned for markers: $MSTFLINT_REMOTE_DEV_DIR when set,
 * MTCR_REMOTE_DEV_DIR otherwise. The override exists so the feature can be
 * exercised without write access to /dev/mstflint. Never returns NULL. */
const char* mtcr_remote_dev_dir(void);

/* True when `name` looks like a remote device name. Cheap and side-effect
 * free: mopen() needs it before it decides whether local root is required. */
int mtcr_remote_is_remote_name(const char* name);

/* Open `name` against the remote MST HTTP server and install the remote
 * access-function table on mf. Returns 0 on success, -1 otherwise. */
int mtcr_remote_open(mfile* mf, const char* name);

/* Forwarded operations that do not go through the ul_ctx dispatch table.
 * All of them require mf to be a remote device (mf->is_remote).
 *
 * read_device_id() deliberately has no entry here: it is built on mread4(), so
 * the dispatch table already remotes it, and going through mread4 preserves
 * the local rev_id extraction that a /device/id round trip would lose. */
int mtcr_remote_set_addr_space(mfile* mf, int space);
int mtcr_remote_maccess_reg(mfile* mf,
                            u_int16_t reg_id,
                            maccess_reg_method_t reg_method,
                            void* reg_data,
                            u_int32_t reg_size,
                            int* reg_status);
int mtcr_remote_icmd_send_command(mfile* mf, int opcode, void* data, int data_size, int skip_write);

#ifdef __cplusplus
}
#endif

#endif /* MTCR_REMOTE_H */
