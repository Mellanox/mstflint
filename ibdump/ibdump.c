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


#include <stdio.h>
#include <stdarg.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <infiniband/verbs.h>
#ifndef __WIN__
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/time.h>
    #include <pthread.h>
#else
    #include "time_compat.h"
    #include "compatibility.h"
#endif
#include <errno.h>
#include <getopt.h>
#include <signal.h>

#if defined(WITH_MFT) || defined(WITH_MSTFLINT)
    #include <mtcr.h>
#ifdef WITH_MFT
    #include "ibd_hw_access.h"
#endif
#endif

#include "ibdump.h"
#include "ibd_device.h"
#include "tools_version.h"

#ifdef __WIN__
    #include "ibd_ibal_access.h"
    #define __WIN_CDECL __cdecl
#else
    #define __WIN_CDECL
#endif


int g_stop_sniffer = 0;

void my_printf(const char* format, ...)
{
    va_list args;

    if (!config.is_silent) {
        va_start(args, format);
        vfprintf(stdout, format, args);
        va_end(args);
    }
}

void* write_to_file(void *ptr)
{
    struct resources *res = (struct resources *)ptr;
    int               writer_current_buf = 0;

    while (1) {
        while (res->thread_status[writer_current_buf] == 0) {
            ;
        }
        int rc =
            fwrite(res->thread_buf[writer_current_buf], (size_t)(res->buf_length[writer_current_buf]), 1, res->fh);
        if (rc != 1) {
            fprintf(stderr, "rc=%d -E- Failed writing to file: %s\n", rc, strerror(errno));
            exit(1);
        }
        res->thread_status[writer_current_buf] = 0;
        writer_current_buf = (writer_current_buf + 1) % 2;
    }
}

static u_int32_t mtu_enum_to_num(int mtu_e)
{
    return 256 * (1 << (mtu_e - 1));
}

/*****************************************
* Function: poll_completion
*****************************************/
static int poll_completion(struct resources *res, FILE* f, int idx, int* added_packets)
{
    struct ibv_wc        wc;
    struct timeval       cur_time;
    int                  rc;
    rec_hdr_t            hdr_obj;
    rec_hdr_t          * hdr = &hdr_obj;
    static unsigned long prev_print_time_sec = 0;
    static unsigned long prev_cap_time_sec = 0;
    static u_int64_t     printed_pkts = 1;
    u_int32_t            poll_count = 50000;
    int                  decap_offs = 0;
    u_int32_t            len;
    u_int32_t            header_size;

    if (!config.is_silent &&
        (prev_cap_time_sec > prev_print_time_sec) &&
        (res->sniffed_pkts != printed_pkts)) {
        if (config.mem_size) {
            printf("\rCaptured:  %8" PRIu64 " packets, %8" PRIu64 "/%" PRIu64 " bytes     ",
                   res->sniffed_pkts,
                   res->sniffed_bytes,
                   config.mem_size);
        } else {
            printf("\rCaptured:  %8" PRIu64 " packets, %8" PRIu64 " bytes     ",
                   res->sniffed_pkts,
                   res->sniffed_bytes);
        }
        fflush(stdout);
        prev_print_time_sec = prev_cap_time_sec;
        printed_pkts = res->sniffed_pkts;
    }

    do {
        --poll_count;
        rc = ibv_poll_cq(res->cq, 1, &wc); /* TODO: Multiple WC poll */
        if (rc < 0) {
            fprintf(stderr, "-E- poll CQ failed\n");
            return 1;
        }
    } while ((rc == 0) && !g_stop_sniffer && poll_count);

    gettimeofday(&cur_time, NULL);
    prev_cap_time_sec = cur_time.tv_sec;

    if (g_stop_sniffer || (poll_count == 0)) {
        *added_packets = 0;
        return 0;
    }

    /* fprintf(stdout, "completion was found in CQ with status 0x%x, bytes: %d\n", wc.status, wc.byte_len); */

    /* check the completion status (here we don't care about the completion opcode */
    if (wc.status != IBV_WC_SUCCESS) {
        fprintf(stderr, "\n-E- got bad completion with status: 0x%x, vendor syndrome: 0x%x\n",
                wc.status, wc.vendor_err);
        /*getchar(); */
        return 1;
    }

    len = wc.byte_len;

    hdr->erf.flags = 4;

    if (config.decap_mode) {
        /* Decap - remove LRH, RWH, and CRC */
        if (((res->buf[idx][2] & 0x3) == 0) &&   /* LRH->LNH Says RAW */
            (res->buf[idx][10] == (PM_ENCAP_ETHERTYPE >> 8)) &&
            (res->buf[idx][11] == (PM_ENCAP_ETHERTYPE & 0xff))) {   /* RWH->EtherType matches port mirroring encap */
            decap_offs = 16;
            len -= 18; /* remove LRW, RWH, Mirror_Prefix and VCRC */
            hdr->erf.flags = 5;
        }
    }

    /* pcap header */
    hdr->pcap.ts_sec = cur_time.tv_sec;
    hdr->pcap.ts_usec = cur_time.tv_usec;
    hdr->pcap.orig_len = len;
    header_size = sizeof(hdr->pcap);
    if (config.with_erf) {
        header_size += sizeof(hdr->erf);
        hdr->pcap.orig_len += sizeof(hdr->erf);
    }

    /* Currently no truncating is done */
    hdr->pcap.incl_len = hdr->pcap.orig_len;

    /* erf header */
    hdr->erf.ts = ((u_int64_t)cur_time.tv_sec) << 32;
    /* 1<<32 / 10E6 = 4294.967296 */
    /* The below is an approximation which is 99.999% accurate. */
    /* TODO - See if tehre's a better way to do that (performance wise) */
    hdr->erf.ts += (u_int64_t)cur_time.tv_usec * 4295;
    hdr->erf.lctr = 0;
    hdr->erf.wlen = ntohs((u_int16_t)len);
    hdr->erf.rlen = ntohs(len + sizeof(hdr->erf));  /* TODO - extra 6 bytes here ??? */
    hdr->erf.type = config.erf_type;

    if (config.mem_size) {
        if (!config.writer_thread) {
            memcpy(res->mem_buf + res->dumped_bytes, hdr, header_size);
            memcpy(res->mem_buf + res->dumped_bytes + header_size, res->buf[idx] + decap_offs, len);
        } else {
            if ((res->dumped_bytes + header_size + len) >= config.mem_size) {
                res->buf_length[res->network_current_buf] = res->dumped_bytes;
                res->dumped_bytes = 0;
                res->thread_status[res->network_current_buf] = 1;
                res->network_current_buf = (res->network_current_buf + 1) % 2;
                while (res->thread_status[res->network_current_buf] == 1) {
                    ;
                }
            }
            memcpy(res->thread_buf[res->network_current_buf] + res->dumped_bytes, hdr, header_size);
            memcpy(res->thread_buf[res->network_current_buf] + res->dumped_bytes + header_size,
                   res->buf[idx] + decap_offs,
                   len);
        }
    } else {
        rc = fwrite(hdr, header_size, 1, f);
        if (rc == 1) {
            rc = fwrite(res->buf[idx] + decap_offs, len, 1, f);
        }

        if (rc != 1) {
            fprintf(stderr, "-E- Failed writing to file: %s\n", strerror(errno));
            return 1;
        }
        if (config.to_stdout) {
            fflush(f);
        }
    }

    res->dumped_bytes += (header_size + len);

    *added_packets = 1;
    res->sniffed_pkts += 1;
    res->sniffed_bytes += len;


    return 0;
}

