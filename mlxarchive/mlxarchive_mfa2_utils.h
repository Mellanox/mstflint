
/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
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
 */

/*
 * mlxarchive_mfa2_utils.h
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXARCHIVE_MFA2_UTILS_H_
#define MLXARCHIVE_MFA2_UTILS_H_
#include <string.h>
#include <string>
#include <vector>
#include <compatibility.h>

#include "mfa2_buff.h"

#define MFA2_FINGER_PRINT "MLNX.MFA2.XZ.00!"
#define FINGER_PRINT_SIZE (strlen(MFA2_FINGER_PRINT))

using namespace std;

#define VECTOR_ITERATOR(t, v, i) \
    for(vector<t>::iterator i = v.begin() ; i != v.end(); ++i)

#define CONST_VECTOR_ITERATOR(t, v, i) \
    for(vector<t>::const_iterator i = v.begin() ; i != v.end(); ++i)

enum MFA2Type {
    MFA2Type_MULTI_PART = 0x1,
    MFA2Type_PACKAGE_DESCRIPTOR = 0x2,
    MFA2Type_DEVICE_DESCRIPTOR = 0x3,
    MFA2Type_COMPONENT_DESCRIPTOR = 0X4,
    MFA2Type_USER_DATA = 0X5,
    MFA2Type_COMMENTS = 0X20,
    MFA2Type_VERSION = 0X21,
    MFA2Type_COMPONENT_PTR = 0X22,
    MFA2Type_VENDOR_NAME = 0x23,
    MFA2Type_PRODUCT_NAME = 0x24,
    MFA2Type_PRODUCT_DESC = 0x25,
    MFA2Type_PACKAGE_CREATOR_URL = 0x26,
    MFA2Type_SOURCE_FILENAME  = 0x27,
    MFA2Type_FILENAME = 0x28,
    MFA2Type_SECURITY_INFO = 0x29,
    MFA2Type_PSID = 0x2A,
    MFA2Type_PSID_BRANCH = 0x2B,
    MFA2Type_PCI_IDs = 0x2C,
    MFA2Type_EXP_ROM_VERSION = 0x2D,
    MFA2Type_USER_TIMESTAMP = 0x2E,
    MFA2Type_SHA256 = 0x2F,
    MFA2Type_DESCRIPTORSSHA256 = 0x30,
    MFA2Type_PADDING  = 0x31
};

void packString(const string& str, vector<u_int8_t>& buff);

void packBytesArray(const u_int8_t* arr, unsigned int len, vector<u_int8_t>& buff);

void unpackBytesArray(u_int8_t* arr, unsigned int len, vector<u_int8_t>& buff);

void packBinFile(const string& file, vector<u_int8_t>& buff);

bool readFromFile(const string& fname, string& content);

unsigned int getFileSize(const string& file);

bool fexists(const string& filename);
bool isFile(const string& filename);

void listDir(const char *path, vector<string>& files);

class FingerPrint {
private:
    string _fingerPrint;
public:
    FingerPrint(string fingerPrint) : _fingerPrint(fingerPrint) {};
    void pack(vector<u_int8_t>& buff) const { packString(_fingerPrint, buff); };
    inline u_int32_t getSize() const {return _fingerPrint.length();}
    bool unpack(Mfa2Buffer & buff) {
        buff.read(_fingerPrint, FINGER_PRINT_SIZE); 
        if (_fingerPrint != MFA2_FINGER_PRINT) {
            return false;
        }
        return true;
    }
    string toString() const {return _fingerPrint;}
};

#endif
