/*
 * Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.
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

/*
 * mflash_new_gw.c
 *
 *  Created on: Jul 8, 2020
 *      Author: edwardg
 */
#include "mflash_pack_layer.h"
#include "mflash_dev_capability.h"
#include "mflash_access_layer.h"
#include "flash_int_defs.h"

#ifdef __WIN__
 //
 // Windows (Under DDK)
 //
#define OP_NOT_SUPPORTED EINVAL
#define usleep(x) Sleep(((x + 999) / 1000))

#endif // __WIN_
#define CHECK_RC_REL_SEM(mfl, rc) do {if (rc) {release_semaphore(mfl, 0); return rc;}} while (0)

static int st_spi_wait_wip(mflash *mfl, u_int32_t init_delay_us, u_int32_t retry_delay_us,
    u_int32_t num_of_retries)
{

    int rc = 0;
    u_int8_t status = 0;
    u_int32_t i = 0;

    usleep(init_delay_us);

    for (i = 0; i < num_of_retries; ++i) {
        rc = mfl->f_spi_status(mfl, SFC_RDSR, &status);
        CHECK_RC(rc);
        if ((status & 1) == 0) {
            return MFE_OK;
        }
        usleep(retry_delay_us);
        if (mfl->cputUtilizationApplied) {
            if ((i % mfl->cpuPercent) == 0) {
                msleep(1);
            }
        }
    }

    return MFE_WRITE_TIMEOUT;
}
static u_int32_t log2up(u_int32_t in)
{
    u_int32_t i = 0;
    for (i = 0; i < 32; i++) {
        if (in <= (u_int32_t)(1 << i)) {
            break;
        }
    }
    return i;
}
static bool is_x_byte_address_access_commands(mflash *mfl, int x)
{
    if (x != 3 && x != 4) {
        return false;
    }

    flash_access_commands_t compared_to_access_commands = (x == 4) ? gen_4byte_address_access_commands() : gen_3byte_address_access_commands();
    flash_access_commands_t cur = mfl->attr.access_commands;

    return (compared_to_access_commands.sfc_sector_erase == cur.sfc_sector_erase && compared_to_access_commands.sfc_subsector_erase == cur.sfc_subsector_erase && compared_to_access_commands.sfc_page_program == cur.sfc_page_program && compared_to_access_commands.sfc_read == cur.sfc_read && compared_to_access_commands.sfc_fast_read == cur.sfc_fast_read);
}
static int new_gw_exec_cmd(mflash *mfl, u_int32_t gw_cmd, char *msg)
{
    if (!IS_CONNECTX_4TH_GEN_FAMILY(mfl->attr.hw_dev_id)) {
        // for old devices lock bit is separate from the flash HW ifc
        //for new devices need to make sure this bit remains locked when writing the dword
        gw_cmd = MERGE(gw_cmd, 1, 31, 1);
    }
    if ((gw_cmd & (1 << HBO_NEW_GW_ADDR_PHASE)) != 0) { // This is an access command
        if (is_x_byte_address_access_commands(mfl, 4)) {
            gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_ADDR_SIZE, 1);
        }
        else if (!is_x_byte_address_access_commands(mfl, 3)) {
            return MFE_ACCESS_COMMANDS_NOT_INITIALIZED;
        }
    }
    gw_cmd = MERGE(gw_cmd, 1, HBO_BUSY, 1);

    MfError status;
    int flash_enable_needed = is_flash_enable_needed(mfl, &status);
    //for new devices this value is always 0
    if (status != MFE_OK) {
        return status;
    }
    if (flash_enable_needed) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_FLASH_ENABLE, 1);
    }

    gw_cmd = MERGE(gw_cmd, (u_int32_t)mfl->curr_bank, HBO_NEW_GW_CHIP_SELECT, HBS_NEW_GW_CHIP_SELECT);
    //  printf("-D- new_gw_exec_cmd: %s, gw_cmd = %#x\n", msg, gw_cmd);
    MWRITE4(CR_FLASH_GW, gw_cmd);
    return gw_wait_ready(mfl, msg);
}

/*
 * execute a flash GW command and get the output: data0...data3 from the flash interface
 *
 * mfl - pointer to an initilized mflash obj
 * gw_cmd - the flash gateway command to execute
 * buff - pointer to a buffer where the output data from the flash GW will be written to
 * buff_dword_sz - size for buff in dwords
 * addr - if != NULL *addr will be written to the addr bits of the flash GW. (for commands that read from flash)
 * msg - optional string that describes the action for debug purposes, not used ATM however its recommended to put usefull
 *        data for future dubugabillity.
 * return : MFE_OK (0) upon success or a value != 0 upon error accroding to mlfash error code.
 */
