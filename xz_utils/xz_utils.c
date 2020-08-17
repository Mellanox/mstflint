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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#ifdef _MSC_VER
#define LZMA_API_STATIC
#endif
#include <lzma.h>
#include "xz_utils.h"

static int32_t init_encoder(lzma_stream *strm, u_int32_t preset, lzma_check check)
{
    // Initialize the encoder using a preset. Set the integrity to check
    // to CRC64, which is the default in the xz command line tool. If
    // the .xz file needs to be decompressed with XZ Embedded, use
    // LZMA_CHECK_CRC32 instead.
    lzma_ret ret = lzma_easy_encoder(strm, preset, check);

    // Return successfully if the initialization went fine.
    if (ret == LZMA_OK) {
        return 0;
    }

    // Something went wrong. The possible errors are documented in
    // lzma/container.h (src/liblzma/api/lzma/container.h in the source
    // package or e.g. /usr/include/lzma/container.h depending on the
    // install prefix).
    // const char *msg;
    switch (ret) {
    case LZMA_MEM_ERROR:
        return XZ_ERR_INTERNAL_MEM;

    case LZMA_OPTIONS_ERROR:
        return XZ_ERR_PRESET_NO_SUPP;
        break;

    case LZMA_UNSUPPORTED_CHECK:
        return XZ_ERR_INTEGRITY_NOT_SUPP;

    default:
        // This is most likely LZMA_PROG_ERROR indicating a bug in
        // this program or in liblzma. It is inconvenient to have a
        // separate error message for errors that should be impossible
        // to occur, but knowing the error code is important for
        // debugging. That's why it is good to print the error code
        // at least when there is no good error message to show.
        return XZ_ERR_UNKNOWN;
    }
}


static int32_t init_decoder(lzma_stream *strm)
{
    lzma_ret ret = lzma_stream_decoder(
        strm, UINT64_MAX, LZMA_CONCATENATED);

    // Return successfully if the initialization went fine.
    if (ret == LZMA_OK) {
        return 0;
    }

    // const char *msg;
    switch (ret) {
    case LZMA_MEM_ERROR:
        return XZ_ERR_INTERNAL_MEM;

    default:
        // This is most likely LZMA_PROG_ERROR indicating a bug in
        // this program or in liblzma. It is inconvenient to have a
        // separate error message for errors that should be impossible
        // to occur, but knowing the error code is important for
        // debugging. That's why it is good to print the error code
        // at least when there is no good error message to show.
        return XZ_ERR_UNKNOWN;
    }
}


static int32_t xcompress(lzma_stream *strm, u_int8_t *inbuf, u_int32_t insz, u_int8_t *outbuf, u_int32_t outsz)
{
    // This will be LZMA_RUN until the end of the input file is reached.
    // This tells lzma_code() when there will be no more input.
    lzma_action action = LZMA_RUN;

    // Buffers to temporarily hold uncompressed input
    // and compressed output.
    u_int8_t obuf[BUFSIZ];

    strm->next_in = NULL;
    strm->avail_in = 0;
    strm->next_out = obuf;
    strm->avail_out = sizeof(obuf);
    u_int32_t rpos = 0;
    u_int32_t wpos = 0;
    u_int32_t chunk_sz = 0;

    // Loop until the file has been successfully compressed or until
    // an error occurs.
    while (1) {
        // Fill the input buffer if it is empty.
        if (strm->avail_in == 0 && (rpos < insz)) {
            strm->next_in = &inbuf[rpos];
            chunk_sz = insz - rpos;
            strm->avail_in = chunk_sz;
        }
        if (rpos >= insz) {
            action = LZMA_FINISH;
        }

        lzma_ret ret = lzma_code(strm, action);

        // If the output buffer is full or if the compression finished
        // successfully, write the data from the output bufffer to
        // the output file.
        if (((strm->avail_out == 0) && (ret == LZMA_OK)) || (ret == LZMA_STREAM_END)) {
            u_int32_t write_size = sizeof(obuf) - strm->avail_out;

            if (outbuf) {
                if (wpos + write_size > outsz) {
                    return XZ_ERR_MEM_EXCEEDED;
                }

                memcpy(&(outbuf[wpos]), obuf, write_size);
            }
            wpos += write_size;
            // Reset next_out and avail_out.
            strm->next_out = obuf;
            strm->avail_out = sizeof(obuf);
        }

        // Normally the return value of lzma_code() will be LZMA_OK
        // until everything has been encoded.
        if (ret != LZMA_OK) {
            // Once everything has been encoded successfully, the
            // return value of lzma_code() will be LZMA_STREAM_END.
            //
            // It is important to check for LZMA_STREAM_END. Do not
            // assume that getting ret != LZMA_OK would mean that
            // everything has gone well.
            if (ret == LZMA_STREAM_END) {
                break;
            }

            // It's not LZMA_OK nor LZMA_STREAM_END,
            // so it must be an error code. See lzma/base.h
            // (src/liblzma/api/lzma/base.h in the source package
            // or e.g. /usr/include/lzma/base.h depending on the
            // install prefix) for the list and documentation of
            // possible values. Most values listen in lzma_ret
            // enumeration aren't possible in this example.
            // const char *msg;
            switch (ret) {
            case LZMA_MEM_ERROR:
                return XZ_ERR_INTERNAL_MEM;

            case LZMA_DATA_ERROR:
                // This error is returned if the compressed
                // or uncompressed size get near 8 EiB
                // (2^63 bytes) because that's where the .xz
                // file format size limits currently are.
                // That is, the possibility of this error
                // is mostly theoretical unless you are doing
                // something very unusual.
                //
                // Note that strm->total_in and strm->total_out
                // have nothing to do with this error. Changing
                // those variables won't increase or decrease
                // the chance of getting this error.
                return XZ_ERR_MEM_EXCEEDED;

            default:
                // This is most likely LZMA_PROG_ERROR, but
                // if this program is buggy (or liblzma has
                // a bug), it may be e.g. LZMA_BUF_ERROR or
                // LZMA_OPTIONS_ERROR too.
                //
                // It is inconvenient to have a separate
                // error message for errors that should be
                // impossible to occur, but knowing the error
                // code is important for debugging. That's why
                // it is good to print the error code at least
                // when there is no good error message to show.
                return XZ_ERR_UNKNOWN;
            }

            return XZ_ERR_ENCODE_FAULT;
        }

        rpos += chunk_sz;
        chunk_sz = 0;
    }

    // In case wpos is zero (for any lzma unknown reason, LZMA_STREAM_END reached immediately) perform clean up.
    if (wpos == 0) {
        return XZ_ERR_ENCODE_FAULT;
    }

    // return size
    return wpos;
}


