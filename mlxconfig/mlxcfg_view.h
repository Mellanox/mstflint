/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 *
 * mlxcfg_view.h
 *
 *  Created on: Jun 22, 2016
 *      Author: ahmads
 */

#ifndef MLXCFG_VIEW_H_
#define MLXCFG_VIEW_H_

#include <string>
#include <vector>
#include <map>

#include "mlxcfg_utils.h"

enum ParamType
{
    BOOLEAN_TYPE,
    ENUM,
    INTEGER,
    UNSIGNED,
    STRING,
    BINARY,
    BYTES
};

enum TLVClass
{
    Global,
    Physical_Port,
    BMC,
    Per_Host_Per_Function,
    Per_SWID,
    NVLog,
    NVFile,
    Per_Host,
    Switch_Global,
    Module,
    Physical_Port_Common = 0x81,
    Per_Host_All_Functions = 0x43,
    All_Hosts_Per_Function = 0x83,
    All_Hosts_All_Functions = 0xC3
};

typedef struct ParamView
{
    ParamView() :
        mlxconfigName(""),
        description(""),
        type(BOOLEAN_TYPE),
        val(MLXCFG_UNKNOWN),
        port(0),
        _module(-1),
        strVal(""),
        setVal(""),
        rule(""),
        isReadOnlyParam(false),
        supportedFromVersion(0){};
    std::string mlxconfigName;
    std::string description;
    enum ParamType type;
    std::map<std::string, u_int32_t> textualVals;
    u_int32_t val;
    u_int32_t port;
    int32_t _module;
    std::string strVal;
    std::string setVal;
    std::vector<u_int32_t> arrayVal;
    std::vector<std::string> strArrayVal;
    std::string rule;
    bool isReadOnlyParam; // in read only TLV all params are read only
    u_int32_t supportedFromVersion;

} ParamView;

typedef struct TLVConfView
{
    std::string name;
    std::string description;
    TLVClass tlvClass;
    std::vector<ParamView> params;
} TLVConfView;

typedef struct BackupView
{
    u_int32_t type;
    u_int8_t writerId;
    u_int8_t writerHostId;
    std::vector<u_int8_t> tlvBin;
} BackupView;
#endif /* MLXCFG_VIEW_H_ */
