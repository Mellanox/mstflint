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
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bit_slice.h>
#include <common/tools_utils.h>

#include "mtcr_tools_cif.h"

#ifdef MST_UL
#include <mtcr_int_defs.h>
#include <mtcr_mf.h>
#endif

#define TOOLS_HCR_ADDR      0x80780
#define CR_MBOX_ADDR        0xe0000
#define CMD_IF_SIZE         28
#define CMD_IF_WAIT_GO      2000

#define TOOLS_HCR_SEM       0xf03bc // sem47
#define TOOLS_SEM_TRIES     1024     // Number of tries to obtain a TOOLS sem.

#define MBOX_WRITE_OP       0x70
#define MBOX_READ_OP        0x71
#define REG_ACCESS_OP       0x3b

#define MREAD4_ADV(offs, val_ptr, action_on_fail)   do { \
        if (mread4(mf, offs, val_ptr) != 4) { \
            /*fprintf(stderr, "-E- Cr read (0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), strerror(errno), (u_int32_t)errno);*/ \
            action_on_fail; \
        } \
        /*printf("-D- %s:%d mread4: offs = %#x, val = %#x\n", __FUNCTION__, __LINE__, offs, val);*/ \
} while (0)

#define MWRITE4_ADV(offs, val, action_on_fail)  do { \
        if (mwrite4(mf, offs, val) != 4) { \
            /*fprintf(stderr, "-E- Cr write (0x%08x, 0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), (u_int32_t)(val), strerror(errno), (u_int32_t)errno);*/ \
            action_on_fail; \
        } \
        /*printf("-D- %s:%d mwrite4: offs = %#x, val = %#x\n",   __FUNCTION__, __LINE__, offs, val);*/ \
} while (0)
#define MREAD4(offs, val_ptr) MREAD4_ADV(offs, val_ptr, return ME_CR_ERROR)
#define MWRITE4(offs, val) MWRITE4_ADV(offs, val, return ME_CR_ERROR)


#define TOCPUn(s, n) do {                                          \
        u_int32_t ii;                                                   \
        u_int32_t *p = (u_int32_t*)(s);                               \
        for (ii = 0; ii < (n); ii++, p++)                         \
            *p = __be32_to_cpu(*p);                                    \
} while (0)

#if __BYTE_ORDER == __BIG_ENDIAN

#define SWAP_DW_BE(uint64_num) \
    (((uint64_num) & 0xffffffffULL) << 32) | (((uint64_num) >> 32) & 0xffffffffULL)

#else
#define SWAP_DW_BE(uint64_num) (uint64_num)
#endif

typedef struct tools_cmdif_t {
    u_int32_t in_param_h;
    u_int32_t in_param_l;
    u_int32_t out_param_h;
    u_int32_t out_param_l;
    u_int32_t input_modifier;
    u_int16_t token;
    u_int16_t opcode;
    u_int8_t opcode_modifier;
    u_int8_t t;
    u_int8_t e;
    u_int8_t go;
    u_int8_t status;
} tools_cmdif;


static int translate_status(int status)
{
    switch (status) {
    case 0x0:
        return ME_OK;

    case 0x1:
        return ME_CMDIF_BUSY;

    case 0x2:
        return ME_CMDIF_BAD_OP;

    case 0x3:
        return ME_CMDIF_UNKN_TLV;

    case 0x4:
        return ME_CMDIF_BAD_SYS;

    case 0x9:
        return ME_CMDIF_RES_STATE;

    default:
        //printf("-D- Unknown status: 0x%x\n", status);
        return ME_CMDIF_UNKN_STATUS;
    }
}

extern void mpci_change(mfile *mf);

static void tools_cmdif_pack(tools_cmdif *cmd, u_int32_t *buf)
{
    memset((char*)buf, 0, CMD_IF_SIZE);
    buf[0] = cmd->in_param_h;
    buf[1] = cmd->in_param_l;
    buf[2] = cmd->input_modifier;
    // out h
    // out l
    buf[5] = MERGE(buf[5], cmd->token,               16, 16);
    buf[6] = MERGE(buf[6], cmd->opcode,               0, 12);
    buf[6] = MERGE(buf[6], cmd->opcode_modifier,     12,  4);
    buf[6] = MERGE(buf[6], cmd->e,                   22,  1);
}

