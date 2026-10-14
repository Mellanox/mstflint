/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include "common/tools_endianness.h"
#ifndef NO_OPEN_SSL
#include "mlxsign_lib/mlxsign_aesctr_c.h"
#include <openssl/sha.h>
#endif

//                                         0x(major)(minor)
//                           0x00000001;  #0x(0000)(0001)
#define MLXA_VERSION 0x00000001
#define MFA_HDR_SZ 16
#define MAP_SECTION_OFFSET MFA_HDR_SZ

#define CHECK_PTR(p)                        \
    do                                      \
    {                                       \
        if (p == NULL)                      \
        {                                   \
            return _ERR(MFA_ERR_MEM_ALLOC); \
        }                                   \
    } while (0)
#define CHECK_RC(rc)   \
    do                 \
    {                  \
        if (rc < 0)    \
        {              \
            return rc; \
        }              \
    } while (0)
#define _ERR(errcode) (-errcode)
#define _ERR_STR(des, errcode, ...) (sprintf((des->err_str), __VA_ARGS__), -errcode)

struct mfa_desc
{
    int bufsz;
    u_int8_t* buffer;
    u_int8_t* map;
    u_int8_t* toc;
    u_int8_t* data_ptr;
    int open_method;
    char err_str[256];
    // Persistent forward reader over the (XZ) DATA section:
    xzhandle_t* data_decompressor; /* open forward XZ decoder */
    u_int8_t* data_window;         /* fixed-size scratch buffer (capacity = MFA_DATA_WINDOW_SIZE) */
    size_t data_window_len;        /* number of valid bytes the last refill produced (<= capacity) */
    size_t data_window_pos;        /* how many of those valid bytes we've already consumed */
    u_int64_t data_pos;            /* absolute decompressed position of data_window[data_window_pos] */
};

#define MFA_DATA_WINDOW_SIZE 8192

enum mfa_open_methods
{
    MFA_OPEN_BUF,
    MFA_OPEN_FILE
};

enum header_types
{
    IMAGES_HEADER,
    PSID_HEADER
};

int mfa_verify_archive(u_int8_t* buf, long sz);
int mfa_read_map(mfa_desc* mfa_d);
int parse_section_header(char* buf, int len, int* header_type, int* nrecs);
int mfa_read_toc(struct mfa_desc* mfa_d);

