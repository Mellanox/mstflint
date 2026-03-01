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

template<bool dynamic = false>
class _RegAccessParser_impl
{
    // Type aliases based on dynamic template parameter
    using Adb = _Adb_impl<dynamic, uint32_t>;
    using AdbInstance = _AdbInstance_impl<dynamic, uint32_t>;
    using AdbCondition = _AdbCondition_impl<uint32_t>;

    struct FieldSearchContext
    {
        string& name;          // reference to the field name being searched for
        u_int32_t size;        // size of the field TODO: remove this after fixing in mlxlink
        u_int32_t offset;      // offset of the field TODO: remove this after fixing in mlxlink
        bool offsetSpecified;  // true if the offset is specified TODO: remove this after fixing in mlxlink
        AdbInstance* instance; // the found instance
    };

    enum class ParamType
    {
        DATA,
        INDEX,
        OP
    };

    struct ParamDetails
    {
        ParamType type;
        uint32_t value;
    };

    using ParamsMap = std::map<string, ParamDetails>;

public:
    _RegAccessParser_impl(string data,
                          string indexes,
                          string ops,
                          Adb* adb,
                          AdbInstance* regNode,
                          std::vector<u_int32_t> buffer,
                          bool ignore_ro = false,
                          bool full_path = false);
    _RegAccessParser_impl(string data,
                          string indexes,
                          string ops,
                          Adb* adb,
                          AdbInstance* regNode,
                          u_int32_t len,
                          bool ignore_ro = false,
                          bool full_path = false);
    std::vector<u_int32_t> genBuff();
    u_int32_t getDataLen() { return _len; };
    static void strToUint32(char* str, u_int32_t& uint);
    static string getAccess(const AdbInstance* field);
    static string get_legacy_path(AdbInstance& instance);
    static bool is_in_path(const string& partial, const string& full);

protected:
    string _data;
    string _indexes;
    string _ops;
    u_int32_t _len;
    Adb* _adb;
    AdbInstance* _regNode;
    parseMode _parseMode;
    string output_file;
    std::vector<u_int32_t> _buffer;
    bool _ignore_ro;
    bool _full_path;
    ParamsMap _params_map;

    static bool _on_traverse_update_buffer(const string& calculated_path,
                                           uint64_t calculated_offset,
                                           uint64_t calculated_value,
                                           AdbInstance* instance,
                                           void* context);
    static bool on_traverse_get_field(const string& calculated_path,
                                           uint64_t calculated_offset,
                                           uint64_t calculated_value,
                                           AdbInstance* instance,
                                           void* context);
    std::vector<u_int32_t> genBuffUnknown();
    std::vector<u_int32_t> genBuffKnown();
    void parse_register_params(const string& data, ParamType param_type);
    void parseUnknown();
    AdbInstance* getField(string name,
                          u_int32_t size = 0,
                          u_int32_t offset = 0,
                          bool offsetSpecified = false,
                          bool is_buffer_full = false);
    std::vector<string> strSplit(string str, char delimiter, bool forcePairs);
    void updateBuffer(u_int32_t offset, u_int32_t size, u_int32_t val);
    void updateBufferUnknwon(std::vector<string> fieldTokens);
    void updateField(string field_name, u_int32_t value);
    u_int32_t getFieldValue(string field_name,
                            std::vector<u_int32_t>& buff,
                            u_int32_t size = 0,
                            u_int32_t offset = 0,
                            bool offsetSpecified = false,
                            bool is_buffer_full = false);
};

// Type aliases
using RegAccessParser = _RegAccessParser_impl<true>;

} // namespace mlxreg
#endif /* MLXREG_PARSER_H */
