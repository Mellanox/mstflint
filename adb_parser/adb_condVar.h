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

#ifndef ADB_CONDVAR_H
#define ADB_CONDVAR_H

#include <common/compatibility.h>
#include <string>
using namespace std;
template<bool eval_expr, typename T_OFFSET>
class _AdbInstance_impl;
template<typename T_OFFSET = uint32_t>
class _AdbCondVar_impl
{
    using AdbInstance = _AdbInstance_impl<true, T_OFFSET>;
public:
    _AdbCondVar_impl() = default;
    ~_AdbCondVar_impl() = default;
    _AdbCondVar_impl(string original_name);

    void set_value(int);
    void set_instance(AdbInstance*);
    bool is_evaluated() const;
    bool is_name_modified() const;
    int get_value() const;
    AdbInstance* get_instance() const;
    const string& get_original_name() const;
    void evaluate(uint8_t* buffer, T_OFFSET offset_shift = 0);

private:
    bool _evaluated{false};
    int _value{};
    AdbInstance* _instance{nullptr};
    string _original_name;
};

using AdbCondVarLegacy = _AdbCondVar_impl<uint32_t>;
using AdbCondVar = _AdbCondVar_impl<uint64_t>;
#endif // ADB_CONDVAR_H
