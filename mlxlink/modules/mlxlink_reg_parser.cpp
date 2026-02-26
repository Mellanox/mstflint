/*
 * Copyright (c) 2020-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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
#include <common/tools_utils.h>

MlxlinkRegParser::MlxlinkRegParser() : RegAccessParser("", "", "", NULL, NULL, false, false)
{
    _mf = nullptr;
    _regLib = nullptr;
    _gvmiAddress = 0;

    _localPort = 0;
    _portType = 0;
    _pnat = 0;
    _planeInd = -1;

    _isHCA = false;
    _isSwControled = false;
    _isDPNvSupported = false;
}

MlxlinkRegParser::~MlxlinkRegParser() {}

void MlxlinkRegParser::resetParser(const string& regName)
{
    _regNode = (_regLib)->findAdbNode(regName);
    _data = "";
    _indexes = "";
    _len = 0;
    if (!_regNode)
    {
        if (_len > MAX_REG_SIZE)
        {
            throw MlxRegException("Register length: 0x%08x is too large", _len);
        }
        _parseMode = Pm_Unknown;
        _len = (_len + 3) / 4;
    }
    else
    {
        _parseMode = Pm_Known;
        _len = (_regNode->get_size()) >> 5;
    }
    _buffer.resize(_len);
    for (std::vector<u_int32_t>::size_type j = 0; j < _len; j++)
    {
        _buffer[j] = 0;
    }
}

void MlxlinkRegParser::genBuffSendRegister(const string& regName, maccess_reg_method_t method)
{
    if (_gvmiAddress)
    {
        writeGvmi(1);
    }
    _buffer = genBuffUnknown();
    (_regLib)->sendRegister(regName, method, _buffer);

    if (_gvmiAddress)
    {
        writeGvmi(0);
    }
}

void MlxlinkRegParser::writeGvmi(u_int32_t data)
{
    mwrite4(_mf, _gvmiAddress, data);
}

void MlxlinkRegParser::updateField(string field_name, u_int32_t value)
{
    RegAccessParser::updateField(field_name, value);

    if (field_name == "local_port")
    {
        try
        {
            // the full value for local port is 10 bits, [0:7] in local_port, and [8:9] in lp_msb
            // this should be provided for all access registers which have local_port field index
            updateField("lp_msb", ((value >> 8) & 0x3));
        }
        catch (...)
        {
            // If the lp_msb does not exists on some access register, no need to fail the command
        }
    }
}

void MlxlinkRegParser::updateWithDefault(const string& fieldName, const string& fieldsStr, u_int32_t val)
{
    if (fieldsStr.find(fieldName) == string::npos)
    {
        try
        {
            updateField(fieldName, val);
        }
        catch (...)
        {
        }
    }
}

void MlxlinkRegParser::setDefaultFields(const string& regName, const string& fieldsStr)
{
    updateWithDefault("local_port", fieldsStr, _localPort);
    updateWithDefault("pnat", fieldsStr, _pnat);

    if (!_isHCA)
    {
        updateWithDefault("port_type", fieldsStr, _portType);
    }

    // Some registers need to have another indication for localport 255 to deal with it as a localport by setting lp_gl
    // field
    if (regName == ACCESS_REG_PPCNT && _localPort == 255)
    {
        updateWithDefault("lp_gl", fieldsStr, 1);
    }

    if (_isHCA && _planeInd >= 0)
    {
        updateWithDefault("plane_ind", fieldsStr, static_cast<u_int32_t>(_planeInd));
    }

    if (_isHCA && _isDPNvSupported &&
        (regName == ACCESS_REG_MPIR || regName == ACCESS_REG_MPCNT || regName == ACCESS_REG_MPEIN ||
         regName == ACCESS_REG_MPEINJ))
    {
        updateWithDefault("DPNv", fieldsStr, 1);
    }
}

void MlxlinkRegParser::sendPrmReg(const string& regName, maccess_reg_method_t method)
{
    resetParser(regName);

    setDefaultFields(regName, "");

    genBuffSendRegister(regName, method);
}

// This function uses va_list to support all flavors of variadic sendPrmReg functions
void MlxlinkRegParser::sendPrmRegVaList(const string& regName,
    maccess_reg_method_t method,
    const char* fields,
    va_list args,
    bool reset,
    bool force_full_path)
{
    char fieldsCstr[MAX_FIELDS_BUFFER];
    vsnprintf(fieldsCstr, MAX_FIELDS_BUFFER, fields, args);

    bool orig_full_path = _full_path;
    try
    {
        if (force_full_path)
        {
            _full_path = true;
        }
        string fieldsStr = string(fieldsCstr);
        auto vectorOffields = MlxlinkRecord::split(fieldsStr, ",");

        if (reset)
        {
            resetParser(regName);
        }
        else
        {
            for (std::vector<u_int32_t>::size_type j = 0; j < _buffer.size(); j++)
            {
                _buffer[j] = CPU_TO_BE32((_buffer[j]));
            }
        }

        for (const auto& token : vectorOffields)
        {
            if (token.empty())
            {
                continue;
            }
            auto fieldToken = MlxlinkRecord::split(token, "=");
            string fieldName = fieldToken[0];
            u_int32_t fieldValue = stoi(fieldToken[1], nullptr, 0);

            updateField(fieldName, fieldValue);
        }
        setDefaultFields(regName, fieldsStr);

        genBuffSendRegister(regName, method);
    }
    catch (...)
    {
        _full_path = orig_full_path;
        throw;
    }
    _full_path = orig_full_path;
}

void MlxlinkRegParser::sendPrmRegWithoutReset(const string& regName,
    maccess_reg_method_t method,
    const char* fields,
    ...)
{
    va_list args;
    va_start(args, fields);
    sendPrmRegVaList(regName, method, fields, args, false, false);
    va_end(args);
}

void MlxlinkRegParser::sendPrmRegWithoutResetFullPath(const string& regName,
            maccess_reg_method_t method,
            const char* fields,
            ...)
{
    va_list args;
    va_start(args, fields);
    sendPrmRegVaList(regName, method, fields, args, false, true);
    va_end(args);
}

void MlxlinkRegParser::sendPrmReg(const string& regName, maccess_reg_method_t method, const char* fields, ...)
{
    va_list args;
    va_start(args, fields);
    sendPrmRegVaList(regName, method, fields, args, true, false);
    va_end(args);
}

void MlxlinkRegParser::sendPrmRegFullPath(const string& regName, maccess_reg_method_t method, const char* fields, ...)
{
    va_list args;
    va_start(args, fields);
    sendPrmRegVaList(regName, method, fields, args, true, true);
    va_end(args);
}

string
  MlxlinkRegParser::getFieldStr(const string& field, const u_int32_t size, const u_int32_t offset, bool offsetSpecified, bool processDynamicFields)
{
    return to_string(getFieldValue(field, size, offset, offsetSpecified, processDynamicFields));
}

string MlxlinkRegParser::getRawFieldValueStr(const string fieldName)
{
    string fullStr = "";
    char hexFormat[32];
    u_int32_t fieldBuf = 0;

    for (int i = 0;; i++)
    {
        string path = fieldName;
        path.append("[");
        path.append(to_string(i));
        path.append("]");
        try
        {
            fieldBuf = getFieldValue(path);
        }
        catch (...)
        {
            break;
        }
        if (fieldBuf)
        {
            sprintf(hexFormat, "%08x", fieldBuf);
            fullStr.append(string(hexFormat));
        }
    }

    return fullStr;
}

u_int32_t MlxlinkRegParser::getFieldValue(string field_name,
                                          u_int32_t size,
                                          u_int32_t offset,
                                          bool offsetSpecified,
                                          bool processDynamicFields)
{
    u_int32_t field_Val =
        RegAccessParser::getFieldValue(field_name, _buffer, size, offset, offsetSpecified, processDynamicFields);

    return field_Val;
}

u_int32_t MlxlinkRegParser::getFieldSize(string field_name)
{
    return RegAccessParser::getField(field_name)->get_size();
}

string MlxlinkRegParser::getAscii(const string& name, u_int32_t size)
{
    string value = "";
    char c;
    u_int32_t name_tmp;

    for (u_int32_t i = 0; i < size / 4; i++)
    {
        name_tmp = getFieldValue(name + "[" + to_string(i) + "]");
        for (int k = 24; k > -1; k -= 8)
        {
            c = (char)(name_tmp >> k);
            if ((int)c != 0 && (int)c != 32)
            {
                value.push_back(c);
            }
        }
    }
    return (value != "") ? value : "N/A";
}