static void tools_cmdif_unpack(tools_cmdif *cmd, u_int32_t *buf)
{
    memset(cmd, 0, sizeof(tools_cmdif));

    cmd->in_param_h       = buf[0];
    cmd->in_param_l       = buf[1];

    cmd->input_modifier = buf[2];
    cmd->out_param_h      = buf[3];
    cmd->out_param_l      = buf[4];
    cmd->opcode         = EXTRACT(buf[6], 0, 12);
    cmd->opcode_modifier = EXTRACT(buf[6], 12, 4);
    cmd->status         = EXTRACT(buf[6], 24, 8);
}

static int tools_cmdif_flash_lock(mfile *mf, int lock_state)
{
    // Obtain Semaphore
    u_int32_t cnt = 0;
    u_int32_t word = 0;
    if (lock_state) {
        do {
            if (++cnt > TOOLS_SEM_TRIES) {
                //printf("-E- Can not obtain Flash semaphore");
                return ME_SEM_LOCKED;
            }
            MREAD4(TOOLS_HCR_SEM, &word);
            if (word) {
                msleep(rand() % 5);
            }
        } while (word);
    } else {
        MWRITE4(TOOLS_HCR_SEM, 0);
    }

    return ME_OK;
}

int tools_cmdif_unlock_semaphore(mfile *mf)
{
    return tools_cmdif_flash_lock(mf, 0);
}

static int tools_cmdif_wait_go(mfile *mf, int *retries)
{
    int i;
    u_int8_t go_bit;
    int wait = 1;

    for (i = 0; i < CMD_IF_WAIT_GO; i++) {
        u_int32_t word = 0;
        MREAD4(TOOLS_HCR_ADDR + CMD_IF_SIZE - 4, &word);
        go_bit = EXTRACT(word, 23, 1);
        if (!go_bit) {
            if (retries) {
                *retries = i;
            }
            return 0;
        }
        if (i > 5) { // after some iteration put sleeps bwtween busy-wait
            msleep(wait);  // don't hog the cpu with busy-wait
            if (wait < 8) {
                wait *= 2;    // exponential backoff - up-to 8ms between polls
            }
        }
    }
    return ME_CMDIF_BUSY;
}

static int tools_cmdif_send_cmd_int(mfile *mf, tools_cmdif *cmd)
{
    u_int32_t raw_cmd[CMD_IF_SIZE / 4];
    int act_retries;
    int rc;

    // Check if the go BIT is ready
    rc = tools_cmdif_wait_go(mf, NULL);
    if (rc) {
        //printf("tools_cmdif_send: GO bit set before command issued (rc=%d)\n", rc);
        return ME_CMDIF_BUSY;
    }
    // Prepare the date of the command we're gonna execute
    tools_cmdif_pack(cmd, raw_cmd);
    if (mwrite4_block(mf, TOOLS_HCR_ADDR, raw_cmd, CMD_IF_SIZE) != CMD_IF_SIZE) {
        return ME_CR_ERROR;
    }

    raw_cmd[6] = MERGE(raw_cmd[6],      1,                   23,  1); // go
    MWRITE4(TOOLS_HCR_ADDR + 24, raw_cmd[6]);

    rc = tools_cmdif_wait_go(mf, &act_retries);

    if (rc) {
        return ME_CMDIF_TOUT;
    }

    if (mread4_block(mf, TOOLS_HCR_ADDR, raw_cmd, CMD_IF_SIZE) != CMD_IF_SIZE) {
        return ME_CR_ERROR;
    }

    tools_cmdif_unpack(cmd, raw_cmd);

    if (cmd->status) {
        //printf("-E- CMD IF Bad status. Op: 0x%x Status: 0x%x\n", cmd->opcode, cmd->status);
        return ME_CMDIF_BAD_STATUS; // TODO - Special return code here - needs a specific attention
    }
    return ME_OK;
}