static int32_t xpress(int comp_decomp_, u_int32_t preset, u_int8_t *inbuf,
                      u_int32_t insz, u_int8_t *outbuf, u_int32_t outsz, lzma_check check)
{
    int32_t rc;
    u_int32_t sz;
    lzma_stream strm;
    lzma_stream init_strm = LZMA_STREAM_INIT;

    strm = init_strm;
    if (comp_decomp_) {
        rc = init_decoder(&strm);
    } else {
        rc = init_encoder(&strm, preset, check);
    }

    if (rc) {
        return rc;
    }

    sz = xcompress(&strm, inbuf, insz, outbuf, outsz);
    lzma_end(&strm);
    return sz;
}

int32_t xz_compress_crc32(u_int32_t preset, u_int8_t* inbuf, u_int32_t insz, u_int8_t* outbuf, u_int32_t outsz)
{
    return xpress(0, preset, inbuf, insz, outbuf, outsz, LZMA_CHECK_CRC32);
}

int32_t xz_compress(u_int32_t preset, u_int8_t *inbuf, u_int32_t insz, u_int8_t *outbuf, u_int32_t outsz)
{
    return xpress(0, preset, inbuf, insz, outbuf, outsz, LZMA_CHECK_CRC64);
}


int32_t xz_decompress(u_int8_t *inbuf, u_int32_t insz, u_int8_t *outbuf, u_int32_t outsz)
{
    return xpress(1, 0, inbuf, insz, outbuf, outsz, LZMA_CHECK_CRC64);
}

int32_t xz_decompress_crc32(u_int8_t *inbuf, u_int32_t insz, u_int8_t *outbuf, u_int32_t outsz)
{
    return xpress(1, 0, inbuf, insz, outbuf, outsz, LZMA_CHECK_CRC32);
}
const char* xz_get_error(int32_t error)
{
    if (error == XZ_ERR_MEM_EXCEEDED) {
        return "XZ_ERR_MEM_EXCEEDED";
    }
    else if (error == XZ_ERR_INTERNAL_MEM) {
        return "XZ_ERR_INTERNAL_MEM";
    }
    else if (error == XZ_ERR_PRESET_NO_SUPP) {
        return "XZ_ERR_PRESET_NO_SUPP";
    }
    else if (error == XZ_ERR_INTEGRITY_NOT_SUPP) {
        return "XZ_ERR_INTEGRITY_NOT_SUPP";
    }
    else if (error == XZ_ERR_ENCODE_FAULT) {
        return "XZ_ERR_ENCODE_FAULT";
    }
    else {
        return "UNKNOWN ERROR";
    }
}
