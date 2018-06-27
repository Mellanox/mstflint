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
#include "mfaerr.h"
#include "mfa_section.h"
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
//#include <sys/param.h>
#include <string.h>
#include "xz_io_ops.h"
#include <compatibility.h>

#define _ERR(errcode) (-errcode)



void mfasec_init()
{
    xz_init();
}


u_int32_t mfasec_crc32(const u_int8_t *buf, size_t size, u_int32_t crc)
{
    return xz_io_crc32(buf, size, crc);
}


ssize_t  mfasec_get_section(u_int8_t *inbuf, size_t inbufsz, u_int8_t **outbuf)
{
    int res = 0;
    int rc;
    xzhandle_t *xzh;
    u_int8_t *buf;

    section_hdr *hdr = (section_hdr*) inbuf;
    if (hdr->flags & SFLAG_XZ_COMPRESSED) {
        ssize_t sz;
        sz = xz_stream_len(&inbuf[sizeof(section_hdr)], __be32_to_cpu(hdr->size));
        if (sz <= 0) {
            return _ERR(MFA_ERR_DECOMPRESSION);
        }
        ssize_t msize = sz + sizeof(section_hdr);
        buf = (u_int8_t*)malloc(msize);
        if (buf == NULL) {
            return _ERR(MFA_ERR_MEM_ALLOC);
        }
        memcpy(buf, inbuf, sizeof(section_hdr));
        //Read section into buffer
        xzh = xz_open_buf(&inbuf[sizeof(section_hdr)], inbufsz - sizeof(section_hdr));
        if (xzh == NULL) {
            res = _ERR(MFA_ERR_DECOMPRESSION);
            goto clean_up;
        }

        rc = xz_read(xzh, &buf[sizeof(section_hdr)], sz);
        xz_close(xzh);

        if (rc != sz) {
            res = _ERR(MFA_ERR_ARCHV_FORMAT);
            goto clean_up;
        }
        section_hdr *hdr = (section_hdr*) buf;
        hdr->flags &= (u_int8_t)(~SFLAG_XZ_COMPRESSED);
        hdr->size = __cpu_to_be32(((u_int32_t)sz));
    } else {
        ssize_t msize = __be32_to_cpu(hdr->size) + sizeof(section_hdr);
        buf = (u_int8_t*)malloc(msize);
        if (buf == NULL) {
            return _ERR(MFA_ERR_MEM_ALLOC);
        }
        memcpy(buf, inbuf, __be32_to_cpu(hdr->size) + sizeof(section_hdr));
    }

    hdr = (section_hdr*) buf;
    hdr->size = __be32_to_cpu(hdr->size);

    *outbuf = buf;
    res = hdr->size + sizeof(section_hdr);

clean_up:
    if (res < 0) {
        free(buf);
    }
    return res;
}


ssize_t  mfasec_get_map(u_int8_t *inbuf, size_t inbufsz, u_int8_t **outbuf)
{
    int res = 0;
    int j;

    res = mfasec_get_section(inbuf, inbufsz, outbuf);
    if (res < 0) {
        return res;
    }
    ssize_t pos = sizeof(section_hdr);
    ssize_t total = res;

    while (pos < total) {
        map_entry_hdr *map_entry = (map_entry_hdr*)&((*outbuf)[pos]);
        int n = map_entry->nimages;
        map_entry->metadata_size = __be16_to_cpu(map_entry->metadata_size);
        //printf("%s %d\n", map_entry->board_type_id, n);
        pos += sizeof(map_entry_hdr);
        if (map_entry->metadata_size > 0) {
            metadata_hdr *md_hdr = (metadata_hdr*)&((*outbuf)[pos]);
            md_hdr->modifier = __be16_to_cpu(md_hdr->modifier);
        }
        pos += map_entry->metadata_size;
        for (j = 0; j < n; j++) {
            map_image_entry *img_entry = (map_image_entry*)&((*outbuf)[pos]);
            img_entry->toc_offset = __be32_to_cpu(img_entry->toc_offset);
            img_entry->image_type = __be16_to_cpu(img_entry->image_type);
            //printf("Image #%d Offset: %08x\n", j, img_entry->toc_offset);
            pos += sizeof(map_image_entry);
        }
    }

    return res;
}


