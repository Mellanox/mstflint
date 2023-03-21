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

#ifndef ADB_FIELD_H
#define ADB_FIELD_H

#include "adb_xmlCreator.h"
#include <map>
#include <string>

using namespace xmlCreator;
using namespace std;

typedef map < string, string > AttrsMap;

class AdbField
{
public:
    /* Methods */
    AdbField();
    ~AdbField();
    bool isLeaf();
    bool isStruct();
    bool isArray();
    u_int32_t arrayLen();
    bool isUnlimitedArr();
    bool isDynamicArr();
    u_int32_t eSize();
    string toXml(const string& addPrefix);

    /* Operator overloading - useful for sorting */
    bool operator < (AdbField & other);

    /* FOR DEBUG */
    void print(int indent = 0);

public:
    /* Members */
    string    name;
    u_int32_t size;   /* in bits */
    u_int32_t offset; /* in bits (relative to the node start addr) */
    string    desc;
    bool      definedAsArr;
    u_int32_t lowBound;
    u_int32_t highBound;
    bool      unlimitedArr;
    bool      dynamicArr;
    string    subNode;
    AttrsMap  attrs;
    bool      isReserved;
    string    condition; /* field's visibility dynamic condition */

    /* FOR USER USAGE */
    void* userData;
};

#endif /* ifndef ADB_FIELD_H */
