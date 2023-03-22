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
/*************************** AdbField ***************************/
/**
 * Function: AdbField::AdbField
 **/

#include "adb_field.h"
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>
#include <iostream>

AdbField::AdbField() :
    size(0),
    offset(0xffffffff),
    definedAsArr(false),
    lowBound(0),
    highBound(0),
    unlimitedArr(false),
    dynamicArr(false),
    isReserved(false),
    userData(0)
{
}

/**
 * Function: AdbField::~AdbField
 **/
AdbField::~AdbField() {}

/**
 * Function: AdbField::isLeaf
 **/
bool AdbField::isLeaf()
{
    return subNode.empty();
}

/**
 * Function: AdbField::isStruct
 **/
bool AdbField::isStruct()
{
    return !isLeaf();
}

/**
 * Function: AdbField::operator<
 **/
bool AdbField::operator<(AdbField& other)
{
    return offset < other.offset;
}

/**
 * Function: AdbField::isArray
 **/
bool AdbField::isArray()
{
    if (unlimitedArr)
    {
        return true;
    }
    else
    {
        return definedAsArr ? true : lowBound != highBound;
    }
}

/**
 * Function: AdbField::arrayLen
 **/
u_int32_t AdbField::arrayLen()
{
    if (unlimitedArr)
    {
        return 1;
    }
    else
    {
        return (highBound - lowBound + 1);
    }
}

/**
 * Function: AdbField::isUnlimitedArr
 **/
bool AdbField::isUnlimitedArr()
{
    return unlimitedArr;
}

/**
 * Function: AdbField::isDynamicArr
 **/
bool AdbField::isDynamicArr()
{
    return dynamicArr;
}

/**
 * Function: AdbField::isArray
 **/
u_int32_t AdbField::eSize()
{
    if (unlimitedArr)
    {
        return size;
    }
    else
    {
        return size / arrayLen();
    }
}

/**
 * Function: AdbField::print
 **/
void AdbField::print(int indent)
{
    cout << indentString(indent);
    cout << "- FIELD - Name: " << name << " offset: 0x" << hex << offset / 32 * 4 << "." << dec << offset % 32
         << " size: 0x" << hex << size / 32 * 4 << "." << dec << size % 32 << " low_bound: " << lowBound
         << " high_bound: " << highBound << " sub_node: " << subNode << " isReserved: " << isReserved << endl;
}

/**
 * Function: AdbField::toXml
 **/
string AdbField::toXml(const string& addPrefix)
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
