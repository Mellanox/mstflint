/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) Jan 2013, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
 *
 * mlxarchive_mfa2_utils.h
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#ifndef MLXARCHIVE_MFA2_UTILS_H_
#define MLXARCHIVE_MFA2_UTILS_H_

#include <string>
#include <vector>
#include <compatibility.h>

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

void packBinFile(const string& file, vector<u_int8_t>& buff);

bool readFromFile(const string& fname, string& content);

unsigned int getFileSize(const string& file);

bool fexists(const string& filename);

void listDir(const char *path, vector<string>& files);

class FingerPrint {
private:
    string _fingerPrint;
public:
    FingerPrint(string fingerPrint) : _fingerPrint(fingerPrint) {};
    void pack(vector<u_int8_t>& buff) const { packString(_fingerPrint, buff); };
    inline u_int32_t getSize() const {return _fingerPrint.length();}
};

#endif
