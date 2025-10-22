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

#ifndef MLXDPA_DPA_APP_REMOVAL_H_
#define MLXDPA_DPA_APP_REMOVAL_H_

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "common/compatibility.h"
#include "dpaAppStructHeader.h"
#include "baseHeader.h"

using namespace std;

class DpaAppRemoveMetadata
{
public:
    DpaAppRemoveMetadata(u_int32_t dpaAppUUID[4], u_int32_t keypairUUID[4]);
    virtual ~DpaAppRemoveMetadata() {}

    vector<u_int8_t> Serialize();
    void Deserialize(vector<u_int8_t> buf);
    u_int16_t GetSize() { return METADATA_SIZE; };
    DpaAppStructHeader::StructType GetType() { return DpaAppStructHeader::StructType::DPA_APP_REMOVE_METADATA; };
    static const u_int32_t KEY_PAIR_UUID_SIZE = 16;
    static const u_int32_t DPA_APP_UUID_SIZE = 16;
    static const u_int32_t RESERVED_SIZE = 4;

private:
    const u_int16_t METADATA_SIZE = 0x24;
    u_int32_t _dpaAppUUID[4];
    u_int32_t _keypairUUID[4];
    u_int32_t _reserved;
};

class DpaAppRemoveSignature
{
public:
    DpaAppRemoveSignature() : _signature(0x0) {}
    DpaAppRemoveSignature(vector<u_int8_t> signature) : _signature(signature) {}
    vector<u_int8_t> Serialize() { return _signature; }
    void Deserialize(vector<u_int8_t> buf) { _signature = buf; }
    DpaAppStructHeader::StructType GetType() { return DpaAppStructHeader::StructType::SIGNATURE; };

private:
    vector<u_int8_t> _signature;
};

#endif /* MLXDPA_DPA_APP_REMOVAL_H_ */