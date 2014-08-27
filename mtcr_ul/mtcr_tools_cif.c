
/*
               - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <bit_slice.h>
#include <common/tools_utils.h>
#include "mtcr_tools_cif.h"

#define TOOLS_HCR_ADDR      0x80780
#define CMD_IF_SIZE         28
#define CMD_IF_WAIT_GO		2000

#define TOOLS_HCR_SEM		0xf03bc // sem47
#define TOOLS_SEM_TRIES		1024     // Number of tries to obtain a TOOLS sem.

#define QUERY_DEV_CAP_OP	0x3
#define MBOX_WRITE_OP		0x70
#define MBOX_READ_OP		0x71
#define REG_ACCESS_OP		0x3b

#ifdef ESS
#define MREAD4(offs, val)  do {*val=READ_WORD(offs);} while (0)
#define MWRITE4(offs, val) do {WRITE_WORD(offs, val);} while (0)
#else
#define MREAD4(offs, val)  do { if (mread4 (mf, offs, val) != 4) { \
                                  /*fprintf(stderr, "-E- Cr read (0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), strerror(errno), (u_int32_t)errno);*/ \
                  return 2; } /*printf("-D- %s:%d mread4: offs = %#x, val = %#x\n", __FUNCTION__, __LINE__, offs, val);*/\
                                  } while (0)

#define MWRITE4(offs, val) do { if (mwrite4(mf, offs, val) != 4) { \
                                  /*fprintf(stderr, "-E- Cr write (0x%08x, 0x%08x) failed: %s(%d)\n", (u_int32_t)(offs), (u_int32_t)(val), strerror(errno), (u_int32_t)errno);*/ \
                  return 2; } /*printf("-D- %s:%d mwrite4: offs = %#x, val = %#x\n",   __FUNCTION__, __LINE__, offs, val);*/ \
                                  } while (0)
#endif

#define TOCPUn(s, n) do {                                          \
	u_int32_t ii;													\
    u_int32_t *p = (u_int32_t *)(s);                               \
    for (ii=0; ii<(n); ii++,p++)                         \
        *p = __be32_to_cpu(*p);                                    \
    } while(0)

#if __BYTE_ORDER == __BIG_ENDIAN

u_int64_t swap_dwords_be(u_int8_t* buff) {
    u_int32_t first = *(u_int32_t*)(&buff[0]);\
    u_int32_t second = *(u_int32_t*)(&buff[4]);\
    u_int64_t dest = 0;
    dest = MERGE64(dest, first, 0, 32);
    dest = MERGE64(dest, second, 32, 32);
    return dest;
}
#else
u_int64_t swap_dwords_be(u_int8_t* buff) {
    return *((u_int64_t*)buff);
}
#endif

typedef struct tools_cmdif_t {
    u_int64_t in_param;
    u_int64_t out_param;
    u_int32_t input_modifier;
    u_int16_t token;
    u_int16_t opcode;
    u_int8_t  opcode_modifier;
    u_int8_t  t;
    u_int8_t  e;
    u_int8_t  go;
    u_int8_t  status;
} tools_cmdif;

static void tools_cmdif_pack(tools_cmdif* cmd, u_int32_t* buf) {
    memset((char*)buf, 0, CMD_IF_SIZE);
    buf[0] = EXTRACT64(cmd->in_param, 32, 32);
    buf[1] = EXTRACT64(cmd->in_param,  0, 32);
    buf[2] = cmd->input_modifier;
    // out h
    // out l
    buf[5] = MERGE(buf[5], cmd->token,               16, 16);
    buf[6] = MERGE(buf[6], cmd->opcode,               0, 12);
    buf[6] = MERGE(buf[6], cmd->opcode_modifier,     12,  4);
    buf[6] = MERGE(buf[6], cmd->e,                   22,  1);
}

static void tools_cmdif_unpack(tools_cmdif* cmd, u_int32_t* buf) {
    memset(cmd, 0, sizeof(tools_cmdif));

    cmd->in_param       = MERGE64(cmd->in_param, buf[0], 32, 32);
    cmd->in_param       = MERGE64(cmd->in_param, buf[1],  0, 32);

    cmd->input_modifier = buf[2];
    cmd->out_param      = MERGE64(cmd->out_param, buf[3], 32, 32);
    cmd->out_param      = MERGE64(cmd->out_param, buf[4],  0, 32);
    cmd->opcode         = EXTRACT(buf[6], 0, 12);
    cmd->opcode_modifier= EXTRACT(buf[6], 12, 4);

    cmd->status         = EXTRACT(buf[6], 24, 8);
}

static int tools_cmdif_flash_lock(mfile* mf, int lock_state) {
    // Obtain Semaphore
    u_int32_t cnt=0;
    u_int32_t word;
    if (lock_state) {
        do {
            if (++cnt > TOOLS_SEM_TRIES) {
                //printf("-E- Can not obtain Flash semaphore");
                return ME_SEM_LOCKED;
            }
            MREAD4(TOOLS_HCR_SEM, &word);
        } while (word);
    } else {
        MWRITE4(TOOLS_HCR_SEM, 0);
    }

    return ME_OK;
}

