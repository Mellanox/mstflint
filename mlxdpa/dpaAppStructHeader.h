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

#ifndef MLXDPA_DPA_APP_STRUCT_HEADER_H_
#define MLXDPA_DPA_APP_STRUCT_HEADER_H_

#include <string>
#include <vector>
#include <memory>
#include <map>
#include "common/compatibility.h"
#include "baseHeader.h"

using namespace std;

class DpaAppStructHeader : public BaseHeader
{
public:
    enum class StructType
    {
        DPA_ELF = 0x1,
        DPA_CRYPTO_BLOB = 0x2,
        DPA_APP_METADATA = 0x3,
        ENC_PARAMS = 0x4,
        DPA_APP = 0x5,
        DPA_APP_REMOVE_METADATA = 0x6,
        SIGNATURE = 0x7,
        ENC_KEY = 0x8,
        DPA_APP_MANIFEST = 0x9,
        RESERVED
    };
    enum class StructSecurityMethod
    {
        NO_AUTH = 0x0,
        ENC_PARAMS = 0x1,
        DUK_GCM = 0x2,
        DUK_GMAC = 0x3,
        CLASS_GCM = 0x4,
        RESERVED
    };

    enum class StructValid
    {
        Free = 11,
        ValidData = 10,
        InvalidatedDataElement = 00,
        Illegal = 01
    };

    DpaAppStructHeader();
    DpaAppStructHeader(StructPriority priority, StructType type);
    DpaAppStructHeader(StructPriority priority, StructType type, u_int32_t length);
    DpaAppStructHeader(u_int32_t length,
                       StructType type,
                       StructPriority priority,
                       StructSecurityMethod securityMethod,
                       StructValid valid,
                       u_int8_t version);

    StructType GetType() { return _type; }
    u_int32_t GetLength() const { return _length; }
    vector<u_int8_t> Serialize();
    bool Deserialize(vector<u_int8_t> buf);
    bool Deserialize(vector<u_int8_t>::const_iterator begin, vector<u_int8_t>::const_iterator end);
    void SetSecurityMethod(StructSecurityMethod securityMethod);
    void SetValid(StructValid valid);
    void SetValidData();
    void SetLength(u_int32_t length);
    void SetVersion(u_int8_t version);
    void SetType(StructType type);
    int GetHeaderSize();
    std::string TypeToString(StructType type);

    static const map<StructPriority, string> _metadataPriorityToString;

    static const u_int32_t HEADER_SIZE_NO_AUTH = 8;
    static const u_int32_t HEADER_SIZE_OTHER = 4;

private:
    u_int32_t _length;
    StructType _type;
    u_int8_t _version : 4;
    StructValid _valid;
    StructSecurityMethod _securityMethod;

    void UpdateLength();
};

#endif /* MLXDPA_DPA_APP_STRUCT_HEADER_H_ */