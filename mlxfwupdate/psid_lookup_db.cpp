
/*
 * Copyright (C) Jan 2006 Mellanox Technologies Ltd. All rights reserved.
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

#include "psid_lookup_db.h"
#include <stdio.h>
#include <iostream>


int PsidLookupDB::csv2vector(string str, vector<string> &explode)
{
    size_t pos;
    int cnt = 0;

    if (str.size() == 0) {
        return 0;
    }

    do {
        cnt++;
        pos = str.find(',');
        if (pos == string::npos) {
            explode.push_back(str);
            break;
        }
        explode.push_back(str.substr(0, pos));
        str = str.substr(pos + 1);
    } while (str.size() > 0);

    return cnt;
}


void PsidLookupDB::readFile(string fName)
{
    FILE *fin;
    char tmpb[256];

    if ((fin = fopen(fName.c_str(), "r")) == NULL) {
        return;
    }

    while (fgets(tmpb, sizeof(tmpb), fin)) {
        PsidLookupInfo pi;
        vector<string> expld;
        string str = tmpb;
        if (str.find('\n')) {
            str = str.substr(0, str.size() - 1); //remove newline character
        }

        if (csv2vector(str, expld) < 4) {
            continue;
        }

        pi.psid = expld[0];
        pi.pn = expld[2];
        pi.prodDesc = expld[3];
        _keyLookupMap[expld[0]] = pi;
        _keyLookupMap[expld[1]] = pi;
    }
    fclose(fin);
}


string PsidLookupDB::getPN(string id)
{
    if (_keyLookupMap.find(id) == _keyLookupMap.end()) {
        return "";
    }
    return _keyLookupMap[id].pn;
}


string PsidLookupDB::getProdDesc(string id)
{
    if (_keyLookupMap.find(id) == _keyLookupMap.end()) {
        return "";
    }
    return _keyLookupMap[id].prodDesc;
}


string PsidLookupDB::getPsid(string id)
{
    if (_keyLookupMap.find(id) == _keyLookupMap.end()) {
        return "";
    }
    return _keyLookupMap[id].psid;
}

bool PsidLookupDB::isPsidExist(string psid)
{
    if (_keyLookupMap.find(psid) == _keyLookupMap.end()) {
        return false;
    }
    return true;
}
