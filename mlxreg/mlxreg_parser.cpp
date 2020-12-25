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

#include <sstream>
#include <common/bit_slice.h>
#include <common/tools_utils.h>
#include "mlxreg_parser.h"
#include <errno.h>

using namespace mlxreg;

/************************************
* Function: RegParser
************************************/
RegAccessParser::RegAccessParser(string data, string indexes, AdbInstance *regNode, std::vector<u_int32_t> buffer)
{
    _data      = data;
    _indexes   = indexes;
    _regNode   = regNode;
    if (!regNode) {
        _parseMode = Pm_Unknown;
    } else {
        _parseMode = Pm_Known;
    }
    _len    = buffer.size();
    _buffer = buffer;
    /*
     * Initiate byte-swapping
     * At this point we know the the buffer <buffer> argument already been trough byte-
     * swapping process, we need to re-commit this process so the data will be correct.
     */
    for (std::vector<u_int32_t>::size_type j = 0; j < _buffer.size(); j++) {
        _buffer[j] = CPU_TO_BE32((_buffer[j]));
    }
}
/************************************
* Function: RegParser
************************************/
RegAccessParser::RegAccessParser(string data, string indexes, AdbInstance *regNode, u_int32_t len)
{
    _data      = data;
    _indexes   = indexes;
    _regNode   = regNode;
    _len       = len;
    // Set parsing method
    if (!regNode) {
        if (_len > MAX_REG_SIZE) {
            throw MlxRegException("Register length: 0x%08x is too large", _len);
        }
        _parseMode = Pm_Unknown;
        _len = (_len + 3) / 4;
    } else {
        _parseMode = Pm_Known;
        _len = (_regNode->size) >> 5;
    }
    //Resize buffer
    _buffer.resize(_len);
}

/************************************
* Function: parse
************************************/
std::vector<u_int32_t> RegAccessParser::genBuff()
{
    if (_parseMode == Pm_Known) {
        return genBuffKnown();
    } else {
        return genBuffUnknown();
    }
}

/************************************
* Function: genBuffKnown
************************************/
std::vector<u_int32_t> RegAccessParser::genBuffKnown()
{
    parseIndexes();
    // Update buffer with data values
    if (_data != "") {
        parseData();
    }
    // Convert to BE32
    for (std::vector<u_int32_t>::size_type j = 0; j < _buffer.size(); j++) {
        _buffer[j] = CPU_TO_BE32((_buffer[j]));
    }
    return _buffer;
}

/************************************
* Function: genBuffUnknown
************************************/
std::vector<u_int32_t> RegAccessParser::genBuffUnknown()
{
    parseUnknown();
    // Convert to BE32
    for (std::vector<u_int32_t>::size_type j = 0; j < _buffer.size(); j++) {
        _buffer[j] = CPU_TO_BE32((_buffer[j]));
    }
    return _buffer;
}

/************************************
* Function: parseIndexes
************************************/
void RegAccessParser::parseIndexes()
{
    std::vector<string> idxTokens = strSplit(_indexes, ',', false);
    std::vector<string> expectedIdxs = getAllIndexes(_regNode);
    std::vector<string> foundIdxs;
    // Update buffer with indexes values
    for (std::vector<std::string>::size_type i = 0; i != idxTokens.size(); i++) {
        std::vector<std::string> idx = strSplit(idxTokens[i], '=', true);
        string idxName = idx[0];
        string idxVal  = idx[1];
        u_int32_t uintVal;
        strToUint32((char*)idxVal.c_str(), uintVal);
        AdbInstance *field = getField(idxName);
        // Make sure that the field is INDEX
        if (std::find(expectedIdxs.begin(), expectedIdxs.end(), idxName) != expectedIdxs.end()) {
            if (std::find(foundIdxs.begin(), foundIdxs.end(), idxName) != foundIdxs.end()) {
                throw MlxRegException("You wrote field: %s twice", idxName.c_str());
            }
            foundIdxs.push_back(idxName);
        } else {
            throw MlxRegException("Field: %s is not an index.", idxName.c_str());
        }
        updateBuffer(field->offset, field->size, uintVal);
    }
    // Make sure that all the indexes are set
    for (std::vector<std::string>::size_type i = 0; i != expectedIdxs.size(); i++) {
        bool idxFound = false;
        for (std::vector<std::string>::size_type j = 0; j != foundIdxs.size(); j++) {
            if (expectedIdxs[i] == foundIdxs[j]) {
                idxFound = true;
            }
        }
        if (!idxFound) {
            throw MlxRegException("Index: %s was not provided", expectedIdxs[i].c_str());
        }
    }
}

