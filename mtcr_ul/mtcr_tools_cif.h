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

#ifndef _MTCR_TOOLS_CIF     /* guard */
#define _MTCR_TOOLS_CIF

#ifdef __cplusplus
extern "C" {
#endif


#include <compatibility.h>
#ifdef MST_UL_ICMD
#include <mtcr_int_defs.h>
#endif
#include <mtcr.h>

#define FLASH_REG_ACCESS	0x9001

#define TOOLS_HCR_MAX_MBOX 256

// tools flash semaphore (62) will be taken at the begining of each command specified here
// and released at the end of the command.


/*
 * send a command to the tools HCR
 * limitations:
 * command should not use mailbox (not supported atm)
 */
int tools_cmdif_send_cmd(mfile* mf,
					 u_int64_t in_param,
					 u_int64_t* out_param,
					 u_int32_t input_modifier,
					 u_int16_t opcode,
					 u_int8_t  opcode_modifier,
					 u_int8_t*  status);


/*
 * register access tools HCR
 *
 * data: 			the raw register data
 * write_data_size:	amount of data to write to the mailbox (rest assumed to be zero)
 * read_data_size:	amount of data to be read from the mailbox
 *
 * data will contain the updated register.
 */

int tools_cmdif_reg_access(mfile *mf, void* data,int write_data_size, int read_data_size);

#ifdef __cplusplus
}
#endif

#endif  /* _MTCR_TOOLS_CIF guard */
