/*
 * Copyright (c) 2013-2024 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED
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
 *  Version: $Id$
 *
 */
#include "dpaAppRemoval.h"
#include "mlxdpa_utils.h"
#include "mft_utils/mft_utils.h"
#include <iostream>
#include <cstring>

DpaAppRemoveMetadata::DpaAppRemoveMetadata(u_int32_t dpaAppUUID[4], u_int32_t keypairUUID[4])
{
    memcpy(_dpaAppUUID, dpaAppUUID, DPA_APP_UUID_SIZE);
    memcpy(_keypairUUID, keypairUUID, KEY_PAIR_UUID_SIZE);
    _reserved = 0x0;
}

vector<u_int8_t> DpaAppRemoveMetadata::Serialize()
{
    vector<u_int8_t> serializedData(GetSize());

    CPUTOn(_dpaAppUUID, sizeof(_dpaAppUUID) / 4);
    memcpy(serializedData.data(), _dpaAppUUID, DPA_APP_UUID_SIZE);
    CPUTOn(_keypairUUID, sizeof(_keypairUUID) / 4);
    memcpy(serializedData.data() + DPA_APP_UUID_SIZE, _keypairUUID, KEY_PAIR_UUID_SIZE);
    serializedData[DPA_APP_UUID_SIZE + KEY_PAIR_UUID_SIZE] = _reserved;

    return serializedData;
}

void DpaAppRemoveMetadata::Deserialize(vector<u_int8_t> buf)
{
    memcpy(_dpaAppUUID, buf.data(), DPA_APP_UUID_SIZE);
    CPUTOn(_dpaAppUUID, sizeof(_dpaAppUUID) / 4);
    memcpy(_keypairUUID, buf.data() + DPA_APP_UUID_SIZE, KEY_PAIR_UUID_SIZE);
    CPUTOn(_keypairUUID, sizeof(_keypairUUID) / 4);
    _reserved = buf[DPA_APP_UUID_SIZE + KEY_PAIR_UUID_SIZE];
}