int tools_cmdif_send_inline_cmd_int(mfile *mf,
                                    u_int32_t in_param[2],
                                    u_int32_t out_param[2],
                                    u_int32_t input_modifier,
                                    u_int16_t opcode,
                                    u_int8_t opcode_modifier)
{
    if (!mf) {
        return ME_BAD_PARAMS;
    }
    tools_cmdif cmdif;
    memset(&cmdif, 0, sizeof(tools_cmdif));
    cmdif.in_param_l = in_param[0];
    cmdif.in_param_h = in_param[1];
    cmdif.input_modifier = input_modifier;
    cmdif.opcode = opcode;
    cmdif.opcode_modifier = opcode_modifier;

    //take semaphore
    mpci_change(mf);
    if (tools_cmdif_flash_lock(mf, 1)) {
        mpci_change(mf);
        return ME_SEM_LOCKED;
    }
    int rc = tools_cmdif_send_cmd_int(mf, &cmdif);
    // release it
    tools_cmdif_flash_lock(mf, 0);
    mpci_change(mf);
    if (out_param) {
        out_param[0] = cmdif.out_param_l;
        out_param[1] = cmdif.out_param_h;
    }
    if (rc || cmdif.status) {
        return (rc != ME_CMDIF_BAD_STATUS) ? rc : translate_status(cmdif.status);
    }
    return rc;
}

int tools_cmdif_send_inline_cmd(mfile *mf,
                                u_int64_t in_param,
                                u_int64_t *out_param,
                                u_int32_t input_modifier,
                                u_int16_t opcode,
                                u_int8_t opcode_modifier)
{
    int rc;
    in_param = SWAP_DW_BE(in_param);
    rc = tools_cmdif_send_inline_cmd_int(mf, (u_int32_t*)((u_int8_t*)&in_param), (u_int32_t*)out_param, input_modifier, opcode, opcode_modifier);
    if (out_param) {
        u_int64_t swapped_out_param = SWAP_DW_BE(*out_param);
        *out_param = swapped_out_param;
    }
    return rc;
}

// read from mailbox method. output[2] is in BigEndian
static int tools_cmdif_mbox_read(mfile *mf, u_int32_t offset, u_int32_t output[2])
{
    if (!mf || (offset & 0x1) != 0 || !output) {// offset should be quad word aligned (i.e only even dwords)
        return ME_BAD_PARAMS;
    }
    tools_cmdif cmdif;
    memset(&cmdif, 0, sizeof(tools_cmdif));
    //printf("-D- offset: 0x%x\n", offset>>2);
    cmdif.input_modifier = offset; // offset is in dwords
    cmdif.opcode = MBOX_READ_OP;

    int rc = tools_cmdif_send_cmd_int(mf, &cmdif);
    // swap endianess because tools_cmdif_send_cmd_int returns output in CPU endianess
    output[0] = __be32_to_cpu(cmdif.out_param_l);
    output[1] = __be32_to_cpu(cmdif.out_param_h);
    if (rc || cmdif.status) {
        return (rc != ME_CMDIF_BAD_STATUS) ? rc : translate_status(cmdif.status);
    }
    //printf("-D- mbox read OK\n");
    return ME_OK;
}

// write to mailbox method. input[2] is in BigEndian
static int tools_cmdif_mbox_write(mfile *mf, u_int32_t offset, u_int32_t input[2])
{
    if (!mf || (offset & 0x1) != 0) {// offset should be quad word aligned (i.e only even dwords)
        return ME_BAD_PARAMS;
    }
    tools_cmdif cmdif;
    memset(&cmdif, 0, sizeof(tools_cmdif));
    // swap endianess because tools_cmdif_send_cmd_int assumes input in CPU endianess
    cmdif.in_param_l = __be32_to_cpu(input[0]);
    cmdif.in_param_h = __be32_to_cpu(input[1]);
    cmdif.input_modifier = offset; // offset is in dwords
    cmdif.opcode = MBOX_WRITE_OP;
    int rc = tools_cmdif_send_cmd_int(mf, &cmdif);

    if (rc || cmdif.status) {
        return (rc != ME_CMDIF_BAD_STATUS) ? rc : translate_status(cmdif.status);
    }
    return ME_OK;
}

