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

#include <stdlib.h>
#include <cstring>
#include <vector>
#include <set>
#include <sstream>
#include "adb_condition.h"
#include "adb_instance.h"
#include "adb_exceptionHolder.h"
#include "expr.h"
#include "common/tools_regex.h"

using namespace std;
namespace Regex = mstflint::common::regex;

// Constants Definitions
template<typename T_OFFSET>
const size_t _AdbCondition_impl<T_OFFSET>::MAX_CONDITION_SIZE = 256;

template<typename T_OFFSET>
const string _AdbCondition_impl<T_OFFSET>::DOLLAR = "__dollar__";
template<typename T_OFFSET>
const string _AdbCondition_impl<T_OFFSET>::DUNDER = "__";
template<typename T_OFFSET>
const string _AdbCondition_impl<T_OFFSET>::VARIABLE_PATTERN =
  "(\\$\\(([a-zA-Z_]\\w*)\\)(\\.[a-zA-Z_]\\w*)*)|([a-zA-Z_]\\w*(\\.[a-zA-Z_]\\w*)*)";
template<typename T_OFFSET>
const string _AdbCondition_impl<T_OFFSET>::SIMPLE_NAME_PATTERN = "[a-zA-Z_]\\w*";
template<typename T_OFFSET>
const std::array<const char*, 42> _AdbCondition_impl<T_OFFSET>::OPERATOR_STRINGS = {
  ":", "POW2", "'", "LOG2", "!", "-", "~", "+", "SWAP32", "SWAP16",
  "%", "*", "/", "+", "-", "<<", "SHIFT_L", ">>", "SHIFT_R", ">", "GREAT", ">=", "GREAT_EQ", "<", "LESS",
  "<=", "LESS_EQ", "==", "EQ", "!=", "NOTEQ", "&", "BIT_AND", "|", "BIT_OR", "^", "BIT_XOR", "&&", "AND", "||", "OR",
  "XOR"};
template<typename T_OFFSET>
void ConditionExpr<T_OFFSET>::Error(const string& msg)
{
    throw AdbException("Expression evaluation error: " + msg);
}
template<typename T_OFFSET>
void _AdbCondition_impl<T_OFFSET>::init(string& condition_str)
{
    this->_condition_str = condition_str;
    if (condition_str != "")
    {
        init_variables();
        modify_condition_names();
    }
}

template<typename T_OFFSET>
void _AdbCondition_impl<T_OFFSET>::init_variables()
{
    static const Regex::regex variable_regex(VARIABLE_PATTERN);

    Regex::sregex_iterator var_match_iter(_condition_str.begin(), _condition_str.end(), variable_regex);
    Regex::sregex_iterator var_match_end;
    for (; var_match_iter != var_match_end; ++var_match_iter)
    {
        auto& match = *var_match_iter;
        string variable_name;
        string variable_modified_name;
        if (match[1].matched)
        {
            variable_name = match[1].str();
            variable_modified_name = variable_name;
            variable_modified_name.replace(0, 2, DOLLAR);
            variable_modified_name.replace(DOLLAR.size() + match[2].str().size(), 1, DUNDER);
        }
        else if (match[4].matched)
        {
            variable_name = match[4].str();
            variable_modified_name = string();
        }
        bool is_operator = false;
        for (const auto& op : OPERATOR_STRINGS)
        {
            if (variable_name == op)
            {
                is_operator = true;
                break;
            }
        }
        if (!is_operator && !variable_name.empty())
        {
            if (variable_modified_name.empty())
            {
                this->_vars_map[variable_name] = AdbCondVar();
            }
            else
            {
                this->_vars_map[variable_modified_name] = AdbCondVar(variable_name);
            }
        }
    }
}