/*****************************************
* Function: post_receive
*****************************************/
static int post_receive(struct resources *res, int idx)
{
    struct ibv_recv_wr  rr;
    struct ibv_sge      sge;
    struct ibv_recv_wr *bad_wr;
    int                 rc;

    /* prepare the scatter/gather entry
     *  Reserve room for the pcap+erf headers before the packet data
     */
    memset(&sge, 0, sizeof(sge));
    sge.addr = (uintptr_t)(res->buf[idx]);
    /*sge.length = 4*1024; //orenk mtu_enum_to_num(res->port_attr.active_mtu) + GRH_SIZE; */
    sge.length = res->entry_size;
    sge.lkey = res->mr->lkey;

    /* prepare the RR */
    memset(&rr, 0, sizeof(rr));

    rr.next = NULL;
    rr.wr_id = 0;
    rr.sg_list = &sge;
    rr.num_sge = 1;

    /* post the Receive Request to the RQ */
    rc = ibv_post_recv(res->qp, &rr, &bad_wr);
    if (rc) {
        fprintf(stderr, "-E- failed to post RR\n");
        return 1;
    }
    return 0;
}

/*****************************************
* Function: resources_init
*****************************************/
static void resources_init(struct resources *res)
{
    res->dev_list = NULL;
    res->ib_ctx = NULL;
    res->cq = NULL;
    res->qp = NULL;
    res->ah = NULL;
    res->pd = NULL;
    res->mr = NULL;
    res->buf = NULL;
    res->mem_buf = NULL;
    res->mem_buf2 = NULL;
    res->fh = NULL;
    res->dumped_bytes = 0;
    res->sniffed_bytes = 0;
    res->sniffed_pkts = 0;
    res->network_current_buf = 0;
    res->buf_length[1] = res->buf_length[0] = 0;
    res->thread_status[1] = res->thread_status[0] = 0;
}


/*****************************************
* Function: Get device id.
*****************************************/
#if defined(WITH_MFT) || defined(WITH_MSTFLINT)
int get_hw_devid(mfile* mf, u_int32_t* devid)
{
    if (mread4(mf, 0xf0014, devid) != 4) {
        return -1;
    }
    *devid = (*devid & 0xffff);
    return 0;
}
#endif