static int _mfa_open_buf(mfa_desc** mfa_d, u_int8_t* arbuf, int size)
{
    int res = 0;

    *mfa_d = (mfa_desc*)malloc(sizeof(mfa_desc));
    if (!(*mfa_d))
    {
        return _ERR(MFA_ERR_MEM_ALLOC);
    }
    memset(*mfa_d, 0, sizeof(mfa_desc));

    if ((res = mfa_verify_archive(arbuf, size)))
    {
        goto clean_up;
    }

    (*mfa_d)->buffer = arbuf;
    (*mfa_d)->bufsz = size;

    if ((res = mfa_read_map(*mfa_d)) < 0)
    {
        goto clean_up;
    }
    if ((res = mfa_read_toc(*mfa_d)) < 0)
    {
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

int mfa_open_buf(mfa_desc** mfa_d, u_int8_t* arbuf, int size)
{
    int res;

    res = _mfa_open_buf(mfa_d, arbuf, size);
    if (res == MFA_OK)
    {
        (*mfa_d)->open_method = MFA_OPEN_BUF;
    }
    return res;
}

int mfa_open_file(mfa_desc** mfa_d, const char* fname)
{
    int res = MFA_OK;
    FILE* fp;
    u_int8_t *buf = NULL, *tmp_buf;
    long int fsize;
    long int sz;

    if ((fp = fopen(fname, "rb")) == NULL)
    {
        return _ERR(MFA_ERR_FILE_OPEN);
    }

    if (fseek(fp, 0L, SEEK_END))
    {
        res = _ERR(MFA_ERR_FSEEK);
        goto err_clean_up;
    }
    if ((fsize = ftell(fp)) <= 0)
    {
        res = _ERR(MFA_ERR_FTELL);
        goto err_clean_up;
    }
    rewind(fp);

    buf = (u_int8_t*)malloc(fsize * sizeof(u_int8_t));
    if (buf == NULL)
    {
        res = _ERR(MFA_ERR_MEM_ALLOC);
        goto err_clean_up;
    }
    memset(buf, 0, fsize);
    tmp_buf = buf;
    sz = fread(tmp_buf, 1, fsize, fp);

    if (sz != fsize || sz <= 0 || tmp_buf == NULL)
    {
        res = _ERR(MFA_ERR_FILE_READ);
        goto err_clean_up;
    }

    if ((res = _mfa_open_buf(mfa_d, buf, fsize)) != MFA_OK)
    {
        goto err_clean_up;
    }

    fclose(fp);
    (*mfa_d)->open_method = MFA_OPEN_FILE;

    return MFA_OK;

err_clean_up:
    fclose(fp);
    if (buf != NULL)
    {
        free(buf);
    }
    return res;
}

int mfa_close(struct mfa_desc* mfa_d)
{
    if (mfa_d->map != NULL)
    {
        free(mfa_d->map);
        mfa_d->map = NULL;
    }
    if (mfa_d->open_method == MFA_OPEN_FILE)
    {
        free(mfa_d->buffer);
        mfa_d->buffer = NULL;
    }
    if (mfa_d->toc != NULL)
    {
        free(mfa_d->toc);
        mfa_d->toc = NULL;
    }
    if (mfa_d->data_decompressor != NULL)
    {
        xz_close(mfa_d->data_decompressor);
        mfa_d->data_decompressor = NULL;
    }
    if (mfa_d->data_window != NULL)
    {
        free(mfa_d->data_window);
        mfa_d->data_window = NULL;
    }
    free(mfa_d);
    return MFA_OK;
}

int mfa_verify_archive(u_int8_t* buf, long sz)
{
    int i;
    u_int32_t crc;
    u_int32_t ar_crc;
    u_int32_t ver;
    u_int32_t major;
    u_int32_t minor;
    u_int32_t mlx_major = (MLXA_VERSION & 0xFFFF0000) >> 16;
    u_int32_t mlx_minor = (MLXA_VERSION & 0x0000FFFF);
    char unencrypted_signature[] = {'M', 'F', 'A', 'R'};
    char encrypted_signature[] = {'M', 'F', 'A', 'E'};

    if (sz < 16)
    {
        return _ERR(MFA_ERR_ARCHV_FORMAT);
    }

    // Check signature
    for (i = 0; i < 4; i++)
    {
        if (unencrypted_signature[i] != buf[i] && encrypted_signature[i] != buf[i])
        {
            return _ERR(MFA_ERR_ARCHV_SIGNATURE);
        }
    }
#ifdef NO_OPEN_SSL
    if (memcmp(buf, encrypted_signature, sizeof(encrypted_signature)) == 0)
    {
        return _ERR(MFA_ERR_NO_OPENSSL);
    }
#endif

    // Check version
    ver = *((u_int32_t*)&buf[4]);
    ver = mft_be32_to_cpu(ver);
    major = (ver & 0xFFFF0000) >> 16;
    minor = (ver & 0x0000FFFF);
    (void)mlx_minor;
    (void)minor;
    if (major > mlx_major)
    {
        return _ERR(MFA_ERR_ARCHV_VER_UNSUPP);
    }

    // Archive CRC
    ar_crc = *((u_int32_t*)&buf[sz - 4]);
    ar_crc = mft_be32_to_cpu(ar_crc);

    crc = mfasec_crc32(buf, sz - 4, 0);
    if (crc != ar_crc)
    {
        // printf("CRC32 = %08x expected = %08x\n", crc, ar_crc);
        return _ERR(MFA_ERR_ARCHV_CRC);
    }

    return MFA_OK;
}

int mfa_get_crc32(u_int8_t* arbuf, long sz, u_int32_t* ar_crc, u_int32_t* calc_crc)
{
    *ar_crc = *((u_int32_t*)&arbuf[sz - 4]);
    *ar_crc = mft_be32_to_cpu(*ar_crc);

    *calc_crc = mfasec_crc32(arbuf, sz - 4, 0);

    return MFA_OK;
}

int mfa_read_map(struct mfa_desc* mfa_d)
{
    u_int8_t* buf;
    int res;

    section_hdr* map_hdr = (section_hdr*)&mfa_d->buffer[MAP_SECTION_OFFSET];

    res =
      mfasec_get_map(&mfa_d->buffer[MAP_SECTION_OFFSET], mft_be32_to_cpu(map_hdr->size) + sizeof(section_hdr), &buf);
    if (res < 0)
    {
        goto clean_up;
    }

    mfa_d->map = buf;

clean_up:
    if (res < 0)
    {
        free(buf);
    }
    return res;
}

int mfa_read_toc(struct mfa_desc* mfa_d)
{
    u_int8_t* buf;
    int res;

    // verify MAP header fits in buffer
    if ((size_t)mfa_d->bufsz < MAP_SECTION_OFFSET + sizeof(section_hdr))
    {
        return _ERR(MFA_ERR_ARCHV_FORMAT);
    }
    section_hdr* map_hdr = (section_hdr*)&mfa_d->buffer[MAP_SECTION_OFFSET];
    size_t map_sz = mft_be32_to_cpu(map_hdr->size);
    // verify TOC header fits in buffer after MAP payload
    if ((size_t)mfa_d->bufsz < MAP_SECTION_OFFSET + sizeof(section_hdr) + map_sz + sizeof(section_hdr))
    {
        return _ERR(MFA_ERR_ARCHV_FORMAT);
    }
    section_hdr* toc_hdr = (section_hdr*)&mfa_d->buffer[MAP_SECTION_OFFSET + map_sz + sizeof(section_hdr)];
    size_t toc_sz = mft_be32_to_cpu(toc_hdr->size);
    size_t data_offset = MAP_SECTION_OFFSET + map_sz + 2 * sizeof(section_hdr) + toc_sz;
    // verify DATA header fits in buffer
    if ((size_t)mfa_d->bufsz < data_offset + sizeof(section_hdr))
    {
        return _ERR(MFA_ERR_ARCHV_FORMAT);
    }
    mfa_d->data_ptr = &mfa_d->buffer[data_offset];

    res = mfasec_get_toc((u_int8_t*)toc_hdr, toc_sz + sizeof(section_hdr), &buf);
    if (res < 0)
    {
        goto clean_up;
    }

    mfa_d->toc = buf;

clean_up:
    if (res < 0)
    {
        free(buf);
    }
    return res;
}

int mfa_map_get_num_images(map_entry_hdr* me)
{
    return me->nimages;
}

const char* mfa_map_get_metadata(map_entry_hdr* me)
{
    if (me->metadata_size == 0)
    {
        return "";
    }
    char* ptr = (char*)me;
    ptr += sizeof(map_entry_hdr);
    return ptr;
}

map_image_entry* mfa_get_map_image(map_entry_hdr* me, int image_index)
{
    u_int8_t* ptr = (u_int8_t*)me;
    if (image_index >= me->nimages)
    {
        return NULL;
    }
    ptr += sizeof(map_entry_hdr);
    ptr += me->metadata_size;
    map_image_entry* img_e = (map_image_entry*)ptr;
    return (map_image_entry*)&img_e[image_index];
}

toc_entry* mfa_get_image_toc(mfa_desc* mfa_d, map_image_entry* img_e)
{
    toc_entry* toc_e = (toc_entry*)&mfa_d->toc[img_e->toc_offset + sizeof(section_hdr)];
    return (toc_entry*)toc_e;
}

/* (Re)open the forward reader at the start of the XZ DATA stream. */
static int data_reader_open(mfa_desc* mfa_d, const u_int8_t* xz_ptr, size_t xz_size)
{
    if (mfa_d == NULL || xz_ptr == NULL)
    {
        return -1;
    }
    if (mfa_d->data_decompressor != NULL)
    {
        xz_close(mfa_d->data_decompressor);
        mfa_d->data_decompressor = NULL;
    }
    if (mfa_d->data_window == NULL)
    {
        mfa_d->data_window = (u_int8_t*)malloc(MFA_DATA_WINDOW_SIZE);
        if (mfa_d->data_window == NULL)
        {
            return -1;
        }
    }
    mfa_d->data_decompressor = xz_open_buf(xz_ptr, xz_size);
    if (mfa_d->data_decompressor == NULL)
    {
        return -1;
    }
    mfa_d->data_window_len = 0;
    mfa_d->data_window_pos = 0;
    mfa_d->data_pos = 0;
    return 0;
}

/* Read n decompressed bytes from the reader; copy into out (or discard if NULL).
   Advances data_pos. Returns 0 on success, <0 on decode error / premature EOF. */
static int data_reader_read(mfa_desc* mfa_d, u_int64_t n, u_int8_t* out)
{
    if (mfa_d == NULL)
    {
        return -1;
    }
    u_int64_t done = 0;
    while (done < n)
    {
        if (mfa_d->data_window_pos == mfa_d->data_window_len)
        {
            int rc = xz_read(mfa_d->data_decompressor, mfa_d->data_window, MFA_DATA_WINDOW_SIZE);
            if (rc <= 0)
            {
                return -1;
            }
            mfa_d->data_window_len = (size_t)rc;
            mfa_d->data_window_pos = 0;
        }
        u_int64_t need = n - done;                                      // bytes still requested
        size_t avail = mfa_d->data_window_len - mfa_d->data_window_pos; // bytes left in the window
        size_t take = (need < avail) ? (size_t)need : avail;            // copy the smaller of the two
        if (out != NULL)
        {
            memcpy(out + done, mfa_d->data_window + mfa_d->data_window_pos, take);
        }
        mfa_d->data_window_pos += take;
        mfa_d->data_pos += take;
        done += take;
    }
    return 0;
}

/* Read [offset, offset+length) from the DATA section into outbuf. For XZ data this
   uses the persistent forward reader: consecutive in-order reads inflate the stream
   only once; a backward request transparently reopens the stream. */
static int mfa_read_data_range(mfa_desc* mfa_d, u_int64_t offset, size_t length, u_int8_t* outbuf)
{
    if (mfa_d == NULL || outbuf == NULL)
    {
        return _ERR(MFA_ERR_ARCHV_FORMAT);
    }
    section_hdr* hdr = (section_hdr*)mfa_d->data_ptr;
    size_t src_sz = mft_be32_to_cpu(hdr->size);
    u_int8_t* xz_ptr = mfa_d->data_ptr + sizeof(section_hdr);

    /* compressed payload must fit within the archive buffer */
    if (xz_ptr + src_sz > mfa_d->buffer + mfa_d->bufsz)
    {
        return _ERR(MFA_ERR_ARCHV_FORMAT);
    }

    if (!(hdr->flags & SFLAG_XZ_COMPRESSED))
    {
        /* non-XZ: data is stored raw after the section header */
        if (offset > src_sz || length > src_sz - offset)
        {
            return _ERR(MFA_ERR_ARCHV_FORMAT);
        }
        memcpy(outbuf, xz_ptr + offset, length);
        return 0;
    }

    // (re)open the reader if not started or if we must seek backward - starting from the beginning
    if (mfa_d->data_decompressor == NULL || offset < mfa_d->data_pos)
    {
        if (data_reader_open(mfa_d, xz_ptr, src_sz) < 0)
        {
            return _ERR(MFA_ERR_DECOMPRESSION);
        }
    }

    // If the offset is greater than the current position, we need to seek forward
    if (offset > mfa_d->data_pos)
    {
        if (data_reader_read(mfa_d, offset - mfa_d->data_pos, NULL) < 0)
        {
            return _ERR(MFA_ERR_DECOMPRESSION);
        }
    }

    if (data_reader_read(mfa_d, length, outbuf) < 0)
    {
        return _ERR(MFA_ERR_DECOMPRESSION);
    }
    return 0;
}

ssize_t get_image_by_map_entry(mfa_desc* mfa_d,
                               u_int8_t type,
                               char* selector_tag,
                               u_int8_t** buffer,
                               map_entry_hdr* map_entry_hdr,
                               char* board_type_id)
{
    int i;
    ssize_t res;
    ssize_t accum_size;
    int last_group_id = -1;
    map_image_entry* map_img;
    ssize_t total_size = 0;
    int n = mfa_map_get_num_images(map_entry_hdr);
    toc_entry** toce_ar = NULL;
    int toce_num = 0;

    if (n > 0)
    {
        toce_ar = (toc_entry**)malloc(sizeof(toc_entry*) * n);
        if (toce_ar == NULL)
        {
            return _ERR_STR(mfa_d, MFA_ERR_MEM_ALLOC, "Failed to allocate %u bytes of memory",
                            (unsigned)(sizeof(toc_entry) * n));
        }
    }
    else
    {
        return _ERR_STR(mfa_d, MFA_ERR_ARCHV_FORMAT, "Didn't expect zero images for board type ID=%s", board_type_id);
    }

    for (i = 0; i < n; i++)
    {
        map_img = mfa_get_map_image(map_entry_hdr, i);

        if (map_img->image_type == type)
        {
            if (map_img->select_tag[0] != 0)
            {
                if (selector_tag == NULL)
                {
                    continue;
                }
                if (strncmp(map_img->select_tag, selector_tag, 32) != 0)
                {
                    continue;
                }
            }
            if (last_group_id == map_img->group_id)
            {
                continue;
            }
            last_group_id = map_img->group_id;
            toc_entry* toc_e = mfa_get_image_toc(mfa_d, map_img);
            toce_ar[toce_num] = toc_e;
            toce_num++;
            total_size += toc_e->data_size;
        }
    }

    if (toce_num == 0)
    {
        res = _ERR_STR(mfa_d, MFA_ERR_NO_ENTRY, "Image not found for board type ID=%s with type=%d and selector_tag=%s",
                       board_type_id, type, selector_tag);
        goto img_alloc_clean_up;
    }
    else
    {
        *buffer = (u_int8_t*)malloc(total_size);
        if (*buffer == NULL)
        {
            res = _ERR_STR(mfa_d, MFA_ERR_MEM_ALLOC, "Failed to allocate %u memory", (unsigned)total_size);
            goto clean_up;
        }
        memset(*buffer, 0, total_size * sizeof(u_int8_t));
    }

    accum_size = 0;
    for (i = 0; i < toce_num; i++)
    {
        if (toce_ar[i]->data_size == 0)
        {
            continue;
        }
        // Since toce_ar[i]->data_offset is only 32bits we can't reach images on larger offsets so we
        // make use of another 16bits from toce_ar[i]->data_offset_msb field
        u_int64_t data_offset = toce_ar[i]->data_offset_msb;
        data_offset = data_offset << 32;
        data_offset += toce_ar[i]->data_offset;
        int rc = mfa_read_data_range(mfa_d, data_offset, toce_ar[i]->data_size, &((*buffer)[accum_size]));
        if (rc < 0)
        {
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

int is_encrypted(map_entry_hdr* me)
{
    map_image_entry* img_e = mfa_get_map_image(me, 0);
    if (img_e == NULL)
    {
        return 0;
    }
    return img_e->is_encrypted;
}

map_entry_hdr* mfa_get_map_entry(mfa_desc* mfa_d, char* board_type_id)
{
    u_int8_t* map = mfa_d->map;
    section_hdr* map_hdr = (section_hdr*)map;
    ssize_t pos = sizeof(section_hdr);
    ssize_t total = sizeof(section_hdr) + map_hdr->size;
    while (pos < total)
    {
        map_entry_hdr* map_entry_header = (map_entry_hdr*)&map[pos];
        int encrypted = is_encrypted(map_entry_header);
        int n = map_entry_header->nimages;
        char img_board_type_id[PSID_SIZE + 1] = {0};
#ifndef NO_OPEN_SSL
        u_int32_t img_board_type_id_len = PSID_SIZE;
#endif

        if (encrypted)
        {
#ifdef NO_OPEN_SSL
            return NULL;
#else
            char iv[AES_CTR_IV_SIZE] = {0};
            char key[KEY_SIZE] = {0};

            SHA256((u_int8_t*)board_type_id, strlen(board_type_id), (u_int8_t*)key);
            mlxsign_aesctr_ctx* aesctr_ctx =
              mlxsign_aesctr_create((u_int8_t*)key, KEY_SIZE, (u_int8_t*)iv, AES_CTR_IV_SIZE);
            if (aesctr_ctx == NULL)
            {
                return NULL;
            }
            int rc = mlxsign_aesctr_decrypt(aesctr_ctx, (u_int8_t*)map_entry_header->board_type_id, PSID_SIZE,
                                            (u_int8_t*)img_board_type_id, &img_board_type_id_len);
            if (rc < 0)
            {
                mlxsign_aesctr_destroy(aesctr_ctx);
                return NULL;
            }
            mlxsign_aesctr_destroy(aesctr_ctx);
#endif
        }
        else
        {
            memcpy(img_board_type_id, map_entry_header->board_type_id, PSID_SIZE);
            img_board_type_id[PSID_SIZE] = '\0';
        }

        if (strcmp(img_board_type_id, board_type_id) != 0)
        {
            pos += sizeof(map_entry_hdr);
            pos += map_entry_header->metadata_size;
            pos += n * sizeof(map_image_entry);
            continue;
        }
        return map_entry_header;
    }

    return NULL;
}

map_entry_hdr* mfa_get_next_mentry(mfa_desc* mfa_d, map_entry_hdr* curr_me)
{
    ssize_t pos;
    ssize_t total;
    int n;
    map_entry_hdr* next_me = NULL;
    u_int8_t* map = mfa_d->map;
    section_hdr* map_hdr = (section_hdr*)map;

    total = sizeof(section_hdr) + map_hdr->size;

    if (curr_me == NULL)
    {
        pos = sizeof(section_hdr);
        next_me = (map_entry_hdr*)&map[pos];
        return next_me;
    }

    pos = (ssize_t)(((u_int8_t*)curr_me) - map);

    n = curr_me->nimages;
    pos += sizeof(map_entry_hdr);
    pos += curr_me->metadata_size;
    pos += n * sizeof(map_image_entry);

    if (pos < total)
    {
        next_me = (map_entry_hdr*)&map[pos];
    }

    return next_me;
}

int find_metadata_value_len(const char* first_key, const char* second_key, const u_int8_t* metadata_start)
{
    const int METADATA_VALUE_NOT_FOUND = -1;
    const size_t MAX_METADATA_SIZE = MAP_ENTRY_METADATA_SIZE - sizeof(metadata_hdr);
    const size_t first_len = strlen(first_key);
    const size_t second_len = strlen(second_key);

    size_t first_pos = (size_t)-1; // Use (size_t)-1 as "not found" indicator
    size_t i;
    size_t value_end;

    if (MAX_METADATA_SIZE < first_len || MAX_METADATA_SIZE < second_len)
    {
        return METADATA_VALUE_NOT_FOUND;
    }

    // Find first key
    for (i = 0; i <= MAX_METADATA_SIZE - first_len; ++i)
    {
        if (memcmp(metadata_start + i, first_key, first_len) == 0)
        {
            first_pos = i;
            break;
        }
    }

    if (first_pos == (size_t)-1)
    {
        return METADATA_VALUE_NOT_FOUND;
    }

    // Calculate value end for length calculation and skip null terminator
    value_end = first_pos + first_len + 1;

    if (value_end >= MAX_METADATA_SIZE)
    {
        return METADATA_VALUE_NOT_FOUND;
    }

    // Find second key
    for (i = value_end; i <= MAX_METADATA_SIZE - second_len; ++i)
    {
        if (memcmp(metadata_start + i, second_key, second_len) == 0)
        {
            return i - value_end - 1; // Length between value end and second key remove null terminator
        }
    }

    return MAX_METADATA_SIZE - value_end - 1; // Length between value end and end of metadata
}

char* mfa_get_map_entry_metadata(map_entry_hdr* map_entry, char* key)
{
    char* ptr;
    metadata_hdr* md_hdr;

    ptr = (char*)map_entry;
    ptr += sizeof(map_entry_hdr);

    // ptr points at beginning of metadata section
    md_hdr = (metadata_hdr*)ptr;
    ptr += sizeof(metadata_hdr);

    if (map_entry->metadata_size == 0)
    {
        return NULL;
    }
    if (map_entry->metadata_size <= sizeof(metadata_hdr))
    {
        return NULL;
    }
    if (md_hdr->type != MDT_KEY_VALUE_PAIR)
    {
        return NULL;
    }

    // Scan byte-by-byte to locate the key. This handles both encrypted and
    // non-encrypted entries: encrypted values may contain internal null bytes,
    size_t key_len = strlen(key);
    size_t metadata_data_size = map_entry->metadata_size - sizeof(metadata_hdr);
    char* found = NULL;
    for (size_t j = 0; j + key_len < metadata_data_size; j++)
    {
        if (memcmp(ptr + j, key, key_len) == 0 && ptr[j + key_len] == '\0')
        {
            found = ptr + j + key_len + 1;
            break;
        }
    }

    if (found == NULL)
    {
        return NULL;
    }

    /* Encrypted values are binary (may contain null bytes) — caller must NOT free this pointer;
       it points directly into the map_entry buffer. */
    if (is_encrypted(map_entry) && (strcmp(key, "DESCRIPTION") == 0 || strcmp(key, "PN") == 0))
    {
        return found;
    }

    /* Non-encrypted: caller owns the returned allocation and must free it. */
    return strdup(found);
}

char* mfa_get_board_metadata(mfa_desc* mfa_d, char* board_type_id, char* key)
{
    map_entry_hdr* map_entry = mfa_get_map_entry(mfa_d, board_type_id);
    if (map_entry == NULL)
    {
        printf("map_entry is NULL for board type ID: %s\n", board_type_id);
        return NULL;
    }
    return mfa_get_map_entry_metadata(map_entry, key);
}

ssize_t mfa_get_image(mfa_desc* mfa_d, char* board_type_id, u_int8_t type, char* selector_tag, u_int8_t** buffer)
{
    map_entry_hdr* map_entry = mfa_get_map_entry(mfa_d, board_type_id);
    if (map_entry == NULL)
    {
        return _ERR_STR(mfa_d, MFA_ERR_NO_ENTRY, "Entry not found for Board Type ID = %s", board_type_id);
    }
    return get_image_by_map_entry(mfa_d, type, selector_tag, buffer, map_entry, board_type_id);
}

void mfa_release_image(u_int8_t* buffer)
{
    free(buffer);
}

const char* mfa_get_last_error(mfa_desc* mfa_d)
{
    return mfa_d->err_str;
}
