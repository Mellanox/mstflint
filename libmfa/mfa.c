/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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
#include "mfa.h"
#include "mfa_section.h"
#include "mfaerr.h"

#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <compatibility.h>

//                                         0x(major)(minor)
//                           0x00000001;  #0x(0000)(0001)
#define MLXA_VERSION         0x00000001
#define MFA_HDR_SZ           16
#define MAP_SECTION_OFFSET   MFA_HDR_SZ

#define CHECK_PTR(p) do { if (p == NULL) {return _ERR(MFA_ERR_MEM_ALLOC);}} while (0)
#define CHECK_RC(rc) do { if (rc < 0) {return rc;}} while (0)
#define _ERR(errcode) (-errcode)
#define _ERR_STR(des, errcode, ...) (sprintf((des->err_str), __VA_ARGS__), -errcode)


struct mfa_desc {
    int bufsz;
    u_int8_t *buffer;
    u_int8_t *map;
    u_int8_t *toc;
    u_int8_t *data_ptr;
    int open_method;
    char err_str[256];
};


enum mfa_open_methods {
    MFA_OPEN_BUF,
    MFA_OPEN_FILE
};


enum header_types {
    IMAGES_HEADER,
    PSID_HEADER
};


int mfa_verify_archive(u_int8_t *buf, long sz);
int mfa_read_map(mfa_desc *mfa_d);
int parse_section_header(char *buf, int len, int *header_type, int *nrecs);
int mfa_read_toc(struct mfa_desc *mfa_d);


static int _mfa_open_buf(mfa_desc **mfa_d, u_int8_t *arbuf, int size)
{
    int res = 0;

    *mfa_d = (mfa_desc*)malloc(sizeof(mfa_desc));
    if (!(*mfa_d)) {
        return _ERR(MFA_ERR_MEM_ALLOC);
    }
    memset(*mfa_d, 0, sizeof(mfa_desc));

    if ((res = mfa_verify_archive(arbuf, size))) {
        goto clean_up;
    }

    (*mfa_d)->buffer = arbuf;
    (*mfa_d)->bufsz = size;

    if ((res = mfa_read_map(*mfa_d)) < 0) {
        goto clean_up;
    }
    if ((res = mfa_read_toc(*mfa_d)) < 0) {
        goto clean_up_map;
    }

    return MFA_OK;

clean_up_map:
    free((*mfa_d)->map);
clean_up:
    free(*mfa_d);
    return res;
}

void mfa_init()
{
    mfasec_init();
}


int mfa_open_buf(mfa_desc **mfa_d, u_int8_t *arbuf, int size)
{
    int res;

    res = _mfa_open_buf(mfa_d, arbuf, size);
    if (res == MFA_OK) {
        (*mfa_d)->open_method = MFA_OPEN_BUF;
    }
    return res;
}


int mfa_open_file(mfa_desc **mfa_d, char *fname)
{
    int res = MFA_OK;
    FILE *fp;
    u_int8_t *buf = NULL, *tmp_buf;
    long int fsize;
    long int sz;

    if ((fp = fopen(fname, "rb")) == NULL) {
        return _ERR(MFA_ERR_FILE_OPEN);
    }

    if (fseek(fp, 0L, SEEK_END)) {
        res = _ERR(MFA_ERR_FSEEK);
        goto err_clean_up;
    }
    if ((fsize = ftell(fp)) <= 0) {
        res = _ERR(MFA_ERR_FTELL);
        goto err_clean_up;
    }
    rewind(fp);

    buf = (u_int8_t*)malloc(fsize * sizeof(u_int8_t));
    if (buf == NULL) {
        res = _ERR(MFA_ERR_MEM_ALLOC);
        goto err_clean_up;
    }
    memset(buf, 0, fsize);
    tmp_buf = buf;
    sz = fread(tmp_buf, 1, fsize, fp);

    if (sz != fsize || sz <= 0 || tmp_buf == NULL) {
        res = _ERR(MFA_ERR_FILE_READ);
        goto err_clean_up;
    }

    if ((res = _mfa_open_buf(mfa_d, buf, fsize)) != MFA_OK) {
        goto err_clean_up;
    }

    fclose(fp);
    (*mfa_d)->open_method = MFA_OPEN_FILE;

    return MFA_OK;

err_clean_up:
    fclose(fp);
    if (buf != NULL) {
        free(buf);
    }
    return res;
}


