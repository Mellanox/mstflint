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

#include "mtcr_ib_res_mgt.h"
#include "mtcr_ib.h"
#include "packets_common.h"
#include <string.h>

#define IB_SMP_DATA_SIZE 48
#define SMP_SEMAPHOE_LOCK_CMD 0xff53

#define DBG_PRINTF(...) do { if (getenv("MFT_DEBUG") != NULL) { fprintf(stderr, __VA_ARGS__); } } while (0)

/* Description -   */
/* Size in bytes - 12 */
struct semaphore_lock_cmd {
/*---------------- DWORD[0] (Offset 0x0) ----------------*/
    /* Description - The maximal Semaphore Address supported by the device. */
    /* 0.0 - 0.7 */
    u_int8_t semaphore_max_addr;
    /* Description - The lease time for a lock is 50msec *2^LeaseTimeExponent */
    /* 0.16 - 0.23 */
    u_int8_t lease_time_exponent;
    /* Description - Should be used to extend a lock. When a lock owner application wish to extend the lock it should set this bit to 1 and fill the Key field with key obtained by the GetResp() to successful acquiring of a lock. */
    /* 0.31 - 4.31 */
    u_int8_t is_lease;
/*---------------- DWORD[1] (Offset 0x4) ----------------*/
    /* Description - The specific Semaphore being queried or requested a lock for */
    /* 4.0 - 4.15 */
    u_int16_t semaphore_addr;
    /* Description - 1 = Lock, 2 = Extend, 3 = Release */
    /* 4.16 - 4.17 */
    u_int8_t op;
/*---------------- DWORD[2] (Offset 0x8) ----------------*/
    /* Description - This field is provided by the device on a successful lock. It should be used by the user in order to either extend or release of the lock. */
    /* 8.0 - 8.31 */
    u_int32_t lock_key;
};


void semaphore_lock_cmd_pack(const struct semaphore_lock_cmd *ptr_struct, u_int8_t *ptr_buff)
{
    u_int32_t offset;
    int i = 0;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset = 24;
    push_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->semaphore_max_addr);

    offset = 8;
    push_to_buff(ptr_buff, offset, 8, (u_int32_t)ptr_struct->lease_time_exponent);

    offset = 0;
    push_to_buff(ptr_buff, offset, 1, (u_int32_t)ptr_struct->is_lease);

    offset = 48;
    push_to_buff(ptr_buff, offset, 16, (u_int32_t)ptr_struct->semaphore_addr);

    offset = 46;
    push_to_buff(ptr_buff, offset, 2, (u_int32_t)ptr_struct->op);

    offset = 64;
    push_to_buff_32(ptr_buff, offset, ptr_struct->lock_key);

}

void semaphore_lock_cmd_unpack(struct semaphore_lock_cmd *ptr_struct, u_int8_t *ptr_buff)
{
    u_int32_t offset;
    int i = 0;
    u_int8_t val = 0;
    (void)val;
    (void)offset;
    (void)i;
    (void)ptr_struct;
    (void)ptr_buff;

    offset = 24;
    ptr_struct->semaphore_max_addr = (u_int8_t)pop_from_buff(ptr_buff, offset, 8);

    offset = 8;
    ptr_struct->lease_time_exponent = (u_int8_t)pop_from_buff(ptr_buff, offset, 8);

    offset = 0;
    ptr_struct->is_lease = (u_int8_t)pop_from_buff(ptr_buff, offset, 1);

    offset = 48;
    ptr_struct->semaphore_addr = (u_int16_t)pop_from_buff(ptr_buff, offset, 16);

    offset = 46;
    ptr_struct->op = (u_int8_t)pop_from_buff(ptr_buff, offset, 2);

    offset = 64;
    ptr_struct->lock_key = pop_from_buff_32(ptr_buff, offset);

}

int mib_semaphore_lock_vs_mad(
    mfile *mf,
    sem_op_t op,
    u_int32_t sem_addr,
    u_int32_t lock_key,
    u_int32_t *res,
    int *is_leaseable,
    u_int8_t *lease_time_exp,
    sem_lock_method_t method)
{
#ifndef NO_INBAND
    u_int8_t mad_data[IB_SMP_DATA_SIZE] = {0};
    int rc = ME_OK;
    struct semaphore_lock_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    cmd.semaphore_addr = sem_addr;
    cmd.op = op;
    cmd.lock_key = lock_key;
    DBG_PRINTF("#######BFORE#####\n# SEM_ADDR: 0x%x\n# OP: %d\n# Lock_Key: 0x%x\n#################\n",
               cmd.semaphore_addr, cmd.op, cmd.lock_key);
    semaphore_lock_cmd_pack(&cmd, mad_data);
    if (method == SEM_LOCK_SET) {
        rc = mib_smp_set(mf, mad_data, SMP_SEMAPHOE_LOCK_CMD, 0);
    } else {
        rc = mib_smp_get(mf, mad_data, SMP_SEMAPHOE_LOCK_CMD, 0);
    }
    semaphore_lock_cmd_unpack(&cmd, mad_data);
    DBG_PRINTF("#######AFTER#####\n# SEM_ADDR: 0x%x\n# OP: %d\n# Lock_Key: 0x%x\n#################\n",
               cmd.semaphore_addr, cmd.op, cmd.lock_key);
    *res = cmd.lock_key;
    *is_leaseable = (int)cmd.is_lease;
    *lease_time_exp = cmd.lease_time_exponent;
    return rc;
#else
    (void)mf;
    (void)op;
    (void)sem_addr;
    (void)lock_key;
    (void)res;
    (void)is_leaseable;
    (void)lease_time_exp;
    (void)method;
    return 1;
#endif
}

int mib_semaphore_lock_is_supported(mfile *mf)
{
#ifndef NO_INBAND
    u_int8_t mad_data[IB_SMP_DATA_SIZE] = {0};
    struct semaphore_lock_cmd cmd;
    memset(&cmd, 0, sizeof(cmd));
    mib_smp_get(mf, mad_data, SMP_SEMAPHOE_LOCK_CMD, 0);
    semaphore_lock_cmd_unpack(&cmd, mad_data);
    DBG_PRINTF("###### QUERY #####\n# MAX_SEM_ADDR: 0x%x\n#################\n", cmd.semaphore_max_addr);
    if (cmd.semaphore_max_addr > 0) {
        return 1;
    } else {
        return 0;
    }
#else
    (void)mf;
    return 1;
#endif
}