static int new_gw_exec_cmd_get(mflash *mfl, u_int32_t gw_cmd, u_int32_t *buff, int buff_dword_sz,
    u_int32_t *addr, char *msg)
{
    int rc = 0;
    if (!mfl || !buff || !buff_dword_sz) {
        return MFE_BAD_PARAMS;
    }

    rc = mfl_com_lock(mfl);
    CHECK_RC(rc);

    // write GW addr if needed
    if (addr) {
        if (mwrite4(mfl->mf, HCR_FLASH_NEW_GW_ADDR, *addr) != 4) {
            release_semaphore(mfl, 0);
            return MFE_CR_ERROR;
        }
    }
    // execute gw command
    rc = new_gw_exec_cmd(mfl, gw_cmd, msg);
    CHECK_RC_REL_SEM(mfl, rc);
    // copy data from CR-space to buff
    if (mread4_block(mfl->mf, HCR_FLASH_DATA, buff, (buff_dword_sz << 2)) != (buff_dword_sz << 2)) {
        release_semaphore(mfl, 0);
        return MFE_CR_ERROR;
    }
    //release semaphore
    release_semaphore(mfl, 0);
    return MFE_OK;
}

/*
 * Set input in: data0...data3 from the flash interface and execute a flash GW command
 *
 * mfl - pointer to an initilized mflash obj
 * gw_cmd - the flash gateway command to execute
 * buff - if != NULL pointer to a buffer to the input data for the flash GW.
 * buff_dword_sz - size for buff in dwords
 * addr - if != NULL *addr will be written to the addr bits of the flash GW. (for commands that write from flash)
 * msg - optional string that describes the action for debug purposes, not used ATM however its recommended to put usefull
 *        data for future dubugabillity.
 * return : MFE_OK (0) upon success or a value != 0 upon error accroding to mlfash error code.
 */
static int new_gw_exec_cmd_set(mflash *mfl, u_int32_t gw_cmd, u_int32_t *buff, int buff_dword_sz,
    u_int32_t *addr, char *msg)
{
    int rc = 0;
    if (!mfl) {
        return MFE_BAD_PARAMS;
    }

    rc = mfl_com_lock(mfl);
    CHECK_RC(rc);

    // write data from buff to CR-space
    if (buff && buff_dword_sz) {
        if (mwrite4_block(mfl->mf, HCR_FLASH_DATA, buff, (buff_dword_sz << 2)) != (buff_dword_sz << 2)) {
            release_semaphore(mfl, 0);
            return MFE_CR_ERROR;
        }
    }

    // write GW addr if needed
    if (addr) {
        if (mwrite4(mfl->mf, HCR_FLASH_NEW_GW_ADDR, *addr) != 4) {
            release_semaphore(mfl, 0);
            return MFE_CR_ERROR;
        }
    }
    // execute gw command
    rc = new_gw_exec_cmd(mfl, gw_cmd, msg);
    CHECK_RC_REL_SEM(mfl, rc);

    //release semaphore
    release_semaphore(mfl, 0);
    return MFE_OK;
}

