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
#include "xz_io_ops.h"
#include <compatibility.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/param.h>
#include <string.h>
#include <xz.h>

#define XZ_IOBUF_SIZE 4096
#define _ERR(errcode) (-errcode)

#define MXZ_ERR_MEM_ALLOC 1
#define MXZ_ERR_DECODER_INIT 2

typedef struct {
    struct xz_dec *s;
    struct xz_buf b;
} xz_env;

static uint8_t xz_has_init = 0;

struct xzhandle_t {
    const u_int8_t *buf;
    ssize_t size;
    ssize_t pos;
    xz_env *envptr;
};


void xz_init()
{
    if (xz_has_init) {
        return;
    }
    xz_crc32_init();
    xz_has_init = 1;
}


uint32_t xz_io_crc32(const uint8_t *buf, size_t size, uint32_t crc)
{
    xz_init();
    return xz_crc32(buf, size, crc);
}


static xz_env* xz_decoder_init(int *status_code)
{
    xz_env *env;
    struct xz_dec *s;
    *status_code = 0;
    struct xz_buf b;

    env = (xz_env*) malloc(sizeof(xz_env));
    if (env == NULL) {
        *status_code = _ERR(MXZ_ERR_MEM_ALLOC);
        return NULL;
    }

    s = xz_dec_init(XZ_DYNALLOC, (uint32_t)-1);
    if (s == NULL) {
        *status_code = _ERR(MXZ_ERR_DECODER_INIT);
        goto err_clean_up;
    }

    b.in_pos = 0;
    b.in_size = 0;
    b.in = NULL;
    b.out_pos = 0;
    b.out_size = 0;
    b.out = NULL;

    env->s = s;
    env->b = b;

    return env;

err_clean_up:
    free(env);
    return NULL;
}


static size_t decode_xz_num(const u_int8_t buf[], size_t size_max, u_int64_t *num)
{
    if (size_max == 0) {
        return 0;
    }

    if (size_max > 9) {
        size_max = 9;
    }

    *num = buf[0] & 0x7F;
    size_t i = 0;

    while (buf[i++] & 0x80) {
        if (i >= size_max || buf[i] == 0x00) {
            return 0;
        }

        *num |= (u_int64_t)(buf[i] & 0x7F) << (i * 7);
    }

    return i;
}


ssize_t xz_stream_len(u_int8_t *buffer, ssize_t len)
{
    //long sz = 0;
    ssize_t pos = len - 1;
    unsigned i;

    while (buffer[pos] == 0) {
        pos--;
    }

    if ((buffer[pos] != 'Z') || (buffer[pos - 1] != 'Y')) {
        return -1;
    }

    pos -= 7;
    u_int32_t backward_size = *((u_int32_t*) &buffer[pos]);//TODO: Must use le2cpu function here
    backward_size = __le32_to_cpu(backward_size);
    backward_size = (backward_size + 1) * 4;
    pos -= 4; //CRC32
    pos -= backward_size - 1; //pos will point at number of records field inside Index

    u_int64_t num_blocks = 0;
    int idx = decode_xz_num(&buffer[pos], len - pos, &num_blocks);
    //printf("idx: %d\n", idx);
    //sz = num_blocks;
    pos += idx;

    ssize_t total_unpadded = 0;
    ssize_t total_uncompressed = 0;

    for (i = 0; i < num_blocks; i++) {
        u_int64_t unpadded = 0;
        u_int64_t uncompressed = 0;
        idx = decode_xz_num(&buffer[pos], len - pos, &unpadded);
        pos += idx;
        idx = decode_xz_num(&buffer[pos], len - pos, &uncompressed);
        pos += idx;
        //printf("Block #%3d: Unpadded: %8u  Uncompressed: %8u\n", i, unpadded, uncompressed);
        total_unpadded += unpadded;
        total_uncompressed += uncompressed;
    }
    //printf("Totals:     Unpadded: %8u  Uncompressed: %8u\n", total_unpadded, total_uncompressed);

    return total_uncompressed;
}


xzhandle_t* xz_open_buf(const u_int8_t *buf, size_t size)
{
    xzhandle_t *xzh;
    int res;

    xz_env *env = xz_decoder_init(&res);
    if (env == NULL) {
        return NULL;
    }
    if (res) {
        return NULL;
    }

    xzh = (xzhandle_t*) malloc(sizeof(xzhandle_t));
    if (xzh == NULL) {
        xz_dec_end(env->s);
        free(env);
        return NULL;
    }
    xzh->buf = buf;
    xzh->size = size;
    xzh->pos = 0;
    xzh->envptr = env;

    return xzh;
}


void xz_close(xzhandle_t *xzh)
{
    xz_env *e = xzh->envptr;
    xz_dec_end(e->s);
    free(e);
    free(xzh);
}


int xz_read(xzhandle_t *xzh, u_int8_t *buf, size_t len)
{
    xz_env *e;
    enum xz_ret ret;

    e = xzh->envptr;
    if (e->b.in == NULL) {
        e->b.in = (uint8_t*)&xzh->buf[xzh->pos];
        e->b.in_size = xzh->size;
        e->b.in_pos = 0;
    }

    e->b.out = buf;
    e->b.out_size = len;
    e->b.out_pos = 0;
    do {
        ret = xz_dec_run(e->s, &e->b);

        if (e->b.out_pos == e->b.out_size) {
            return e->b.out_pos;
        } else if (ret == XZ_STREAM_END) {
            break;
        }
    } while (ret == XZ_OK);

    switch (ret) {
    case XZ_STREAM_END:
        return e->b.out_pos;

    case XZ_MEM_ERROR:
        //This can occur only in multi-call mode. XZ decompressor ran out of memory
        break;

    case XZ_FORMAT_ERROR:
        //Input is not in the XZ format (wrong magic bytes)
        break;

    case XZ_OPTIONS_ERROR:
        //Input was encoded with settings that are not supported by this XZ decoder
        break;

    case XZ_DATA_ERROR:
    case XZ_BUF_ERROR:
        //XZ-compressed data is corrupt;
        break;

    default:
        //Bug in the XZ decompressor;
        break;
    }

    return -1;
}


