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

/**
 *  * Function: AdbNode_impl::AdbNode_impl
 *   **/

#include "adb_node.h"
#include "adb_field.h"
#include <iostream>
#include <algorithm>

/**
 *  * Function: AdbNode_impl::create_AdbNode
 *   **/
template<typename T_OFFSET>
AdbNode_impl<T_OFFSET>* AdbNode_impl<T_OFFSET>::create_AdbNode(string name,
                                                               address_t size,
                                                               bool is_union,
                                                               string desc,
                                                               string file_name,
                                                               int line_num)
{
    return size <= LEGACY_ADDRESS_SPACE ?
             new AdbNode_impl<T_OFFSET>(name, size, is_union, desc, file_name, line_num) :
             new AdbNodeLarge_impl<T_OFFSET>(name, size, is_union, desc, file_name, line_num);
}

template<>
AdbNode_impl<uint32_t>* AdbNode_impl<uint32_t>::create_AdbNode(string name,
                                                               address_t size,
                                                               bool is_union,
                                                               string desc,
                                                               string file_name,
                                                               int line_num)
{
    return new AdbNode_impl<uint32_t>(name, size, is_union, desc, file_name, line_num);
}

/**
 *  * Function: AdbNode_impl::AdbNode_impl
 *   **/
template<typename T_OFFSET>
AdbNode_impl<T_OFFSET>::AdbNode_impl(string i_name,
                                     short_address_t size,
                                     bool is_union,
                                     string i_desc,
                                     string file_name,
                                     int line_num) :
    _size{size}, name{i_name}, isUnion{is_union}, desc{i_desc}, fileName{file_name}, lineNumber{line_num}
{
}

/**
 *  * Function: AdbNode_impl::~AdbNode_impl
 *   **/
template<typename T_OFFSET>
AdbNode_impl<T_OFFSET>::~AdbNode_impl()
{
    for (size_t i = 0; i < fields.size(); i++)
    {
        delete fields[i];
    }
    fields.clear();
    for (size_t i = 0; i < condFields.size(); i++)
    {
        delete condFields[i];
    }
    condFields.clear();
}

/**
 * Function: AdbNode_impl::get_size
 **/
template<typename T_OFFSET>
typename AdbNode_impl<T_OFFSET>::address_t AdbNode_impl<T_OFFSET>::get_size() const
{
    return _size;
}

/**
 * Function: AdbNode_impl::set_size
 **/
template<typename T_OFFSET>
void AdbNode_impl<T_OFFSET>::set_size(short_address_t size)
{
    _size = size;
}

/**
 * Function: AdbNode_impl::get_max_leaf_size
 **/
template<typename T_OFFSET>
typename AdbNode_impl<T_OFFSET>::address_t AdbNode_impl<T_OFFSET>::get_max_leaf_size() const
{
    return _max_leaf ? _max_leaf->get_size() : 0;
}

/**
 * Function: AdbNode_impl::update_max_leaf
 **/
template<typename T_OFFSET>
void AdbNode_impl<T_OFFSET>::update_max_leaf(AdbField* other)
{
    uint64_t esize = other->eSize();
    if ((other->isLeaf() || other->subNode == "uint64") && (esize == 16 || esize == 32 || esize == 64) &&
        esize > get_max_leaf_size())
    {
        _max_leaf = other;
    }
}

/**
 *  * Function: AdbNode_impl::toXml
 *   **/
template<typename T_OFFSET>
string AdbNode_impl<T_OFFSET>::toXml(const string& addPrefix, bool bigEndian)
{
    string xml = "<node name=\"" + addPrefix + name + "\" descr=\"" + encodeXml(descNativeToXml(desc)) + "\"";
    for (AttrsMap::iterator it = attrs.begin(); it != attrs.end(); it++)
    {
        if (it->first == "name" || it->first == "descr")
        {
            continue;
        }

        xml += " " + it->first + "=\"" + encodeXml(it->second) + "\"";
    }
    xml += " >\n";

    FieldsList allFields = fields;
    allFields.insert(allFields.end(), condFields.begin(), condFields.end());
    std::stable_sort(
      allFields.begin(), allFields.end(), bigEndian ? AdbField::compareFieldsForXmlOutput : compareFieldsPtr<AdbField>);

    for (size_t i = 0; i < allFields.size(); i++)
    {
        if (allFields[i]->isReserved)
        {
            continue;
        }

        xml += "\t" + allFields[i]->toXml(addPrefix) + "\n";
    }

    xml += "</node>";
    return xml;
}

/**
 *  * Function: AdbNode_impl::print
 *   **/
template<typename T_OFFSET>
void AdbNode_impl<T_OFFSET>::print(int indent)
{
    cout << indentString(indent);
    cout << "+ Node Name: " << name << " size: 0x" << hex << get_size() / 32 * 4 << "." << dec << get_size() % 32
         << " isUnion: " << isUnion << " Description: " << desc << endl;

    cout << indentString(indent) << "Fields:" << endl;
    for (size_t i = 0; i < fields.size(); i++)
        fields[i]->print(indent + 1);
}

// Explicit instantiations
template class AdbNode_impl<uint32_t>;
template class AdbNode_impl<uint64_t>;

/**
 * Function: AdbNodeLarge_impl::AdbNodeLarge_impl
 **/
template<typename T_OFFSET>
AdbNodeLarge_impl<T_OFFSET>::AdbNodeLarge_impl(string name,
                                               address_t size,
                                               bool is_union,
                                               string desc,
                                               string file_name,
                                               int line_num) :
    AdbNode_impl<T_OFFSET>{name, AdbField::calculate_size_low(size), is_union, desc, file_name, line_num},
    _size_high{AdbField::calculate_size_high(size)}
{
}

/**
 * Function: AdbNodeLarge_impl::get_size
 **/
template<typename T_OFFSET>
typename AdbNodeLarge_impl<T_OFFSET>::address_t AdbNodeLarge_impl<T_OFFSET>::get_size() const
{
    return AdbField::calculate_size(this->_size, _size_high);
}
/**
 * Function: AdbNodeLarge_impl::set_size
 **/
template<typename T_OFFSET>
void AdbNodeLarge_impl<T_OFFSET>::set_size(address_t size)
{
    this->_size = AdbField::calculate_size_low(size);
    _size_high = AdbField::calculate_size_high(size);
}

/**
 * Function: AdbNodeLarge_impl::set_size
 **/
template<typename T_OFFSET>
void AdbNodeLarge_impl<T_OFFSET>::set_size(short_address_t size)
{
    this->_size = size;
    _size_high = 0;
}

// Explicit instantiations
template class AdbNodeLarge_impl<u_int64_t>;