static int tools_cmdif_cr_mbox_write(mfile *mf, u_int32_t offset, u_int8_t *data, int size)
{
    if (!mf || !data || (offset + size > TOOLS_HCR_MAX_MBOX)) {
        return ME_BAD_PARAMS;
    }
    if (mwrite_buffer(mf, CR_MBOX_ADDR + offset, data, size) != size) {
        return ME_CR_ERROR;
    }
    return ME_OK;
}

static int tools_cmdif_cr_mbox_read(mfile *mf, u_int32_t offset, u_int8_t *data, int size)
{
    if (!mf || !data || (offset + size > TOOLS_HCR_MAX_MBOX)) {
        return ME_BAD_PARAMS;
    }
    if (mread_buffer(mf, CR_MBOX_ADDR + offset, data, size) != size) {
        return ME_CR_ERROR;
    }
    return ME_OK;
}

int tools_cmdif_is_supported(mfile *mf)
{
    int rc = ME_OK;
    // run mailbox write cmd (read command fails after driver restart or internal reset)
    u_int32_t writebuf[2] = {0};
    if (!mf) {
        return ME_BAD_PARAMS;
    }
    mpci_change(mf);
    // take semaphore
    if (tools_cmdif_flash_lock(mf, 1)) {
        rc = ME_SEM_LOCKED;
        goto cleanup;
    }
    rc = tools_cmdif_mbox_write(mf, 0, writebuf);
    if (rc) {
        tools_cmdif_flash_lock(mf, 0);
        goto cleanup;
    }
    tools_cmdif_flash_lock(mf, 0);
cleanup:
    mpci_change(mf);
    return rc;
}

#define MAGIC 0xbadb00f
int tools_cmdif_is_cr_mbox_supported(mfile *mf)
{
    int rc;
    u_int32_t val = 0;
    mpci_change(mf);
    if ((rc = tools_cmdif_flash_lock(mf, 1))) {
        goto cleanup_no_sem;
    }
    // attempt to write/read from cr-mbox
    MWRITE4_ADV(CR_MBOX_ADDR, MAGIC, rc = ME_CR_ERROR; goto cleanup);
    MREAD4_ADV(CR_MBOX_ADDR, &val, rc = ME_CR_ERROR; goto cleanup);
cleanup:
    tools_cmdif_flash_lock(mf, 0);
cleanup_no_sem:
    mpci_change(mf);
    if (rc) {
        return rc;
    }
    return val == MAGIC ? ME_OK : ME_CMDIF_NOT_SUPP;
}

#define COMPLEMENT_TO_QUAD_ALIGNED(byte_sz) \
    ((byte_sz) + ((8 - ((byte_sz) & 7) == 8) ? 0 : (8 - ((byte_sz) & 7))))

