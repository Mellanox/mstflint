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

ImgVersion::ImgVersion()
{
    _verNumFields = 0;
    _isExpansionRomUnkown = false;
    memset(_ver, 0, sizeof(_ver));
}

/*
   void ImgVersion::setExpansionRomtoUnknown()
   {
    _isExpansionRomUnkown = true;
   }

   bool ImgVersion::isExpansionRomUnknown()
   {
    return _isExpansionRomUnkown;
   }
 */


u_int16_t ImgVersion::getImgVerField(int index)
{
    return _ver[index];
}


const u_int16_t* ImgVersion::getVerArray()
{
    return _ver;
}


u_int8_t ImgVersion::getVerNumFields()
{
    return _verNumFields;
}


string ImgVersion::getTypeStr()
{
    return _type;
}


void ImgVersion::setVersion(const char *imgType, u_int8_t verSz, const u_int16_t *ver)
{
    _type = imgType;
    for (int i = 0; i < verSz; i++) {
        _ver[i] = ver[i];
    }
    _verNumFields = verSz;
}


string ImgVersion::getPrintableVersion(int ffv, bool show_type)
{
    string st;
    char buf[64];
    if (_type.size()) {
        if (!_type.compare("FW") || !_type.compare("Running FW")) {
            if (!ffv) {
                sprintf(buf, (_ver[1] > 99 ? "%s%d.%04d.%04d" : "%s%d.%d.%04d"), (show_type ? (_type + " ").c_str() : ""), _ver[0], _ver[1], _ver[2]);
            } else {
                sprintf(buf, "%s%02d.%02d.%02d.%02d", (show_type ? (_type + " ").c_str() : ""), _ver[0], _ver[1], _ver[2], _ver[3]);
            }
            st = buf;
        } else {
            if (show_type) {
                st = _type;
                st += " ";
            }
            for (int i = 0; i < _verNumFields; i++) {
                if (i > 0) {
                    st += '.';
                }
                if (i == (_verNumFields - 1) && (i != 0)) {
                    sprintf(buf, "%04d", _ver[i]);
                } else {
                    sprintf(buf, "%d", _ver[i]);
                }
                st += buf;
            }
        }
    }

    return st;
}


int ImgVersion::compare(const ImgVersion &imv) const
{
    int j;
    int versionFields = _verNumFields;

    if (_type.size() && !_type.compare("FW")) {
        return compareFw(imv);
    }

    for (j = 0; j < versionFields; j++) {
        if (_ver[j] != imv._ver[j]) {
            break;
        }
    }

    if (j < versionFields) {
        return (imv._ver[j] - _ver[j]);
    }

    return 0;
}


int ImgVersion::compareFw(const ImgVersion &imv) const
{
    int res;
    int versionFields = _verNumFields;
    u_int16_t thisFwVer[3] = {0};
    u_int16_t fwVer[3] = {0};
    memcpy(thisFwVer, _ver, sizeof(thisFwVer[0]) * 2);
    thisFwVer[2] = versionFields == 3 ? _ver[2] : _ver[2] * 100 + _ver[3];
    memcpy(fwVer, imv._ver, sizeof(fwVer[0]) * 2);
    fwVer[2] = versionFields == 3 ? imv._ver[2] : imv._ver[2] * 100 + imv._ver[3];
    res = FwOperations::FwVerLessThan(thisFwVer, fwVer);
    switch (res) {
    case FVI_SMALLER:
        return 1;

    case FVI_GREATER:
        return -1;

    case FVI_EQUAL:
        return 0;

    default:
        return -2;
    }
}
