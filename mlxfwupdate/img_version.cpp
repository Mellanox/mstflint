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
#include <stdio.h>
#include <string.h>

#include <fw_ops.h>

#include "img_version.h"
#include "fw_version_old_clp.h"
#include "fw_version_with_sub_build.h"

const string MASTER_ARGUMENTS = "Unknown number of master arguments";
const string SUBMINOR_VALUE = "Invalid subminor value";
const string NOT_SET = "FW version isn't set";
const string ALREADY_SET = "Trying to set an already set FW version";
const int UPDATE_ON_DIFFERENT_BRANCHES = -1;

ImgVersion::ImgVersion() :
        _type(), _fwVer(NULL), _isExpansionRomUnknown(false), _isOldMinor(
                false), _isSubBuild(false) {
}

ImgVersion::ImgVersion(const ImgVersion& rhs) :
        _type(rhs._type), _isExpansionRomUnknown(rhs._isExpansionRomUnknown), _isOldMinor(
                rhs._isOldMinor), _isSubBuild(rhs._isSubBuild) {
    _fwVer = rhs._fwVer->clone();
}

ImgVersion::~ImgVersion() {
    if (_fwVer != NULL) {
        delete _fwVer;
        _fwVer = NULL;
    }
}

string ImgVersion::getTypeStr() {
    return _type;
}

ImgVersion& ImgVersion::operator =(const ImgVersion& rhs) {
    if (this != &rhs) {
        _type = rhs._type;
        if (_fwVer != NULL) {
            throw SetVersionException(ALREADY_SET);
        }
        _fwVer = rhs._fwVer->clone();
        _isExpansionRomUnknown = rhs._isExpansionRomUnknown;
        _isOldMinor = rhs._isOldMinor;
        _isSubBuild = rhs._isSubBuild;
    }
    return *this;
}

void ImgVersion::setVersion(const std::string& imgType, u_int8_t verSz,
        const u_int16_t* ver, const string& verBranch) {
    if (_fwVer != NULL) {
        throw SetVersionException(ALREADY_SET);
    }
    switch (verSz) {
    case 3:
        _fwVer = new FwVersion(ver[0], ver[1], ver[2], verBranch);
        _isSubBuild = false;
        break;
    case 4:
        if (ver[2] * 100 + ver[3] > 9999) {
            throw SetVersionException(SUBMINOR_VALUE);
        }
        _fwVer = new FwVersionWithSubBuild(ver[0], ver[1],
                ver[2] * 100 + ver[3], verBranch);
        _isSubBuild = true;
        break;
    case 1:
        if (imgType != "CLP") {
            throw SetVersionException(MASTER_ARGUMENTS);
        }
        _fwVer = new FwVersionOldClp(0, ver[0], 0, verBranch);
        _isSubBuild = false;
        break;
    default:
        throw SetVersionException(MASTER_ARGUMENTS);
    }
    _type = imgType;
    _isOldMinor = (ver[1] <= 99);
}

string ImgVersion::getPrintableVersion(int ffv, bool show_type) {
    if (_fwVer == NULL) {
        throw SetVersionException(NOT_SET);
    }
    string prefix = show_type ? (_type + " ") : "", format;
    if (_type.size()) {
        if (!_type.compare("FW") || !_type.compare("Running FW")) {
            if (!ffv) {
                format = _isOldMinor ? "%d.%d.%04d" : "%d.%04d.%04d";
            } else {
                format = "%02d.%02d.%02d.%02d";
            }
        } else {
            format = _isSubBuild ? "%d.%d.%d.%04d" : "%d.%d.%04d";
        }
    }

    return prefix + _fwVer->get_fw_version(format);
}

int ImgVersion::compareFw(const ImgVersion &imv) const {
    if (_fwVer == NULL) {
        throw SetVersionException(NOT_SET);
    }
    if (!_fwVer->are_same_branch(*imv._fwVer)) {
        return UPDATE_ON_DIFFERENT_BRANCHES;
    }
    return _fwVer->compare(*imv._fwVer);
}