int mfa_close(struct mfa_desc *mfa_d)
{
    if (mfa_d->map != NULL) {
        free(mfa_d->map);
        mfa_d->map = NULL;
    }
    if (mfa_d->open_method == MFA_OPEN_FILE) {
        free(mfa_d->buffer);
        mfa_d->buffer = NULL;
    }
    if (mfa_d->toc != NULL) {
        free(mfa_d->toc);
        mfa_d->toc = NULL;
    }
    free(mfa_d);
    return MFA_OK;
}


int mfa_verify_archive(u_int8_t *buf, long sz)
{
    int i;
    u_int32_t crc;
    u_int32_t ar_crc;
    u_int32_t ver;
    u_int32_t major;
    u_int32_t minor;
    u_int32_t mlx_major = (MLXA_VERSION & 0xFFFF0000 ) >> 16;
    u_int32_t mlx_minor = (MLXA_VERSION & 0x0000FFFF );
    char signature[] = {'M', 'F', 'A', 'R'};

    if (sz < 16) {
        return _ERR(MFA_ERR_ARCHV_FORMAT);
    }

    //Check signature
    for (i = 0; i < 4; i++) {
        if (signature[i] != buf[i]) {
            return _ERR(MFA_ERR_ARCHV_SIGNATURE);
        }
    }

    //Check version
    ver   = *((u_int32_t*)&buf[4]);
    ver   = __be32_to_cpu(ver);
    major = (ver & 0xFFFF0000 ) >> 16;
    minor = (ver & 0x0000FFFF );
    (void) mlx_minor;
    (void) minor;
    if (major > mlx_major) {
        return _ERR(MFA_ERR_ARCHV_VER_UNSUPP);
    }

    //Archive CRC
    ar_crc = *((u_int32_t*)&buf[sz - 4]);
    ar_crc = __be32_to_cpu(ar_crc);

    crc = mfasec_crc32(buf, sz - 4, 0);
    if (crc != ar_crc) {
        //printf("CRC32 = %08x expected = %08x\n", crc, ar_crc);
        return _ERR(MFA_ERR_ARCHV_CRC);
    }

    return MFA_OK;
}


int mfa_get_crc32(u_int8_t *arbuf, long sz, u_int32_t *ar_crc, u_int32_t *calc_crc)
{
    *ar_crc = *((u_int32_t*)&arbuf[sz - 4]);
    *ar_crc = __be32_to_cpu(*ar_crc);

    *calc_crc = mfasec_crc32(arbuf, sz - 4, 0);

    return MFA_OK;
}


int mfa_read_map(struct mfa_desc *mfa_d)
{
    u_int8_t *buf;
    int res;

    section_hdr *map_hdr = (section_hdr*) &mfa_d->buffer[MAP_SECTION_OFFSET];

    res = mfasec_get_map(&mfa_d->buffer[MAP_SECTION_OFFSET], __be32_to_cpu(map_hdr->size) + sizeof(section_hdr), &buf);
    if (res < 0) {
        goto clean_up;
    }

    mfa_d->map = buf;

clean_up:
    return res;
}


int mfa_read_toc(struct mfa_desc *mfa_d)
{
    u_int8_t *buf;
    int res;

    section_hdr *map_hdr = (section_hdr*) &mfa_d->buffer[MAP_SECTION_OFFSET];
    section_hdr *toc_hdr = (section_hdr*) &mfa_d->buffer[MAP_SECTION_OFFSET + __be32_to_cpu(map_hdr->size) + sizeof(section_hdr)];
    mfa_d->data_ptr = &mfa_d->buffer[MAP_SECTION_OFFSET + __be32_to_cpu(map_hdr->size) + 2 * sizeof(section_hdr) + __be32_to_cpu(toc_hdr->size)];

    res = mfasec_get_toc((u_int8_t*)toc_hdr, __be32_to_cpu(toc_hdr->size) + sizeof(section_hdr), &buf);
    if (res < 0) {
        goto clean_up;
    }

    mfa_d->toc = buf;

clean_up:
    return res;
}


