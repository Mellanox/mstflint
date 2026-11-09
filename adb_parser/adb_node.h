/*
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. ALL RIGHTS RESERVED.
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
 */
/*************************** AdbNode_impl ***************************/

#ifndef ADB_NODE_H
#define ADB_NODE_H

#include "adb_xmlCreator.h"
#include <string>
#include <map>
#include <vector>

using namespace std;
using namespace xmlCreator;

template<typename T_OFFSET>
class AdbField_impl;

template<typename T_OFFSET>
class AdbFieldLarge_impl;

typedef map<string, string> AttrsMap;

template<typename T_OFFSET>
class AdbNode_impl
{
public:
    using AdbField = AdbField_impl<T_OFFSET>;
    using FieldsList = vector<AdbField*>;

    using short_address_t = typename AdbField::short_address_t; // for address in bits
    using address_t = typename AdbField::address_t;             // for address in bits

    constexpr static auto LEGACY_ADDRESS_SPACE = AdbField::LEGACY_ADDRESS_SPACE; // in bits

    // Methods
    static AdbNode_impl<T_OFFSET>* create_AdbNode(string name,
                                                  address_t size,
                                                  bool is_union = false,
                                                  string desc = "",
                                                  string file_name = "",
                                                  int line_num = -1);

    AdbNode_impl() = default;
    AdbNode_impl(string name,
                 short_address_t size,
                 bool is_union = false,
                 string desc = "",
                 string file_name = "",
                 int line_num = -1);
    virtual ~AdbNode_impl();

    virtual address_t get_size() const;
    virtual void set_size(short_address_t size);

    address_t get_max_leaf_size() const;
    void update_max_leaf(AdbField* other);

    string toXml(const string& addPrefix, bool bigEndian = false);

    // FOR DEBUG
    void print(int indent = 0);

protected:
    short_address_t _size{0}; // in bits

public:
    // Members
    string name;
    AdbField* _max_leaf{nullptr};
    bool isUnion{false};
    string desc;
    FieldsList fields;
    FieldsList condFields; // Field that weren't instantiated due to not satisfied condition
    AttrsMap attrs;
    bool inLayout{false};

    // defined in
    string fileName;
    int lineNumber{-1};

    // FOR USER USAGE
    void* userData{nullptr};
};

template<typename T_OFFSET>
class AdbNodeLarge_impl : public AdbNode_impl<T_OFFSET>
{
public:
    using AdbField = AdbFieldLarge_impl<T_OFFSET>;
    using FieldsList = vector<AdbField*>;

    using short_address_t = typename AdbNodeLarge_impl<T_OFFSET>::short_address_t;
    using address_t = typename AdbNodeLarge_impl<T_OFFSET>::address_t;

    constexpr static auto NUM_LOW_BITS = AdbField::NUM_LOW_BITS;
    constexpr static auto LOW_MASK = AdbField::LOW_MASK;

    AdbNodeLarge_impl() = default;
    AdbNodeLarge_impl(string name,
                      address_t size,
                      bool is_union = false,
                      string desc = "",
                      string file_name = "",
                      int line_num = -1);
    ~AdbNodeLarge_impl(){};
    address_t get_size() const override;
    void set_size(short_address_t size) override;
    void set_size(address_t size);

private:
    short_address_t _size_high{0};
};

using AdbNodeLegacy = AdbNode_impl<uint32_t>;
// using AdbNode = AdbNode_impl<uint32_t>;
using AdbNode = AdbNode_impl<uint64_t>;
// using AdbNodeNewDevices = AdbNode_impl<uint64_t>;
using AdbNodeLarge = AdbNodeLarge_impl<uint64_t>;

#endif
