/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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

#ifndef MLXLINK_CMD_PRINT_H
#define MLXLINK_CMD_PRINT_H

#include <vector>
#include "mlxlink_record.h"
#include <json/json.h>

class MlxlinkCmdPrint{

public:
    MlxlinkCmdPrint();
    virtual ~MlxlinkCmdPrint();
    friend std::ostream & operator << (std::ostream &out, const MlxlinkCmdPrint &cmdPrint);
    void initRecords(int size);
    void toJsonFormat(Json::Value& jsonRoot);
    u_int32_t getCurrRow();

    std::string title;
    std::vector<MlxlinkRecord> mlxlinkRecords;
    bool visible;
    u_int32_t lastInsertedRow;
};

#endif /* MLXLINK_CMD_PRINT_H */