int mfa_map_get_num_images(map_entry_hdr *me)
{
    return me->nimages;
}


const char* mfa_map_get_metadata(map_entry_hdr *me)
{
    if (me->metadata_size == 0) {
        return "";
    }
    char *ptr = (char*)me;
    ptr += sizeof(map_entry_hdr);
    return ptr;
}


map_image_entry* mfa_get_map_image(map_entry_hdr *me, int image_index)
{
    u_int8_t *ptr = (u_int8_t*) me;
    if (image_index >= me->nimages) {
        return NULL;
    }
    ptr += sizeof(map_entry_hdr);
    ptr += me->metadata_size;
    map_image_entry *img_e = (map_image_entry*)ptr;
    return (map_image_entry*) &img_e[image_index];
}


toc_entry* mfa_get_image_toc(mfa_desc *mfa_d, map_image_entry *img_e)
{
    toc_entry *toc_e = (toc_entry*) &mfa_d->toc[img_e->toc_offset + sizeof(section_hdr)];
    return (toc_entry*) toc_e;
}


map_entry_hdr* mfa_get_map_entry(mfa_desc *mfa_d, char *board_type_id)
{
    u_int8_t *map = mfa_d->map;
    section_hdr *map_hdr = (section_hdr*) map;
    ssize_t pos = sizeof(section_hdr);
    ssize_t total = sizeof(section_hdr) + map_hdr->size;

    while (pos < total) {
        map_entry_hdr *map_entry = (map_entry_hdr*)&map[pos];
        int n = map_entry->nimages;
        if (strcmp(map_entry->board_type_id, board_type_id) != 0) {
            pos += sizeof(map_entry_hdr);
            pos += map_entry->metadata_size; //metadata length
            pos += n * sizeof(map_image_entry);
            continue;
        }
        return map_entry;
    }

    return NULL;
}


map_entry_hdr* mfa_get_next_mentry(mfa_desc *mfa_d, map_entry_hdr *curr_me)
{
    ssize_t pos;
    ssize_t total;
    int n;
    map_entry_hdr *next_me = NULL;
    u_int8_t *map = mfa_d->map;
    section_hdr *map_hdr = (section_hdr*) map;

    total = sizeof(section_hdr) + map_hdr->size;

    if (curr_me == NULL) {
        pos = sizeof(section_hdr);
        next_me = (map_entry_hdr*)&map[pos];
        return next_me;
    }

    pos = (ssize_t) (((u_int8_t*)curr_me) - map);

    n = curr_me->nimages;
    pos += sizeof(map_entry_hdr);
    pos += curr_me->metadata_size; //metadata length
    pos += n * sizeof(map_image_entry);

    if (pos < total) {
        next_me = (map_entry_hdr*)&map[pos];
    }

    return next_me;
}


char* mfa_get_map_entry_metadata(map_entry_hdr *map_entry, char *key)
{
    u_int16_t count;
    u_int16_t i;
    char *ptr;
    metadata_hdr *md_hdr;
    char *val;

    ptr = (char*)map_entry;
    ptr += sizeof(map_entry_hdr);

    //ptr points at beginning of metadata section
    md_hdr = (metadata_hdr*)ptr;
    ptr += sizeof(metadata_hdr);

    if (map_entry->metadata_size == 0) {
        return NULL;
    }
    if (md_hdr->type != MDT_KEY_VALUE_PAIR) {
        return NULL;
    }

    count = md_hdr->modifier;

    for (i = 0; i < count; i++) {
        if (strcmp(ptr, key) == 0) {
            break;
        }
        if (i == (count - 1)) {
            return NULL;
        }
        ptr += strlen(ptr) + 1;
        ptr += strlen(ptr) + 1;
    }

    ptr += strlen(ptr) + 1;
    val = strdup(ptr);

    return val;
}


