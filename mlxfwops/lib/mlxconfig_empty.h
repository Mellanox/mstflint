
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
 */


#ifndef MLXCONFIG_EMPTY_H
#define MLXCONFIG_EMPTY_H

// #include <string>
#include "flint_ops.h"

#define OLD_MLXCONFIG_VERSION 1
#define ERASE_CMD             "r"

class string
{
public:
    string();
    ~string();
    const char* c_str ( ) const {return (const char*)NULL;}
};

class MlxConfig
{
public:

    MlxConfig();
    ~MlxConfig();
    bool setNonFailSafeCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo); // For flint use pre-burn
    string getLastError() const;
    bool eraseCfg(Flash* flash, Operations* op, Operations::ImageInfo &flashImageInfo);
    bool checkExistProfileCompat(Flash* flash, Operations* op,
                                 Operations::ImageInfo &flashImageInfo,
                                 Operations::ImageInfo &newImageInfo,
                                 bool &compat); // For flint use
    bool isConfigPresent(Flash* flash, Operations* op,
                         Operations::ImageInfo &flashImageInfo,
                         bool &presents, u_int32_t &configVer); // For flint use
    bool reconfigureCfg(Flash* flash, Operations* op, Operations::ImageInfo &newImageInfo);  // For flint use post-burn

};

#endif // MLXCONFIG_EMPTY_H
