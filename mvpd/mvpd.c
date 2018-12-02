/*
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
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#ifdef MST_UL
#include <syslog.h>
#endif
#include "mvpd.h"

#if defined(__MINGW32__) || defined(__MINGW64__) || defined(_MSC_VER)    /* Windows */
#define syslog(lvl, format, ...)
#else
#include <syslog.h>
#endif

enum {
    INTERNAL_PARAMS_ERROR = 0x33444,
};

enum {
    VPD_TAG_ID = 0x02, /* Product name of the device */
    VPD_TAG_R = 0x10, /* Read-only keywords */
    VPD_TAG_W = 0x11, /* Read-write keywords */
    VPD_TAG_END = 0x0F /* End Tag */
};

#define VPD_MAX_SIZE 1 << 15

#define VPD_TAG_LARGE(a) (a[0] & 0x80)

#define VPD_TAG_NAME(a) (VPD_TAG_LARGE(a) ? (a[0] & 0x7F) : (a[0] >> 3))

#define VPD_TAG_LENGTH(a)  (VPD_TAG_LARGE(a) ? ((a[2] << 8) | (a[1])) : (a[0] & 0x7))

#define VPD_TAG_HEAD(a) (VPD_TAG_LARGE(a) ? 0x3 : 0x1)

#define VPD_TAG_DATA(d) (d + VPD_TAG_HEAD(d))

#define CONVERT(r) (r == VPD_RO ? VPD_TAG_R : VPD_TAG_W)

#if defined(_MSC_VER)
#define PACK( __declaration__ ) __pragma( pack(push, 1) ) __declaration__ __pragma( pack(pop) )
#else
#define PACK( __declaration__ ) __declaration__ __attribute__((__packed__))
#endif

PACK(
struct vpd_field {
    unsigned char keyword[2];
    unsigned char length;
    unsigned char data[0];
}); 


int my_vpd_read(mfile *mf,
                u_int8_t *raw_vpd,
                int raw_vpd_size,
                u_int8_t *buf,
                unsigned offset,
                int size)
{
    unsigned i;
    int ret;
    if (mf != NULL) {
        for (i = 0; (int)i < size; i += 0x4) {
            u_int8_t value[4] = {0};
            ret = mvpd_read4(mf, offset + i, value);
            if (ret) {
                syslog(3, "LIBMVPD: MVPD_READ4 failed on offset:%d, RC[%d]", offset, ret);
                return MVPD_ACCESS_ERR;
            }
            memcpy(buf + i, value, 4 * sizeof(u_int8_t));
        }
    } else if (raw_vpd != NULL) {
        if ((int)(offset + size) > raw_vpd_size) {
            size = raw_vpd_size - offset;
            if (size < 0) {
                return MVPD_TRUNCATED;
            }
        }
        memcpy(buf, raw_vpd + offset, size * sizeof(u_int8_t));
    } else {
        return INTERNAL_PARAMS_ERROR;
    }
    return MVPD_OK;
}

int mvpd_get_raw_vpd(mfile *mf, u_int8_t *raw_data_buf, int size)
{
    return my_vpd_read(mf, NULL, 0, raw_data_buf, 0, size);
}

int allocate_result(vpd_result_t **result)
{
    vpd_result_t *res;
    res = (vpd_result_t*) malloc(sizeof(vpd_result_t));
    if (res == NULL) {
        return MVPD_MEM_ERR;
    }
    memset(res, 0, sizeof(vpd_result_t));
    *result = res;
    return MVPD_OK;
}

int fill_id(vpd_result_t *result,
            u_int8_t *data,
            unsigned offset
            )
{
    vpd_tag_t id_tag;
    strcpy(id_tag.id, "ID");
    id_tag.len = VPD_TAG_LENGTH(data);
    id_tag.data = (char*) malloc(id_tag.len + 1);
    if (id_tag.data == NULL) {
        return MVPD_MEM_ERR;
    }
    memcpy(id_tag.data, VPD_TAG_DATA(data), id_tag.len);
    id_tag.data[id_tag.len] = '\0';
    id_tag.offset = offset;
    result->id = id_tag;
    result->vpd_size += VPD_TAG_LENGTH(data);
    return MVPD_OK;
}