char* mfa_get_board_metadata(mfa_desc *mfa_d, char *board_type_id, char *key)
{
    map_entry_hdr *map_entry = mfa_get_map_entry(mfa_d, board_type_id);
    if (map_entry == NULL) {
        return NULL;
    }
    return mfa_get_map_entry_metadata(map_entry, key);
}


ssize_t mfa_get_image(mfa_desc *mfa_d, char *board_type_id, u_int8_t type, char *selector_tag, u_int8_t **buffer)
{
    int i;
    ssize_t res;
    ssize_t accum_size;
    int last_group_id = -1;
    map_image_entry *map_img;
    map_entry_hdr *map_entry = mfa_get_map_entry(mfa_d, board_type_id);
    if (map_entry == NULL) {
        return _ERR_STR(mfa_d, MFA_ERR_NO_ENTRY, "Entry not found for Board Type ID = %s", board_type_id);
    }

    *buffer = NULL;
    int n = mfa_map_get_num_images(map_entry);
    ssize_t total_size = 0;

    toc_entry **toce_ar;
    int toce_num = 0;
    if (n > 0) {
        toce_ar = (toc_entry**) malloc(sizeof(toc_entry*) * n);
        if (toce_ar == NULL) {
            return _ERR_STR(mfa_d, MFA_ERR_MEM_ALLOC, "Failed to allocate %u bytes of memory", (unsigned)(sizeof(toc_entry) * n));
        }
    } else {
        return _ERR_STR(mfa_d, MFA_ERR_ARCHV_FORMAT, "Didn't expect zero images for board type ID=%s", board_type_id);
    }

    for (i = 0; i < n; i++) {
        map_img = mfa_get_map_image(map_entry, i);
        if (map_img->image_type == type) {
            if (map_img->select_tag[0] != 0) {
                if (selector_tag == NULL) {
                    continue;
                }
                if (strncmp(map_img->select_tag, selector_tag, 32) != 0) {
                    continue;
                }
            }
            if (last_group_id == map_img->group_id) {
                continue;
            }
            last_group_id = map_img->group_id;
            toc_entry *toc_e = mfa_get_image_toc(mfa_d, map_img);
            toce_ar[toce_num] = toc_e;
            toce_num++;
            total_size += toc_e->data_size;
        }
    }

    if (toce_num == 0) {
        res = _ERR_STR(mfa_d, MFA_ERR_NO_ENTRY, "Image not found for board type ID=%s with type=%d and selector_tag=%s", board_type_id, type, selector_tag);
        goto img_alloc_clean_up;
    } else {
        *buffer = (u_int8_t*) malloc(total_size);
        if (*buffer == NULL) {
            res = _ERR_STR(mfa_d, MFA_ERR_MEM_ALLOC, "Failed to allocate %u memory", (unsigned)total_size);
            goto clean_up;
        }
    }

    accum_size = 0;
    for (i = 0; i < toce_num; i++) {
        if (toce_ar[i]->data_size == 0) {
            continue;
        }
        int rc = mfasec_get_data_chunk(mfa_d->data_ptr, (mfa_d->buffer + mfa_d->bufsz) - mfa_d->data_ptr, toce_ar[i]->data_offset,
                                       toce_ar[i]->data_size, &((*buffer)[accum_size]));
        if (rc < 0) {
            res = _ERR_STR(mfa_d, -rc, "Failed to get image");
            goto img_alloc_clean_up;
        }
        accum_size += toce_ar[i]->data_size;
    }

    res = total_size;
    goto clean_up;

img_alloc_clean_up:
    free(*buffer);

clean_up:
    free(toce_ar);

    return res;
}


void mfa_release_image(u_int8_t *buffer)
{
    free(buffer);
}


const char* mfa_get_last_error(mfa_desc *mfa_d)
{
    return mfa_d->err_str;
}

