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
 *
 */

#include "fw_version_with_sub_build.h"
#include <stdio.h>

FwVersionWithSubBuild::FwVersionWithSubBuild() :
        FwVersion() {
}

FwVersionWithSubBuild::FwVersionWithSubBuild(unsigned short int major,
        unsigned short int minor, unsigned short int subminor,
        const std::string& devBranchTag) :
        FwVersion(major, minor, subminor, devBranchTag) {

}

FwVersionWithSubBuild::~FwVersionWithSubBuild() {
}

std::string FwVersionWithSubBuild::get_master_version(const std::string& format,
        bool even_subminor) const {
    char buff[MAX_VERSION_LENGTH + 1] = { 0 };
    snprintf(buff, sizeof(buff), format.c_str(), _major, _minor,
            _subminor / 100,
            _subminor % 100 - (even_subminor ? _subminor % 2 : 0));
    return buff;
}

FwVersionWithSubBuild* FwVersionWithSubBuild::clone() const {
    return new FwVersionWithSubBuild(*this);
}
