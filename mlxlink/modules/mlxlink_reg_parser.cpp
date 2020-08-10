/*
 * Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.
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

#include "mlxlink_reg_parser.h"

MlxlinkRegParser::MlxlinkRegParser() : RegAccessParser("", "", NULL, 0)
{
    _mf = NULL;
    _regLib = NULL;
    _gvmiAddress = 0;
    _mlxlinkLogger = NULL;
}

MlxlinkRegParser::~MlxlinkRegParser()
{
}

void MlxlinkRegParser::resetParser(const string &regName)
{
    DEBUG_LOG(_mlxlinkLogger, "%s: %-30s\n","OPERATION ON REGISTER",
                (char*)regName.c_str());
    _regNode = (_regLib)->findAdbNode(regName);
    _data = "";
    _indexes = "";
    _len = 0;
    if (!_regNode) {
        if (_len > MAX_REG_SIZE) {
            throw MlxRegException("Register length: 0x%08x is too large", _len);
        }
        _parseMode = Pm_Unknown;
        _len = (_len + 3) / 4;
    } else {
        _parseMode = Pm_Known;
        _len = (_regNode->size) >> 5;
    }
    _buffer.resize(_len);
    for (std::vector<u_int32_t>::size_type j = 0; j < _len; j++) {
        _buffer[j] = 0;
    }
}

void MlxlinkRegParser::genBuffSendRegister(const string &regName, maccess_reg_method_t method)
{
    DEBUG_LOG(_mlxlinkLogger, "%-15s: %s\n", "ACCESS_METHOD",
                method == MACCESS_REG_METHOD_GET ? "GET": "SET");
    if (_gvmiAddress) {
        writeGvmi(1);
    }
    _buffer = genBuffUnknown();
    (_regLib)->sendRegister(regName, method, _buffer);

    if (_gvmiAddress) {
        writeGvmi(0);
    }
}

void MlxlinkRegParser::writeGvmi(u_int32_t data)
{
    mwrite4(_mf, _gvmiAddress, data);
}

void MlxlinkRegParser::updateField(string field_name, u_int32_t value)
{
    DEBUG_LOG(_mlxlinkLogger, "%-15s: %-30s\tVALUE: 0x%08x (%d)\n",
              "UPDATE_FIELD", (char*)field_name.c_str(),value,value);
    RegAccessParser::updateField(field_name, value);
}

string MlxlinkRegParser::getFieldStr(const string &field)
{
    return to_string(getFieldValue(field));
}

u_int32_t MlxlinkRegParser::getFieldValue(string field_name)
{
    u_int32_t field_Val = RegAccessParser::getFieldValue(field_name, _buffer);
    DEBUG_LOG(_mlxlinkLogger,"%-15s: %-30s\tVALUE: 0x%08x (%d)\n","GET_FIELD",
            (char*)field_name.c_str(),field_Val,field_Val) ;
    return field_Val;
}