int new_gw_int_spi_get_status_data(mflash *mfl, u_int8_t op_type, u_int32_t *status, u_int8_t bytes_num)
{
    int rc = 0;

    u_int32_t gw_cmd = 0;
    u_int32_t flash_data = 0;
    //TODO: adrianc: update msize from log2(bytes_num)
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_READ_OP, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 2, HBO_NEW_GW_DATA_SIZE, HBS_NEW_GW_MSIZE);

    gw_cmd = MERGE(gw_cmd, op_type, HBO_NEW_GW_CMD, HBS_CMD);

    if (bytes_num > 4) {
        return MFE_BAD_PARAMS;
    }
    rc = new_gw_exec_cmd_get(mfl, gw_cmd, &flash_data, 1, (u_int32_t*)NULL, "Read id");
    CHECK_RC(rc);
    // printf("-D- new_gw_int_spi_get_status_data: op=%02x status=%08x\n", op_type, flash_data);
    *status = (flash_data >> 8 * (4 - bytes_num));
    return MFE_OK;
}
int new_gw_st_spi_write_enable(mflash *mfl)
{
    u_int32_t gw_cmd = 0;
    int rc = 0;
    // Write enable:
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, SFC_WREN, HBO_NEW_GW_CMD, HBS_CMD);

    rc = new_gw_exec_cmd_set(mfl, gw_cmd, (u_int32_t*)NULL, 0, (u_int32_t*)NULL, "WREN command");
    CHECK_RC(rc);
    return MFE_OK;
}
int new_gw_spi_write_status_reg(mflash *mfl, u_int32_t status_reg, u_int8_t write_cmd, u_int8_t bytes_num)
{
    int rc = 0;
    u_int32_t gw_cmd = 0;
    // TODO: adrianc: add support for dynamic writes of power of 2 bytes_num not just 1,2 bytes
    rc = new_gw_st_spi_write_enable(mfl);
    CHECK_RC(rc);
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_DATA_PHASE, 1);

    gw_cmd = MERGE(gw_cmd, write_cmd, HBO_NEW_GW_CMD, HBS_CMD);

    if (bytes_num != 1 && bytes_num != 2) {
        return MFE_NOT_SUPPORTED_OPERATION;
    }
    // push status reg to upper bytes
    status_reg = status_reg << ((bytes_num == 2) ? 16 : 24);
    if (bytes_num == 2) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_DATA_SIZE, 1);
    }
    rc = new_gw_exec_cmd_set(mfl, gw_cmd, &status_reg, 1, (u_int32_t*)NULL, "Write-Status-Register");
    // wait for flash to write the register
    if (mfl->attr.vendor == FV_S25FLXXXX && mfl->attr.type == FMT_S25FLXXXL) { // New CYPRESS
        msleep(WRITE_STATUS_REGISTER_DELAY_CYPRESS);
    }
    else if (mfl->attr.vendor == FV_ST && mfl->attr.type == FMT_N25QXXX) { // New MICRON
        msleep(WRITE_STATUS_REGISTER_DELAY_MICRON);
    }
    else {
        msleep(WRITE_STATUS_REGISTER_DELAY_MIN); // Some can sleep only 30 or even 15. We should consider optimize this.
    }
    return rc;
}
int new_gw_st_spi_erase_sect(mflash *mfl, u_int32_t addr)
{
    int rc = 0;

    u_int32_t gw_cmd = 0;
    u_int32_t gw_addr = 0;
    rc = set_bank(mfl, addr);
    CHECK_RC(rc);

    rc = new_gw_st_spi_write_enable(mfl);
    CHECK_RC(rc);

    // Erase sector command:
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_ADDR_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, mfl->attr.erase_command, HBO_NEW_GW_CMD, HBS_CMD);

    gw_addr = addr & ONES32(mfl->attr.log2_bank_size);

    // printf("-D- cntx_st_spi_erase_sect: addr = %#x, gw_cmd = %#x.\n", addr, gw_cmd);

    rc = new_gw_exec_cmd_set(mfl, gw_cmd, (u_int32_t*)NULL, 0, &gw_addr, "ES");
    CHECK_RC(rc);

    // Wait for erase completion
    rc = st_spi_wait_wip(mfl, ERASE_SUBSECTOR_INIT_DELAY, ERASE_SUBSECTOR_RETRY_DELAY, ERASE_SUBSECTOR_RETRIES);
    CHECK_RC(rc);
    return MFE_OK;
}
int new_gw_st_spi_block_write_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data,
    u_int8_t is_first, u_int8_t is_last, u_int32_t total_size)
{
    int rc = 0;
    u_int32_t offs = 0;
    u_int32_t gw_cmd = 0;
    u_int32_t gw_addr = 0;
    u_int32_t buff[4];

    if (blk_addr & ((u_int32_t)mfl->attr.block_write - 1)) {
        return MFE_BAD_ALIGN;
    }

    // sanity check ??? remove ???
    if (blk_size != (u_int32_t)mfl->attr.block_write) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);
    CHECK_RC(rc);

    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, blk_size, HBO_NEW_GW_DATA_SIZE, HBS_NEW_GW_MSIZE);

    if (is_first) {
        rc = new_gw_st_spi_write_enable(mfl);
        CHECK_RC(rc);

        // Write the data block
        gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_CMD_PHASE, 1);
        gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_ADDR_PHASE, 1);
        gw_cmd = MERGE(gw_cmd, mfl->attr.access_commands.sfc_page_program, HBO_NEW_GW_CMD, HBS_CMD);
        gw_addr = blk_addr & ONES32(mfl->attr.log2_bank_size);
        //printf("-D- gw_addr = %#x, blk_addr = %#x\n", gw_addr, blk_addr);
    }

    if (!is_last) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_CS_HOLD, 1);
    }

    // Data:
    for (offs = 0; offs < blk_size; offs += 4) {
        u_int32_t word = 0;

        word = MERGE(word, data[offs + 0], 24, 8);
        word = MERGE(word, data[offs + 1], 16, 8);
        word = MERGE(word, data[offs + 2], 8, 8);
        word = MERGE(word, data[offs + 3], 0, 8);
        //MWRITE4(HCR_FLASH_DATA + offs, word );
        buff[offs / 4] = word;
        //printf("-D- word = %#x, %d\n", word, HBS_CMD);
    }

    rc = new_gw_exec_cmd_set(mfl, gw_cmd, buff, (blk_size >> 2), &gw_addr, "PP command");
    CHECK_RC(rc);

    //
    // Wait for end of write in flash (WriteInProgress = 0):
    //

    if (is_last) {
        rc = st_spi_wait_wip(mfl, WRITE_BLOCK_INIT_DELAY + WRITE_ADDITIONAL_BYTE_DELAY * total_size, WRITE_BLOCK_RETRY_DELAY, WRITE_BLOCK_RETRIES);
        CHECK_RC(rc);
    }

    return MFE_OK;
}