int fill_fields(vpd_result_t *result,
                u_int8_t *data,
                unsigned offset,
                int read_type,
                unsigned *checksum_offset,
                int strict)
{
    int i;
    int fields_num = 0;
    int fields_idx = 0;
    vpd_tag_t id_tag;
    vpd_tag_t *fields_list;
    struct vpd_field *field = NULL;
    if (read_type == VPD_TAG_R) {
        if (result->ro_fields_size != 0) {
            syslog(3, "LIBMVPD: Format error RO fields !");
            return MVPD_FORMAT_ERR;
        }
    } else {
        if (result->rw_fields_size != 0) {
            syslog(3, "LIBMVPD: Format error RW fields !");
            return MVPD_FORMAT_ERR;
        }
    }
    for (i = 0; i < VPD_TAG_LENGTH(data); i += 0x3 + field->length) {
        field = (struct vpd_field*) (VPD_TAG_DATA(data) + i);
        if (strict) {
            if (i + 0x3 > VPD_TAG_LENGTH(data) ||  i + 0x3 + field->length > VPD_TAG_LENGTH(data)) {
                fprintf(stderr, "-E- In tag %s offset 0x%x+0x%x there is an invalid field (keyword: 0x%x).\n",
                        VPD_TAG_NAME(data) == VPD_TAG_R ? "VPD_R" : "VPD_W", offset, i, field->keyword[0]);
                return MVPD_FORMAT_ERR;
            }
        }
        fields_num++;
    }
    fields_list = (vpd_tag_t*) malloc(fields_num * sizeof(vpd_tag_t));
    if (fields_list == NULL) {
        return MVPD_MEM_ERR;
    }
    for (i = 0; i < VPD_TAG_LENGTH(data); i += 0x3 + field->length) {
        field = (struct vpd_field*) (VPD_TAG_DATA(data) + i);
        id_tag.id[0] = field->keyword[0];
        id_tag.id[1] = field->keyword[1];
        id_tag.id[2] = '\0';
        if (strict && ( strlen(id_tag.id) == 0 ||
                      !isprint(field->keyword[0]) ||
                      !isprint(field->keyword[1]))) {
            // fail if keywords are non printable/empty if strict==1 (indicates corrupt VPD)
            free(fields_list);
            return MVPD_FORMAT_ERR;
        }
        id_tag.len = field->length;
        id_tag.data = (char*) malloc(id_tag.len + 1);
        if (id_tag.data == NULL) {
            free(fields_list);
            return MVPD_MEM_ERR;
        }
        memcpy(id_tag.data, field->data, id_tag.len);
        id_tag.data[id_tag.len] = '\0';
        id_tag.offset = offset + i + VPD_TAG_HEAD(data);
        if (strcmp(id_tag.id, "RV") == 0) {
            *checksum_offset = id_tag.offset + 0x3; /* 0x3 is the header of the field */
        }
        //syslog(3, "LIBMVPD: Filed TAG: %s, data: %s", id_tag.id, id_tag.data);
        fields_list[fields_idx++] = id_tag;
    }
    if (read_type == VPD_TAG_R) {
        result->ro_fields_size += fields_num;
        result->ro_fields = fields_list;
    } else {
        result->rw_fields_size += fields_num;
        result->rw_fields = fields_list;
    }
    return MVPD_OK;
}

int check_checksum(u_int8_t *id_data,
                   int id_size,
                   u_int8_t *ro_data,
                   unsigned rv_offset)
{

    int i;
    u_int8_t sum = 0;
    //printf("-D- RV OFF: 0x%x, id_size: %x\n", rv_offset, id_size);
    if ((int)rv_offset < id_size) {
        return MVPD_BAD_CHECKSUM;
    }
    for (i = 0; i < id_size; i++) {
        sum += id_data[i];
    }
    for (i = 0; i <= (int)(rv_offset - id_size); i++) {
        sum += ro_data[i];
    }
    if (sum) {
        return MVPD_BAD_CHECKSUM;
    }
    return MVPD_OK;
}

#define CHECK_RC(rc) do {if (rc) {goto error;}} while (0)
#define CHECK_NULL(ptr) do {if (NULL == ptr) {goto error;}} while (0)