/*****************************************
* Function: resources_create
*****************************************/
static int resources_create(struct resources *res)
{
    struct ibv_qp_init_attr qp_init_attr;
    struct ibv_device      *ib_dev = NULL;
    int                     i;
    u_int32_t               n;
    int                     mr_flags = 0;
    int                     cq_size = 0;
    int                     num_devices;
    int                     mtu;
    char                  * tmp;

    memset(res, 0, sizeof(*res));
    my_printf("searching for IB devices in host\n");

    /* get device names in the system */

    if (config.to_stdout) {
        res->fh = stdout;
    } else {
        res->fh = fopen(config.out_file_name, "wb");
        if (res->fh == NULL) {
            fprintf(stderr, "-E- Failed to open file %s: %s\n", config.out_file_name, strerror(errno));
            return 1;
        }
    }

    res->dev_list = ibv_get_device_list(&num_devices);
    if (!res->dev_list) {
        fprintf(stderr, "-E- failed to get IB devices list\n");
        return 1;
    }

    /* if there isn't any IB device in host */
    if (!num_devices) {
        fprintf(stderr, "-E- found %d device(s)\n", num_devices);
        return 1;
    }

    /* search for the specific device we want to work with (default is the first one we found) */
    if (NULL == config.dev_name) {
        ib_dev = res->dev_list[0];
        const char *dev_name = ibv_get_device_name(res->dev_list[0]);
        if (NULL == dev_name) {
            fprintf(stderr, "-E- Can't find RDMA devices\n");
            return 1;
        }
        config.dev_name = strdup(dev_name);
    } else {
        for (i = 0; i < num_devices; i++) {
            if (!strcmp(ibv_get_device_name(res->dev_list[i]), config.dev_name)) {
                ib_dev = res->dev_list[i];
                break;
            }
        }
    }

#if defined(WITH_MFT) || defined(WITH_MSTFLINT)
    if (config.mst_dev_name == NULL) {
        #ifdef __WIN__
        usage(argv[0]);
        return 1;
        #else
        config.mst_dev_name = config.dev_name;
        #endif
    }
#endif

    /* if the device wasn't found in host */
    if (!ib_dev) {
        fprintf(stderr, "-E- IB device %s wasn't found\n", config.dev_name);
        return 1;
    }

    /* get device handle */
    res->ib_ctx = ibv_open_device(ib_dev);
    if (!res->ib_ctx) {
        fprintf(stderr, "-E- failed to open device %s\n", config.dev_name);
        return 1;
    }

    if (ibv_query_device(res->ib_ctx, &res->device_attr)) {
        fprintf(stderr, "-E- Failed to query device");
        return 1;
    }

    /* query port properties  */
    if (ibv_query_port(res->ib_ctx, (uint8_t)config.ib_port, &res->port_attr)) {
        fprintf(stderr, "-E- ibv_query_port on port %u failed\n", config.ib_port);
        return 1;
    }

#if defined(WITH_MFT) || defined(WITH_MSTFLINT)
    /* using user level mtcr - ib dev name can be used to open the mst device*/
    res->mf = mopen(config.mst_dev_name);
    if (!res->mf) {
        fprintf(stderr, "-E- Failed to open mst device %s: %s\n",
                config.mst_dev_name,
                strerror(errno));
        return 1;
    }

    if (get_hw_devid(res->mf, &res->dev_rev_id) != 0) {
        fprintf(stderr, "-E- Failed to get device ID\n");
        return -1;
    }

    if ((res->dev_rev_id != DI_CX) &&
        (res->dev_rev_id != DI_CX2) &&
        (res->dev_rev_id != DI_CX3) &&
        (res->dev_rev_id != DI_CX3A1) &&
        (res->dev_rev_id != DI_CX3Pro) &&
        (res->dev_rev_id != DI_CIB) &&
        (res->dev_rev_id != DI_CX4) &&
        (res->dev_rev_id != DI_CX4LX) &&
        (res->dev_rev_id != DI_CX5) &&
        (res->dev_rev_id != DI_CX6) &&
        (res->dev_rev_id != DI_CX6DX) &&
        (res->dev_rev_id != DI_BF2) &&
        (res->dev_rev_id != DI_BF2A1) &&
        (res->dev_rev_id != DI_BF3) &&
        (res->dev_rev_id != DI_BF4) &&
        (res->dev_rev_id != DI_CX7) &&
        (res->dev_rev_id != DI_CX8) &&
        (res->dev_rev_id != DI_CX9)) {
        fprintf(stderr, "-E- Unsupported HW device id (%x)\n", res->dev_rev_id);
        return -1;
    }

    if (res->dev_rev_id == DI_CX2) {
        #ifndef WIN_NOT_SUPPORTED
        if (res->port_attr.link_layer == IBV_LINK_LAYER_ETHERNET) {
            fprintf(stderr, "-E- Ethernet sniffing is not supported in CX2\n");
            return -1;
        }
        #endif
        config.use_a0_mode = 1;
    }
#endif

    /* allocate Protection Domain */
    res->pd = ibv_alloc_pd(res->ib_ctx);
    if (!res->pd) {
        fprintf(stderr, "-E- ibv_alloc_pd failed\n");
        return 1;
    }

    /* each side will send only one WR, so Completion Queue with 1 entry is enough */
    cq_size = config.entries_num;
    res->cq = ibv_create_cq(res->ib_ctx, cq_size, NULL, NULL, 0);
    if (!res->cq) {
        fprintf(stderr, "-E- failed to create CQ with %u entries\n", cq_size);
        return 1;
    }

    /* allocate the memory buffer that will hold the data */
    /* To save resources, only 1 buffer is allocated (in buf[0])
     *  buf[1..entries_num-1] points to this mem block
     *  To save fime / mem acceses, a space for the pcap+erf headers
     *  is saved before the pkt data
     */

    mtu = mtu_enum_to_num(res->port_attr.active_mtu);

    if (config.jumbo_mtu) {
        res->entry_size = 1024 * 16;
    } else {
        if (mtu <= 2 * 1024) {
            /* Seem that sniffer QP SGEs should be page aligned. */
            /* TODO: Check why. */
            res->entry_size = 1024 * 4;
        } else if (mtu <= 4 * 1024) {
            res->entry_size = 1024 * 8;
        } else {
            fprintf(stderr, "-E- MTU > 4KB is not supported (port is configured to %d bytes MTU)\n",
                    mtu);
            return 1;
        }
    }

    res->buf = malloc(config.entries_num * sizeof(char*));
    if (!res->buf) {
        fprintf(stderr, "-E- failed to allocate %Zu bytes to memory buffer\n",
                config.entries_num * sizeof(char*));
        return 1;
    }

    if (!config.contiguous_pages) {
        tmp = malloc(res->entry_size * config.entries_num + 0x1000); /* Add 4KB to ensure MR is page aligned */
        if (!tmp) {
            fprintf(stderr,
                    "-E- failed to allocate %d bytes to memory buffer data\n",
                    res->entry_size * config.entries_num);
            return 1;
        }

        res->buf_alloc_ptr = tmp;
        if ((u_int64_t)tmp & 0xfff) {
            tmp = (char*)(((u_int64_t)tmp + 0x1000) & ~0xfff);
        }
        res->buf[0] = tmp;

        /* register this memory buffer */
        mr_flags = IBV_ACCESS_LOCAL_WRITE;
        res->mr = ibv_reg_mr(res->pd, res->buf[0], res->entry_size * config.entries_num, mr_flags);
        if (!res->mr) {
            fprintf(stderr, "-E- ibv_reg_mr failed with mr_flags=0x%x\n", mr_flags);
            return 1;
        }
    } else {
#ifndef WIN_NOT_SUPPORTED

#ifdef LIBS_EXP

        struct ibv_exp_reg_mr_in in;
        in.pd = res->pd;
        in.addr = NULL;
        in.length = res->entry_size * config.entries_num;
        in.exp_access = IBV_EXP_ACCESS_LOCAL_WRITE | IBV_EXP_ACCESS_ALLOCATE_MR;
        in.comp_mask = 0;
        res->mr = ibv_exp_reg_mr(&in);
        if (!res->mr) {
            fprintf(stderr, "-E- ibv_exp_reg_mr failed\n");
            return 1;
        }
        res->buf[0] = res->mr->addr;

#else

        res->mr = ibv_reg_mr(res->pd, NULL,
                             res->entry_size * config.entries_num,
                             IBV_ACCESS_LOCAL_WRITE);

#endif

        if (res->buf) {
            free(res->buf);
        }
        fprintf(stderr, "-E- contiguous_pages is not supported in Windows\n");
        return 1;
#endif
    }

    memset(res->buf[0], 0, res->entry_size * config.entries_num); /* TODO: redundant. */
    for (n = 1; n < config.entries_num; n++) {
        res->buf[n] = res->buf[0] + res->entry_size * n;
    }

    if (config.mem_size) {
        /* Allocate additional MTU entry to assure mem_size bytes are captured. */
        res->mem_buf = malloc((size_t)config.mem_size + res->entry_size);
        res->thread_buf[0] = res->mem_buf;
        if (config.writer_thread) {
            res->mem_buf2 = malloc((size_t)config.mem_size + res->entry_size);
            res->thread_buf[1] = res->mem_buf2;
        }
        if ((res->mem_buf == NULL) || (config.writer_thread && (res->mem_buf2 == NULL))) {
            fprintf(stderr, "-E- failed to allocate %" PRIu64 " bytes to memory buffer\n",
                    config.mem_size + res->entry_size);
            return 1;
        }
    }

    my_printf("Port active_mtu=%d\n", mtu_enum_to_num(res->port_attr.active_mtu));
    my_printf("MR was registered with addr=%p, lkey=0x%x, rkey=0x%x, flags=0x%x\n",
              res->buf, res->mr->lkey, res->mr->rkey, mr_flags);

    /* create the Queue Pair */
    memset(&qp_init_attr, 0, sizeof(qp_init_attr));
    qp_init_attr.qp_type = IBV_QPT_UD;

#ifndef WIN_NOT_SUPPORTED
    if (res->port_attr.link_layer == IBV_LINK_LAYER_ETHERNET) {
#ifdef LIBS_EXP
        qp_init_attr.qp_type = IBV_QPT_RAW_ETH;
#else
        qp_init_attr.qp_type = IBV_QPT_RAW_PACKET;
#endif
    } else {
        qp_init_attr.qp_type = IBV_QPT_UD;
    }
#endif

    qp_init_attr.sq_sig_all = 1;
    qp_init_attr.send_cq = res->cq;
    qp_init_attr.recv_cq = res->cq;
    qp_init_attr.cap.max_send_wr = 1;
    qp_init_attr.cap.max_recv_wr = config.entries_num;
    qp_init_attr.cap.max_send_sge = 1;
    qp_init_attr.cap.max_recv_sge = 1;

    res->qp = ibv_create_qp(res->pd, &qp_init_attr);
    if (!res->qp) {
        fprintf(stderr, "-E- failed to create QP\n");
        return 1;
    }

    return 0;
}

