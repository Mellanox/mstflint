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

#include "adb_condVar.h"
#include "adb_exceptionHolder.h"
#include "adb_instance.h"

using namespace std;

u_int64_t pop_from_buf(const u_int8_t* buff, u_int32_t bit_offset, u_int32_t field_size);

template<typename T_OFFSET>
_AdbCondVar_impl<T_OFFSET>::_AdbCondVar_impl(string original_name) : _original_name(original_name)
{
}

template<typename T_OFFSET>
void _AdbCondVar_impl<T_OFFSET>::set_value(int value)
{
    this->_evaluated = true;
    this->_value = value;
}

template<typename T_OFFSET>
bool _AdbCondVar_impl<T_OFFSET>::is_evaluated() const
{
    return this->_evaluated;
}

template<typename T_OFFSET>
bool _AdbCondVar_impl<T_OFFSET>::is_name_modified() const
{
    return !this->_original_name.empty();
}
template<typename T_OFFSET>
void _AdbCondVar_impl<T_OFFSET>::set_instance(AdbInstance* instance)
{
    this->_instance = instance;
}
template<typename T_OFFSET>
int _AdbCondVar_impl<T_OFFSET>::get_value() const
{
    return this->_value;
}
template<typename T_OFFSET>
const string& _AdbCondVar_impl<T_OFFSET>::get_original_name() const
{
    return this->_original_name;
}

template<typename T_OFFSET>
typename _AdbCondVar_impl<T_OFFSET>::AdbInstance* _AdbCondVar_impl<T_OFFSET>::get_instance() const
{
    return this->_instance;
}
template<typename T_OFFSET>
void _AdbCondVar_impl<T_OFFSET>::evaluate(uint8_t* buffer, T_OFFSET offset_shift)
{
    if (!is_evaluated())
    {
        if (this->_instance)
        {
            uint64_t value = pop_from_buf(buffer, this->_instance->offset + offset_shift, this->_instance->get_size());
            set_value(static_cast<int>(value));
        }
        else
        {
            throw AdbException("Variable has no instance and cannot be evaluated");
        }
    }
}
template class _AdbCondVar_impl<uint32_t>;
template class _AdbCondVar_impl<uint64_t>;