int mvpd_read_or_parse(mfile *mf,
                       u_int8_t *raw_vpd,
                       int raw_vpd_size,
                       vpd_result_t **result,
                       vpd_tags_type_t read_type,
                       int strict,
                       int checksum_verify)
{
    struct vpd_tags_info_t {
        unsigned id_tag_offset;
        int id_tag_len;
        unsigned ro_tag_offset;
        int ro_tag_len;
        unsigned rw_tag_offset;
        int rw_tag_len;
    };
    struct vpd_tags_info_t vpd_tags_info = { .id_tag_len = -1, .ro_tag_len = -1, .rw_tag_len = -1};
    u_int8_t buff[4] = {0};
    unsigned offset = 0;
    unsigned checksum_offset = 0;
    u_int8_t *id_data = NULL;
    u_int8_t *ro_data = NULL;
    u_int8_t *rw_data = NULL;
    int checksum_res = -1;
    int rc = MVPD_MEM_ERR;
    unsigned actual_size = 1 << 15; /*MAX SIZE OF VPD */
    int len = 0;
    if (raw_vpd != NULL) {
        actual_size = raw_vpd_size;
    }
    if (allocate_result(result)) {
        return MVPD_MEM_ERR;
    }
    for (offset = 0; offset < actual_size; offset += len) {
        rc = my_vpd_read(mf, raw_vpd, raw_vpd_size, buff, offset, 4); CHECK_RC(rc);
        len = VPD_TAG_HEAD(buff) + VPD_TAG_LENGTH(buff);
        if (VPD_TAG_NAME(buff) == VPD_TAG_END) {
            break;
        } else if (VPD_TAG_NAME(buff) == VPD_TAG_ID) {
            vpd_tags_info.id_tag_len = len;
            vpd_tags_info.id_tag_offset = offset;
        } else if (VPD_TAG_NAME(buff) == VPD_TAG_R) {
            vpd_tags_info.ro_tag_len = len;
            vpd_tags_info.ro_tag_offset = offset;
        } else if (VPD_TAG_NAME(buff) == VPD_TAG_W) {
            vpd_tags_info.rw_tag_len = len;
            vpd_tags_info.rw_tag_offset = offset;
        } else {
            syslog(3, "LIBMVPD: Unknown TAG %x in offset: %x !", VPD_TAG_NAME(buff), offset);
            rc = MVPD_FORMAT_ERR;
            goto error;
        }
    }
    if (offset == 0) {
        rc = MVPD_EMPTY;
        goto error;
    }
    if (vpd_tags_info.ro_tag_len <= 0 || vpd_tags_info.id_tag_len <= 0) {
        rc = MVPD_FORMAT_ERR;
        goto error;
    }
    if (read_type & VPD_RO) {
        /* TAKE THE ID TAG */
        //syslog(3, "LIBMVPD: Reading VPD RO SECTION");
        int id_len = vpd_tags_info.id_tag_len;
        int ro_len = vpd_tags_info.ro_tag_len;
        int read_size = (id_len + 3) & ~3;
        size_t alocated_read_size = read_size * sizeof(u_int8_t);
        offset = vpd_tags_info.id_tag_offset;
        id_data = (u_int8_t*) malloc(alocated_read_size);
        CHECK_NULL(id_data);
        memset(id_data, 0, alocated_read_size);
        rc = my_vpd_read(mf, raw_vpd, raw_vpd_size, id_data, offset, read_size); CHECK_RC(rc);
        rc = fill_id(*result, id_data, offset); CHECK_RC(rc);
        (*result)->vpd_size += id_len;
        /* TAKE THE RO FIELDS */
        read_size = (ro_len + 3) & ~3;
        alocated_read_size = read_size * sizeof(u_int8_t);
        offset = vpd_tags_info.ro_tag_offset;
        ro_data = (u_int8_t*) malloc(alocated_read_size);
        CHECK_NULL(ro_data);
        memset(ro_data, 0, alocated_read_size);
        rc = my_vpd_read(mf, raw_vpd, raw_vpd_size, ro_data, offset, read_size); CHECK_RC(rc);
        //syslog(3, "LIBMVPD: Reading VPD RO Done, filling fields !");
        rc = fill_fields(*result, ro_data, offset, VPD_TAG_NAME(ro_data), &checksum_offset, strict); CHECK_RC(rc);
        //syslog(3, "LIBMVPD: Filling fields done, checking CHECKSUM: %d!", checksum_offset);
        (*result)->vpd_size += ro_len;
        checksum_res = check_checksum(id_data, id_len, ro_data, checksum_offset);
        //syslog(3, "LIBMVPD: checking CHECKSUM Done !");
        free(ro_data); ro_data = NULL;
        free(id_data); id_data = NULL;
    }

    if ((read_type & VPD_RW) && vpd_tags_info.rw_tag_len > 0) {
        //syslog(3, "LIBMVPD: Reading VPD RW SECTION");
        int len = vpd_tags_info.rw_tag_len;
        int read_size = (len + 3) & ~3;
        size_t allocated_rw_size = read_size * sizeof(u_int8_t);
        offset = vpd_tags_info.rw_tag_offset;
        rw_data = (u_int8_t*) malloc(allocated_rw_size);
        CHECK_NULL(rw_data);
        memset(rw_data, 0, allocated_rw_size);
        rc = my_vpd_read(mf, raw_vpd, raw_vpd_size, rw_data, offset, read_size); CHECK_RC(rc);
        rc = fill_fields(*result, rw_data, offset, VPD_TAG_NAME(rw_data), &checksum_offset, strict); CHECK_RC(rc);
        (*result)->vpd_size += len;
        free(rw_data);
    }
    /* If the RO field were read check the checksum */
    if (checksum_verify && checksum_res != -1) {
        return checksum_res;
    }
    return MVPD_OK;

error:
    if (id_data != NULL) {
        free(id_data);
    }
    if (ro_data != NULL) {
        free(ro_data);
    }
    if (rw_data != NULL) {
        free(rw_data);
    }
    mvpd_result_free(*result);
    return rc;

}