/************************************
* Function: parseData
************************************/
void RegAccessParser::parseData()
{
    std::vector<string> datTokens = strSplit(_data, ',', false);
    // Update buffer with data values
    for (std::vector<std::string>::size_type i = 0; i != datTokens.size(); i++) {
        std::vector<std::string> dat = strSplit(datTokens[i], '=', true);
        string datName = dat[0];
        string datVal  = dat[1];
        u_int32_t uintVal;
        strToUint32((char*)datVal.c_str(), uintVal);
        AdbInstance *field = getField(datName);
        if (isRO(field)) {
            throw MlxRegException("Field: %s is ReadOnly", datName.c_str());
        }
        updateBuffer(field->offset, field->size, uintVal);
    }
}

/************************************
* Function: parseUnknown
************************************/
void RegAccessParser::parseUnknown()
{
    // Split input strings
    std::vector<string> idxTokens = strSplit(_indexes, ',', false);
    updateBufferUnknwon(idxTokens);
    if (_data != "") {
        std::vector<string> datTokens = strSplit(_data, ',', false);
        updateBufferUnknwon(datTokens);
    }
}

/************************************
* Function: updateBuffer
************************************/
void RegAccessParser::updateBuffer(u_int32_t offset, u_int32_t size, u_int32_t val)
{
    _buffer[offset >> 5] = MERGE(_buffer[offset >> 5], val, (offset % 32), size);
}

/************************************
* Function: updateBufferUnknown
*
* Raw Data/Indexes Pattern is:
* Address.Offset:Size=Data
* Where:
* Address: In bytes (DWORD aligned).
* Offset:  In bits within the address.
* Size:    In bits.
************************************/
void RegAccessParser::updateBufferUnknwon(std::vector<string> fieldTokens)
{
    // Parse fields
    for (std::vector<std::string>::size_type i = 0; i != fieldTokens.size(); i++) {
        std::vector<std::string> fieldToken = strSplit(fieldTokens[i], '=', true);
        // extract <data>
        u_int32_t fieldDataUint;
        string fieldDataStr = fieldToken[1];
        strToUint32((char*)fieldDataStr.c_str(), fieldDataUint);
        // <Address>.<Offset>:<size>
        string fieldPropStr = fieldToken[0];
        std::vector<std::string> fieldPropVec = strSplit(fieldPropStr, ':', true);
        // extract <size>
        u_int32_t fieldSizeUint;
        string fieldSizeStr = fieldPropVec[1];
        strToUint32((char*)fieldSizeStr.c_str(), fieldSizeUint);
        // validate <size>
        if (fieldSizeUint > 32) {
            throw MlxRegException("Invalid size: %d. max size = 32 (bits)", fieldSizeUint);
        }
        // extract <address> <offset>
        string fieldLocStr = fieldPropVec[0];
        std::vector<std::string> fieldLocVec = strSplit(fieldLocStr, '.', true);
        // extract <address>
        u_int32_t fieldAddrUint;
        string fieldAddrStr = fieldLocVec[0];
        strToUint32((char*)fieldAddrStr.c_str(), fieldAddrUint);
        // extract <offset>
        u_int32_t fieldOffsetUint;
        string fieldOffsetStr = fieldLocVec[1];
        strToUint32((char*)fieldOffsetStr.c_str(), fieldOffsetUint);
        // validation
        // Address out of range
        if (fieldAddrUint > (_buffer.size() << 2)) {
            throw MlxRegException("Address: 0x%08x is out of range", fieldOffsetUint);
        }
        // Address not 4 bytes aligned
        if (fieldAddrUint % 0x4 != 0) {
            throw MlxRegException("Address: 0x%08x is not 4-bytes aligned", fieldOffsetUint);
        }
        // offset + size out of address range
        if ((fieldOffsetUint + fieldSizeUint) > 32) {
            throw MlxRegException("Offset: %d and Size: %d is out of address range", fieldOffsetUint, fieldSizeUint);
        }
        // Update buffer
        u_int32_t val = _buffer[fieldAddrUint >> 2];
        val = MERGE(val, fieldDataUint, fieldOffsetUint, fieldSizeUint);
        _buffer[fieldAddrUint >> 2] = val;
    }
}

