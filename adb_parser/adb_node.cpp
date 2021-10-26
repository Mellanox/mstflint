/*
 * Copyright (C) Jan 2019 Mellanox Technologies Ltd. All rights reserved.
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
 */
/*************************** AdbNode ***************************/

/**
 *  * Function: AdbNode::AdbNode
 *   **/

#include "adb_node.h"
#include "adb_field.h"
#include <iostream>

#if __cplusplus >= 201402L
#include <regex>
#else
#include <boost/regex.hpp>
using namespace boost;
#endif

#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

AdbNode::AdbNode() : size(0), isUnion(false), lineNumber(-1), userData(0)
{
}

/**
 *  * Function: AdbNode::~AdbNode
 *   **/
AdbNode::~AdbNode()
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
 *  * Function: AdbNode::toXml
 *   **/
string AdbNode::toXml(const string &addPrefix)
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
    stable_sort(allFields.begin(), allFields.end(), compareFieldsPtr<AdbField>);

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
 *  * Function: AdbNode::print
 *   **/
void AdbNode::print(int indent)
{
    cout << indentString(indent);
    cout << "+ Node Name: " << name << " size: 0x" << hex << size / 32 * 4
         << "." << dec << size % 32 << " isUnion: " << isUnion
         << " Description: " << desc << endl;

    cout << indentString(indent) << "Fields:" << endl;
    for (size_t i = 0; i < fields.size(); i++)
        fields[i]->print(indent + 1);
}
