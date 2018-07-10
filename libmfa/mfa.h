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
#ifndef _MFA_H_
#define _MFA_H_
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "mfa_section.h"

enum mfa_image_types {
    MFA_NO_IMAGE     = 0,
    MFA_FW_IMAGE     = 1,
    MFA_EXPROM_IMAGE = 2
};


typedef struct mfa_desc mfa_desc;

void        mfa_init(); //Must be called before any MFA function to perform one time initializations
int         mfa_open_buf(mfa_desc**, u_int8_t *arbuf, int size);
int         mfa_open_file(mfa_desc**, char *fname);
int         mfa_close(mfa_desc *mfa_d);
ssize_t     mfa_get_image(mfa_desc *mfa_d, char *board_type_id, u_int8_t type, char *selector_tag, u_int8_t **buffer);
char*       mfa_get_board_metadata(mfa_desc *mfa_d, char *board_type_id, char *key);
void        mfa_release_image(u_int8_t *buffer);
const char* mfa_get_last_error(mfa_desc *mfa_d);
int         mfa_get_crc32(u_int8_t *arbuf, long sz, u_int32_t *ar_crc, u_int32_t *calc_crc);
char*       mfa_get_map_entry_metadata(map_entry_hdr *map_entry, char *key);
map_entry_hdr*   mfa_get_next_mentry(mfa_desc *mfa_d, map_entry_hdr *curr_me);
map_image_entry* mfa_get_map_image(map_entry_hdr *me, int image_index);
toc_entry*       mfa_get_image_toc(mfa_desc *mfa_d, map_image_entry *img_e);

#ifdef __cplusplus
}
#endif

#endif

