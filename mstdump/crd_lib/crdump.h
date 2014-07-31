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

#ifndef _CRDUMP_H_
#define _CRDUMP_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mtcr.h>


#ifdef __cplusplus
extern "C" {
#endif

enum crd_return_code {
    CRD_OK = 0,
    CRD_MEM_ALLOCATION_ERR,
    CRD_CR_READ_ERR,
    CRD_INVALID_PARM,
    CRD_UNKOWN_DEVICE,
    CRD_CSV_BAD_FORMAT,
    CRD_CONF_BAD_FORMAT,
    CRD_OPEN_FILE_ERROR,
    CRD_SKIP,
    CRD_NOT_SUPPORTED,
    CRD_EXCEED_VALUE,
    CRD_CAUSE_BIT,
};


typedef struct crd_ctxt crd_ctxt_t;

typedef struct crd_dword {
    u_int32_t addr;
    u_int32_t data;
} crd_dword_t;


typedef void (*crd_callback_t) (crd_dword_t *); // call back


#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#ifndef INOUT
#define INOUT
#endif

/*

Must be called before others methods to allocat memory and store all needed configuration

 */
int crd_init(OUT crd_ctxt_t **context, IN mfile *mf, IN int is_full, IN int cause, IN int cause_off); // fill device type, and number of dewords according to the is_full

/*
Store cr space length at arr_size
 */
int crd_get_dword_num(IN crd_ctxt_t *context, OUT u_int32_t *arr_size);


/*
Store all addresses are dword_arr array
 */
int crd_get_addr_list(IN crd_ctxt_t *context, OUT crd_dword_t* dword_arr); // caller well allocate the array and addresses will be filled.

/*
Store all addresses and data in dword_arr, if func is not null, it will be called on each dword
 */
int crd_dump_data(IN crd_ctxt_t *context, OUT crd_dword_t* dword_arr, IN crd_callback_t func);// values will be filled.

/*
Return string representation of the error code
 */
const char* crd_err_str(int rc);

/*
Free context
 */
void crd_free(IN crd_ctxt_t *context);

#ifdef __cplusplus
}
#endif

#endif // _CRDUMP_H_
