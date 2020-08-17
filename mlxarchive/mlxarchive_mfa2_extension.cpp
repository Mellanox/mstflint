
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
 * mlxarchive_mfa2_extension.cpp
 *
 *  Created on: March 23, 2017
 *      Author: Ahmad Soboh
 */

#include <sstream>
#include "mlxarchive_mfa2_extension.h"
#include <ctime>

using namespace mfa2;

void VersionExtension::fillTimeAndDate()
{
    time_t tt;
    time(&tt);
    tm TM = *localtime(&tt);
    _seconds = TM.tm_sec;
    _minutes = TM.tm_min;
    _hours = TM.tm_hour;
    _day = TM.tm_mday;
    _month = TM.tm_mon;
    _year = 1900 + TM.tm_year;
}

MFA2Type Extension::extensionTypeToMFA2Type(ExtensionType type)
{
    switch(type) {
        case VersionExtensionType:
            return MFA2Type_VERSION;
        case SecurityInfoExtensionType:
            return MFA2Type_SECURITY_INFO;
        case ComponentPointerExtensionType:
            return MFA2Type_COMPONENT_PTR;
        case CommentExtensionType:
            return MFA2Type_COMMENTS;
        case PSIDExtensionType:
            return MFA2Type_PSID;
        case SourceFileNameExtensionType:
            return MFA2Type_SOURCE_FILENAME;
        default:
            //TODO throw exception
            return MFA2Type_SOURCE_FILENAME;
    }
}
Extension::Extension(u_int8_t version, ExtensionType type, u_int32_t length) :
        Element(version, extensionTypeToMFA2Type(type), length)
{
}

VersionExtension::VersionExtension(const u_int16_t* version) :
        Extension(ELEMENT_VERSION, VersionExtensionType, LENGTH)
{
    /*printf("version = %d.%d.%d", version[0], version[1], version[2]);
    printf("date = %d.%d.%d", date[0], date[1], date[2]);*/
    _major = version[0];
    _subMinor = version[2];
    _minor = version[1];
    fillTimeAndDate();
}

VersionExtension::VersionExtension(const string& version) :
        Extension(ELEMENT_VERSION, VersionExtensionType, LENGTH)
{
    int a, b, c;
    sscanf(version.c_str(), "%d.%d.%d", &a, &b, &c);
    _major = a;
    _subMinor = c;
    _minor = b;
    fillTimeAndDate();
}

VersionExtension::VersionExtension(const u_int16_t* version, const u_int16_t* fw_rel_date):
    Extension(ELEMENT_VERSION, VersionExtensionType, LENGTH)
{
    _major = version[0];
    _subMinor = version[2];
    _minor = version[1];
    _seconds = 0;
    _minutes = 0;
    _hours = 12;
    _day = fw_rel_date[0];
    _month = fw_rel_date[1];
    _year = fw_rel_date[2];
}

void VersionExtension::pack(vector<u_int8_t>& buff) const
{
    vector<u_int8_t> tmpBuff;
    struct tools_open_version version;

    //pack common header
    _commonHeader.pack(buff);

    //pack version info
    tmpBuff.resize(tools_open_version_size());
    memset(&version, 0x0, sizeof(version));
    version.version_major = _major;
    version.version_sub_minor = _subMinor;
    version.version_minor = _minor;
    version.day = _day;
    version.month = _month;
    version.year = _year;
    version.seconds = _seconds;
    version.minutes = _minutes;
    version.hour = _hours;
 
    tools_open_version_pack(&version, tmpBuff.data());
    buff.insert(buff.end(), tmpBuff.begin(), tmpBuff.end());
}

bool VersionExtension::unpack(Mfa2Buffer & buff)
{
    //unpack common header
    _commonHeader.unpack(buff);

    struct tools_open_version version;
    int arr_size = tools_open_version_size();
    u_int8_t * arr = new u_int8_t[arr_size];
    buff.read(arr, arr_size);
    memset(&version, 0x0, arr_size);
    tools_open_version_unpack(&version, arr);
    delete[] arr;
    arr = NULL;
    //unpack version info
    _major = version.version_major;
    _subMinor = version.version_sub_minor;
    _minor = version.version_minor;
    _day = version.day;
    _month = version.month;
    _year = version.year;
    _seconds = version.seconds;
    _minutes = version.minutes;
    _hours = version.hour;
    return true;
}