/*****************************************
* Function: modify_qp_to_init
*****************************************/
static int modify_qp_to_init(struct ibv_qp *qp, u_int8_t is_eth)
{
    struct ibv_qp_attr attr;
    int                flags;
    int                rc;


    /* do the following QP transition: RESET -> INIT */
    memset(&attr, 0, sizeof(attr));

    attr.qp_state = IBV_QPS_INIT;
    attr.port_num = (u_int8_t)config.ib_port;
    attr.pkey_index = 0;
    attr.qkey = DEF_QKEY;

    /*orenk-eth */
    if (is_eth) {
        flags = IBV_QP_STATE | IBV_QP_PORT;
    } else {
        flags = IBV_QP_STATE | IBV_QP_PKEY_INDEX | IBV_QP_PORT | IBV_QP_QKEY;
    }

    #ifdef __WIN__
    attr.qp_access_flags = IBV_ACCESS_SNIFFER;
    #endif

    rc = ibv_modify_qp(qp, &attr, flags);
    if (rc) {
        fprintf(stderr, "-E- failed to modify QP state to INIT\n");
        return rc;
    }

    return 0;
}

/*****************************************
* Function: modify_qp_to_rtr
*****************************************/
static int modify_qp_to_rtr(struct ibv_qp *qp)
{
    struct ibv_qp_attr attr;
    int                flags;
    int                rc;

    /* do the following QP transition: INIT -> RTR */
    memset(&attr, 0, sizeof(attr));

    attr.qp_state = IBV_QPS_RTR;

    flags = IBV_QP_STATE;

    rc = ibv_modify_qp(qp, &attr, flags);
    if (rc) {
        fprintf(stderr, "-E- failed to modify QP state to RTR\n");
        return rc;
    }

    return 0;
}

/*****************************************
* Function: connect_qp
*****************************************/
static int connect_qp(struct resources *res)
{
    int       rc;
    u_int32_t n;

    /* modify the QP to init */
    rc = modify_qp_to_init(res->qp, config.is_eth);
    if (rc) {
        fprintf(stderr, "-E- change QP state to INIT failed\n");
        return rc;
    }

    /* let the client post RR to be prepared for incoming messages */
    for (n = 0; n < config.entries_num; n++) {
        rc = post_receive(res, n);
        if (rc) {
            fprintf(stderr, "-E- failed to post RR\n");
            return rc;
        }
    }

    /* modify the QP to RTR */
    rc = modify_qp_to_rtr(res->qp);
    if (rc) {
        fprintf(stderr, "-E- failed to modify QP state from RESET to RTS\n");
        return rc;
    }

    return 0;
}

/*****************************************
* Function: resources_destroy
*****************************************/
static int resources_destroy(struct resources *res)
{
    int test_result = 0;

    if (config.mem_size) {
        if (config.writer_thread) {
            if (res->dumped_bytes) {
                res->buf_length[res->network_current_buf] = res->dumped_bytes;
                res->dumped_bytes = 0;
                res->thread_status[res->network_current_buf] = 1;
                while (res->thread_status[res->network_current_buf] == 1) {
                    ;
                }
            }
        } else if ((res->dumped_bytes > 0) && res->fh) {
            int rc;
            rc = fwrite(res->mem_buf, (size_t)res->dumped_bytes, 1, res->fh);
            if (rc != 1) {
                fprintf(stderr, "-E- Failed writing to file: %s\n", strerror(errno));
                return 1;
            }
            my_printf("-I- Wrote file %s\n", config.out_file_name);
        }
    }

    if (config.dev_name) {
        free(config.dev_name);
    }

    if (res->fh && !config.to_stdout) {
        fclose(res->fh);
    }

    if (res->qp) {
        if (ibv_destroy_qp(res->qp)) {
            fprintf(stderr, "-E- failed to destroy QP\n");
            test_result = 1;
        }
    }

    if (res->mr) {
        if (ibv_dereg_mr(res->mr)) {
            fprintf(stderr, "-E- failed to deregister MR\n");
            test_result = 1;
        }
    }

    if (res->mem_buf) {
        free(res->mem_buf);
    }

    if (res->mem_buf2) {
        free(res->mem_buf2);
    }

    if (res->buf && res->buf_alloc_ptr) {
        free(res->buf_alloc_ptr);
    }

    if (res->buf) {
        free(res->buf);
    }

    if (res->cq) {
        if (ibv_destroy_cq(res->cq)) {
            fprintf(stderr, "-E- failed to destroy CQ\n");
            test_result = 1;
        }
    }

    if (res->ah) {
        if (ibv_destroy_ah(res->ah)) {
            fprintf(stderr, "-E- failed to destroy AH\n");
            test_result = 1;
        }
    }

    if (res->pd) {
        if (ibv_dealloc_pd(res->pd)) {
            fprintf(stderr, "-E- failed to deallocate PD\n");
            test_result = 1;
        }
    }

    if (res->ib_ctx) {
        if (ibv_close_device(res->ib_ctx)) {
            fprintf(stderr, "-E- failed to close device context\n");
            test_result = 1;
        }
    }

    if (res->dev_list) {
        ibv_free_device_list(res->dev_list);
    }

    return test_result;
}