static int tools_cmdif_wait_go(mfile* mf, int* retries)
{
    int i;
    u_int8_t go_bit;
    int wait=1;

    for (i = 0; i < CMD_IF_WAIT_GO; i++) {
        u_int32_t word;
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

static int tools_cmdif_send_cmd_int(mfile* mf, tools_cmdif* cmd)
{
    u_int32_t raw_cmd[CMD_IF_SIZE/4];
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

int tools_cmdif_send_cmd(mfile* mf,
					 u_int64_t in_param,
					 u_int64_t* out_param,
					 u_int32_t input_modifier,
					 u_int16_t opcode,
					 u_int8_t  opcode_modifier,
					 u_int8_t*  status)
{
	if (!mf || !out_param || !status) {
		return ME_BAD_PARAMS;
	}
	tools_cmdif cmdif;
	memset(&cmdif, 0, sizeof(tools_cmdif));
	cmdif.in_param = in_param;
	cmdif.input_modifier = input_modifier;
	cmdif.opcode = opcode;
	cmdif.opcode_modifier = opcode_modifier;

	//take semaphore
	if (tools_cmdif_flash_lock(mf, 1)) {
		return ME_SEM_LOCKED;
	}
	int rc = tools_cmdif_send_cmd_int(mf, &cmdif);
	// release it
	tools_cmdif_flash_lock(mf, 0);
	*out_param = cmdif.out_param;
	*status = cmdif.status;
	return rc;
}

static int translate_status(int status) {
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
	default:
	    //fprintf(stderr, "-D- Unknown status: 0x%x\n", status);
		return ME_CMDIF_BAD_STATUS;
	}
}

static int tools_cmdif_mbox_read(mfile* mf, u_int32_t offset, u_int64_t* output)
{
	if (!mf || (offset & 0x1) != 0 || !output) {// offset should be quad word alligned (i.e only even dwords)
		return ME_BAD_PARAMS;
	}
	tools_cmdif cmdif;
	memset(&cmdif, 0, sizeof(tools_cmdif));
	//printf("-D- offset: 0x%x\n", offset>>2);
	cmdif.input_modifier = offset; // offset is in dwords
	cmdif.opcode = MBOX_READ_OP;

	int rc = tools_cmdif_send_cmd_int(mf, &cmdif);
	*output = cmdif.out_param;
	//printf("-D- outparam: 0x%lx\n", cmdif.out_param);
	if (rc || cmdif.status) {
		return rc ? rc : translate_status(cmdif.status);
	}
	//printf("-D- mbox read OK\n");
	return ME_OK;
}

static int tools_cmdif_mbox_write(mfile* mf, u_int32_t offset, u_int64_t input)
{
	if (!mf || (offset & 0x1) != 0) {// offset should be quad word alligned (i.e only even dwords)
		return ME_BAD_PARAMS;
	}
	tools_cmdif cmdif;
	memset(&cmdif, 0, sizeof(tools_cmdif));
	cmdif.in_param = input;
	cmdif.input_modifier = offset; // offset is in dwords
	cmdif.opcode = MBOX_WRITE_OP;

	int rc = tools_cmdif_send_cmd_int(mf, &cmdif);

	if (rc || cmdif.status) {
		return rc ? rc : translate_status(cmdif.status);
	}
	return ME_OK;
}

int tools_cmdif_query_dev_cap(mfile *mf, u_int32_t offset, u_int64_t* data)
{
	if (!mf || offset > (TOOLS_HCR_MAX_MBOX - 8)) {
		return ME_BAD_PARAMS;
	}
	// take semaphore
	if (tools_cmdif_flash_lock(mf, 1)) {
		return ME_SEM_LOCKED;
	}
	// run query_dev_cap cmd
	tools_cmdif cmdif;
	memset(&cmdif, 0, sizeof(tools_cmdif));
	cmdif.opcode = QUERY_DEV_CAP_OP;

	int rc = tools_cmdif_send_cmd_int(mf, &cmdif);

	if (rc || cmdif.status) {
		tools_cmdif_flash_lock(mf, 0);
		if (rc == ME_CMDIF_BAD_STATUS) {
			return translate_status(cmdif.status);
		}
		return rc;
	}
	// read offset from Mbox

	if (!data) { // if data is null we just check capability of the Tools HCR (i.e if its capable to execute query_dev_cap op)
		tools_cmdif_flash_lock(mf, 0);
		return ME_OK;
	}
	// offset needs to be in even dwords
	if (((offset >> 2) & 0x1) != 0) {
		return ME_BAD_PARAMS;
	}
	rc = tools_cmdif_mbox_read(mf, offset>>2, data);
	// free semaphore
	tools_cmdif_flash_lock(mf, 0);
	return rc;
}

/*
static void read_entire_mbox(mfile* mf)
{
	int i;
	int rc;
	u_int64_t val= 0;

	printf("-D- reading entire mailbox\n");

	for(i=0; i<256 ; i+=8) {
		rc = tools_cmdif_mbox_read(mf, i/4, &val);
		if (rc) {
			printf("-D- rc:%d\n", rc);
		}
		printf("-D- 0x%x\n", (u_int32_t)val);
		printf("-D- 0x%x\n", (u_int32_t)(val>>32));
	}
}


static void print_buffer(u_int8_t buffer[TOOLS_HCR_MAX_MBOX], const char* pre)
{
	int i;
	u_int32_t *ptr = (u_int32_t*)buffer;
	printf("-I- %s\n", pre);
	for (i=0; i< 16; i++) {
		printf("0x%x\n", ptr[i]);
	}
	return;
}
*/

int tools_cmdif_reg_access(mfile *mf, void* data, int write_data_size, int read_data_size)
{
	//printf("-D- write data sz: %d, read data sz: %d \n", write_data_size, read_data_size);
	if (!mf || !data || write_data_size > TOOLS_HCR_MAX_MBOX || read_data_size > TOOLS_HCR_MAX_MBOX) {
		return ME_BAD_PARAMS;
	}
	//take semaphore
	if (tools_cmdif_flash_lock(mf, 1)) {
		return ME_SEM_LOCKED;
	}
	int rc;
	// place the data inside 256 bytes buffer (init with zeroes) and write the entire buffer to mbox
	// it is required in the TOOLS_HCR HLD to write the ENTIRE MBOX
	u_int8_t buffer[TOOLS_HCR_MAX_MBOX] = {0};
	memcpy(buffer, data, write_data_size);
	// switch endianess as fw expects output in big endian
	TOCPUn(buffer, TOOLS_HCR_MAX_MBOX/4);
	int i;
	//print_buffer(buffer, "before sending sending");
	for (i=0 ; i< TOOLS_HCR_MAX_MBOX; i+=8) { // it is required to write in quad word chunks (64bits each time)
	    // on big endian cpu need to swap between the dwords in the quad word
	    u_int64_t val = swap_dwords_be((&buffer[i]));
		rc = tools_cmdif_mbox_write(mf, i/4, val);
		if (rc) {
			goto cleanup;
		}
	}
	// send access reg cmd
	tools_cmdif cmdif;
	memset(&cmdif, 0, sizeof(tools_cmdif));
	cmdif.opcode = REG_ACCESS_OP;
	rc = tools_cmdif_send_cmd_int(mf, &cmdif);

	if (rc || cmdif.status) {
		if (rc == ME_CMDIF_BAD_STATUS) {
			rc = translate_status(cmdif.status); // means that driver is down or we dont support the extended version of tools hcr.
		}
		goto cleanup;
	}
	// read read_data_size bytes from mbox and update our data
	for (i=0 ; i< read_data_size; i+=8) { // it is required to write in quad word chunks (64bits each time)
		rc = tools_cmdif_mbox_read(mf, i/4, (u_int64_t*)&(buffer[i]));
		// on big endian cpu need to swap back between the dwords in the quad word
		u_int64_t val = swap_dwords_be((&buffer[i]));
		memcpy(&(buffer[i]), (u_int8_t*)&val, 8*sizeof(u_int8_t));
		if (rc) {
			goto cleanup;
		}
	}

	//print_buffer(buffer, "after sending");
	// switch endianness back
	TOCPUn(buffer, TOOLS_HCR_MAX_MBOX/4);
	// copy data back to user
	memcpy(data, buffer, read_data_size);
	rc = ME_OK;
cleanup:
	tools_cmdif_flash_lock(mf, 0);
	//printf("-D- rc in cmdif: 0x%x\n", rc);
	return rc;
}

/*
int test_mbox(mfile* mf)
{
	u_int32_t data_w[8] = {1,2,3,4,5,6,7,8};
	u_int32_t data_r[8] = {0};
	//take semaphore
	if (tools_cmdif_flash_lock(mf, 1)) {
		return ME_SEM_LOCKED;
	}
	// write data to mbox
	printf("-D- writing data to Mbox.\n");
	int i;
	for(i = 0 ; i < 8/2 ; i++) {
		u_int64_t input = *(u_int64_t*)(&data_w[i*2]);
		printf("-D- attempting to write 0x%lx\n", input);
		int rc = tools_cmdif_mbox_write(mf, i*2,input);
		if (rc){
			tools_cmdif_flash_lock(mf, 0);
			return ME_CR_ERROR;
		}
	}
	// read data from mbox
	printf("-D- reading data from Mbox.\n");
	for (i = 0; i < 8/2 ; i++) {
		if (tools_cmdif_mbox_read(mf, i*2,(u_int64_t*)&data_r[i*2])) {
			tools_cmdif_flash_lock(mf, 0);
			return ME_CR_ERROR;
		}
	}
	// print what have been read
	for (i=0 ; i<8 ; i++) {
		printf("-D- 0x%x\n", data_r[i]);
	}

	tools_cmdif_flash_lock(mf, 0);
	return ME_OK;

}
*/

