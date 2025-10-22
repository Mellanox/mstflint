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
/**
 * Function: AdbField_impl::AdbField_impl
 **/

#include "adb_field.h"
#include <iostream>
#include <sstream>
#include <iomanip>

#include "common/tools_algorithm.h"
namespace Algorithm = mstflint::common::algorithm;

template<typename T_OFFSET>
AdbField_impl<T_OFFSET>* AdbField_impl<T_OFFSET>::create_AdbField(string name,
                                                                  T_OFFSET offset,
                                                                  address_t size,
                                                                  bool is_reserved,
                                                                  string sub_node,
                                                                  string desc)
{
    return size <= LEGACY_ADDRESS_SPACE ?
             new AdbField_impl<T_OFFSET>(name, offset, size, is_reserved, sub_node, desc) :
             new AdbFieldLarge_impl<T_OFFSET>(name, offset, size, is_reserved, sub_node, desc);
}

template<>
AdbField_impl<uint32_t>* AdbField_impl<uint32_t>::create_AdbField(string name,
                                                                  uint32_t offset,
                                                                  address_t size,
                                                                  bool is_reserved,
                                                                  string sub_node,
                                                                  string desc)
{
    return new AdbField_impl<uint32_t>(name, offset, size, is_reserved, sub_node, desc);
}

template<typename T_OFFSET>
AdbField_impl<T_OFFSET>::AdbField_impl(string i_name,
                                       T_OFFSET i_offset,
                                       short_address_t size,
                                       bool is_reserved,
                                       string sub_node,
                                       string i_desc) :
    _size{size}, name{i_name}, offset{i_offset}, desc{i_desc}, subNode{sub_node}, isReserved{is_reserved}
{
}

/**
 * Function: AdbField_impl::get_size
 **/
template<typename T_OFFSET>
typename AdbField_impl<T_OFFSET>::address_t AdbField_impl<T_OFFSET>::get_size() const
{
    return _size;
}

/**
 * Function: AdbField_impl::set_size
 **/
template<typename T_OFFSET>
void AdbField_impl<T_OFFSET>::set_size(short_address_t size)
{
    _size = size;
}

/**
 * Function: AdbField_impl::isLeaf
 **/
template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::isLeaf()
{
    return subNode.empty();
}

/**
 * Function: AdbField_impl::isStruct
 **/
template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::isStruct()
{
    return !isLeaf();
}

/**
 * Function: AdbField_impl::operator<
 **/
template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::operator<(const AdbField_impl& other) const
{
    return offset != other.offset ? offset < other.offset : name < other.name;
}

/**
 * Function: AdbField::isArray
 **/
template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::isArray()
{
    return array_type >= ArrayType::definite;
}

/**
 * Function: AdbField_impl::arrayLen
 **/
template<typename T_OFFSET>
uint32_t AdbField_impl<T_OFFSET>::arrayLen()

{
    if (array_type >= ArrayType::unlimited)
    {
        return 1;
    }
    else
    {
        return (highBound - lowBound + 1);
    }
}

/**
 * Function: AdbField_impl::isUnlimitedArr
 **/
template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::isUnlimitedArr()
{
    return array_type == ArrayType::unlimited;
}

/**
 * Function: AdbField_impl::isDynamicArr
 **/
template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::isDynamicArr()
{
    return array_type == ArrayType::dynamic;
}

/**
 * Function: AdbField_impl::isArray
 **/
template<typename T_OFFSET>
typename AdbField_impl<T_OFFSET>::address_t AdbField_impl<T_OFFSET>::eSize()
{
    if (array_type == ArrayType::unlimited)
    {
        return get_size();
    }
    else
    {
        return get_size() / arrayLen();
    }
}

/**
 * Function: AdbField_impl::isEnum
 **/
template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::isEnum()
{
    auto it = attrs.find("enum");
    return it != attrs.end();
}

/**
 * Function: AdbField_impl::getEnum
 **/
template<typename T_OFFSET>
vector<pair<string, uint64_t>> AdbField_impl<T_OFFSET>::getEnum()
{
    vector<pair<string, uint64_t>> ret;

    auto it = attrs.find("enum");
    if (it == attrs.end())
    {
        return ret;
    }

    vector<string> enum_pairs;
    vector<string> enum_pair;

    uint64_t value;
    string key;

    Algorithm::split(enum_pairs, it->second, Algorithm::is_any_of(","));

    for (auto enum_pair_str : enum_pairs)
    {
        Algorithm::split(enum_pair, enum_pair_str, Algorithm::is_any_of("="));
        if (enum_pair.size() != 2)
        {
            continue;
        }
        try
        {
            value = stoull(enum_pair[1], 0, 0);
        }
        catch (const std::invalid_argument& e)
        {
            continue;
        }
        catch (const std::out_of_range& e)
        {
            continue;
        }

        key = enum_pair[0];
        Algorithm::trim(key);
        if (key.size() == 0)
        {
            continue;
        }

        ret.push_back(make_pair(key, value));
    }
    return ret;
}

