/*
 * Copyright (c) 2020 Mellanox Technologies Ltd.  All rights reserved.
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
 * pldm_utils.h
 *
 *  Created on: Feb 27, 2019
 *      Author: Samer Deeb
 */

#ifndef _PLDM_PKG_H_
#define _PLDM_PKG_H_

#include <string>
#include <vector>
#include <map>

#include "pldm_buff.h"
#include "pldm_pkg_hdr.h"

class PldmDevIdRecord;
class PldmComponenetImage;

class PldmPkg {
public:
    PldmPkg();
    virtual ~PldmPkg();

    bool unpack(PldmBuffer & buff);
    void print(FILE * fp);

    const PldmComponenetImage * getImageByPsid(const std::string & psid) const;

    static const u_int8_t UUID[];

    u_int8_t getDeviceIDRecordCount() const { return deviceIDRecordCount; }
    PldmDevIdRecord * getDeviceIDRecord(u_int8_t index) const {
        return deviceIDRecords[index];
    }
    PldmComponenetImage * getComponentImage(u_int16_t index) const {
        return componentImages[index];
    }
    void getDeviceComponentImages(u_int8_t dev_index,
            std::vector<PldmComponenetImage *> images_list) const;

private:
    typedef std::map<std::string, int> PsidImageMap;
    PsidImageMap psidImageMap;

    PldmPkgHdr packageHeader;
    u_int8_t deviceIDRecordCount;
    std::vector<PldmDevIdRecord *> deviceIDRecords;
    u_int16_t componentImageCount;
    std::vector<PldmComponenetImage *> componentImages;
    u_int32_t packageHeaderChecksum;
};

#endif /* _PLDM_PKG_H_ */