/* fw_ver_a/b are 3 dotted strings in format "magor.minor.sub_minor" */
/* Returns 1 if fw_ver_a is less than fw_ver_b */
/*         0 if fw_ver_a is greater or equal than fw_ver_b */
/*        -1 if either string has bad format */
int fw_version_less_than(char* fw_ver_a, char* fw_ver_b)
{
    int       i;
    u_int32_t ver_a[3];
    u_int32_t ver_b[3];

    if (sscanf(fw_ver_a, "%u.%u.%u", &ver_a[0], &ver_a[1], &ver_a[2]) != 3) {
        return -1;
    }

    if (sscanf(fw_ver_b, "%u.%u.%u", &ver_b[0], &ver_b[1], &ver_b[2]) != 3) {
        return -1;
    }

    for (i = 0; i < 3; i++) {
        if (ver_a[i] < ver_b[i]) {
            return 1;
        } else if (ver_a[i] > ver_b[i]) {
            return 0;
        }
    }

    return 0; /* equal versions */
}


int fourth_gen_set_sw_sniffer(struct resources *res, int mode, int is_tx, int is_rx)
{
#ifndef WIN_NOT_SUPPORTED

    (void)is_tx;
    (void)is_rx;

#ifdef LIBS_EXP

    if (mode != 0) {
        struct ibv_exp_flow_attr flow_attr;
        memset(&flow_attr, 0, sizeof(flow_attr));

        flow_attr.type = IBV_EXP_FLOW_ATTR_SNIFFER;
        flow_attr.size = sizeof(flow_attr);
        flow_attr.port = config.ib_port;

        res->flow = ibv_exp_create_flow(res->qp, &flow_attr);
        if (res->flow == NULL) {
            fprintf(stderr, "-E- Failed to set sniffer mode. ibv_create_flow failed: %s\n"
                    "    This problem might be because Flow Steering is not enabled, to enable it:\n"
                    "    1. Add the following to /etc/modprobe.d/mlnx.conf file:\n"
                    "       options mlx4_core log_num_mgm_entry_size=-1\n"
                    "    2. Restart the drivers.\n"
                    , strerror(errno));
            return -1;
        }
    } else {
        ibv_exp_destroy_flow(res->flow);
    }

#else

    if (mode != 0) {
        struct ibv_flow_attr flow_attr;
        memset(&flow_attr, 0, sizeof(flow_attr));

        flow_attr.type = IBV_FLOW_ATTR_SNIFFER;
        flow_attr.size = sizeof(flow_attr);
        flow_attr.port = config.ib_port;

        res->flow = ibv_create_flow(res->qp, &flow_attr);
        if (res->flow == NULL) {
            fprintf(stderr, "-E- Failed to set sniffer mode. ibv_create_flow failed: %s\n"
                    "    This problem might be because Flow Steering is not enabled, to enable it:\n"
                    "    1. Add the following to /etc/modprobe.d/mlnx.conf file:\n"
                    "       options mlx4_core log_num_mgm_entry_size=-1\n"
                    "    2. Restart the drivers.\n"
                    , strerror(errno));
            return -1;
        }
    } else {
        ibv_destroy_flow(res->flow);
    }

#endif

#else  /* ifndef WIN_NOT_SUPPORTED */
    int rc;
    if (mode != 0) {
        rc = ibd_ibal_open_sniffer(res->device_attr.node_guid,
                                   config.ib_port,
                                   res->qp->qp_num,
                                   is_tx,
                                   is_rx,
                                   &res->ibal_ctx);
        if (rc) {
            return rc;
        }
    } else {
        ibd_ibal_close_sniffer(res->ibal_ctx);
    }

#endif /* ifndef WIN_NOT_SUPPORTED */
    return 0;
}

#if defined(__WIN__) || defined(WITHOUT_FW_TOOLS)
int fifth_gen_set_sw_sniffer(struct resources *res, int mode)
{
    (void)mode;  /*avoid not used warnings. */
    fprintf(stderr, "-E- Unsupported HW device id (%x)\n", res->dev_rev_id);
    return 1;
}
#else
#if defined(WITH_MSTFLINT)
#define SNIFFER_STRUCT connectib_icmd_set_port_sniffer
#include <tools_layouts/icmd_layouts.h>
#include <cmdif/icmd_cif_common.h>
#include <cmdif/icmd_cif_open.h>
#include <common/compatibility.h>
#else
#include <cmdif/cib_cif.h>

#if defined(IBDUMP_LAYOUTS)
#include <cmdif/icmd_ibdump.h>
#include <tools_layouts/ibdump_layouts.h>
#define SNIFFER_STRUCT ibdump_icmd_set_port_sniffer
#else
#define SNIFFER_STRUCT connectib_icmd_set_port_sniffer
#endif