template<typename T_OFFSET>
void _AdbCondition_impl<T_OFFSET>::modify_condition_names()
{
    for (const auto& pair : _vars_map)
    {
        const string& modified_name = pair.first;
        const auto& cond_var = pair.second;
        if (cond_var.is_name_modified())
        {
            const string& original_name = cond_var.get_original_name();
            size_t pos = 0;
            while ((pos = _condition_str.find(original_name, pos)) != string::npos)
            {
                _condition_str.replace(pos, original_name.length(), modified_name);
                pos += modified_name.length();
            }
        }
    }
}
template<typename T_OFFSET>
map<string, _AdbCondVar_impl<T_OFFSET>>& _AdbCondition_impl<T_OFFSET>::get_vars_map()
{
    return this->_vars_map;
}

template<typename T_OFFSET>
const string& _AdbCondition_impl<T_OFFSET>::get_condition() const
{
    return this->_condition_str;
}
template<typename T_OFFSET>
string _AdbCondition_impl<T_OFFSET>::find_enclosing_parenthesis(size_t var_pos)
{
    size_t open = string::npos;
    int depth = 0;
    for (int i = static_cast<int>(var_pos) - 1; i >= 0; i--)
    {
        if (_condition_str[i] == ')')
        {
            depth++;
        }
        else if (_condition_str[i] == '(')
        {
            if (depth == 0)
            {
                open = static_cast<size_t>(i);
                break;
            }
            else
            {
                depth--;
            }
        }
    }
    if (open == string::npos)
    {
        return _condition_str;
    }
    else
    {
        depth = 1;
        size_t close = open + 1;
        while (close < _condition_str.size() && depth > 0)
        {
            if (_condition_str[close] == '(')
                depth++;
            else if (_condition_str[close] == ')')
                depth--;
            close++;
        }
        if (depth != 0)
        {
            return "";
        }
        return _condition_str.substr(open + 1, (close - 1) - (open + 1));
    }
}
template<typename T_OFFSET>
void _AdbCondition_impl<T_OFFSET>::update_enum(const string& var_name)
{
    auto it = _vars_map.find(var_name);
    if (it == _vars_map.end())
        return;
    auto& cond_var = it->second;
    auto* instance = cond_var.get_instance();
    if (!(instance && instance->isEnumExists()))
        return;
    const auto& enum_map = instance->getEnumMap();
    for (size_t var_pos = 0; (var_pos = _condition_str.find(var_name, var_pos)) != string::npos;
         var_pos += var_name.length())
    {
        string enum_scope = find_enclosing_parenthesis(var_pos);
        if (enum_scope.empty())
        {
            continue;
        }
        static const Regex::regex name_regex(SIMPLE_NAME_PATTERN);
        Regex::sregex_iterator word_match_iter(enum_scope.begin(), enum_scope.end(), name_regex);
        Regex::sregex_iterator word_match_end;
        for (; word_match_iter != word_match_end; ++word_match_iter)
        {
            auto& match = *word_match_iter;
            const auto& found_name = match[0].str();
            if (found_name == var_name)
                continue;
            auto enum_it = enum_map.find(found_name);
            if (enum_it != enum_map.end())
            {
                auto it2 = _vars_map.find(found_name);
                if (it2 != _vars_map.end())
                {
                    it2->second.set_value(enum_it->second);
                }
            }
        }
    }
}
template<typename T_OFFSET>
uint64_t _AdbCondition_impl<T_OFFSET>::evaluate(uint8_t* buffer)
{
    for (auto& pair : _vars_map)
    {
        const string& var_name = pair.first;
        auto& cond_var = pair.second;
        try
        {
            cond_var.evaluate(buffer);
        }
        catch (const AdbException& e)
        {
            throw AdbException("Failed to evaluate condition variable '" + var_name + "': " + e.what());
        }
    }
    ConditionExpr<T_OFFSET> expr_evaluator(_vars_map);
    char condition_str_cpy[MAX_CONDITION_SIZE];
    char* condition_str_ptr = condition_str_cpy;
    strncpy(condition_str_cpy, _condition_str.c_str(), MAX_CONDITION_SIZE);
    uint64_t result = 0;
    int status = expr_evaluator.expr(&condition_str_ptr, &result);
    if (status < 0)
    {
        throw AdbException("Failed to evaluate condition, error code: " + to_string(status));
    }
    return result;
}
template class _AdbCondition_impl<uint32_t>;
template class _AdbCondition_impl<uint64_t>;
