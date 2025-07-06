/*
 * Copyright (c) 2019-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef MLXREG_PARSER_H
#define MLXREG_PARSER_H

#include <string>
#include <algorithm>
#include <adb_parser/adb_parser.h>
#include "mlxreg_exception.h"

namespace mlxreg
{
#define MAX_REG_SIZE 0x2000

typedef enum
{
    Pm_Known = 0,
    Pm_Unknown
} parseMode;

class RegAccessParser
{
public:
    RegAccessParser(string data,
                    string indexes,
                    string ops,
                    AdbInstanceAdvLegacy* regNode,
                    std::vector<u_int32_t> buffer,
                    bool ignore_ro = false);
    RegAccessParser(string data,
                    string indexes,
                    string ops,
                    AdbInstanceAdvLegacy* regNode,
                    u_int32_t len,
                    bool ignore_ro = false);
    std::vector<u_int32_t> genBuff();
    u_int32_t getDataLen() { return _len; };
    static void strToUint32(char* str, u_int32_t& uint);
    static string getAccess(const AdbInstanceAdvLegacy* field);
    enum access_type_t
    {
        INDEX,
        OP
    };

protected:
    string _data;
    string _indexes;
    string _ops;
    u_int32_t _len;
    AdbInstanceAdvLegacy* _regNode;
    parseMode _parseMode;
    string output_file;
    std::vector<u_int32_t> _buffer;
    bool _ignore_ro;
    std::vector<u_int32_t> genBuffUnknown();
    std::vector<u_int32_t> genBuffKnown();
    void parseAccessType(std::vector<string> tokens, std::vector<string> validTokens, access_type_t accessType);
    void parseIndexes();
    void parseOps();
    void parseData();
    void parseUnknown();
    bool checkFieldWithPath(AdbInstanceAdvLegacy* field,
                            u_int32_t idx,
                            std::vector<string>& fieldsChain,
                            u_int32_t size = 0,
                            u_int32_t offset = 0,
                            bool offsetSpecified = false);
    AdbInstanceAdvLegacy* getField(string name, u_int32_t size = 0, u_int32_t offset = 0, bool offsetSpecified = false);
    std::vector<string> strSplit(string str, char delimiter, bool forcePairs);
    void updateBuffer(u_int32_t offset, u_int32_t size, u_int32_t val);
    void updateBufferUnknwon(std::vector<string> fieldTokens);
    void updateField(string field_name, u_int32_t value);
    u_int32_t getFieldValue(string field_name,
                            std::vector<u_int32_t>& buff,
                            u_int32_t size = 0,
                            u_int32_t offset = 0,
                            bool offsetSpecified = false);
    bool isRO(AdbInstanceAdvLegacy* field);
    bool isIndex(AdbInstanceAdvLegacy* field);
    bool isOP(AdbInstanceAdvLegacy* field);
    std::vector<string> getAllIndexes(AdbInstanceAdvLegacy* node);
    std::vector<string> getAllOps(AdbInstanceAdvLegacy* node);
    const std::string accessTypeToString(access_type_t accessType);

private:
    bool checkAccess(const AdbInstanceAdvLegacy* field, const string accessStr);
};

} // namespace mlxreg
#endif /* MLXREG_PARSER_H */