/************************************
* Function: strSplit
************************************/
std::vector<string> RegAccessParser::strSplit(string str, char delimiter, bool forcePairs)
{
    std::vector<string> internal;
    std::stringstream ss(str); // Turn the string into a stream.
    std::string tok;
    while (getline(ss, tok, delimiter)) {
        internal.push_back((const string)tok);
    }
    // Vector must contain <key-values> otherwise it's invalid.
    if (forcePairs) {
        if (internal.size() != 2) {
            throw MlxRegException("Argument: %s is invalid", str.c_str());
        }
    }
    // Can't have an empty key/value
    for (std::vector<string>::size_type i = 0; i != internal.size(); i++) {
        if (internal[i].length() == 0) {
            throw MlxRegException("Argument: %s is invalid", str.c_str());
        }
    }
    return internal;
}

/************************************
* Function: strToUint32
************************************/
void RegAccessParser::strToUint32(char *str, u_int32_t &uint)
{
    char *endp;
    uint = strtoul(str, &endp, 0);
    if (*endp || errno == ERANGE) {
        throw MlxRegException("Argument: %s is invalid.", str);
    }
    if (str[0] == '-') {
        throw MlxRegException("Argument: %s is invalid. It must be non-negative.", str);
    }
    return;
}

/************************************
* Function: getField
************************************/
AdbInstance* RegAccessParser::getField(string name)
{
    std::vector<AdbInstance*> subItems = _regNode->getLeafFields();
    for (std::vector<AdbInstance*>::size_type i = 0; i != subItems.size(); i++) {
        if (subItems[i]->name == name) {
            return subItems[i];
        }
    }
    throw MlxRegException("Can't find field name: \"%s\"", name.c_str());
}

string RegAccessParser::getAccess(const AdbInstance *field)
{
    string access = field->getInstanceAttr("access");
    if (access.empty()) {
        access = "N/A";
        if (field->parent) {
        access = getAccess(field->parent);
        }
    }
    return access;
}

bool RegAccessParser::checkAccess(const AdbInstance *field, const string accessStr)
{
    return getAccess(field) == accessStr;
}


bool RegAccessParser::isRO(AdbInstance *field)
{
    return checkAccess(field, "RO");
}

bool RegAccessParser::isIndex(AdbInstance *field)
{
    return checkAccess(field, "INDEX");
}

/************************************
* Function: getAllIndexes
************************************/
std::vector<string> RegAccessParser::getAllIndexes(AdbInstance *node)
{
    std::vector<string> indexes;
    std::vector<AdbInstance*> subItems = node->getLeafFields();
    for (std::vector<AdbInstance*>::size_type i = 0; i != subItems.size(); i++) {
        if (isIndex(subItems[i])) {
            indexes.push_back(subItems[i]->name);
        }
    }
    return indexes;
}

void RegAccessParser::updateField(string field_name, u_int32_t value)
{
    AdbInstance *field = getField(field_name);
    updateBuffer(field->offset, field->size, value);
}

u_int32_t RegAccessParser::getFieldValue(string field_name, std::vector<u_int32_t>& buff)
{
    AdbInstance *field = getField(field_name);
    return (u_int32_t)field->popBuf((u_int8_t*)&buff[0]);
}
