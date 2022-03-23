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
/*************************** AdbConfig ***************************/
/**
 * Function: AdbField::print
 **/

#include "adb_config.h"
#include <iostream>

void AdbConfig::print(int indent) {
    cout << indentString(indent) << "Attributes:" << endl;
    AttrsMap::iterator iter;
    for (iter = attrs.begin(); iter != attrs.end(); iter++)
        cout << indentString(indent + 1) << iter->first << " - "
                << iter->second << endl;

    cout << indentString(indent) << "Enums:" << endl;
    for (iter = enums.begin(); iter != enums.end(); iter++)
        cout << indentString(indent + 1) << iter->first << " - "
                << iter->second << endl;
}

/**
 * Function: AdbConfig::toXml
 **/
string AdbConfig::toXml() {
    string xml = "<config ";

    for (AttrsMap::iterator it = attrs.begin(); it != attrs.end(); it++) {
        xml += " " + it->first + "=\"" + encodeXml(it->second) + "\"";
    }

    if (!enums.empty()) {
        xml += " >\n";

        for (AttrsMap::iterator it = enums.begin(); it != enums.end(); it++) {
            xml += "\t<enum  name=\"" + encodeXml(it->first) + "\" value=\""
                    + encodeXml(it->second) + "\" />\n";
        }
        xml += "</config>";
    } else {
        xml += " />";
    }

    return xml;
}
