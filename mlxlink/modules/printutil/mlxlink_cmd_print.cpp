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

#include "mlxlink_cmd_print.h"

MlxlinkCmdPrint::MlxlinkCmdPrint()
{
    lastInsertedRow = 0;
}

MlxlinkCmdPrint::~MlxlinkCmdPrint()
{
}

void MlxlinkCmdPrint::initRecords(int size)
{
    mlxlinkRecords.insert(mlxlinkRecords.begin(), size, MlxlinkRecord());
}

u_int32_t MlxlinkCmdPrint::getCurrRow()
{
    if(!lastInsertedRow) {
        return lastInsertedRow;
    } else {
        return lastInsertedRow + 1;
    }
}

void MlxlinkCmdPrint::toJsonFormat(Json::Value& jsonRoot)
{
    if (!visible) {
        return;
    }
    Json::Value outputGroup;
    MlxlinkRecord record;
    for (u_int32_t i = 0; i < mlxlinkRecords.size(); i++) {
        record = mlxlinkRecords[i];
        MlxlinkRecord::trim(record.key);
        MlxlinkRecord::trim(record.val);
        if (record.visible && record.key != "") {
            if (record.arrayValue) {
                Json::Value subObject;
                subObject[JSON_VALUES_TITLE] = Json::Value(Json::arrayValue);
                std::string val = record.val;
                if (title == HEADER_SUPPORTED_INFO ||
                        title == HEADER_FEC_INFO) {
                    std::string mask = val.substr(0, val.find("(")-1);
                    val = val.substr(
                            val.find("(")+1, val.find_last_of(")")-mask.length()-2);
                    subObject[JSON_MASK_TITLE] = mask;
                }
                if (!val.empty()) {
                    std::vector<std::string> vals;
                    if (title == HEADER_FEC_INFO) {
                        vals = MlxlinkRecord::split(val, ", ");
                    } else {
                      vals = MlxlinkRecord::split(val, ",");
                    }
                    for (std::vector<std::string>::iterator it = vals.begin() ;
                            it != vals.end(); ++it) {
                        subObject[JSON_VALUES_TITLE].append(*it);
                    }
                }
                outputGroup[record.key] = subObject;
            } else {
                outputGroup[record.key] = record.val;
            }
        }
    }
    if (!outputGroup.isNull()) {
        jsonRoot[JSON_RESULT_SECTION][JSON_OUTPUT_SECTION][title] = outputGroup;
    }
}

std::ostream & operator << (std::ostream &out, const MlxlinkCmdPrint &cmdPrint)
{
    if (!MlxlinkRecord::jsonFormat) {
        if (!cmdPrint.visible) {
            return out;
        }
        out << std::endl << cmdPrint.title << std::endl;
        out << std::string(cmdPrint.title.length(), '-') << std::endl;
        for (u_int32_t i = 0; i < cmdPrint.mlxlinkRecords.size(); i++) {
            out <<  cmdPrint.mlxlinkRecords[i];
        }
    }
    return out;
}