int tools_cmdif_send_mbox_command_int(mfile *mf,
                                      u_int32_t input_modifier,
                                      u_int16_t opcode,
                                      u_int8_t opcode_modifier,
                                      int data_offs_in_mbox,
                                      void *data,
                                      int write_data_size,
                                      int read_data_size,
                                      int skip_write,
                                      int use_cr_mbox)
{
    int read_data_size_quad_aligned =  COMPLEMENT_TO_QUAD_ALIGNED(read_data_size);
    int write_data_size_quad_aligned =  COMPLEMENT_TO_QUAD_ALIGNED(write_data_size);
    int rc,
        i;
    /*printf("-D- opcode: 0x%x, opcode mod: 0x%x, data_offs_in_mbox: 0x%x, write_data_size: 0x%x(0x%x), read_data_size 0x%x(0x%x), skip_write: %d\n",\
             opcode, opcode_modifier, data_offs_in_mbox, write_data_size, write_data_size_quad_aligned, read_data_size, read_data_size_quad_aligned, skip_write);*/
    // check params
    if (!mf || !data || data_offs_in_mbox < 0 || (data_offs_in_mbox & 7) != 0 || \
        data_offs_in_mbox + read_data_size_quad_aligned > TOOLS_HCR_MAX_MBOX || \
        data_offs_in_mbox + write_data_size_quad_aligned > TOOLS_HCR_MAX_MBOX) {
        return ME_BAD_PARAMS;
    }
    mpci_change(mf);
    //take semaphore
    if (tools_cmdif_flash_lock(mf, 1)) {
        mpci_change(mf);
        return ME_SEM_LOCKED;
    }

    // write to mailbox if needed
    u_int8_t mailbox[TOOLS_HCR_MAX_MBOX] = {0};
    if (!skip_write) {
        // place the data inside 256 bytes buffer (init with zeroes) and write the entire buffer to mbox
        // it is required in the TOOLS_HCR HLD to write the ENTIRE MBOX

        memcpy(&(mailbox[data_offs_in_mbox]), data, write_data_size);

        if (use_cr_mbox == 1) {
            //write mbox to virtual cr-space
            rc = tools_cmdif_cr_mbox_write(mf, 0x0, mailbox, TOOLS_HCR_MAX_MBOX);
            if (rc) {
                goto cleanup;
            }
        } else {
            int i;
            for (i = 0; i < TOOLS_HCR_MAX_MBOX; i += 8) { // it is required to write in quad word chunks
                rc = tools_cmdif_mbox_write(mf, i / 4, (u_int32_t*)&mailbox[i]);
                if (rc) {
                    goto cleanup;
                }
            }
        }
    }
    // send cmd
    tools_cmdif cmdif;
    memset(&cmdif, 0, sizeof(tools_cmdif));
    cmdif.opcode = opcode;
    cmdif.opcode_modifier = opcode_modifier;
    cmdif.input_modifier = input_modifier;
    rc = tools_cmdif_send_cmd_int(mf, &cmdif);

    if (rc || cmdif.status) {
        if (rc == ME_CMDIF_BAD_STATUS) {
            rc = translate_status(cmdif.status); // means that driver is down or we dont support the extended version of tools hcr.
        }
        goto cleanup;
    }
    // read from mbox
    // read read_data_size bytes from mbox and update our data
    if (use_cr_mbox == 1) {
        // read mailbox from virtual CR-space
        rc = tools_cmdif_cr_mbox_read(mf, data_offs_in_mbox, &mailbox[data_offs_in_mbox], read_data_size_quad_aligned);
        if (rc) {
            goto cleanup;
        }
    } else {
        for (i = data_offs_in_mbox; i < (data_offs_in_mbox + read_data_size_quad_aligned); i += 8) { // it is required to write in quad word chunks (64bits each time)
            rc = tools_cmdif_mbox_read(mf, i / 4, (u_int32_t*)&(mailbox[i]));
            if (rc) {
                goto cleanup;
            }
        }
    }
    // copy data back to user
    memcpy(data, &(mailbox[data_offs_in_mbox]), read_data_size);
    rc = ME_OK;
cleanup:
    tools_cmdif_flash_lock(mf, 0);
    mpci_change(mf);
    return rc;
}


int tools_cmdif_reg_access(mfile *mf, void *data, int write_data_size, int read_data_size)
{
    int rc;
    if (mf->hcr_params.supp_cr_mbox == 0) {
        rc = tools_cmdif_is_cr_mbox_supported(mf);
        if (rc == ME_OK) {
            mf->hcr_params.supp_cr_mbox = 1;
        } else if (rc == ME_CMDIF_NOT_SUPP) {
            mf->hcr_params.supp_cr_mbox = -1;
        } else {
            // CR error or Semaphore locked
            return rc;
        }
    }
    if (mf->hcr_params.supp_cr_mbox == 1) {
        rc = tools_cmdif_send_mbox_command_int(mf, 1, REG_ACCESS_OP, 0, \
                                               0, data, write_data_size, read_data_size, 0, 1);
    } else {
        rc = tools_cmdif_send_mbox_command_int(mf, 0, REG_ACCESS_OP, 0, \
                                               0, data, write_data_size, read_data_size, 0, 0);
    }
    return rc;
}


int tools_cmdif_send_mbox_command(mfile *mf,
                                  u_int32_t input_modifier,
                                  u_int16_t opcode,
                                  u_int8_t opcode_modifier,
                                  int data_offs_in_mbox,
                                  void *data,
                                  int data_size,
                                  int skip_write)
{

    return tools_cmdif_send_mbox_command_int(mf, input_modifier, opcode, opcode_modifier, \
                                             data_offs_in_mbox, data, data_size, \
                                             data_size, skip_write, 0);
}