int new_gw_sst_spi_block_write_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data)
{
    int rc = 0;
    u_int32_t gw_cmd = 0;
    u_int32_t gw_addr = 0;
    u_int32_t word = 0;

    // sanity check ??? remove ???
    if (blk_size != (u_int32_t)mfl->attr.block_write) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);
    CHECK_RC(rc);

    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 0, HBO_NEW_GW_DATA_SIZE, HBS_NEW_GW_MSIZE);

    rc = new_gw_st_spi_write_enable(mfl);
    CHECK_RC(rc);

    // Write the data block
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_CMD_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_ADDR_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, 0x02, HBO_NEW_GW_CMD, HBS_CMD);

    gw_addr = blk_addr & ONES32(mfl->attr.log2_bank_size);

    //gw_cmd = MERGE(gw_cmd, 1               , HBO_NEW_GW_CS_HOLD,    1);

    word = MERGE(word, data[0], 24, 8);

    //printf("-D- data[0] = %#x, gw_addr = %#x, word = %#x, gw_cmd = %#x\n", data[0], gw_addr, word, gw_cmd);

    rc = new_gw_exec_cmd_set(mfl, gw_cmd, &word, 1, &gw_addr, "PB command");
    CHECK_RC(rc);

    rc = st_spi_wait_wip(mfl, 0, 0, 50000);
    CHECK_RC(rc); // Full throttle polling - no cpu optimization for this flash

    return MFE_OK;
}
int new_gw_st_spi_block_read_ex(mflash *mfl, u_int32_t blk_addr, u_int32_t blk_size, u_int8_t *data,
    u_int8_t is_first, u_int8_t is_last, bool verbose)
{
    (void)verbose;
    int rc = 0;
    u_int32_t i = 0;
    u_int32_t gw_cmd = 0;
    u_int32_t gw_addr = 0;

    //printf("-D- new_gw_st_spi_block_read_ex(addr=%05x, u_int32_t size=%03x, first=%d, last=%d)\n", blk_addr, blk_size, (u_int32_t) is_first, (u_int32_t) is_last);
    COM_CHECK_ALIGN(blk_addr, blk_size);

    if (blk_size > (u_int32_t)mfl->attr.block_write || blk_size < 4) {
        return MFE_BAD_PARAMS;
    }

    rc = set_bank(mfl, blk_addr);
    CHECK_RC(rc);

    if (is_first) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_CMD_PHASE, 1);
        gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_ADDR_PHASE, 1);
        gw_cmd = MERGE(gw_cmd, mfl->attr.access_commands.sfc_read, HBO_NEW_GW_CMD, HBS_CMD);
        rc = get_flash_offset(blk_addr, mfl->attr.log2_bank_size, &gw_addr);
        CHECK_RC(rc);
    }
    //printf("-D- gw_addr = %#x, gw_cmd = %#x, blk_addr = %#x, mfl->attr.log2_bank_size = %#x\n", gw_addr, gw_cmd, blk_addr, mfl->attr.log2_bank_size);
    if (!is_last) {
        gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_CS_HOLD, 1);
    }

    // Read the data block
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_READ_OP, 1);
    gw_cmd = MERGE(gw_cmd, 1, HBO_NEW_GW_DATA_PHASE, 1);
    gw_cmd = MERGE(gw_cmd, log2up(blk_size), BO_MSIZE, BS_MSIZE);

    rc = new_gw_exec_cmd_get(mfl, gw_cmd, (u_int32_t*)data, (blk_size >> 2), &gw_addr, "Read");
    CHECK_RC(rc);
    for (i = 0; i < blk_size; i += 4) {
        *(u_int32_t*)(data + i) = __be32_to_cpu(*(u_int32_t*)(data + i));
    }
    return MFE_OK;
}
