/*
 * Copyright (c) 2025 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#define MTCR_EXPORT
#include <mtcr.h>
#include <stdio.h>
#include <stdlib.h>
#include "ibd_hw_access.h"
#include "ibd_device.h"
#include <memaccess/qpcaccess.h>

// BIT Slicing macros
#define ONES32(size)                    ((size)?(0xffffffff>>(32-(size))):0)
#define MASK32(offset,size)             (ONES32(size)<<(offset))

#define EXTRACT_C(source,offset,size)   ((((unsigned)(source))>>(offset)) & ONES32(size))
#define EXTRACT(src,start,len)          (((len)==32)?(src):EXTRACT_C(src,start,len))
#define EXT(src,end,start)              EXTRACT(src,start,end-start+1)

#define MERGE_C(rsrc1,rsrc2,start,len)  ((((rsrc2)<<(start)) & (MASK32((start),(len)))) | ((rsrc1) & (~MASK32((start),(len)))))
#define MERGE(rsrc1,rsrc2,start,len)    (((len)==32)?(rsrc2):MERGE_C(rsrc1,rsrc2,start,len))


int ibd_set_hw_sniffer_mode(mfile*    mf,
                            u_int32_t devid,
                            int       ib_port,
                            u_int32_t qp_num,
                            u_int32_t sniffer_en,
                            int       tx,
                            int       rx,
                            u_int32_t source_qps[],
                            int       source_qps_num
                            )
{
    // Set tx and rx global sniffing. set rx and tx qp to the opened qp num
    u_int32_t cfg_base    = 0x40510;
    u_int32_t cfg_base_sx = 0x1c1d0;
    u_int32_t word = 0;
    u_int32_t port_offs    = 0;
    u_int32_t port_offs_sx = 0;
    u_int32_t mode;
    int i;

    // Turn off dup packets cheks
    for (i = 0; i < 5 ; i++) {
        if (mwrite4(mf, 0x450ec + i*4,          0) != 4  ||
            mwrite4(mf, 0x45104 + i*4, 0xffffffff) != 4 ) {
            fprintf(stderr, "-E- CR access failed\n");
            return -1;
        }
    }

    // set mode:
    if (sniffer_en == 0) {
        mode = 0;
    } else  {
        if (source_qps_num != 0) {
            mode = 1; // PER QP Sniffing
        } else {
            mode = 2; // Global port sniffing
        }
    }

    if (sniffer_en && (devid == DI_CX2 || devid == DI_CX3 || devid == DI_CX3A1 || devid == DI_CX3Pro)) {
        QpcAccess* qpc;
        u_int32_t  qpc_data[32];
        int rc;

        rc = qpc_opend(&qpc, mf);
        if (rc) {
            fprintf(stderr, "-E- Failed to open Sniffer QP access\n");
            return -1;
        }
        rc = qpc_get_context(qpc, qp_num, qpc_data, QRcv);
        if (rc) {
            fprintf(stderr, "-E- Failed to read Sniffer QP\n");
            return -1;
        }

        // Fix data - Set TX and RX sniffer bits.
        // I set here both sides because tx/rx are filtered
        // via crspace.
        qpc_data[2] |= 3;
        rc = qpc_set_context(qpc, qp_num, qpc_data, QRcv);
        if (rc) {
            fprintf(stderr, "-E- Failed to set Sniffer QP\n");
            return -1;
        }
        qpc_close(qpc);
    }

    if (ib_port == 2) {
        port_offs    = 4;
        port_offs_sx = 0x20;
    }

    if (sniffer_en) {
        // SX qpn:
        if (mwrite4(mf, cfg_base + 8 + port_offs, qp_num) != 4 ) {
            fprintf(stderr, "-E- CR access failed\n");
            return -1;
        }
        word  = qp_num;
    }

    word |= (mode << 29);

    // RX qpn and mode
    if (rx) {
        if (mwrite4(mf, cfg_base + port_offs, word) != 4 ) {
            fprintf(stderr, "-E- CR access failed\n");
            return -1;
        }
    }

    // SX Mode:
    // 1c1d0
    // 1c1f0
    if (tx) {
        if (devid == DI_CX) {
            if (mread4(mf, cfg_base_sx + port_offs_sx, &word) != 4 ) {
                fprintf(stderr, "-E- CR access failed\n");
                return -1;
            }

            //word = MERGE(word, mode, 29, 2);
            word = (word & ~(3<<29)) | ((sniffer_en & 3)<<29);

            if (mwrite4(mf, cfg_base_sx + port_offs_sx, word) != 4 ) {
                fprintf(stderr, "-E- CR access failed\n");
                return -1;
            }
        } else if (devid == DI_CX2 || devid == DI_CX3 || devid == DI_CX3A1 || devid == DI_CX3Pro) {
            cfg_base_sx = 0x1c1d8;
            word = !sniffer_en    ? 0     :
                   source_qps_num ? 0x100 : 0x10000;
            if (mwrite4(mf, cfg_base_sx + port_offs_sx, word) != 4 ) {
                fprintf(stderr, "-E- CR access failed\n");
                return -1;
            }
        } else {
            fprintf(stderr, "-F- Unknown devid %x\n", devid );
            exit(1);
        }
    }

    if (source_qps_num != 0
        && sniffer_en  // For now, never try to clear the sniffer bits. That's because
                       // it the qp does not exist, it causes a driver FATAL for accessing a
                       // non existing QP
        ) {
        int i;
        QpcAccess* qpc;
        u_int32_t  qpc_data[32];
        int rc;

        rc = qpc_opend(&qpc, mf);
        if (rc) {
            fprintf(stderr, "-E- Failed to open Source QP access\n");
            return -1;
        }

        // rx_sniffer bit - DW 28 (from end) bit 31
        // sx_sniffer bit - DW 31 (from end) bit 1
        for (i = 0; i < source_qps_num; i++) {
            u_int32_t qpn = source_qps[i];
            int qs_idx;
            QpcSrc qp_src[2] = {QRcv, QSnd};

            // Set the sniffer _rx/_tx bit in the RCV and SND QP Contexts:
            for (qs_idx = 0; qs_idx < 2; qs_idx++) {
                rc = qpc_get_context(qpc, qpn, qpc_data, qp_src[qs_idx]);
                if (sniffer_en && rc) {
                    fprintf(stderr, "-E- Failed to read Source QP %x\n", qpn);
                    return -1;
                }

                if (rx) {
                    qpc_data[28] = MERGE(qpc_data[28], sniffer_en, 31, 1);
                }
                if (tx) {
                    qpc_data[31] = MERGE(qpc_data[31], sniffer_en, 1, 1);
                }

                rc = qpc_set_context(qpc, qpn, qpc_data, qp_src[qs_idx]);
                if (sniffer_en && rc) {
                    fprintf(stderr, "-E- Failed to set Source QP %x\n", qpn);
                    return -1;
                }
            }
        }
        qpc_close(qpc);
    }

    return 0;
}

