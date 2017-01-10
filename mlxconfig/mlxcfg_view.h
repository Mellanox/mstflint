/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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

enum ParamType {
    BOOLEAN_TYPE,
    ENUM,
    INTEGER,
    UNSIGNED,
    STRING
};

typedef struct ParamView {
    std::string mlxconfigName;
    std::string description;
    enum ParamType type;
    std::map<std::string, u_int32_t> textualVals;
    u_int32_t val;
    std::string strVal;
    std::string setVal;
} ParamView;

typedef struct TLVConfView {
    std::string name;
    std::string description;
    std::vector<ParamView> params;
} TLVConfView;

typedef struct BackupView {
    u_int32_t           type;
    u_int8_t            writerId;
    u_int8_t            writerHostId;
    std::vector<u_int8_t>    tlvBin;
} BackupView;
#endif /* MLXCFG_VIEW_H_ */
