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
/*************************** AdbField_impl ***************************/

#ifndef ADB_FIELD_H
#define ADB_FIELD_H

#include "adb_xmlCreator.h"
#include <map>
#include <string>
#include <vector>
#include <utility>
#include <limits>

using namespace xmlCreator;
using namespace std;

typedef map<string, string> AttrsMap;

template<typename T_OFFSET>
class AdbField_impl
{
public:
    enum struct ArrayType : unsigned char
    {
        none,
        definite,
        single_entry,
        unlimited,
        dynamic
    };

    using short_address_t = uint32_t; // for address in bits
    using address_t = T_OFFSET;       // for address in bits

    constexpr static auto LEGACY_ADDRESS_SPACE = (uint32_t)(-1); // in bits

    static AdbField_impl<T_OFFSET>* create_AdbField(string name,
                                                    T_OFFSET offset,
                                                    address_t size,
                                                    bool is_reserved = false,
                                                    string sub_node = "",
                                                    string desc = "");

    // Methods
    AdbField_impl() = default;
    AdbField_impl(string name,
                  T_OFFSET offset,
                  short_address_t size,
                  bool is_reserved = false,
                  string sub_node = "",
                  string desc = "");
    virtual ~AdbField_impl(){};
    bool isLeaf();
    bool isStruct();
    bool isArray();
    bool isEnum();
    vector<pair<string, uint64_t>> getEnum();
    bool merge_broken_name(AdbField_impl<T_OFFSET>& other);
    bool reformat_name_bitspan(AdbField_impl<T_OFFSET>& previous, AdbField_impl<T_OFFSET>& next);
    string get_broken_base_name();
    bool merge_broken_default(AdbField_impl<T_OFFSET>& other);
    bool merge_broken(AdbField_impl<T_OFFSET>& other);
    uint32_t arrayLen();
    bool isUnlimitedArr();
    bool isDynamicArr();

    virtual address_t get_size() const;
    virtual void set_size(short_address_t size);

    address_t eSize();
    string toXml(const string& addPrefix);

    // Operator overloading - useful for sorting
    bool operator<(const AdbField_impl<T_OFFSET>& other) const;

    // FOR DEBUG
    void print(int indent = 0);

protected:
    short_address_t _size{0};

public:
    // Members
    string name;
    T_OFFSET offset{(static_cast<T_OFFSET>(-1))}; // in bits (relative to the node start addr)
    string desc;
    uint32_t lowBound{0};
    uint32_t highBound{0};
    ArrayType array_type{};
    string subNode;
    AttrsMap attrs;
    bool isReserved{false};
    string condition; // field's visibility dynamic condition

    // FOR USER USAGE
    void* userData{nullptr};
};

template<typename T_OFFSET>
class AdbFieldLarge_impl : public AdbField_impl<T_OFFSET>
{
public:
    using short_address_t = typename AdbField_impl<T_OFFSET>::short_address_t;
    using address_t = typename AdbField_impl<T_OFFSET>::address_t;

    constexpr static auto NUM_LOW_BITS = 32;
    constexpr static auto LOW_MASK = (address_t)(-1) >> NUM_LOW_BITS;

    static short_address_t calculate_size_low(address_t size);
    static short_address_t calculate_size_high(address_t size);
    static address_t calculate_size(short_address_t low, short_address_t high);

    AdbFieldLarge_impl() = default;
    AdbFieldLarge_impl(string name,
                       T_OFFSET offset,
                       address_t size,
                       bool is_reserved = false,
                       string sub_node = "",
                       string desc = "");
    ~AdbFieldLarge_impl(){};

    address_t get_size() const override;
    void set_size(short_address_t size) override;
    void set_size(address_t size);

private:
    short_address_t _size_high{0};
};

using AdbFieldLegacy = AdbField_impl<uint32_t>;
// using AdbField = AdbField_impl<uint32_t>;
using AdbField = AdbField_impl<uint64_t>;
// using AdbFieldNewDevices = AdbField_impl<uint64_t>;
using AdbFieldLarge = AdbFieldLarge_impl<uint64_t>;

#endif