ssize_t  mfasec_get_toc(u_int8_t *inbuf, size_t inbufsz, u_int8_t **outbuf)
{
    int res = 0;
    int i;

    res = mfasec_get_section(inbuf, inbufsz, outbuf);
    if (res < 0) {
        return res;
    }
    ssize_t pos = sizeof(section_hdr);
    ssize_t total = res;

    while (pos < total) {
        toc_entry *toc_e = (toc_entry*)&((*outbuf)[pos]);
        toc_e->data_offset = __be32_to_cpu(toc_e->data_offset);
        toc_e->data_size = __be32_to_cpu(toc_e->data_size);
        toc_e->subimage_type = __be16_to_cpu(toc_e->subimage_type);
        for (i = 0; i < 4; i++) {
            toc_e->version[i] = __be16_to_cpu(toc_e->version[i]);
        }
        toc_e->metadata_size = __be16_to_cpu(toc_e->metadata_size);
        pos += sizeof(toc_entry);
        pos += toc_e->metadata_size;
    }

    return res;
}

#define BUF_SIZE 1024

enum read_states {
    SEEK,
    COPY
};

int mfasec_get_data_chunk(u_int8_t *data_sec_ptr, size_t data_sec_len, size_t chunk_offset, size_t length, u_int8_t *outbuf)
{
    int res = 0;
    int rc;
    xzhandle_t *xzh;
    u_int8_t *buf = NULL;
    size_t src_sz;

    u_int8_t *ptr = data_sec_ptr;
    if (data_sec_len < sizeof(section_hdr)) {
        return _ERR(MFA_ERR_BUFF_SIZE);
    }
    ptr += sizeof(section_hdr);
    data_sec_len -= sizeof(section_hdr);

    section_hdr *hdr = (section_hdr*) data_sec_ptr;
    src_sz = __be32_to_cpu(hdr->size);

    if (hdr->flags & SFLAG_XZ_COMPRESSED) {
        size_t sz;
        buf = (u_int8_t*)malloc(BUF_SIZE);
        if (buf == NULL) {
            return _ERR(MFA_ERR_MEM_ALLOC);
        }
        if (data_sec_len < src_sz) {
            res = _ERR(MFA_ERR_BUFF_SIZE);
            goto clean_up;
        }
        sz = xz_stream_len(ptr, src_sz);
        if (sz <= 0) {
            res = _ERR(MFA_ERR_DECOMPRESSION);
            goto clean_up;
        }
        if (sz < (chunk_offset + length)) {
            res = _ERR(MFA_ERR_DECOMPRESSION);
            goto clean_up;
        }

        //Read section into buffer
        xzh = xz_open_buf(ptr, src_sz);
        if (xzh == NULL) {
            res = _ERR(MFA_ERR_DECOMPRESSION);
            goto clean_up;
        }

        size_t index = 0;
        size_t rlen = 0;
        int state = SEEK;
        do {
            rc = xz_read(xzh, buf, BUF_SIZE);
            if (rc > 0) {
                index += rc;
            } else {
                break;
            }

            if (state == SEEK) {
                if (index > chunk_offset) {
                    rlen += index - chunk_offset;
                    memcpy(outbuf, &buf[rc - (rlen)], rlen);
                    state = COPY;
                }
            } else if (state == COPY) {
                size_t delta = rc;
                if ((rlen + rc) > length) {
                    delta = length - rlen;
                }
                memcpy(&outbuf[rlen], buf, delta);
                rlen += delta;
            }
            if (rlen == length) {
                break;
            }
        } while (rc == BUF_SIZE);

        xz_close(xzh);

        if (rlen != length) {
            res = _ERR(MFA_ERR_DECOMPRESSION);
            goto clean_up;
        }
    } else {
        ptr += chunk_offset;
        memcpy(outbuf, ptr, length);
    }

clean_up:
    if (buf != NULL) {
        free(buf);
    }
    return res;
}


char* mfasec_get_sub_image_type_str(int t)
{
    char *tstr;

    switch (t) {
    case SIT_PADDING:
        tstr = "";
        break;

    case SIT_FW:
        tstr = "FW";
        break;

    case SIT_CLP:
        tstr = "CLP";
        break;

    case SIT_PXE:
        tstr = "PXE";
        break;

    case SIT_UEFI:
        tstr = "UEFI";
        break;

    case SIT_FCODE:
        tstr = "FCODE";
        break;

    default:
        tstr = NULL;
        break;
    }
    return tstr;
}