string VersionExtension::getVersion(bool pad_sub_minor) const {
    stringstream ss;
    string res;
    if (pad_sub_minor){
        char _sub_minor_str[5] = {0};
        snprintf(_sub_minor_str, sizeof(_sub_minor_str), "%04d", (int)_subMinor);
        ss << (int)_major << '.' << (int)_minor << '.' << _sub_minor_str;
    }
    else {
        ss << (int)_major << '.' << (int)_minor << '.' << (int)_subMinor;
    }
    ss>>res;
    return res;
}


string VersionExtension::getDateAndTime() const {
    tm tm_obj;
    tm_obj.tm_sec = _seconds;
    tm_obj.tm_min = _minutes;
    tm_obj.tm_hour = _hours;
    tm_obj.tm_mday = _day;
    tm_obj.tm_mon = _month;
    tm_obj.tm_year = _year - 1900;
    char buffer [64];
    strftime(buffer,64,"%Y-%m-%d %H:%M:%S", &tm_obj);
    return string(buffer);
}

void VersionExtension::getDateAndTime(char* buffer) const {
    sprintf(buffer, "%x.%x.%x", _day, _month, _year);
}

void ComponentPointerExtension::pack(vector<u_int8_t>& buff) const
{
    vector<u_int8_t> tmpBuff;
    struct tools_open_component_ptr componentPointer;

    //pack common header
    _commonHeader.pack(buff);

    tmpBuff.resize(tools_open_component_ptr_size());
    memset(&componentPointer, 0x0, sizeof(componentPointer));
    componentPointer.component_index = _componentIndex;
    componentPointer.storage_id = _storageId;
    componentPointer.storage_address = _storageAddress;
    tools_open_component_ptr_pack(&componentPointer, tmpBuff.data());
    buff.insert(buff.end(), tmpBuff.begin(), tmpBuff.end());

}

bool ComponentPointerExtension::unpack(Mfa2Buffer & buff)
{
    //unpack common header
    _commonHeader.unpack(buff);

    struct tools_open_component_ptr componentPointer;
    int arr_size = tools_open_component_ptr_size();
    u_int8_t * arr = new u_int8_t[arr_size];
    buff.read(arr, arr_size);
    memset(&componentPointer, 0x0, arr_size);
    tools_open_component_ptr_unpack(&componentPointer, arr);
    delete[] arr;
    arr = NULL;
    //unpack version info
    _componentIndex = componentPointer.component_index;
    _storageId = componentPointer.storage_id;
    _storageAddress = componentPointer.storage_address;
    return true;
}

SHA256Extension::SHA256Extension(enum SHA256Scope scope) :
        Extension(ELEMENT_VERSION, scopeToExtensionType(scope), LENGTH)
{
    _digest.resize(LENGTH);
};

Extension::ExtensionType SHA256Extension::scopeToExtensionType(enum SHA256Scope scope)
{
    switch(scope) {
    case SHA256Scope_Descriptors:
        return DescriptorsSHA256ExtensionType;
    case SHA256Scope_All:
        return SHA256ExtensionType;
    default:
        //throw exception TODO
        return SHA256ExtensionType;
    }
}

void SHA256Extension::setDigest(vector<u_int8_t> digest)
{
    _digest = digest;
}

void SHA256Extension::pack(vector<u_int8_t>& buff) const
{
    //pack common header
    _commonHeader.pack(buff);

    packBytesArray(_digest.data(), _digest.size(), buff);
}

bool SHA256Extension::unpack(Mfa2Buffer & buff)
{
    //unpack common header
    _commonHeader.unpack(buff);

    u_int16_t length = _commonHeader.getLength();
    u_int8_t * arr = new u_int8_t[length];
    buff.read(arr, length);
    _digest.resize(length);
    for(u_int16_t i = 0; i < length; i++) {
        _digest.push_back(arr[i]);
    }
    delete[] arr;
    arr = NULL;
    return true;
}

/*void DescriptorsSHA256Extension::pack(vector<u_int8_t>& buff) const
{
    u_int8_t sha[0x140] = {0};
    packBytesArray(sha, 0x140, buff);
}*/

/*StringExtension::StringExtension(HeaderType type, string str) :_str(str)
{

}*/

void StringExtension::pack(vector<u_int8_t>& buff) const
{
    //pack common header
    _commonHeader.pack(buff);

    packString(_str, buff);
}

bool StringExtension::unpack(Mfa2Buffer & buff)
{
    //unpack common header
    _commonHeader.unpack(buff);

    u_int16_t length = _commonHeader.getLength();
    buff.read(_str, length);
    return true;
}
