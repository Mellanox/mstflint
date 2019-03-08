/*                  - Mellanox Confidential and Proprietary -
 *
 *  Copyright (C) 2019, Mellanox Technologies Ltd.  ALL RIGHTS RESERVED.
 *
 *  Except as specifically permitted herein, no portion of the information,
 *  including but not limited to object code and source code, may be reproduced,
 *  modified, distributed, republished or otherwise exploited in any form or by
 *  any means for any purpose without the prior written permission of Mellanox
 *  Technologies Ltd. Use of software subject to the terms and conditions
 *  detailed in the file "LICENSE.txt".
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

    const PldmPkgHdr & getPkgHeader() const { return packageHeader; }
    u_int8_t getDeviceIDRecordCount() const { return deviceIDRecordCount; }
    PldmDevIdRecord * getDeviceIDRecord(u_int8_t index) const {
        return deviceIDRecords[index];
    }
    u_int16_t getComponentImageCount() const { return componentImageCount; }
    PldmComponenetImage * getComponentImage(u_int16_t index) const {
        return componentImages[index];
    }
    u_int32_t getPackageHeaderChecksum() const { return packageHeaderChecksum;}
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

