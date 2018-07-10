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
#include "txz.h"

#include <libtar.h>

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/param.h>
#include <string.h>

#include <lzma.h>


tbuf_t* xzopen_frontend(char *pathname, int oflags, int mode);
int     xzread(tbuf_t *tbuf, void *buf, size_t len);
int     xzwrite(tbuf_t *tbuf, const void *buf, size_t len);


void xz_init()
{
}


uint32_t xz_io_crc32(const uint8_t *buf, size_t size, uint32_t crc)
{
    return lzma_crc32(buf, size, crc);
}


void* xz_decoder_init(int *status_code)
{
    lzma_stream *strm;
    lzma_stream tmp = LZMA_STREAM_INIT;
    *status_code = 0;

    strm = (lzma_stream*) malloc(sizeof(lzma_stream));
    if (strm == NULL) {
        *status_code = _ERR(TXZ_ERR_MEM_ALLOC);
        return NULL;
    }

    *strm = tmp;

    if (init_decoder(strm)) {
        // Decoder initialization failed. There's no point
        // to retry it so we need to exit.
        *status_code = _ERR(TXZ_ERR_DECODER_INIT);
        goto err_clean_up;
    }
    strm->next_in = NULL;
    strm->avail_in = 0;
    return strm;

err_clean_up:
    free(strm);
    return NULL;
}


void xz_close(void *strm)
{
    lzma_end((lzma_stream*)strm);
}


int init_decoder(lzma_stream *strm)
{
    lzma_ret ret = lzma_stream_decoder(
        strm, UINT64_MAX, LZMA_CONCATENATED);

    if (ret == LZMA_OK) {
        return 0;
    }

    const char *msg;
    switch (ret) {
    case LZMA_MEM_ERROR:
        msg = "Memory allocation failed";
        break;

    case LZMA_OPTIONS_ERROR:
        msg = "Unsupported decompressor flags";
        break;

    default:
        msg = "Unknown error, possibly a bug";
        break;
    }

    printf( "Error initializing the decoder: %s (error code %u)\n",
            msg, ret);
    return -1;
}


int lzma_code_ret(lzma_ret ret);


int xzread(tbuf_t *tbuf, void *buf, size_t len)
{
    lzma_stream *strm;
    lzma_action action = LZMA_RUN;

    strm = (lzma_stream*)tbuf->envptr;
    strm->next_out = (uint8_t*)buf;
    strm->avail_out = len;

    while (1) {
        if (strm->avail_in == 0 && action != LZMA_FINISH) {
            int chunksz = tbuf->size - tbuf->pos;
            if (chunksz > BUFSIZ) {
                chunksz = BUFSIZ;
            }

            strm->next_in = &tbuf->buf[tbuf->pos];
            tbuf->pos += chunksz;

            strm->avail_in = chunksz;

            // Once the end of the input file has been reached,
            // we need to tell lzma_code() that no more input
            // will be coming. As said before, this isn't required
            // if the LZMA_CONATENATED flag isn't used when
            // initializing the decoder.
            if (!strm->avail_in) {
                action = LZMA_FINISH;
            }
        }

        lzma_ret ret = lzma_code(strm, action);
        if (lzma_code_ret(ret)) {
            return -1;
        }

        if (strm->avail_out == 0 || ret == LZMA_STREAM_END) {
            size_t write_size = len - strm->avail_out;
            return write_size;
        }

    }
    return 0;
}


tbuf_t* xzopen_frontend(char *pathname, int oflags, int mode)
{
    if (pathname || oflags || mode) { //omits compiler warnings
        return NULL;
    }
    return NULL;
}


int xzclose(tbuf_t *tbuf)
{
    if (tbuf) { //omits compiler warnings
        return 0;
    }
    return 0;
}


int xzwrite(tbuf_t *tbuf, const void *buf, size_t len)
{
    if (tbuf || buf || len) { //omits compiler warnings
        return 0;
    }
    return 0;
}


int lzma_code_ret(lzma_ret ret)
{
    if (ret != LZMA_OK) {
        // Once everything has been decoded successfully, the
        // return value of lzma_code() will be LZMA_STREAM_END.
        //
        // It is important to check for LZMA_STREAM_END. Do not
        // assume that getting ret != LZMA_OK would mean that
        // everything has gone well or that when you aren't
        // getting more output it must have successfully
        // decoded everything.
        if (ret == LZMA_STREAM_END) {
            return 0;
        }

        // It's not LZMA_OK nor LZMA_STREAM_END,
        // so it must be an error code. See lzma/base.h
        // (src/liblzma/api/lzma/base.h in the source package
        // or e.g. /usr/include/lzma/base.h depending on the
        // install prefix) for the list and documentation of
        // possible values. Many values listen in lzma_ret
        // enumeration aren't possible in this example, but
        // can be made possible by enabling memory usage limit
        // or adding flags to the decoder initialization.
        const char *msg;
        switch (ret) {
        case LZMA_MEM_ERROR:
            msg = "Memory allocation failed";
            break;

        case LZMA_FORMAT_ERROR:
            // .xz magic bytes weren't found.
            msg = "The input is not in the .xz format";
            break;

        case LZMA_OPTIONS_ERROR:
            // For example, the headers specify a filter
            // that isn't supported by this liblzma
            // version (or it hasn't been enabled when
            // building liblzma, but no-one sane does
            // that unless building liblzma for an
            // embedded system). Upgrading to a newer
            // liblzma might help.
            //
            // Note that it is unlikely that the file has
            // accidentally became corrupt if you get this
            // error. The integrity of the .xz headers is
            // always verified with a CRC32, so
            // unintentionally corrupt files can be
            // distinguished from unsupported files.
            msg = "Unsupported compression options";
            break;

        case LZMA_DATA_ERROR:
            msg = "Compressed file is corrupt";
            break;

        case LZMA_BUF_ERROR:
            // Typically this error means that a valid
            // file has got truncated, but it might also
            // be a damaged part in the file that makes
            // the decoder think the file is truncated.
            // If you prefer, you can use the same error
            // message for this as for LZMA_DATA_ERROR.
            msg = "Compressed file is truncated or "
                  "otherwise corrupt";
            break;

        default:
            // This is most likely LZMA_PROG_ERROR.
            msg = "Unknown error, possibly a bug";
            break;
        }

        printf( "Decoder error: "
                "%s (error code %u)\n",
                msg, ret);
        return -1;
    }
    return 0;
}