#endif
int fifth_gen_set_sw_sniffer(struct resources *res, int mode)
{
    struct SNIFFER_STRUCT set_port_sniffer;
    int                   rc;

    
    if (res->dev_rev_id == DI_CX8 || res->dev_rev_id == DI_CX9)
    {
        mwrite4(res->mf, 0x1a023f0, 0xbadc0ffe);
    }
    else
    {
        mwrite4(res->mf, 0x23f0, 0xbadc0ffe);
    }

    memset(&set_port_sniffer, 0, sizeof(struct SNIFFER_STRUCT));
    set_port_sniffer.port = config.ib_port;
    set_port_sniffer.sniffer_qpn = res->qp->qp_num;
    set_port_sniffer.sx_rx_ = 0;
    set_port_sniffer.attach_detach_ = mode;

    rc = gcif_set_port_sniffer(res->mf, &set_port_sniffer);
    if (rc != GCIF_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to set port sniffer1: %s\n", gcif_err_str(rc));
        return 1;
    }

    set_port_sniffer.sx_rx_ = 1;
    rc = gcif_set_port_sniffer(res->mf, &set_port_sniffer);
    if (rc != GCIF_STATUS_SUCCESS) {
        fprintf(stderr, "Failed to set port sniffer2: %s\n", gcif_err_str(rc));
        return 1;
    }
    return 0;
}
#endif /* if defined(__WIN__) || defined(WITHOUT_FW_TOOLS) */
int set_sw_sniffer(struct resources *res, int mode, int is_tx, int is_rx)
{
    if ((res->dev_rev_id == DI_CIB) || (res->dev_rev_id == DI_CX4) ||
        (res->dev_rev_id == DI_CX4LX) || (res->dev_rev_id == DI_CX5) ||
        (res->dev_rev_id == DI_CX6) || (res->dev_rev_id == DI_CX6DX) ||
        (res->dev_rev_id == DI_CX7) || (res->dev_rev_id != DI_CX8) ||
        (res->dev_rev_id != DI_CX9) || (res->dev_rev_id != DI_BF2) ||
        (res->dev_rev_id != DI_BF2A1) || (res->dev_rev_id != DI_BF3) ||
        (res->dev_rev_id != DI_BF4))
    {
        return fifth_gen_set_sw_sniffer(res, mode);
    }
    return fourth_gen_set_sw_sniffer(res, mode, is_tx, is_rx);
}


#define MAX_ARG_SIZE 1024
/* size in INOUT - IN - size of arr. OUT - actual count. */
int csv_to_num_array(char* csv_line, u_int32_t arr[], int* size)
{
    char  buff[MAX_ARG_SIZE];
    char *p;
    int   i;

    strncpy(buff, csv_line, MAX_ARG_SIZE);
    p = strtok(buff, ",");

    for (i = 0, p = strtok(buff, ","); p; p = strtok(NULL, ","), ++i) {
        char* ep;

        if (i >= *size) {
            fprintf(stderr, "-E- Too many csv elements\n");
            return 1;
        }

        arr[i] = strtoul(p, &ep, 0);
        if (*ep != '\0') {
            fprintf(stderr, "-E- \"%s\" is not a numerical value\n", p);
            return 2;
        }
    }

    *size = i;
    return 0;
}

int set_pcap_header(FILE* fh)
{
    int        rc;
    pcap_hdr_t hdr;

    memset(&hdr, 0, sizeof(hdr));

    hdr.magic_number = 0xa1b2c3d4;  /* pcap magic */
    hdr.version_major = 2;
    hdr.version_minor = 4;
    hdr.snaplen = 0xffff;

    /* pcap header erf settings  */
    if (config.with_erf == -1) {
        if (config.is_eth) {
            config.with_erf = 0;
        } else {
            config.with_erf = 1;
        }
    }

    /* NOTE: Assuming no ERF is eth. Currently no DLT_INFINIBAND */
    hdr.network = config.with_erf ? DLT_ERF : DLT_EN10MB;

    rc = fwrite(&hdr, sizeof(hdr), 1, fh);
    if (rc != 1) {
        fprintf(stderr, "-E- Failed writing to output file.\n");
        return 1;
    }
    return 0;
}

/*****************************************
* Function: print_config
*****************************************/
static void print_config(void)
{
    fprintf(stdout, " ------------------------------------------------\n");
/* TODO: Add RX/TX/BOTH mode */
    fprintf(stdout, " Device                         : \"%s\"\n", config.dev_name);
    fprintf(stdout, " Physical port                  : %u\n", config.ib_port);
    fprintf(stdout, " Link layer                     : %s\n", config.is_eth ? "Ethernet" : "Infiniband");
    fprintf(stdout, " Dump file                      : %s\n", config.out_file_name);
    fprintf(stdout, " Sniffer WQEs (max burst size)  : %u\n", config.entries_num);

    if (config.src_qp_str) {
        fprintf(stdout, " Monitored QPs:                 : %s\n", config.src_qp_str);
    }

    fprintf(stdout, " ------------------------------------------------\n\n");
}

/*****************************************
* Function: termination_handler
*****************************************/
static void __WIN_CDECL termination_handler(int signum)
{
    my_printf("\n\nInterrupted (signal %d) - exiting ...\n", signum);
    g_stop_sniffer = 1;
}


