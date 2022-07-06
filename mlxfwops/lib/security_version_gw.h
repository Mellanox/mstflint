/*
 * Copyright (C) Jan 2013 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2021 NVIDIA CORPORATION & AFFILIATES. All rights reserved.
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

#ifndef SECURITY_VERSION_GW_
#define SECURITY_VERSION_GW_

#include <mtcr.h>
#include "flint_base.h"

class SecurityVersionGW
{
public:
    SecurityVersionGW(mfile* mf, chip_type_t chip_type) : _mf(mf), _chip_type(chip_type){};
    ~SecurityVersionGW(){};

    bool isAccessibleInLiveFish();
    bool getSecurityVersion(u_int32_t* result);

private:
    mfile* _mf;
    chip_type_t _chip_type;
    u_int32_t static const GW_NOT_SUPPORTED = 0x0;
    typedef enum
    {
        ROLLBACK_PROTECTION,
        MINIMAL_VERSION
    } gw_type_t;

    u_int32_t _ctrl_address;
    u_int32_t _result1_address;
    u_int32_t _result2_address;

    u_int32_t static const CTRL_LOCK = 0x80000000;
    u_int32_t static const CTRL_RW = 0x40000000;
    u_int32_t static const CTRL_READ = CTRL_RW & 0xffffffff;
    u_int32_t static const CTRL_BUSY = 0x20000000;

    void getRollbackProtection(u_int32_t* result);
    void getMinimalSecurityVersion(u_int32_t* result);
    void setGWAddress(gw_type_t gw_type);

    void lock();
    void executeReadCommand();
    void waitForResult();
    void readResult1(u_int32_t* result);
    void readResult2(u_int32_t* result);
    void unlock();

    u_int32_t countSetBits(u_int32_t num);
};

#endif /*SECURITY_VERSION_GW_*/