/**
 * Function: AdbFieldLarge_impl::merge_broken_name
 **/
template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::merge_broken_name(AdbField_impl<T_OFFSET>& other)
{
    vector<string> first_splitted;
    vector<string> second_splitted;
    unsigned long first_high, first_low, second_high, second_low = 0;
    signed long long first_deferred_size, second_deferred_size = 0;

    Algorithm::split(first_splitted, name, Algorithm::is_any_of("_"));
    Algorithm::split(second_splitted, other.name, Algorithm::is_any_of("_"));
    if (first_splitted.size() < 3 || first_splitted.back() == "" || second_splitted.size() != first_splitted.size())
    {
        return false;
    }
    for (size_t i = 0; i < first_splitted.size() - 2; ++i)
    {
        if (first_splitted[i] != second_splitted[i])
        {
            return false;
        }
    }
    try
    {
        first_high = stoul(first_splitted[first_splitted.size() - 2]);
        first_low = stoul(first_splitted[first_splitted.size() - 1]);
        first_deferred_size = first_high - first_low + 1;

        second_high = stoul(second_splitted[second_splitted.size() - 2]);
        second_low = stoul(second_splitted[second_splitted.size() - 1]);
        second_deferred_size = second_high - second_low + 1;
    }
    catch (const std::runtime_error&)
    {
        return false;
    }
    catch (const std::logic_error&)
    {
        return false;
    }
    if (first_deferred_size >= 0 && second_deferred_size >= 0 && get_size() == (T_OFFSET)first_deferred_size &&
        other.get_size() == (T_OFFSET)second_deferred_size && first_high + 1 == second_low)
    {
        first_splitted[first_splitted.size() - 2] = second_splitted[second_splitted.size() - 2];
        name = Algorithm::join(first_splitted, "_");
    }
    else
    {
        return false;
    }
    return true;
}

template<typename T_OFFSET>
string AdbField_impl<T_OFFSET>::get_broken_base_name()
{
    auto found_broken = attrs.find("broken32");
    auto broken = found_broken != attrs.end() && found_broken->second == "1";
    string base_name = name;
    if (!broken)
    {
        return base_name;
    }

    vector<string> splitted;
    unsigned long high, low = 0;
    signed long long deferred_size = 0;

    Algorithm::split(splitted, name, Algorithm::is_any_of("_"));
    if (splitted.size() < 3 || splitted.back() == "")
    {
        return base_name;
    }

    try
    {
        high = stoul(splitted[splitted.size() - 2]);
        low = stoul(splitted[splitted.size() - 1]);
        deferred_size = high - low + 1;
    }
    catch (const std::runtime_error&)
    {
        return base_name;
    }
    catch (const std::logic_error&)
    {
        return base_name;
    }
    if (deferred_size >= 0 && (T_OFFSET)deferred_size == get_size())
    {
        splitted.erase(splitted.end() - 2, splitted.end());
        base_name = Algorithm::join(splitted, "_");
    }
    return base_name;
}

template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::reformat_name_bitspan(AdbField_impl<T_OFFSET>& previous, AdbField_impl<T_OFFSET>& next)
{
    string previous_base_name = previous.get_broken_base_name();
    string base_name = get_broken_base_name();
    string next_base_name = next.get_broken_base_name();

    if (base_name != name && previous_base_name != base_name && base_name != next_base_name)
    {
        name = base_name;
        return true;
    }
    return false;
}

/**
 * Function: AdbFieldLarge_impl::merge_broken_default
 **/
template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::merge_broken_default(AdbField_impl<T_OFFSET>& other)
{
    auto first_found_default = attrs.find("default");
    auto second_found_default = other.attrs.find("default");
    unsigned long long first_default, second_default;

    if (first_found_default == attrs.end() || second_found_default == other.attrs.end())
    {
        return false;
    }
    try
    {
        first_default = stoull(first_found_default->second, nullptr, 0);
        second_default = stoull(second_found_default->second, nullptr, 0);
    }
    catch (const std::runtime_error&)
    {
        return false;
    }
    catch (const std::logic_error&)
    {
        return false;
    }

    second_default <<= get_size();

    stringstream hex_stream;
    hex_stream << hex << showbase << first_default + second_default;

    attrs["default"] = string(hex_stream.str());
    return true;
}

/**
 * Function: AdbFieldLarge_impl::merge_broken
 **/