/*****************************************
* Function: usage
*****************************************/
static void usage(const char *argv0)
{
    fprintf(stdout, "   ibdump - Dump Infiniband traffic from Mellanox Technologies ConnectX HCA\n"
            "            The dump file can be loaded by Wireshark for graphical traffic analysis\n\n");
    fprintf(stdout, "Usage:\n");
    fprintf(stdout, "  %s [options]\n", argv0);
    fprintf(stdout, "\n");
    fprintf(stdout, "Options:\n");
    fprintf(stdout, "  -d, --ib-dev=<dev>     use IB device <dev> (default first device found)\n");
    #if defined(__WIN__) && defined(IBDUMP_A0_MODE)
    fprintf(stdout, "  -m, --mst-dev=<dev>    use MST device <dev> (mandatory parameter)\n");
    fprintf(stdout, "                         <dev> must refer to the MST device corresponding to the selected\n");
    fprintf(stdout, "                         IB device, otherwise application behavior is undefined\n");
    #endif
    fprintf(stdout, "  -i, --ib-port=<port>   use port <port> of IB device (default 1)\n");
    fprintf(stdout,
            "  -w, --write=<file>     dump file name (default \"%s\")\n"
            "                         '-' stands for stdout - enables piping to tcpdump or tshark.\n",
            config.out_file_name);
    fprintf(stdout, "  -o, --output=<file>    alias for the '-w' option. Do not use - for backward compatibility\n");
    fprintf(stdout, "  -b, --max-burst=<log2 burst> log2 of the maximal burst size that can be\n"
            "                               captured with no packets loss.\n"
            "                               Each entry takes ~ MTU bytes of memory (default %d - %d entries)\n",
            config.log2entries_num,
            1 << config.log2entries_num);
    fprintf(stdout, "  -s, --silent           do not print progress indication.\n");
    fprintf(stdout, "  -T, --conti            Use contiguous pages.\n");
    fprintf(stdout, "  -M, --mem-mode <size>  when specified, packets are written to file only after the capture\n"
            "                         is stopped. It is faster than default mode (less chance for\n"
            "                         packet loss), but takes more memory. In this mode, ibdump\n"
            "                         stops after <size> bytes are captured\n");
    fprintf(stdout, "  -p, --writer-thread <size>   Use a specific thread for writing data to disk.\n"
            "                               In order to use this functionality you have to specify the\n"
            "                               size of two temporary buffers used to save data while the\n"
            "                               thread writes to disk\n");
    fprintf(stdout, "\n");
    fprintf(stdout, "  --decap                Decapsulate port mirroring headers. Should be used\n"
            "                         when capturing RSPAN traffic.\n");
    fprintf(stdout, "  -h, --help             Display this help screen.\n");
    fprintf(stdout, "  -v, --version          Print version information.\n");
}

/*****************************************
******************************************
* Function: main
******************************************
*****************************************/

