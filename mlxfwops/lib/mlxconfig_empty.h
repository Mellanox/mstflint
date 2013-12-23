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