int mvpd_read(mfile *mf,
              vpd_result_t **result,
              vpd_tags_type_t read_type)
{
    return mvpd_read_adv(mf, result, read_type, 0);
}

int mvpd_read_adv(mfile *mf,
                  vpd_result_t **result,
                  vpd_tags_type_t read_type,
                  int strict)
{
    if (mf == NULL || result == NULL) {
        return MVPD_BAD_PARAMS;
    }
    return mvpd_read_or_parse(mf, NULL, -1, result, read_type, strict, 0);
}

int mvpd_parse(u_int8_t *raw_vpd,
               int size,
               vpd_result_t **result,
               vpd_tags_type_t read_type)
{
    return mvpd_parse_adv(raw_vpd, size, result, read_type, 0, 0);
}

int mvpd_parse_adv(u_int8_t *raw_vpd,
                   int size,
                   vpd_result_t **result,
                   vpd_tags_type_t read_type,
                   int strict,
                   int checksum_ver)
{
    if (raw_vpd == NULL || size <= 0 || result == NULL) {
        return MVPD_BAD_PARAMS;
    }
    return mvpd_read_or_parse(NULL, raw_vpd, size, result, read_type, strict, checksum_ver);
}

void free_fields(vpd_tag_t *fields_list,
                 int len)
{
    int i;
    for (i = 0; i < len; i++) {
        free(fields_list[i].data);
    }
    free(fields_list);
}

int mvpd_result_free(vpd_result_t *result)
{
    if (result == NULL) {
        return 1;
    }
    if (result->ro_fields != NULL) {
        free_fields(result->ro_fields, result->ro_fields_size);
    }
    if (result->rw_fields != NULL) {
        free_fields(result->rw_fields, result->rw_fields_size);
    }
    if (result->id.data != NULL) {
        free(result->id.data);
    }
    free(result);
    return MVPD_OK;
}

int mvpd_get_vpd_size(mfile *mf, int *size)
{
    int mvpd_len;
    int len = 0;
    u_int8_t buff[4] = {0};
    int res;

    for (mvpd_len = 0; mvpd_len < VPD_MAX_SIZE; mvpd_len += len) {
        res = my_vpd_read(mf, NULL, 0, buff, mvpd_len, 4);
        if (res != MVPD_OK) {
            return res;
        }
        len = VPD_TAG_HEAD(buff) + VPD_TAG_LENGTH(buff);
        if (VPD_TAG_NAME(buff) == VPD_TAG_END) {
            break;
        }
        if (VPD_TAG_NAME(buff) != VPD_TAG_ID && VPD_TAG_NAME(buff) != VPD_TAG_R && VPD_TAG_NAME(buff) != VPD_TAG_W) {
            syslog(3, "LIBMVPD: Unknown TAG %x in offset: %x !", VPD_TAG_NAME(buff), mvpd_len);
            return MVPD_FORMAT_ERR;
        }
    }
    *size = mvpd_len;
    return 0;
}

