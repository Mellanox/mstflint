/*
 * Copyright (C) Jan 2020 Mellanox Technologies Ltd. All rights reserved.
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

#include "fw_version.h"
#include <sstream>
#include <stdlib.h>
#include <stdio.h>

const unsigned short MAX_MINOR_LENGETH = 4;
const unsigned short FORMAT0_CIB_MAJOR = 10;
const unsigned short FORMAT0_MAX_MINOR_CIB = 10;
const unsigned short FORMAT0_SIB_MAJOR = 11;
const unsigned short FORMAT0_MAX_MINOR_SIB = 1;
const unsigned short FORMAT1_MIN_MINOR = 100;

FwVersion::FwVersion() :
        _major(0), _minor(0), _subminor(0), _devBranchTag("") {
}

FwVersion::FwVersion(unsigned short int major, unsigned short int minor,
        unsigned short int subminor, const std::string& devBranchTag) :
        _major(major), _minor(minor), _subminor(subminor), _devBranchTag(
                devBranchTag) {
}

FwVersion::~FwVersion() {
}

FwVersion::FwVersion(const FwVersion& rhs) :
        _major(rhs._major), _minor(rhs._minor), _subminor(rhs._subminor), _devBranchTag(
                rhs._devBranchTag) {
}

std::string FwVersion::get() const {
    return get_fw_version();
}

FwVersion& FwVersion::operator =(const FwVersion& rhs) {
    if (this != &rhs) {
        _major = rhs._major;
        _minor = rhs._minor;
        _subminor = rhs._subminor;
        _devBranchTag = rhs._devBranchTag;
    }
    return *this;
}

bool FwVersion::operator ==(const FwVersion& rhs) const {
    return _major == rhs._major &&
           _minor == rhs._minor &&
           _subminor == rhs._subminor &&
           _devBranchTag == rhs._devBranchTag;
}

std::ostream& operator <<(std::ostream& os, const FwVersion& fw_ver) {
    return os << fw_ver.get_fw_version();
}

std::string FwVersion::get_fw_version(const std::string& master_format,
        bool even_subminor, const std::string& not_set) const {
    if (!is_set()) {
        return not_set;
    }
    if (!is_master_branch()) {
        return _devBranchTag;
    }
    return get_master_version(master_format, even_subminor);
}

std::string FwVersion::get_master_version(const std::string& format,
        bool even_subminor) const {
    char buff[MAX_VERSION_LENGTH + 1];
    snprintf(buff, sizeof(buff), format.c_str(), _major, _minor,
            _subminor - (even_subminor ? _subminor % 2 : 0));
    return buff;
}

bool FwVersion::is_set() const {
    return _major || _minor || _subminor;
}

bool FwVersion::operator !=(const FwVersion& rhs) const {
    return !(this->operator ==(rhs));
}

bool FwVersion::is_master_branch() const {
    return _devBranchTag.empty();
}

bool FwVersion::are_same_branch(const FwVersion& rhs) const {
    // one is master other is dev
    if (is_master_branch() != rhs.is_master_branch())
        return false;
    // both are master
    if (is_master_branch())
        return true;
    // check if prefix for string is the same
    return _devBranchTag.substr(0, _devBranchTag.size() - MAX_MINOR_LENGETH)
            == rhs._devBranchTag.substr(0,
                    rhs._devBranchTag.size() - MAX_MINOR_LENGETH);
}

int FwVersion::compare_master_version(const FwVersion& rhs) const {
    if (get_master_format() != rhs.get_master_format()) {
        // check for old formats
        return get_master_format() - rhs.get_master_format();
    }
    unsigned short int lhs_master_version[] = { _major, _minor, _subminor };
    unsigned short int rhs_master_version[] = { rhs._major, rhs._minor, rhs._subminor };
    for (unsigned short i = 0; i < sizeof(lhs_master_version)/sizeof(lhs_master_version[0]); i++) {
        if (lhs_master_version[i] != rhs_master_version[i]) {
            return lhs_master_version[i] - rhs_master_version[i];
        }
    }
    return 0;
}

int FwVersion::compare(const FwVersion& rhs) const {
    if (!are_same_branch(rhs)) {
        throw FwVersionException();
    }
    if (is_master_branch()) {
        //master branch
        return compare_master_version(rhs);
    }
    // branch version
    return atoi(
            _devBranchTag.substr(_devBranchTag.size() - MAX_MINOR_LENGETH,
                    MAX_MINOR_LENGETH).c_str())
            - atoi(
                    rhs._devBranchTag.substr(
                            rhs._devBranchTag.size() - MAX_MINOR_LENGETH,
                            MAX_MINOR_LENGETH).c_str());
}

int FwVersion::get_master_format() const {
    if (_minor >= FORMAT1_MIN_MINOR) {
        return 1;
    }
    if ((_major == FORMAT0_CIB_MAJOR && _minor <= FORMAT0_MAX_MINOR_CIB)
            || (_major == FORMAT0_SIB_MAJOR && _minor <= FORMAT0_MAX_MINOR_SIB)) {
        return 0;
    }
    return 2;
}

bool FwVersion::operator <(const FwVersion& rhs) const {
    return compare(rhs) < 0;
}

bool FwVersion::operator <=(const FwVersion& rhs) const {
    return compare(rhs) <= 0;
}

bool FwVersion::operator >(const FwVersion& rhs) const {
    return compare(rhs) > 0;
}

bool FwVersion::operator >=(const FwVersion& rhs) const {
    return compare(rhs) >= 0;
}

FwVersion* FwVersion::clone() const {
    return new FwVersion(*this);
}