int __WIN_CDECL main(int argc, char *argv[])
{
    int              src_qps_size = MAX_SRC_QPS;
    int              test_result = 1;
    int              hw_sniffer_on = 0;
    int              sw_sniffer_on = 0;
    int              sniff_tx = 1;
    int              sniff_rx = 1;
    int              iret;
    int              idx;
    int              rc;
    u_int32_t        src_qps[MAX_SRC_QPS];
    u_int32_t        entries_mask;
    struct resources res;
    char           * ef;

#ifndef WIN_NOT_SUPPORTED
    pthread_t writer_thread;
#endif
    enum ibdump_long_opts {
        OPT_WITH_ERF = 1000,
        OPT_A0_MODE  = 1001
    };

    (void)hw_sniffer_on;  /*avoid not used variable warning. */

    /* parse the command line parameters */
    while (1) {
        int c;

        static struct option long_options[] = {
            { "ib-dev",        1, NULL, 'd' },
            { "mst-dev",       1, NULL, 'm' },
            { "ib-port",       1, NULL, 'i' },
            { "output",        1, NULL, 'o' },
            { "write",         1, NULL, 'w' },
            { "max-burst",     1, NULL, 'b' },
            { "mem-mode",      1, NULL, 'M' },
            { "writer-thread", 1, NULL, 'p' },
            { "direction",     1, NULL, 'I' },
            { "decap",         0, NULL, 'E' },
            { "src_qp",        1, NULL, 'q' },
            { "silent",        0, NULL, 's' },
            { "conti",         0, NULL, 'T' },
            { "jumbo-mtu",     0, NULL, 'j' },
            { "help",          0, NULL, 'h' },
            { "version",       0, NULL, 'v' },
            { "erf",           1, NULL, OPT_WITH_ERF },
            { "a0-mode",       0, NULL, OPT_A0_MODE },
            { NULL,            0, NULL, '\0'}
        };

        c = getopt_long(argc, argv, "p:w:d:i:o:b:hM:vC:EI:Lq:sm:jT", long_options, NULL);
        if (c == -1) {
            break;
        }

        switch (c) {
        case 'd':
            config.dev_name = strdup(optarg); /* TODO: Why strdup ? */
            break;

        case 'm':
            config.mst_dev_name = optarg;
            break;

        case 'o':
        case 'w':
            config.out_file_name = optarg;
            break;

        case 'i':
            config.ib_port = strtoul(optarg, NULL, 0);
            if (config.ib_port < 0) {
                usage(argv[0]);
                return 1;
            }
            break;

        case 'b':
            config.log2entries_num = strtoul(optarg, &ef, 0);
            if (*ef != '\0') {
                usage(argv[0]);
                return 1;
            }
            break;

        case 'M':
            config.mem_mode = 1;
            config.mem_size = strtoull(optarg, &ef, 0);
            if (*ef != '\0') {
                usage(argv[0]);
                return 1;
            }
            break;

        case 'I':
            if (!strcmp("tx", optarg)) {
                sniff_rx = 0;
            } else if (!strcmp("rx", optarg)) {
                sniff_tx = 0;
            } else {
                fprintf(stderr, "-E- Bad parameter for direction flag\n");
                usage(argv[0]);
                return 1;
            }
            break;

        case 'j':
            config.jumbo_mtu = 1;
            break;

        case 'T':
            config.contiguous_pages = 1;
        /* fall through */

        case 'q':
            config.src_qp_str = optarg;
            break;

#ifndef WIN_NOT_SUPPORTED
        case 'p':
            config.writer_thread = 1;
            config.mem_size = strtoull(optarg, &ef, 0);
            if (*ef != '\0') {
                usage(argv[0]);
                return 1;
            }
            break;
#endif /* !WIN_NOT_SUPPORTED */


        case 'E':
            config.decap_mode = 1;
            break;

        case 's':
            config.is_silent = 1;
            break;

        case OPT_WITH_ERF:
            config.with_erf = strtol(optarg, &ef, 0);
            if ((*ef != '\0') || ((config.with_erf != 1) && (config.with_erf != 0))) {
                fprintf(stderr, "-E- Bad parameter for --erf flag. Expected 0 or 1\n");
                usage(argv[0]);
                return 1;
            }
            break;

        case OPT_A0_MODE:
            config.use_a0_mode = 1;
            break;

        case 'h':
            usage(argv[0]);
            return 0;
            break;

        case 'v':
            print_version_string("ibdump", "");
            return 0;

        default:
            usage(argv[0]);
            return 1;
        }
    }

    if (optind < argc) {
        usage(argv[0]);
        return 1;
    }

    if (config.writer_thread && config.mem_mode) {
        fprintf(stderr, "-E- You can not use mem-mode and writer-thread simultaneously.\n");
        return 1;
    }

    config.entries_num = 1 << config.log2entries_num;

    if (config.src_qp_str) {
        if (csv_to_num_array(config.src_qp_str, src_qps, &src_qps_size)) {
            fprintf(stderr, "-E- Failed to parse source QPs list\n");
            return -1;
        }
    } else {
        src_qps_size = 0;
    }

    if (!strcmp(config.out_file_name, "-")) {
        config.to_stdout = 1;
        config.is_silent = 1;
    }

    signal(SIGINT,  termination_handler);
    #ifndef __WIN__ /* no SIGPIPE on Windows */
    signal(SIGPIPE, termination_handler);
    signal(SIGTERM, termination_handler);
    signal(SIGHUP, termination_handler);
    #endif

    my_printf("Initiating resources ...\n");

    /* init all of the resources, so cleanup will be easy */
    resources_init(&res);

    /* create resources before using them */
    if (resources_create(&res)) {
        fprintf(stderr, "-E- failed to create resources\n");
        goto cleanup;
    }

#ifndef WIN_NOT_SUPPORTED

    if (config.writer_thread) {
        iret = pthread_create(&writer_thread, NULL, write_to_file, &res);
        if (iret) {
            fprintf(stderr, "-E- pthread_create() return code: %d\n", iret);
            goto cleanup;
        }
    }


    if (res.port_attr.link_layer == IBV_LINK_LAYER_ETHERNET) {
        config.is_eth = 1;
    }
#else
    if (res.port_attr.transport != 0) {
        config.is_eth = 1;
    }
#endif /* !WIN_NOT_SUPPORTED */


    /* print the used parameters for info*/
    if (!config.is_silent) {
        print_config();
    }

    /* connect the QPs */
    if (connect_qp(&res)) {
        fprintf(stderr, "-E- failed to connect QPs\n");
        goto cleanup;
    }

    if (config.use_a0_mode) {
#ifdef IBDUMP_A0_MODE
        if (ibd_set_hw_sniffer_mode(res.mf,
                                    res.dev_rev_id,
                                    config.ib_port,
                                    res.qp->qp_num,
                                    1,
                                    sniff_tx,
                                    sniff_rx,
                                    src_qps,
                                    src_qps_size)) {
            fprintf(stderr, "-E- Failed to set sniffer mode\n");
            goto cleanup;
        }
        hw_sniffer_on = 1;
#else
        fprintf(stderr, "-E- This tool does not support A0 mode\n");
        goto cleanup;

#endif
    } else {
        #define MIN_FW_REQUIRED_ETH   "2.11.1140" /* This is the initial version with sniffer rules support. RX only. */
        #define MIN_FW_REQUIRED_IB_RC "2.33.1330"    /* This version contains a fix for sniffing in ib mode. */
        #define MIN_FW_REQUIRED_IB    "2.33.5000" /* This is the rc version that contains the fix in ib mode. */
        char* min_fw;
        char* min_fw_rc;
        if (config.is_eth) {
            min_fw = MIN_FW_REQUIRED_ETH;
            min_fw_rc = MIN_FW_REQUIRED_ETH;
        } else {
            min_fw = MIN_FW_REQUIRED_IB;
            min_fw_rc = MIN_FW_REQUIRED_IB_RC;
        }
        int fwvlt = fw_version_less_than(res.device_attr.fw_ver, min_fw_rc);
        if (fwvlt > 0) {
            fprintf(stderr, "-E- Device firmware version (%s) does not support sniffing. Required %s or higher\n",
                    res.device_attr.fw_ver,
                    min_fw);
            goto cleanup;
        } else if (fwvlt < 0) {
            fprintf(stderr, "-W- Bad device firmware version format (%s) - skipping check\n",
                    res.device_attr.fw_ver);
            /* orenk: fix goto cleanup; */
        }
        if (set_sw_sniffer(&res, 1, sniff_tx, sniff_rx)) {
            goto cleanup;
        }
        sw_sniffer_on = 1;
    }

    if (!config.is_eth && !config.with_erf) {
        /* IB must have an ERF header. */
        fprintf(stderr, "-E- Can not dump Infiniband traffic without an ERF header (--erf 0)\n");
        return -1;
    }

    rc = set_pcap_header(res.fh);
    if (rc) {
        return rc;
    }

    my_printf("\nReady to capture (Press ^c to stop):\n");

    /* Main loop: */
    entries_mask = (config.entries_num - 1);
    idx = 0;
    while (!g_stop_sniffer &&
           (config.mem_size == 0 ||
            config.writer_thread ||
            res.dumped_bytes < config.mem_size)) {
        int rc;
        int added_packets;
        if (poll_completion(&res, res.fh, idx, &added_packets)) {
            fprintf(stderr, "-E- poll completion failed\n");
            goto cleanup;
        }
        if (!g_stop_sniffer && (added_packets > 0)) {
            rc = post_receive(&res, idx);
            if (rc) {
                fprintf(stderr, "-E- failed to post RR\n");
                return rc;
            }
        }
        idx = (idx + added_packets) & entries_mask;
    }

    my_printf("\n");
    if (config.mem_size && (res.dumped_bytes >= config.mem_size)) {
        my_printf("Buffer full ...\n");
    }

    fprintf(stderr, "\nCaptured:  %8" PRIu64 " packets, %8" PRIu64 " bytes\n", res.sniffed_pkts, res.sniffed_bytes);

    test_result = 0;

cleanup:
#ifdef IBDUMP_A0_MODE
    if (hw_sniffer_on) {
        if (ibd_set_hw_sniffer_mode(res.mf,
                                    res.dev_rev_id,
                                    config.ib_port,
                                    res.qp->qp_num,
                                    0,
                                    sniff_tx,
                                    sniff_rx,
                                    src_qps,
                                    src_qps_size)) {
            fprintf(stderr, "-E- Failed to clear sniffer mode\n");
        }
    }
#endif
    if (sw_sniffer_on) {
        if (set_sw_sniffer(&res, 0, sniff_tx, sniff_rx)) {
            fprintf(stderr, "-E- Failed to clear ethernet sniffer mode\n");
        }
    }

    if (resources_destroy(&res)) {
        fprintf(stderr, "-E- failed to destroy resources\n");
        test_result = 1;
    }

    return test_result;
}
