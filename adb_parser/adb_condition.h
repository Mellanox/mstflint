/*
 *
 * Copyright (c) 2013-2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef ADB_CONDITION_H
#define ADB_CONDITION_H

#include <map>
#include <string>
#include <array>
#include "adb_condVar.h"
#include "expr.h"

using namespace std;
template<typename T_OFFSET>
class _AdbCondVar_impl;

template<typename T_OFFSET>
class _AdbCondition_impl
{
    using AdbCondVar = _AdbCondVar_impl<T_OFFSET>;
public:
    _AdbCondition_impl() = default;
    ~_AdbCondition_impl() = default;
    void init(string& condition_str);
    map<string, AdbCondVar>& get_vars_map();
    const std::string& get_condition() const;
    void update_enum(const std::string& var_name);
    uint64_t evaluate(uint8_t* buffer, T_OFFSET offset_shift = 0);

private:
    void init_variables();
    void modify_condition_names();
    std::string find_enclosing_parenthesis(size_t var_pos);
    std::string _condition_str;
    map<string, AdbCondVar> _vars_map;
    static const size_t MAX_CONDITION_SIZE;
    static const string DOLLAR;
    static const string DUNDER;
    static const string VARIABLE_PATTERN;
    static const string SIMPLE_NAME_PATTERN;
    static const std::array<const char*, 42> OPERATOR_STRINGS;
};

using AdbConditionLegacy = _AdbCondition_impl<uint32_t>;
using AdbCondition = _AdbCondition_impl<uint64_t>;
template<typename T_OFFSET>
class ConditionExpr : public Expr
{
private:
    map<string, _AdbCondVar_impl<T_OFFSET>>& _vars_map;
public:
    ConditionExpr(map<string, _AdbCondVar_impl<T_OFFSET>>& vars) : _vars_map(vars) {}
    int ResolveName(char* name, u_int64_t* val) override
    {
        auto it = _vars_map.find(string(name));
        if (it != _vars_map.end())
        {
            *val = static_cast<u_int64_t>(it->second.get_value());
            return 0;
        }
        return -1; // Name not found
    }
    void Error(const std::string& msg) override;
};
#endif // ADB_CONDITION_Hs
