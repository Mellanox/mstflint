
/*
 *
 * Copyright (c) 2013 Mellanox Technologies Ltd.  All rights reserved.
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
 *
 */


#ifndef _MVPD_H
#define _MVPD_H

#include <mtcr.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef _MSC_VER
#define MVPD_DLL_EXPORT __declspec(dllexport)
#else
#define MVPD_DLL_EXPORT
#endif

enum {
    MVPD_OK = 0,
    MVPD_ERR,
    MVPD_MEM_ERR,
    MVPD_BAD_PARAMS,
    MVPD_ACCESS_ERR,
    MVPD_FORMAT_ERR,
    MVPD_TRUNCATED,
    MVPD_BAD_CHECKSUM,
    MVPD_EMPTY,
    MVPD_END,
};

typedef enum {
    VPD_RO = 1 << 0, /* Read-only VPD tags type */
    VPD_RW = 1 << 1, /* Read-Write VPD tags type */
    VPD_ALL = VPD_RO | VPD_RW, /* Read All VPD tags */
} vpd_tags_type_t;

typedef struct vpd_tag {
    char id[3];   // Leave a slot for NULL termination
    int len;
    char *data;
    int offset;   // start of this tag in vpd address space
} vpd_tag_t;

typedef struct {
    int vpd_size;
    vpd_tag_t id;
    int ro_fields_size;
    vpd_tag_t *ro_fields;
    int rw_fields_size;
    vpd_tag_t *rw_fields;
} vpd_result_t;

MVPD_DLL_EXPORT int mvpd_get_vpd_size(mfile *mf, int *size);

MVPD_DLL_EXPORT int mvpd_read(mfile *mf, vpd_result_t **result, vpd_tags_type_t read_type);

MVPD_DLL_EXPORT int mvpd_read_adv(mfile *mf, vpd_result_t **result, vpd_tags_type_t read_type, int strict);

MVPD_DLL_EXPORT int mvpd_parse(u_int8_t *raw_vpd, int size, vpd_result_t **result, vpd_tags_type_t read_type);

MVPD_DLL_EXPORT int mvpd_parse_adv(u_int8_t *raw_vpd, int size, vpd_result_t **result, vpd_tags_type_t read_type, int strict, int checksum_verify);

MVPD_DLL_EXPORT int mvpd_result_free(vpd_result_t *result);

MVPD_DLL_EXPORT int mvpd_get_raw_vpd(mfile *mf, u_int8_t *raw_data_buf, int size);

#ifdef __cplusplus
}
#endif

#endif