template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::merge_broken(AdbField_impl<T_OFFSET>& other)
{
    auto merged_name(merge_broken_name(other));
    auto merged_default_value(merge_broken_default(other));

    set_size(get_size() + other.get_size());

    // TODO: in the future add wanings if one of the below failed
    return merged_name && merged_default_value;
}

/**
 * Function: AdbField_impl::print
 **/
template<typename T_OFFSET>
void AdbField_impl<T_OFFSET>::print(int indent)
{
    cout << indentString(indent);
    cout << "- FIELD - Name: " << name << " offset: 0x" << hex << offset / 32 * 4 << "." << dec << offset % 32
         << " size: 0x" << hex << get_size() / 32 * 4 << "." << dec << get_size() % 32 << " low_bound: " << lowBound
         << " high_bound: " << highBound << " sub_node: " << subNode << " isReserved: " << isReserved << endl;
}

/**
 * Function: AdbField_impl::toXml
 **/
template<typename T_OFFSET>
string AdbField_impl<T_OFFSET>::toXml(const string& addPrefix)
{
    string xml = "<field name=\"" + name + "\" descr=\"" + encodeXml(descNativeToXml(desc)) + "\"";
    if (isStruct())
    {
        xml += " subnode=\"" + addPrefix + subNode + "\"";
    }

    for (AttrsMap::iterator it = attrs.begin(); it != attrs.end(); it++)
    {
        if (it->first == "name" || it->first == "subnode" || it->first == "descr")
        {
            continue;
        }

        xml += " " + it->first + "=\"" + encodeXml(it->second) + "\"";
    }

    xml += " />";
    return xml;
}

template<typename T_OFFSET>
bool AdbField_impl<T_OFFSET>::compareFieldsForXmlOutput(AdbField_impl<T_OFFSET>* f1, AdbField_impl<T_OFFSET>* f2)
{
    AdbField_impl<T_OFFSET> first = *f1;
    AdbField_impl<T_OFFSET> second = *f2;
    if (first.offset / 32 < second.offset / 32)
    {
        return true;
    }
    else if (first.offset / 32 == second.offset / 32)
    {
        return first.offset > second.offset;
    }
    return false;
}

// Explicit instantiations
template class AdbField_impl<u_int32_t>;
template class AdbField_impl<u_int64_t>;

/**
 * Function: AdbFieldLarge_impl::calculate_size_low
 **/
template<typename T_OFFSET>
typename AdbFieldLarge_impl<T_OFFSET>::short_address_t AdbFieldLarge_impl<T_OFFSET>::calculate_size_low(address_t size)
{
    return size & LOW_MASK;
}

/**
 * Function: AdbFieldLarge_impl::calculate_size_high
 **/
template<typename T_OFFSET>
typename AdbFieldLarge_impl<T_OFFSET>::short_address_t AdbFieldLarge_impl<T_OFFSET>::calculate_size_high(address_t size)
{
    return size >> NUM_LOW_BITS;
}

/**
 * Function: AdbFieldLarge_impl::calculate_size
 **/
template<typename T_OFFSET>
typename AdbFieldLarge_impl<T_OFFSET>::address_t AdbFieldLarge_impl<T_OFFSET>::calculate_size(short_address_t low,
                                                                                              short_address_t high)
{
    return low + ((address_t)high << NUM_LOW_BITS);
}

/**
 * Function: AdbFieldLarge_impl::AdbFieldLarge_impl
 **/
template<typename T_OFFSET>
AdbFieldLarge_impl<T_OFFSET>::AdbFieldLarge_impl(string name,
                                                 T_OFFSET offset,
                                                 address_t size,
                                                 bool is_reserved,
                                                 string sub_node,
                                                 string desc) :
    AdbField_impl<T_OFFSET>{name, offset, calculate_size_low(size), is_reserved, sub_node, desc},
    _size_high{calculate_size_high(size)}
{
}

/**
 * Function: AdbFieldLarge_impl::get_size
 **/
template<typename T_OFFSET>
typename AdbFieldLarge_impl<T_OFFSET>::address_t AdbFieldLarge_impl<T_OFFSET>::get_size() const
{
    return calculate_size(this->_size, _size_high);
}

/**
 * Function: AdbFieldLarge_impl::set_size
 **/
template<typename T_OFFSET>
void AdbFieldLarge_impl<T_OFFSET>::set_size(address_t size)
{
    this->_size = calculate_size_low(size);
    _size_high = calculate_size_high(size);
}

/**
 * Function: AdbFieldLarge_impl::set_size
 **/
template<typename T_OFFSET>
void AdbFieldLarge_impl<T_OFFSET>::set_size(short_address_t size)
{
    this->_size = size;
    _size_high = 0;
}

// Explicit instantiations
template class AdbFieldLarge_impl<uint64_t>;
